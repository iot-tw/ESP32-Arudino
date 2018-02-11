//讀取 A0 的電壓資料，利用LoRa 發送出去。
//#include <SoftwareSerial.h>
//The HardwareSerial line assigns Serial to pins 16 and 17. ESP UART2
//UART1 is connect to Flash memory need patch Library
HardwareSerial Serial1(2);
// LoRaSerial Port Arduino Mega 2560 //Tx2,Rx2
HardwareSerial& LoRaUART = Serial1;
//SoftwareSerial LoRaUART(10, 11); // to TX, to RX
const int variable = 36;

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 17, 16);
  while (!Serial) {
    ; 
  }
  Serial.println("Serial Ready");

  LoRaUART.begin(9600);
  LoRaUART.println("at+echo=0");

  while (!LoRaUART.available()) {
    ;
  }
  Serial.println("LoRa Serial Ready");
}

void loop() {
  int sensorValue = analogRead(variable);
  String sensorData;
  sensorData = String(sensorValue);
  Serial.println(sensorData);
  LoRaUART.println("AT+DTX=" + String(sensorData.length()) + ",\"" + sensorData + "\"");

  delay(3*1000);
  if (LoRaUART.available()) {
    Serial.println(LoRaUART.readString());
  }
}
