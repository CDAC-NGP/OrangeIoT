#include <ESP32Servo.h>
//#include <analogWrite.h>
//#include <tone.h>
//#include <ESP32Tone.h>
//#include <ESP32PWM.h>

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

//#include <Servo.h>

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>


//For RFID
#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
//#include <MFRC522DriverI2C.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>

#define USE_SERIAL Serial
WiFiMulti wifiMulti;

const char* allData_Digital_Out_1 = " ";
const char* allData_Digital_Out_2 = " ";
const char* allData_Servo_1 = " ";
const char* allData_Servo_2 = " ";

StaticJsonDocument<192> doc;

Servo s1;
Servo s2;

#define onBoardLED 2

#define dIn1 15
#define dIn2 15

#define dOut1 12
#define dOut2 13

#define aIn1 36
#define aIn2 39

#define Servo1 32
#define Servo2 33

#define aOut1
#define aOut2



//Control Function's Prototypes
//Output
void ServoControl(String, String);
void DigitalActuation(int, String);

//Input
int DigitalSensorRead(int);
int AnalogSensorRead(int);
void ReadRFID(void);

void ledFailSignal(void);
void ledSuccessSignal(void);
//----------------------------------------

MFRC522DriverPinSimple ss_pin(5);  // Configurable, see typical pin layout above.

MFRC522DriverSPI driver{ ss_pin };  // Create SPI driver.

MFRC522 mfrc522{ driver };  // Create MFRC522 instance.

//String IP = "192.168.1.6:5000"; //home
//String IP = "192.168.29.229:5000"; //CDAC
//String IP = "192.168.69.245:5000";  //Abhishek Mob.
 //String IP = "192.168.48.245:5000";  //Abhishek Mob. 2
String IP = "angolepython.pythonanywhere.com";  //Abhishek Mob. 2
String Mode = "senData";
String nodeId = "o101";

void setup() {

  // Pin Initialization

  pinMode(onBoardLED, OUTPUT);

  pinMode(dOut1, OUTPUT);
  pinMode(dOut2, OUTPUT);

  pinMode(dIn1, INPUT);
  pinMode(dIn2, INPUT);

  pinMode(aIn1, INPUT);
  pinMode(aIn2, INPUT);

  s1.attach(Servo1);
  s2.attach(Servo2);
  //-------------------------------------------------------

  USE_SERIAL.begin(115200);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();
  s1.write(0);
  s2.write(0);
  digitalWrite(dOut1,LOW);
  digitalWrite(dOut2,LOW);

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }


  wifiMulti.addAP("Abhi", "00123456789900");
  //  wifiMulti.addAP("SPIPL-CDAC-4G", "SpiplCdac^&*");
  // wifiMulti.addAP("Airtel_abhi_9422", "air47559");

  mfrc522.PCD_Init();
}

//192.168.1.6:5000/senData?id=o102

String URL_Prefix = "http://" + IP + "/" + Mode + "?id=" + nodeId + "&";
String RFID_Data = "Blank";
String RFID_DataTemp = "Blank";
String URL_Suffix = "&a1=150&a2=1020&di2=1";
String URL = URL_Prefix + "rfd=" + RFID_Data + URL_Suffix + "&di1=1";

void loop() {

  int digitalSensorvalue;
  char buffer[20];
  // wait for WiFi connection
  if ((wifiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;



    //http://192.168.1.6:5000/senData?id=o102&rfd=202303&a1=150&a2=1020&di1=1&di2=1
    http.begin(URL);  //HTTP


    // RFID_DataTemp = RFID_Data;

    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        USE_SERIAL.println(payload);

        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
          Serial.print("deserializeJson() failed: ");
          Serial.println(error.c_str());
          return;
        }

        JsonObject allData = doc["allData"];

        allData_Digital_Out_1 = allData["Digital Out 1"];
        DigitalActuation(dOut1, allData_Digital_Out_1);
        //USE_SERIAL.println(allData_Digital_Out_1);

        allData_Digital_Out_2 = allData["Digital Out 2"];  // "High"
        DigitalActuation(dOut2, allData_Digital_Out_2);

        allData_Servo_1 = allData["Servo 1"];  // "180"
        ServoControl("Servo 1", allData_Servo_1);

        allData_Servo_2 = allData["Servo 2"];  // "180"
        ServoControl("Servo 2", allData_Servo_2);

        ReadRFID();

        digitalSensorvalue = DigitalSensorRead(dIn1);


        URL = URL_Prefix + "rfd=" + RFID_Data + "&di1=" + itoa(digitalSensorvalue, buffer, 10) + URL_Suffix;

        // if (strcmp(allData_Digital_Out_1, "1") == 0) {
        //   digitalWrite(2, HIGH);
        //   USE_SERIAL.println("Hello");
        // }

        // else digitalWrite(2, LOW);
      }
    } else {
      //ledFailSignal();
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(1000);
}


void DigitalActuation(int pin, String state) {
  
  digitalWrite(pin, state.toInt());
}

void ServoControl(String pin, String key) {

  if (pin == "Servo 1") {
    if(key=="Done"){
    
    //s1.write(angle.toInt());
    for(uint8_t n=0;n<3;n++) {
    digitalWrite(dOut1,HIGH);
    delay(2000);
    digitalWrite(dOut1,LOW);
    delay(2000);
    }
    s1.write(90);
    delay(6000);
    s1.write(0);
    Serial.println(key);
    }
    else{s1.write(0);}
  } else if (pin == "Servo 2") {
    s2.write(key.toInt());
  }
}

void ReadRFID() {

 // for (uint8_t f = 0; f < 3; f++) {
    if (mfrc522.PICC_IsNewCardPresent()) {
      RFID_Data = "";

      for (byte i = 0; i < mfrc522.uid.size; i++) {
        //Serial.print(mfrc522.uid.uidByte[i], HEX);
        RFID_Data += String(mfrc522.uid.uidByte[i], HEX);
      }
     // delay(300);
    }
 // }
  RFID_Data.replace(" ", "");
  USE_SERIAL.println(RFID_Data);
  //return;


  // Select one of the cards.
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called.
  //MFRC522Debug::PICC_DumpToSerial(mfrc522, Serial, &(mfrc522.uid));

  // for (byte i = 0; i < mfrc522.uid.size; i++) {
  //   //Serial.print(mfrc522.uid.uidByte[i], HEX);
  //   RFID_Data += String(mfrc522.uid.uidByte[i], HEX);
  // }

  // if(RFID_DataTemp != RFID_Data) {

  //       RFID_DataTemp=RFID_Data;
  //     }
  // RFID_Data.replace(" ","");
  // USE_SERIAL.println(RFID_Data );

  // MFRC522Debug::PrintUID(Serial, mfrc522.uid);
  // Serial.println();
}

int DigitalSensorRead(int pin) {
  int sensorValue;

  sensorValue = digitalRead(pin);

  // if (sensorValue == 1) {
  //  // RFID_Data = "00 AA 22 FF";
  //   RFID_Data.replace(" ","");
  // }
  // else  {
  //   RFID_Data = "11 BB 33 EE";
  //   RFID_Data.replace(" ","");
  // }


  return sensorValue;
}

void ledFailSignal() {
  for (uint8_t i = 0; i < 4; i++) {
    digitalWrite(2, HIGH);
    delay(200);
    digitalWrite(2, LOW);
    delay(200);
  }
}

void ledSuccessSignal() {
  for (uint8_t i = 0; i < 2; i++) {
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
  }
}