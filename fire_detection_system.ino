#include <ESP8266WiFi.h>
#include <Grandeur.h>

// Grandeur credentials
const char* apiKey = "grandeurl7rt9rrt01hf0ljl71ed9aco";
const char* deviceID = "devicel7rtbn5b01hi0ljl6nrk2kig";
const char* token = "4e79b47b67adbd6fffa8c38b97ed90e64cad9d452f4b080b31586b1070feaa45";

Grandeur::Project project;
Grandeur::Project::Device device;

int mq2 = A0; // smoke sensor is connected to analog pin A0
int data = 0;
int buzzer = D1;

void getSMK(const char* code, int smk) 
{
  Serial.print("SMOKE: ");
  Serial.println(smk);
}

void connectWiFi(const char* ssid, const char* password) {
  Serial.print("Connecting to WiFi");
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
}

void setup() 
{
  Serial.begin(9600);
  connectWiFi("Ptcl Gpon Al quim", "pakistan123");
  
  project.begin(apiKey, deviceID, token);
  device = project.device(deviceID);
  
  pinMode(buzzer, OUTPUT);
}

void loop() 
{
  if (project.isConnected()) 
  {
    data = analogRead(mq2);
    device.data().set("smk", data, getSMK);
    
    if (data > 400)
    {
      tone(buzzer, 6000, 500);
      delay(400);
    }
    else
    {
      noTone(buzzer);
    }
  }

  delay(1000);
  project.loop();
}
