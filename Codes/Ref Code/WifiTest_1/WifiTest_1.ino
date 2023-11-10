#include <ESP32Servo.h>



#define LED 13

#define LEDC_CHANNEL_0     1
// use 13 bit precission for LEDC timer
#define LEDC_TIMER_13_BIT  16

// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ     50






#include <WiFi.h>

const char* ssid     = "Indus Joister";
const char* password = "indus12345!";

WiFiServer server(80);

WiFiClient client;

Servo s1;
Servo s2;
Servo s3;
#define Servo_Pin1 23
#define Servo_Pin2 22
#define Servo_Pin3 16

void setup()
{
  s1.attach(Servo_Pin1);
  s2.attach(Servo_Pin2);
  s3.attach(Servo_Pin3);

  Serial.begin(115200);
  //  pinMode(LED, OUTPUT);      // set the LED pin mode

  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();

  client = server.available();   // listen for incoming clients

  //ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  // ledcAttachPin(LED, LEDC_CHANNEL_0);
}


void loop() {

  Serial.println(WiFi.localIP());
  client = server.available();   // listen for incoming clients


  if (client) {                             // if you get a client,
    Serial.println("New Client.");
    Serial.println(client);// print a message out the serial port

    while (client.connected()) {
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        char buff[10];
        itoa(100, buff, 10);

        if (c == 'a') {
          // digitalWrite(LED, HIGH);
          /*  for(int i=1000;i<8192;i=i+100)
            {
             ledcWrite(LEDC_CHANNEL_0, i);
             delay(10);
            }*/
          //   ledcWrite(LEDC_CHANNEL_0, 1500);

          s1.write(0);
          s2.write(0);
          s3.write(0);
          client.write("Tinkrz");
        }
        if (c == 'b') {
          //ledcWrite(LEDC_CHANNEL_0, 100);
          /*   for(int i=0;i<8192;i=i+10)
            {
            ledcWrite(LEDC_CHANNEL_0, i);
            delay(10);
            }*/
          s1.write(45);
          s2.write(45);
          s3.write(45);
          //ledcWrite(LEDC_CHANNEL_0, 2000);
          client.write(buff);
          // digitalWrite(LED, LOW);
        }
        if (c == 'c') {

          s1.write(90);
          s2.write(90);
          s3.write(90);

          //  ledcWrite(LEDC_CHANNEL_0, 3000);
          // digitalWrite(LED, LOW);
        }
        if (c == 'd') {
          s1.write(135);
          s2.write(135);
          s3.write(135);

          // ledcWrite(LEDC_CHANNEL_0, 4000);
          // digitalWrite(LED, LOW);
        }
        if (c == 'e') {
          s1.write(150);

          s2.write(150);
          s3.write(150);
          //ledcWrite(LEDC_CHANNEL_0, 6000);
          // digitalWrite(LED, LOW);
        }
        if (c == 'f') {
          s1.write(180);
          s2.write(180);
          s3.write(180);
          // ledcWrite(LEDC_CHANNEL_0,8000);
          // digitalWrite(LED, LOW);
        }
        // ledcWrite(LEDC_CHANNEL_0, d);
        // digitalWrite(LED, LOW);
      }
    }
  }
}
