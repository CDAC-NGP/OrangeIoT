#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#define USE_SERIAL Serial
WiFiMulti wifiMulti;

const char* allData_Digital_Out_1 = " ";
const char* allData_Digital_Out_2 = " ";
const char* allData_Servo_1 = " ";
const char* allData_Servo_2 = " ";

StaticJsonDocument<192> doc;


void setup() {

    pinMode(2,OUTPUT);

    USE_SERIAL.begin(115200);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
       
   // wifiMulti.addAP("SPIPL-CDAC-4G", "SpiplCdac^&*");
    wifiMulti.addAP("Airtel_abhi_9422", "air47559");
    

}

void loop() {
    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        //USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        http.begin("http://192.168.1.6:5000/senData?id=o102&rfd=202303&a1=150&a2=1020&di1=1&di2=1"); //HTTP

        //USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);                

                DeserializationError error = deserializeJson(doc, payload);

                  if (error) {
                    Serial.print("deserializeJson() failed: ");
                    Serial.println(error.c_str());
                    return;
                  }

                  JsonObject allData = doc["allData"];  
                  allData_Digital_Out_1 = allData["Digital Out 1"];  USE_SERIAL.println(allData_Digital_Out_1);
                  allData_Digital_Out_2 = allData["Digital Out 2"]; // "High"
                  allData_Servo_1 = allData["Servo 1"]; // "180"
                  allData_Servo_2 = allData["Servo 2"]; // "180"

                  if(strcmp(allData_Digital_Out_1,"1")==0){
                    digitalWrite(2,HIGH);
                    USE_SERIAL.println("Hello");
                  }
                  
                  else digitalWrite(2,LOW); 
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(5000);
}
