/***************************************************** 
* ESP32 DHT Reading 
* DHT Input: ==> GPIO23.
* 讀取DHT11 溫濕度計，通過LoRa 模組發送出去。
* MJRoBot.org 9Sept17
*****************************************************/
//The HardwareSerial line assigns Serial to pins 16 and 17. ESP UART2
//UART1 is connect to Flash memory need patch Library
HardwareSerial Serial1(2);  //Tx2 Rx2 be Serial1
HardwareSerial& LoRaUART = Serial1; // LoRaUART = Serial1
/* DHT , Library Key Word= Adafruit Unified Sensor, DHT Sersor Library*/
#include "DHT.h"
#define DHTPIN 23     // what pin we're connected to GPIO23
#define DHTTYPE DHT11   // DHT 11 

#include <Wire.h>
#include "SSD1306.h" 
SSD1306  display(0x3c, 21, 22); // OLED use 21,22 pin
DHT dht(DHTPIN, DHTTYPE);
String sensorData;
const int DTX_LED_PIN = 5;
boolean ledState = false;

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Serial Ready");

  LoRaUART.begin(9600);
  LoRaUART.println("AT");
  //while (!LoRaUART.available()) {
  //  ;
  //}
  Serial.println("LoRa Serial Ready");
  dht.begin();
  pinMode(DTX_LED_PIN, OUTPUT);
  display.init();
  //display.flipScreenVertically();
  //display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Hello Go");
  display.display();
}

void loop()
{
  ledState = !ledState;
  digitalWrite(DTX_LED_PIN, ledState);
  delay(3 * 1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    display.clear();
    display.drawString(0, 0, "Failed to Read DHT");
    display.display();
    return;
  }

  sensorData = String(h, 2) + "/" + String(t, 2);
  Serial.println("value:"+sensorData);
  LoRaUART.println("AT+DTX=11,\"" + sensorData + "\"");
  display.clear(); 
  display.drawString(0,0,"Humi./Temp.");
  display.drawString(0, 15, sensorData);
  display.display();
}

