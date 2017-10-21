#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTPIN 5
#define PHOTOCELL_PIN A0
#define DHTTYPE DHT11

// set wifi ssid and password
const char* ssid = "Pi3-AP";
const char* password = "raspberry";
const char* host = "master";
const int httpPort = 80;
String mac  = "";

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

// connecting
void setup() {

  Serial.begin(115200);
  delay(100);

  dht.begin();
  mac = WiFi.macAddress();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Print the IP address
  Serial.print("IP Address : ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
  Serial.print("MAC : ");
  Serial.print(mac);
  Serial.print("\n");
}

// send data every 30s
void loop() {
  delay(30000);
  mac.replace(":", "");

  char t_buffer[10];
  char h_buffer[10];
  char l_buffer[10];

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float l = analogRead(PHOTOCELL_PIN) ;

  if (isnan(h) || isnan(t) || isnan(l)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  String temp = dtostrf(t, 0, 2, t_buffer);
  String humi = dtostrf(h, 0, 2, h_buffer);
  String light = dtostrf(l, 0, 2, l_buffer);

  // We now create a URI for the request
  String url = "/addenvdata/";
  url += mac;

  //request data
  String postData = "{\"light\":" + light + ",\"temp\":" + temp + ",\"humi\":" + humi + "}";

  //check data and url
  Serial.print(postData);
  Serial.print("\n");
  Serial.print(url);
  Serial.print("\n");

  client.println(String("POST ") + url + " HTTP/1.1");
  client.println("Host: " + String(host) );
  client.println("Cache-Control: no-cache");
  client.println("Content-Type: application/json;");
  //client.println("Content-Type: application/x-www-form-urlencoded;");
  //client.println("Content-Type: text/plain");
  client.print("Content-Length: ");
  client.println(postData.length());
  client.println();
  client.println(postData);

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
}
