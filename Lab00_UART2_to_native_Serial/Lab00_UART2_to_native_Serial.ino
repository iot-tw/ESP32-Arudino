if defined(ESP32)
//The HardwareSerial line assigns Serial to pins 16 and 17. ESP UART2
//UART1 is connect to Flash memory need patch Library
HardwareSerial Serial1(2);
#endif

void setup() {
  Serial.begin(115200);
  while (!Serial){
    ;
  }
  Serial.println("Hardware Serial Ready");
  // set the baud rate for the Serial1 port
  Serial1.begin(9600);      // default GIoT LoRa Module baud
  Serial1.println("AT+SGMD?");
}
     
void loop() {
  if (Serial.available()) {
    Serial1.write(Serial.read());
  }
  if (Serial1.available()) {
    Serial.write(Serial1.read());
  }
}
