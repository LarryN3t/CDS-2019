#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// Hardcode WiFi parameters as this isn't going to be moving around.
const char* ssid = "Pippo1";
const char* password = "retewirelesspippo1";

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



String testo = "LORENZO ELETTRONICO";

// Start a TCP Server on port 
WiFiServer server(1235);

void setup() {
  Serial.begin(9600);

  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
    }
    
   WiFi.softAP(ssid, password);
    delay(1000);
    IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
 Serial.println(myIP);

  // Start the TCP server
  server.begin();
}

void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(testo);
  display.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
}



void loop() {
  // listen for incoming clients
   WiFiClient client = server.available();
   
  if (client){
    testo = "";
 while (client.connected()) {
 
      while (client.available()) {
        char c = client.read();
        Serial.write(c);
        testo = testo + c;     
      }
 
      delay(10);
      if (testo!="") {
        testscrolltext();
      }
      testo="";
    }
    client.stop();
    Serial.println("Client disconnected"); 
  }
 }
 
