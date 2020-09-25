#include <ESP8266WiFi.h>
#include <WiFiServer.h>

#define pin D0

const char* ssid = "wifi_ssid";
const char* password = "wifi_password";

const int port = 8626;

char message[5];
int current = 0;

int timing = 0;
bool getPressed = false;
bool dataSend = true;

WiFiServer server(port);

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("...");
  }
   
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
  pinMode(pin, INPUT);
  
  server.begin();
}

// the loop function runs over and over again forever
void loop() {
    WiFiClient wifiClient = server.available();
    if (wifiClient) {
      Serial.println("Client connected");
      while (wifiClient.connected()) {
        if (!wifiClient.available()) {
        if ((millis() - timing > 900 && !dataSend) || current > 4){
          Serial.println("Sending data...");
          char arr[current];
          for (int i = 0; i < current; i++) {
            arr[i] = message[i];
          }
          Serial.println(arr);
          wifiClient.print(arr);
          dataSend = true;
          current = 0;
        }
        int pushRead = digitalRead(pin);
        if (pushRead == HIGH && !getPressed){
           timing = millis();
           getPressed = true;
           
        } else if (pushRead == LOW && getPressed) {
          float t = millis();
          timing = t - timing;
          if(timing < 200){
            Serial.print('.');
            message[current] = '.';
          }else{
            Serial.print('-');
            message[current] = '-';
          }
          ++current;
          timing = t;
          getPressed = false;
          dataSend = false;
          delay(100);
        }

       } else {
        Serial.println("Client not available");
       }
      }
    } else {
      Serial.println("No client connected");
      delay(1000);
    }
}