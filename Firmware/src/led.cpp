#include "led.h"
#include "util.h"
#include "globals.h"
#include "ws2812.h"

#include <stdlib.h>

// TODO: remove function when using LED strip with correct length
// void setLedFunc(uint16_t index, uint32_t rgb) {
//     setLed(index + 103, rgb);
// }

uint8_t currentAnimation = 4;


void initLed() {
    ws2812Init();
    initAnimation(NUM_LEDS, ws2812SetLed);
    setAnimation(currentAnimation);
    // setAnimation("vu1");
    // setAnimationIntensity(255);
    // stepAnimation();
}

uint32_t lastLedUpdate = 0;
uint32_t lastAnimationNext = 0;
bool shownBatteryStatus = false;

void loopLed() {
    // TODO: replace this with timer
    if (millis() - lastLedUpdate > 1000 / UPDATE_RATE) { // only do update if update rate allows it
        lastLedUpdate = millis();
        
        stepAnimation();
        // doLedTransfer();
    }

    if (millis() - lastAnimationNext >= 10000) {
        // resetting lastAnimationNext happens in the function
        // ledNextAnimation();
        ledRandomAnimation();
    }
}

void ledNextAnimation() {
    lastAnimationNext = millis();  // also reset next animation counter on manual call of this function
    currentAnimation++;
    if (currentAnimation >= getAnimationCount()) {
        currentAnimation = 0;
    }
    setAnimation(currentAnimation);
}

void ledRandomAnimation() {
    lastAnimationNext = millis();  // also reset next animation counter on manual call of this function
    uint8_t randNum = rand() % getAnimationCount();
    if (randNum == currentAnimation) {  // if it choses the same animation, try again
        ledRandomAnimation();
        return;
    }
    currentAnimation = randNum;
    setAnimation(currentAnimation);
}

void ledBlink(uint32_t blinks, uint32_t delayMs, uint32_t rgb) {
    for (uint32_t i = 0; i < blinks; i++) {
        delay(delayMs);
        ws2812Fill(rgb);
        // doLedTransfer();
        delay(delayMs);
        ws2812Fill(0x000000);
        // doLedTransfer();
    }
}

void ledDisplayBatteryPercent(uint8_t battPercent) {
    uint8_t numberOfLedsToShow = NUM_LEDS *  battPercent / 100;
    ws2812Fill(0);
    for (int i = 0; i < numberOfLedsToShow; i++) {
        uint8_t iScaled = i * 255 / (NUM_LEDS-1);
        ws2812SetLed(i, (255 - iScaled) << 16 | iScaled << 8);
    }
    // doLedTransfer();
}