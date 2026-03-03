#include <DHT.h>

//definindo  a porta do arduino
const int gpio_pin_dht_pin = 10;
//Instanciando o objeto (construtor recebe (pino, tipo_do_sensor))
DHT dht (gpio_pin_dht_pin, DHT22);
//Pre-processador, toda vez que o compilador encontrar 'sensor' ele muda direto p dht 
#define sensor dht
void setup() {
  Serial.begin(9600);
  while(!Serial);
  SENSOR.begin();
  delay(2000);

  Serial.print("Test Temperature = ");
  Serial.print(SENSOR.readTemperature(), 2);
  Serial.println(" °C");
  Serial.print("Test Humidity = ");
  Serial.print(SENSOR.readHumidity(), 2);
  Serial.println(" %");
}

void loop() {
}
