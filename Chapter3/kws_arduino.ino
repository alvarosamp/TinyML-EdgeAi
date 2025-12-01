// If your target is limited in memory, you can define this macro to reduce the size of
#define EIDSP_QUANTIZE_FILTERBANK 0

//Define the number of slices per model window. A model window of 1000 ms.
//with slices per model window set to 4. Results in slice size of 250ms.

#define EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW  4

// If you run into tflite arena location issue
// This may be due to may dynamic memory fragmentation
//Try define "-DIE_CLASSIFIER_ALLOCATION_STATIC" in boards.local.txt(create if it doens wxists)
//If the problem persists then there not enought memory for this model and application

#include "mbed.h"
#include <PDM.h>
#include <voice_controlling_led_inferencing.h>





//Audio buffers, pointers and selectors
typedef struct{
    signed short *buffers[2];
    unsigned char buf_select;
    unsigned char buf_ready;
    unsigned int buf_count;
    unsigned int n_samples;
}inference_t;

static inference_t inference;
static bool record_ready = false;
static signed short *samplebuffer;
static bool debug_nn = false; // Set this to trueto see debug info from NN
static int print_results = -{EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW}; // Used to print results every n inferences

static mbed::DigitalOut rgb[] = {p24, p16, p6};
static constexpr ON = 0 ;
static constexpr OFF =1;

static constexpr int RED = 0;
static constexpr int GREEN = 1;
static constexpr int BLUE = 2;
static size_t current_collor = RED;

static constexpr size_t NUM_COLORS = 3;

static bool is_color(size_t ix){
    return ix < NUM_COLORS;
}
static bool is_unknown(size_t ix){
    return ix == (EI_CLASSIFIER_LABEL_COUNT - 1);
}

void setup(){
    Serial.begin(115200);
    while(!Serial);
    Serial.println("Starting inference");
    // Setup RGB LED
    rgb[RED] = OFF;
    rgb[GREEN] = OFF;
    rgb[BLUE] = OFF;
    rgb[current_collor] = ON;
    //summary inference settings(from model_metadata.h)
    ei_printf("Inferencing settings:\n");
    ei_printf("\tInterval: %.2f ms.\n", (float)EI_CLASSIFIER_INTERVAL_MS);
    ei_printf("\tFrame size: %d\n", EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE);
    ei_printf("\tSample length: %d ms.\n", EI_CLASSIFIER_RAW_SAMPLE_COUNT / 16);
    ei_printf("\tNo. of classes: %d\n", sizeof(ei_classifier_inferencing_categories) /
                                                sizeof(ei_classifier_inferencing_categories[0]));

    run_classifier_init();//initialize the classifier
    if(microphone_inference_start(EI_CLASSIFIER_SLICE_SIZE) != 0){
        ei_printf("Failed to setup audio sampling\r\n");
        return;
    }
}
void loop(){
    bool m = microphone_inference_record();
    if(!m){
        ei_printf("ERR: Failed to record audio");
        return;
    }
    signal_t signal;
    signal.total_lenght = EI_CLASSIFIER_RAW_SAMPLE_COUNT;
    signal.get_data = &microphone_inference_get_data;
    ei_impulse_result_t result = {0};
    EI_IMPULSE_ERROR res = run_classifier(&signal, &result, debug_nn, false);
    if(res != EI_IMPULSE_OK){
        ei_printf("ERR: Failed to run classifier (%d)\n", res);
        return;
    }
    size_t ix =0;
    size_t ix_max = 0;
    float pb_ma = 0.0;
    for(ix; ix< EI_CLASSIFIER_LABEL_COUNT; ix++){
        if(result.classification[ix].value > pb_ma){
            ix_max = ix;
            pb_ma = result.classification[ix].value;
        }
    }
    #define PROBABILITY_THR 0.5
    if(pb_max > PROBABILITY_THR && !is_unknown(ix_max)) {
        record_ready = false;
        if(is_color(ix_max)) {
            size_t new_color = ix_max;
            if(new_color != current_color) {
                rgb[current_color] = OFF;
                rgb[new_color] = ON;
                current_color = new_color;
            }   
        }
    }
    else{
        size_t num_blinks = ix_max = 2;
        for(size_t i=0; i < num_blinks; i++){
            rgb[current_color] = OFF;
            wait_ms(200);
            rgb[current_color] = ON;
            wait_ms(200);
        }
    }
    delay(1000);
    infrence.buf_select = 0;
    inference.buf_count = 0;
    inference.buf_ready = 0;
    record_ready = true;
}

static void pdm_data_handler(uint32_t n_samples){
    inferece.buffers[0] = (signal short *)malloc(n_samples * sizeof(signed short));
    if(inference.buffers[0] == NULL){
        return false;
    }
    inference.buffers[1] = (signed short *)malloc(n_samples * sizeof(signed short));
    if(inference.buffers[1] == NULL){
        free(inference.buffers[0]);
        return false;
    }
    sampleBuffer = (signed short *)malloc((n_samples >> 1) *sizeof(signed short));
    if(sampleBuffer == NULL){
        free(inference.buffers[0]);
        free(inference.buffers[1]);
        return false;
    }
    infrence.buf_select = 0;
    inference.buf_count = 0;
    inference.buf_ready = 0;
    inference.n_samples = n_samples ;

    //Configure the data receive callback
    PDM.onReceive(&pdm_data_ready_inferece_callback);
    PDM.setBufferSize((n_samples >> 1) * sizeof(signed short));
    //Initialize PDm
    // - one channel (mono mode)
    // a 16kHz sample rate
    if(!PDM.begin(1, EI_CLASSIFIER_FREQUENCY)){
        ei_printf('Failed to start PDM');
    }
    //set the gain, defaults to 20
    PDM.setGain(127);
    record_ready = 1;
    return true;
}
    /**
     * @brief PDM data ready callback
     * @return True when finished
     */
static bool microphone_inference_record(void){
    bool ret = true;
  if(inference.buf_ready == 1) {
    ei_printf(
      "Error sample buffer overrun. Decrease the number of slices per model window "
      "(EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW)\n");
      ret = false;
  }
  while(inference.buf_ready ==0){
    //wait for buffer to be ready
    delay(1);
  }
  infrence.buf_ready = 0;
  return ret;
}
// Get raw audio signal data

static int microphone_audio_signal_get_data(size_t offset, size_t lenght, float **out_ptr){
    numpy::int16_to_float(&inference.buffers[inference.buf_select][offset], out_ptr, lenght);
    return 0;
}
//@brief Stop PDM and release buffer
static void microphone_inference_end(void){
    PDM.end();
    free(inference.buffers[0]);
    free(inference.buffers[1]);
    free(sampleBuffer);
}

// PDM data ready callback
#if !defined(EI_CLASSIFIER_ALLOCATION_SENSOR) || EI_CLASSIFIER_SENSOR != EI_CLASSIFIER_SENSOR_MICROPHONE
#error "Invalid model for current sensor."
#endif


