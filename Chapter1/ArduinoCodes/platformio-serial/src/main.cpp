#include <Arduino.h>
#include <HardwareSerial.h>

void setup(){
    Serial.begin(9600);
    while(!Serial);
    Serial.println("Inicializando");
}
void loop(){
    delay(2000);
    Serial.println("Executado");
}
