#include "A_LED_controller.h"
//#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 1

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 48

// Time scaling factors for each component
#define TIME_FACTOR_HUE 60
#define TIME_FACTOR_SAT 100
#define TIME_FACTOR_VAL 100

LED_Controller<10> *onBoard;
LED_Controller<11> *extraLED;

void setup() {
    Serial.begin(115200);

    FastLED.setBrightness(255);

    //FastLED.addLeds<WS2812B, DATA_PIN>(leds, 1)
    onBoard = new LED_Controller<10>();
    extraLED = new LED_Controller<11>();

    delay(2000);  // If something ever goes wrong this delay will allow upload.
    onBoard->SetColour(CRGB::White);
}

uint32_t last_ms = 0;
int bright = 0;

void loop() {
    uint32_t ms = millis();
    
    /*
    for(int i = 0; i < NUM_LEDS; i++) {
        // Use different noise functions for each LED and each color component
        uint8_t hue = inoise16(ms * TIME_FACTOR_HUE, i * 1000, 0) >> 8;
        uint8_t sat = inoise16(ms * TIME_FACTOR_SAT, i * 2000, 1000) >> 8;
        uint8_t val = inoise16(ms * TIME_FACTOR_VAL, i * 3000, 2000) >> 8;
        
        // Map the noise to full range for saturation and value
        sat = map(sat, 0, 255, 30, 255);
        val = map(val, 0, 255, 100, 255);
        
        controller->SetColour(CRGB(hue, sat, val));
    }
    */

    if(ms - last_ms > 10) {
        last_ms = ms;
        bright++;
        onBoard->SetBrightness((bright % 255));
    }
    
}