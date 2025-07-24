#define auth "TMPL6KDONIvc-"
#define BLYNK_TEMPLATE_NAME "Laser Fence"

#include <BlynkSimpleEsp8266.h>  

char auth[] = "";  

const int laserPin = D2;        
const int ldrPin = A0;          
const int buzzerPin = D8;       
const int threshold = 800;      

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, "Oppo A5s", "5432154321");  

  pinMode(laserPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  timer.setInterval(1000L, checkLaserFence);
}

void loop() {
  Blynk.run();
  timer.run();
}

void checkLaserFence() {
  int ldrValue = analogRead(ldrPin);
  Blynk.virtualWrite(V1, ldrValue);  // Update Value Display widget with LDR readings

  if (Blynk.connected()) {
    if (ldrValue > threshold && !digitalRead(laserPin)) {
      digitalWrite(buzzerPin, HIGH);
      Blynk.virtualWrite(V0, HIGH);
      Serial.println("Intruder detected!");
    } else {
      digitalWrite(buzzerPin, LOW);
      Blynk.virtualWrite(V0, LOW); 
    }
  }
}

BLYNK_WRITE(V0) {
  int laserStatus = param.asInt();
  digitalWrite(laserPin, laserStatus);
}
