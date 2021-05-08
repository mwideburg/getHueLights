/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/Users/michaelwideburg/Desktop/getHueLights/getHueLights/src/getHueLights.ino"
/*
 * Project getHueLights
 * Description:
 * Author:
 * Date:
 */
#include <HttpClient.h>

#include "Particle.h"

#include "JsonParserGeneratorRK.h"

// setup() runs once, when the device is first turned on.
void setup();
void loop();
void getLights();
void setHueLights(String command);
void numTimesLoopCommand(String command);
#line 14 "/Users/michaelwideburg/Desktop/getHueLights/getHueLights/src/getHueLights.ino"
SYSTEM_THREAD(ENABLED);

// This uses the USB serial port for debugging logs.
SerialLogHandler logHandler;

// This is where your LED is plugged in. The other side goes to a resistor
// connected to GND.
const pin_t LED_PIN = D6;

// This is where your photoresistor or phototransistor is plugged in.
const pin_t SENSOR_PIN = A0;

const String API_USERNAME = "akHjyXarISzdmN6e4rjLn5pxcpIVgiAzO3GZl-1o";
const String BEDROOM_PATH = "/lights/5";  // Local HUE bridge port
const String BATHROOM_PATH = "/lights/5"; // Local HUE bridge port
const String LIGHT_PATH = "/groups/3/action";
const String REQUEST_ON = "{\"on\": true, \"scene\": \"vYmauYCRgzUFz3-\", \"transitiontime\": 30}";
const String test = "{\"state\": {\"hue\": \"10000\"}}";
HttpClient http;
IPAddress hueIP(192, 168, 1, 157);
// Default header for HTTP requests
http_header_t headers[] = {
    {"Accept", "*/*"},
    {NULL, NULL} // NOTE: Always terminate headers will NULL
};

// Request and response objects
http_request_t request;
http_response_t response;
JsonParserStatic<1024, 50> parse1;
int analogvalue;
int hue = 8418;
int count = 0;
int trigger = 0;
bool lightStatus = false;
String last = "null";


void setup() {
  // Put initialization like pinMode and begin functions here.
  request.ip = hueIP;
  request.port = 80;
  Serial.begin(9600);
  // First, declare all of our pins. This lets our device know which ones
  // will be used for outputting voltage, and which ones will read
  // incoming voltage.
  pinMode(LED_PIN, OUTPUT); // Our LED pin is output (lighting up the LED)
  digitalWrite(LED_PIN, LOW);

  // We are going to declare a Particle.variable() here so that we can
  // access the value of the photosensor from the cloud.
  Particle.variable("analogvalue", analogvalue);
}



// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
    
    analogvalue = analogRead(SENSOR_PIN);
    lightStatus = false;
    getLights();

    // Serial.println("HUE DATA");
    // Serial.println(hue);
    // Serial.println();
    // Serial.println(lightStatus);
    // count++;
    // Serial.println("count");
    // Serial.println(count);
    // Serial.println("------------------");

    if (hue != 8418 && lightStatus == true && trigger >= 3)
    {
      if (analogvalue >= 8 && analogvalue < 10 && last != "Dusk")
        {
          Particle.publish("Dusk");
          last = "Dusk";
          String command = "{\"on\": true, \"scene\": \"dpRaqSDvH6m0nx2\", \"transitiontime\": 30}";
          numTimesLoopCommand(command);
          
          
        }
        else if (analogvalue >= 4 && analogvalue < 8 && last != "Dusk 2")
        {
          Particle.publish("Dusk 2");
          String command = "{\"on\": true, \"scene\": \"O2PwRXlDLslyAId\", \"transitiontime\": 30}";
          last = "Dusk 2";

          numTimesLoopCommand(command);
        }
        else if (analogvalue <= 2 && analogvalue < 4 && last != "Night")
        {
          Particle.publish("Night");
          String command = "{\"on\": true, \"scene\": \"bbI-AG7rdXVVyxI\", \"transitiontime\": 30}";
          last = "Night";
          numTimesLoopCommand(command);
        }
        else if (analogvalue >= 10 && last != "Day")
        {
          Particle.publish("DAY");
          //  getHueBedroom(5);
          String command = "{\"on\": true, \"scene\": \"vYmauYCRgzUFz3-\", \"transitiontime\": 30}";
          last = "Day";
          numTimesLoopCommand(command);
        }
        trigger = 0;
    }
    
    // Serial.println("------------------");
    // Serial.println("This is main loop");
    // Serial.println(lightStatus);
    // count++;
    // Serial.println("count");
    // Serial.println(count);
    // Serial.println("------------------");
    // delay(500);
    if (trigger > 3)
    {
      trigger = 0;
    }
    trigger ++;
    
  
  }


void getLights(){
  request.path = "/api/" + API_USERNAME + BEDROOM_PATH;
  
  http.get(request, response, headers);
  String data = response.body.c_str();
  // Serial.println("Full Data");
  // Serial.println(lightStatus);
  // Serial.println(data);
  // Serial.println();
  // count ++;
  // Serial.println("count");
  // Serial.println(count);
  // Serial.println("------------------");
  int pos = data.indexOf("h") + 5;

  hue = data.substring(pos, pos + 4).toInt();
  
  delay(1000);
  lightStatus = true;
  // Serial.println("2 seconds");
  // Serial.println(lightStatus);
  // count++ ;
  // Serial.println("count");
  // Serial.println(count);
  // Serial.println("------------------");
}

void setHueLights(String command){
  request.path = "/api/" + API_USERNAME + LIGHT_PATH;
  request.body = command;
  http.put(request, response, headers);

}

void numTimesLoopCommand(String command)
{
  for (int i = 0; i < 5; i++)
  {
    setHueLights(command);
    delay(200);
  }
}