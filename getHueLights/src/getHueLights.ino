/*
 * Project getHueLights
 * Description:
 * Author:
 * Date:
 */
#include <HttpClient.h>
#include "Particle.h"
// setup() runs once, when the device is first turned on.
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

HttpClient http;

// Default header for HTTP requests
http_header_t headers[] = {
    {"Accept", "*/*"},
    {NULL, NULL} // NOTE: Always terminate headers will NULL
};

// Request and response objects
http_request_t request;
http_response_t response;

void setup() {
  // Put initialization like pinMode and begin functions here.

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

}