// Se estiver usando o nano ble sense rev 2, set para 1
#define ARDUINO_ARDUINO_NANO33BLE_REV2 0
#if ARDUINO_ARDUINO_NANO33BLE_REV2 == 0
#include <Arduino_HTS221.h>
#define SENSOR HTS

#else
#include <Arduino_HS300x.h>
#define SENSOR HS300x
#endif

void_setup(){
    Serial.begin(9600);
    while(!Serial);
    if(!SENSOR.begin()){
        Serial.println("Falha na inicializacao do sensor!");
        while(1);
    }
    Serial.print("Temperatura de Teste = ");
    Serial.print(SENSOR.readTemperature(),2);
    Serial.println(" °C");
    Serial.print("Umidade de Teste = ");
    Serial.print(SENSOR.readHumidity(),2);
    Serial.println(" %");

}
void_loop(){
}