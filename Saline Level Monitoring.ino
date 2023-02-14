#include <Wire.h>
#include<Servo.h>
#include "HX711.h"
#define BLYNK_TEMPLATE_ID "TMPL70LGeCFd"
#define BLYNK_DEVICE_NAME "Saline level"
#define BLYNK_AUTH_TOKEN "YLgiB8f7N8Q-zizQoqPKybmP258OimlW"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial
#define BLYNK_MAX_SENDBYTES 256
#include "blynk.h"

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Mayur_Moto";
char pass[] = "4164afdc4854";

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;

Servo servo;
HX711 scale;
BlynkTimer timer;
void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  Blynk.begin(auth,ssid,pass);
  servo.attach(14);
}

void loop() {
Blynk.run();
timer.run();
  if (scale.is_ready()) {
    scale.set_scale(563.041);    
    long reading = scale.get_units(10);   
    Serial.print("Result: ");
    Serial.println(reading);
     Blynk.virtualWrite(V0,reading);
      if (reading <=176){
        Blynk.logEvent("trigger");
        servo.write(90);
                        }
  } 
  else {
    Serial.println("HX711 not found.");
  }
  
  delay(1000);
}
