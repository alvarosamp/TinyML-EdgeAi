#include <mbed.h>

#if defined(ARDUINO_ARDUINO_NANO33BLE)
static const PinName gpio_pin_out = P0_23;
static const PinName gpio_pin_in  = P0_30;
#elif defined(ARDUINO_RASPBERRY_PI_PICO)
static const PinName gpio_pin_out = p22;
static const PinName gpio_pin_in  = p10;
#else
#error "Placa não suportada. Defina os pinos para sua placa."
#endif

static mbed::InterruptIn button(gpio_pin_in);
static mbed::DigitalOut led(gpio_pin_out);

void rise_ISR() {
  led = 0;
}

void fall_ISR() {
  led = 1;
}

void setup() {
  button.mode(PullUp);
  button.rise(&rise_ISR);
  button.fall(&fall_ISR);
}

void loop() {
  delay(4000);
}
