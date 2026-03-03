//set 1 if you are using Arduino Nano 33 BLE sense rev2
//Criando uma constante de pre-processador para usar a versao certa 
#define ARDUINO_ARDUINO_NANO33BLE_REV2 0

// Processador do C/C++
#if ARDUINO_ARDUINO_NANO33BLE_REV2 == 0
#include <Arduino_HTS221.h>
#define SENSOR HTS
#else
#include <Arduino.HS300x.h>
#define SENSOR HS300x
#endif
//logica esta no void setup a fim de testar somente uma vez o projeto 
void setup() { #
  Serial.begin(9600);
  while(!Serial); //aguardando a porta serial ficar pronta
  if(!SENSOR.begin()){
    Serial.println("Sensor falhou");
    while(1); //entra em loop infinito
  }
  Serial.print("Testando temperatura");
  Serial.print(SENSOR.readTemperature(), 2);
  Serial.println(" º C");
  Serial.print("Testando umidade = ");
  Serial.print(SENSOR.readHumidity(), 2);
  Serial.println(" %")

}

void loop() {
  // put your main code here, to run repeatedly:

}
