// Libraries
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Wire.h>
//#include "SSD1306.h"

#define CONNECTED_TO_PC false

// Pins
//#define SDA 14
//#define SCL 12
//#define I2C 0x3D

// Create display
//SSD1306 display(I2C, SDA, SCL);

// WiFi settings
const char* ssid     = "ssid";
const char* password = "password";

// API server
const char* host = "api.coindesk.com";

void setup() {

  // Serial
  Serial.begin(9600);
  delay(10);

  // Initialize display
  //  display.init();
  //  display.flipScreenVertically();
  //  display.clear();
  //  display.display();

  // We start by connecting to a WiFi network
  if (CONNECTED_TO_PC) {
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
  }
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

    if (CONNECTED_TO_PC) Serial.print(".");
  }

  if (CONNECTED_TO_PC) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void loop() {

  // Connect to API
  if (CONNECTED_TO_PC) Serial.print("connecting to ");
  if (CONNECTED_TO_PC) Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    if (CONNECTED_TO_PC) Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/v1/bpi/currentprice.json";

  if (CONNECTED_TO_PC) Serial.print("Requesting URL: ");
  if (CONNECTED_TO_PC) Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(100);

  // Read all the lines of the reply from server and print them to Serial
  String answer;
  while (client.available()) {
    String line = client.readStringUntil('\r');
    answer += line;
  }

  client.stop();
  if (CONNECTED_TO_PC) Serial.println();
  if (CONNECTED_TO_PC) Serial.println("closing connection");

  // Process answer
  if (CONNECTED_TO_PC) Serial.println();
  if (CONNECTED_TO_PC) Serial.println("Answer: ");
  if (CONNECTED_TO_PC) Serial.println(answer);

  // Convert to JSON
  String jsonAnswer;
  int jsonIndex;

  for (int i = 0; i < answer.length(); i++) {
    if (answer[i] == '{') {
      jsonIndex = i;
      break;
    }
  }

  // Get JSON data
  jsonAnswer = answer.substring(jsonIndex);
  if (CONNECTED_TO_PC) Serial.println();
  if (CONNECTED_TO_PC) Serial.println("JSON answer: ");
  if (CONNECTED_TO_PC) Serial.println(jsonAnswer);
  jsonAnswer.trim();

  // Get rate as float
  int rateIndex = jsonAnswer.indexOf("rate_float");
  String priceString = jsonAnswer.substring(rateIndex + 12, rateIndex + 18);
  priceString.trim();
  float price = priceString.toFloat();

  // Print price
  if (CONNECTED_TO_PC) Serial.println();
  if (CONNECTED_TO_PC) Serial.println("Bitcoin price: ");
  if (!CONNECTED_TO_PC) Serial.print("$");
  Serial.print(price);
  if (!CONNECTED_TO_PC) Serial.print("%");

  // Display on OLED
  //  display.clear();
  //  display.setFont(ArialMT_Plain_24);
  //  display.drawString(26, 20, priceString);
  //  display.display();

  // Wait 30 seconds
  delay(5000);
}


