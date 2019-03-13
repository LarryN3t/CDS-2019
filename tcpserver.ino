
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// Hardcode WiFi parameters as this isn't going to be moving around.
const char* ssid = "Pippo1";
const char* password = "retewirelesspippo1";

// Start a TCP Server on port 
WiFiServer server(1235);

void setup() {
  Serial.begin(115200);
   WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
 Serial.println(myIP);

  // Start the TCP server
  server.begin();
}

void loop() {
  // listen for incoming clients
   WiFiClient client = server.available();
   
  if (client){
 while (client.connected()) {
 
      while (client.available()) {
        char c = client.read();
        Serial.write(c);
      }
 
      delay(10);
    
    }
    client.stop();
    Serial.println("Client disconnected"); 
  }
 }
 
