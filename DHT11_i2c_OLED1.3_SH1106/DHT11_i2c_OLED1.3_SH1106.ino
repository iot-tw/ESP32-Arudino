#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
// Sh1106 Library https://github.com/nhatuan84/esp32-sh1106-oled/archive/master.zip
// 1.3" 
#include <Adafruit_SH1106.h>

#define OLED_SDA 21
#define OLED_SCL 22

Adafruit_SH1106 display(OLED_SDA, OLED_SCL);

//The HardwareSerial line assigns Serial to pins 16 and 17. ESP UART2
//UART1 is connect to Flash memory need patch Library
HardwareSerial Serial1(2);  //Tx2 Rx2 be Serial1
HardwareSerial& LoRaUART = Serial1; // LoRaUART = Serial1
/* DHT , Library Key Word= Adafruit Unified Sensor, DHT Sersor Library*/
#include "DHT.h"
#define DHTPIN 23     // what pin we're connected to GPIO23
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);
String sensorData;
const int DTX_LED_PIN = 5;
boolean ledState = false;

void setup()   {                
  Serial.begin(115200);
  /* initialize OLED with I2C address 0x3C */
  display.begin(SH1106_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay();
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
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Ready, Go!");
  display.display();
  delay(2000);
}
void loop() { 
  /* set text size, color, cursor position, 
  set buffer with  Hello world and show off*/
 
  ledState = !ledState;
  digitalWrite(DTX_LED_PIN, ledState);
  delay(3 * 1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Failed to read from DHT sensor!");
    display.display();
    return;
  }

  sensorData = String(h, 2) + "/" + String(t, 2);
  Serial.println("value:"+sensorData);
  LoRaUART.println("AT+DTX=11,\"" + sensorData + "\"");
  display.clearDisplay(); 
  display.setCursor(0,0);
  display.println("Humi./Temp.");
  display.setCursor(0,10);
  display.println(sensorData);
  display.display();
}
