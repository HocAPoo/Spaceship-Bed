#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>
#include<Servo.h>
// define the GPIO connected with Relays
#define RelayPin1 5  //D1



// prototypes
boolean connectWifi();

//callback functions 
void firstLightChanged(uint8_t brightness);


// WiFi Credentials
const char* ssid = "VillageLAN"; //<----------------------- Wifi details
const char* password = "abracadabra11";

// device names
String Device_1_Name = "c";


boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);

  pinMode(RelayPin1, OUTPUT);


  // Initialise wifi connection
  wifiConnected = connectWifi();

  if (wifiConnected)
  {
    // Define your devices here.
    espalexa.addDevice(Device_1_Name, firstLightChanged);


    espalexa.begin();
  }
  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}

void loop()
{
  espalexa.loop();
  delay(1);
}

//our callback functions
void firstLightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness == 255)
    {
    digitalWrite(RelayPin1, HIGH);
    Serial.println("Device1 OFF"); 
    }
  else
  {
    
    
    digitalWrite(RelayPin1, LOW);
    Serial.println("Device1 ON");
  }
}

boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
