/***************************************************** 
* ESP32 DHT Reading 
* DHT Input: ==> GPIO23.
* 讀取DHT11 溫濕度計，通過LoRa 模組發送出去。
* MJRoBot.org 9Sept17
*****************************************************/
//The HardwareSerial line assigns Serial to pins 16 and 17. ESP UART2
//UART1 is connect to Flash memory need patch Library
HardwareSerial Serial1(2);
HardwareSerial& LoRaUART = Serial1;
/* DHT */
#include "DHT.h"
#define DHTPIN 23     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);
String sensorData;
const int DTX_LED_PIN = 13;
boolean ledState = false;

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Serial Ready");

  LoRaUART.begin(9600);
  LoRaUART.println("AT");
  while (!LoRaUART.available()) {
    ;
  }
  Serial.println("LoRa Serial Ready");
  dht.begin();
  pinMode(DTX_LED_PIN, OUTPUT);
}

void loop()
{
  ledState = !ledState;
  digitalWrite(DTX_LED_PIN, ledState);
  delay(5 * 1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  sensorData = String(h, 2) + "/" + String(t, 2);
  Serial.println("value:"+sensorData);
  LoRaUART.println("AT+DTX=11,\"" + sensorData + "\"");
}

