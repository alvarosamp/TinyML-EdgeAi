#include <Arduino.h>
#include <mbed.h>
// Mbed: Biblioteca para manipulação de hardware de baixo nível, como GPIO

#if defined(ARDUINO_ARDUINO_NANO33BLE)
static const PinName LED = P0_23; // Pino do LED para Nano 33 BLE
static const PinName ENTRADA = P0_30; // Pino de entrada para Nano 33 BLE
#elif defined(ARDUINO_RASPBERRY_PI_PICO)
static const PinName LED = p22; // Pino do LED para Raspberry Pi Pico
static const PinName ENTRADA = p10; // Pino de entrada para Raspberry Pi Pico
#else
#error "Placa não suportada. Defina os pinos para sua placa."
#endif

static mbed::DigitalOut LedPin(LED); // Objeto DigitalOut para o LED
static mbed::DigitalIn EntradaPin(ENTRADA); // Objeto DigitalIn para a entrada

void setup() {
    EntradaPin.mode(PullUp); // Configura o pino de entrada com resistor pull-up
}

void loop() {
    LedPin = !LedPin; // Alterna o estado do LED
    delay(1000); // Aguarda 1 segundo
}
