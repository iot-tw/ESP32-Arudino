#doit ESP32 DEV board LED is GPIO 2
#Ai-thinker ESP32 LED is GPIO 5
#define LED_PIN 2
void setup(){
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);  // setup LED PIN 13 輸出
  Serial.print("Welcome to Arduino!");
}
void loop(){
  char d;
  while(Serial.available()){
    d = Serial.read();
    Serial.print(d);
    if(d == '0'){          // 熄滅
      Serial.println("Turn OFF LED");
      digitalWrite(LED_PIN, LOW);
    }
    else if(d == '1'){     // 點亮
      digitalWrite(LED_PIN, HIGH);
        Serial.println("Turn ON LED");
    }
  }
}

