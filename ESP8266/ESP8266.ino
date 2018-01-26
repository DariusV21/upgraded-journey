// Libraries
//#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Wire.h>
//#include "SSD1306.h"

#include <PacketSerial.h>

#define CONNECTED_TO_PC false

// Pins
//#define SDA 14
//#define SCL 12
//#define I2C 0x3D

// Create display
//SSD1306 display(I2C, SDA, SCL);

//// WiFi settings
//const char* ssid     = "is-1";
//const char* password = "helloworld";
//
//// API server
//const char* host = "api.coindesk.com";
//


PacketSerial serial_Price;
PacketSerial serial_Time;
PacketSerial myCombinedSerial;


typedef union {
 float number ;
 uint8_t bytes[4];
} FLOATUNION_t;

FLOATUNION_t myFloat;

  uint8_t packet00 = 0;
  uint8_t packet01 = 0;
  uint8_t packet10 = 0;

void setup() {

  // Serial
  //Serial.begin(115200);
//  delay(10);

  myCombinedSerial.begin(115200);
  //serial_Price.begin(9600);
//  serial_Price.setPacketHandler(&onPacketReceived);

  //serial_Time.begin(115200);
//  serial_Time.setPacketHandler(&onPacketReceived);

  delay(100);
  // Initialize display
  //  display.init();
  //  display.flipScreenVertically();
  //  display.clear();
  //  display.display();
//
//  // We start by connecting to a WiFi network
//  if (CONNECTED_TO_PC) {
//    Serial.println();
//    Serial.println();
//    Serial.print("Connecting to ");
//    Serial.println(ssid);
//  }
//  WiFi.begin(ssid, password);
//
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//
//    if (CONNECTED_TO_PC) Serial.print(".");
//  }
//
//  if (CONNECTED_TO_PC) {
//    Serial.println("");
//    Serial.println("WiFi connected");
//    Serial.println("IP address: ");
//    Serial.println(WiFi.localIP());
//  }
//
//
//
//  
}

void loop() {

//  // Connect to API
//  if (CONNECTED_TO_PC) Serial.print("connecting to ");
//  if (CONNECTED_TO_PC) Serial.println(host);
//
//  // Use WiFiClient class to create TCP connections
//  WiFiClient client;
//  const int httpPort = 80;
//  if (!client.connect(host, httpPort)) {
//    if (CONNECTED_TO_PC) Serial.println("connection failed");
//    return;
//  }
//
//  // We now create a URI for the request
//  String url = "/v1/bpi/currentprice.json";
//  String historical_URL = "/v1/bpi/historical/close.json?for=yesterday";
//
//  if (CONNECTED_TO_PC) Serial.print("Requesting URL: ");
//  if (CONNECTED_TO_PC) Serial.println(url);
//
//  // This will send the request to the server
//  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "Connection: close\r\n\r\n");
//  delay(100);
//
//  // Read all the lines of the reply from server and print them to Serial
//  String answer;
//  while (client.available()) {
//    String line = client.readStringUntil('\r');
//    answer += line;
//  }
//
//
//  client.stop();
//  if (CONNECTED_TO_PC) Serial.println();
//  if (CONNECTED_TO_PC) Serial.println("closing connection");
//
//
//  ////////////// YESTERDAY
//
//  // Connect to API
//  if (CONNECTED_TO_PC) Serial.print("connecting to ");
//  if (CONNECTED_TO_PC) Serial.println(host);
//
//  // Use WiFiClient class to create TCP connections
//  WiFiClient client1;
//  //const int httpPort = 80;
//  if (!client1.connect(host, httpPort)) {
//    if (CONNECTED_TO_PC) Serial.println("connection failed");
//    return;
//  }
//
//
//  // This will send the request to the server ABOUT YESTERDAYS PRICE
//  client1.print(String("GET ") + historical_URL + " HTTP/1.1\r\n" +
//                "Host: " + host + "\r\n" +
//                "Connection: close\r\n\r\n");
//  delay(100);
//
//  // Read all the lines of the reply from server and print them to Serial
//  String yesterday_answer;
//  while (client1.available()) {
//    String yesterday_line = client1.readStringUntil('\r');
//    yesterday_answer += yesterday_line;
//  }
//
//  client1.stop();
//  if (CONNECTED_TO_PC) Serial.println();
//  if (CONNECTED_TO_PC) Serial.println("closing connection");
//
//  // Process answer
//  if (CONNECTED_TO_PC) Serial.println();
//  if (CONNECTED_TO_PC) Serial.println("Answer: ");
//  if (CONNECTED_TO_PC) Serial.println(answer);
//
//  // Process answer
//  if (CONNECTED_TO_PC) Serial.println();
//  if (CONNECTED_TO_PC) Serial.println("Yesterday answer: ");
//  if (CONNECTED_TO_PC) Serial.println(yesterday_answer);
//
//  // Convert to JSON
//  String jsonAnswer;
//  int jsonIndex;
//
//  String jsonYAnswer;
//  int jsonYIndex;
//
//  for (int i = 0; i < answer.length(); i++) {
//    if (answer[i] == '{') {
//      jsonIndex = i;
//      break;
//    }
//  }
//
//  for (int i = 0; i < yesterday_answer.length(); i++) {
//    if (yesterday_answer[i] == '{') {
//      jsonYIndex = i;
//      break;
//    }
//  }
//
//  // Get JSON data
//  jsonAnswer = answer.substring(jsonIndex);
//  if (CONNECTED_TO_PC) Serial.println();
//  if (CONNECTED_TO_PC) Serial.println("JSON answer: ");
//  if (CONNECTED_TO_PC) Serial.println(jsonAnswer);
//  jsonAnswer.trim();
//
//  // Get YJSON data
//  jsonYAnswer = yesterday_answer.substring(jsonYIndex);
//  if (CONNECTED_TO_PC) Serial.println();
//  if (CONNECTED_TO_PC) Serial.println("JSON yesterday answer: ");
//  if (CONNECTED_TO_PC) Serial.println(jsonYAnswer);
//  jsonYAnswer.trim();
//
//  // Get rate as float
//  int rateIndex = jsonAnswer.indexOf("rate_float");
//  String priceString = jsonAnswer.substring(rateIndex + 12, rateIndex + 18);
//  priceString.trim();
//  float price = priceString.toFloat();
//
//  // Get rate as float
//  int rateYIndex = jsonYAnswer.indexOf("bpi");
//  String priceYString = jsonYAnswer.substring(rateYIndex + 19, rateYIndex + 26);
//  priceYString.trim();
//  float priceY = priceYString.toFloat();


  // Print price
//  if (CONNECTED_TO_PC) Serial.println();
//  if (CONNECTED_TO_PC) Serial.println("Bitcoin price: ");
//  if (!CONNECTED_TO_PC) Serial.print("$");
//  //Serial.print(price);
//  if (!CONNECTED_TO_PC) Serial.print("%");
//
//  // Print yesterdays price
//  if (CONNECTED_TO_PC) Serial.println();
//  if (CONNECTED_TO_PC) Serial.println("Yesterdays Bitcoin price: ");
//  if (CONNECTED_TO_PC) Serial.print(priceY);
//  float perc = -(100-(price/priceY)*100);
//
//
//  if (CONNECTED_TO_PC) Serial.println("Change in percentage: ");
//  if (CONNECTED_TO_PC) Serial.print(perc);
//
//  
//  if (!CONNECTED_TO_PC) Serial.print("&");
//  //Serial.print(perc);
//  if (!CONNECTED_TO_PC) Serial.print("*");
//  if (CONNECTED_TO_PC) Serial.println();

  // Display on OLED
  //  display.clear();
  //  display.setFont(ArialMT_Plain_24);
  //  display.drawString(26, 20, priceString);
  //  display.display();


//  for (int i = 0; i < 30; i++) {
//    if (!CONNECTED_TO_PC) Serial.print("@");
//    //Serial.print(30-i);
//    if (!CONNECTED_TO_PC) Serial.print("#");
//    delay(1000);
//  }


const size_t bufferSize = JSON_OBJECT_SIZE(3);
DynamicJsonBuffer jsonBuffer(bufferSize);

JsonObject& root = jsonBuffer.createObject();
root["price"] = 93340.93;
root["yesterday"] = 11200.31;
root["time"] = 30;

//root.printTo(Serial);

myCombinedSerial.send(root, 1);

//
//      String str0 = "String to send";
//      char buf[str0.length()];
//
//
//      
//      str0.toCharArray(buf, str0.length());
// //   char p1 = "Package 1";
// //   char p2 = "Package 2";
//
//    float floatie = 13450.49;
//
//    
//    packet00 = packet00 + 1;
//    packet01 = packet01 + 2;
 //   packet10 = packet10 + 5;





 // myFloat.number = floatie;


    // Make an array.
//    uint8_t combPacket[5] = { myFloat.bytes[0], myFloat.bytes[1], myFloat.bytes[2], myFloat.bytes[3], 10 };
//    char combPacket[4] = {buf, packet00, packet01, floatie};
//    uint8_t pricePacket[3] = { p0, packet00, packet01 };
//    uint8_t timePacket[1] = { packet10 };

    // Send the array.
//    serial_Price.send(combPacket, 1);
//    serial_Price.send(pricePacket, 3);
//    serial_Time.send(timePacket, 1);
    delay(2000);


  // Wait 30 seconds
  
}


