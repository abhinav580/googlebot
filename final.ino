
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "manthan"
#define WLAN_PASS       "believer"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "Abhinav580"
#define AIO_KEY         "02e7674145b34e34b5802c71851a6e9b"

/************ Global State (you don't need to change this!) ******************/
String i;

WiFiClient client;
WiFiServer server(80);
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/vehicle");


void MQTT_connect();

void setup() {
  Serial.begin(115200);
  delay(10);
  i = "";
pinMode(D5 ,OUTPUT);
pinMode(D0,OUTPUT);
pinMode(D1,OUTPUT);
pinMode(D2,OUTPUT);
pinMode(D3,OUTPUT);
digitalWrite(D0,LOW);
digitalWrite(D1,LOW);
digitalWrite(D2,LOW);
digitalWrite(D3,LOW);
digitalWrite(D5,LOW);
  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
server.begin();
  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffbutton);
}

uint32_t x=0;

void loop() {






  
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(500))) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton.lastread);
      uint16_t readvoice = atoi((char *)onoffbutton.lastread);

  if(readvoice == 1 )
  {
    digitalWrite(D0, HIGH);
    digitalWrite (D1, LOW);
    digitalWrite(D2,HIGH);
    digitalWrite(D3,LOW);
    delay(100);
  }

  else if(readvoice == 5)
  {
    digitalWrite(D0, LOW);
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
    digitalWrite(D3,HIGH);
    delay(100);
  }

  else if (readvoice == 3)
  {
    digitalWrite (D0,LOW);
    digitalWrite (D1,LOW);
    digitalWrite (D2,HIGH);
    digitalWrite (D3,LOW);
   delay (800);
      digitalWrite(D0, HIGH);
    digitalWrite (D1, LOW);
    digitalWrite(D2,HIGH);
    digitalWrite(D3,LOW);
    delay(100);
  
  }

 else if ( readvoice == 4)
 {
   digitalWrite (D0, HIGH);
   digitalWrite (D1,LOW );
   digitalWrite (D2, LOW);
   digitalWrite (D3, LOW);
   delay (800);
      digitalWrite(D0, HIGH);
    digitalWrite (D1, LOW);
    digitalWrite(D2,HIGH);
    digitalWrite(D3,LOW);
    delay(100);
 }

 else if (readvoice == 2)
 {
   digitalWrite (D0, LOW);
   digitalWrite (D1, LOW);
   digitalWrite (D2, LOW);
   digitalWrite (D3, LOW);
   delay (100);
 }
 else if (readvoice == 6)
 {
   digitalWrite (D0, HIGH);
   digitalWrite (D1, LOW);
   digitalWrite (D2, LOW);
   digitalWrite (D3, LOW);
   delay (100);
 }

else if(readvoice == 7)
digitalWrite(D5,HIGH);
else if(readvoice == 8)
digitalWrite(D5,LOW);





     
    }
  }


  WiFiClient client = server.available();
 if (!client) { return; }
    while(!client.available()){  delay(1); }
   i = (client.readStringUntil('\r'));
    i.remove(0, 5);
    i.remove(i.length()-9,9);
    if (i == "forward") {
      digitalWrite(16,HIGH);
      digitalWrite(5,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(0,LOW);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("forward");
      client.println("</html>");
      client.stop();
      delay(1);

    }
    if (i == "reverse") {
      digitalWrite(16,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(4,LOW);
      digitalWrite(0,HIGH);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("reverse");
      client.println("</html>");
      client.stop();
      delay(1);

    }
    if (i == "right") {
      digitalWrite(16,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(0,LOW);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("right");
      client.println("</html>");
      client.stop();
      delay(1);

    }
    if (i == "left") {
      digitalWrite(16,HIGH);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(0,LOW);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("left");
      client.println("</html>");
      client.stop();
      delay(1);

    }
    if (i == "stop") {
      digitalWrite(16,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(0,LOW);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("stop");
      client.println("</html>");
      client.stop(); }








}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
