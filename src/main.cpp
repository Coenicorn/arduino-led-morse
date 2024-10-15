#include <Arduino.h>

#define PIN_B A3
#define PIN_G A4
#define PIN_R A5

typedef unsigned int pin_t;

static const char* morseText = "kerstmisislit";

#define NONE 0x00
#define DOT 0x01
#define DASH 0x03

#define MORSE_MAX_CHAR_LEN 5

static const unsigned int morseCode[26][MORSE_MAX_CHAR_LEN] = {
    {DOT, DASH, NONE, NONE, NONE},   // A
    {DASH, DOT, DOT, DOT, NONE},     // B
    {DASH, DOT, DASH, DOT, NONE},    // C
    {DASH, DOT, DOT, NONE, NONE},    // D
    {DOT, NONE, NONE, NONE, NONE},   // E
    {DOT, DOT, DASH, DOT, NONE},     // F
    {DASH, DASH, DOT, NONE, NONE},   // G
    {DOT, DOT, DOT, DOT, NONE},      // H
    {DOT, DOT, NONE, NONE, NONE},    // I
    {DOT, DASH, DASH, DASH, NONE},   // J
    {DASH, DOT, DASH, NONE, NONE},   // K
    {DOT, DASH, DOT, DOT, NONE},     // L
    {DASH, DASH, NONE, NONE, NONE},  // M
    {DASH, DOT, NONE, NONE, NONE},   // N
    {DASH, DASH, DASH, NONE, NONE},  // O
    {DOT, DASH, DASH, DOT, NONE},    // P
    {DASH, DASH, DOT, DASH, NONE},   // Q
    {DOT, DASH, DOT, NONE, NONE},    // R
    {DOT, DOT, DOT, NONE, NONE},     // S
    {DASH, NONE, NONE, NONE, NONE},  // T
    {DOT, DOT, DASH, NONE, NONE},    // U
    {DOT, DOT, DOT, DASH, NONE},     // V
    {DOT, DASH, DASH, NONE, NONE},   // W
    {DASH, DOT, DOT, DASH, NONE},    // X
    {DASH, DOT, DASH, DASH, NONE},   // Y
    {DASH, DASH, DOT, DOT, NONE}     // Z
};

#define DOT_DELAY_TIME 300 /* milliseconds */

void ledOn(pin_t pin) {
    digitalWrite(pin, HIGH);
}
void ledOff(pin_t pin) {
    digitalWrite(pin, LOW);
}

// blocking
void showMorseLetter(char letter) {
    // check ascii range
    if (letter < 97 || letter > 172) return;
    // fit to range
    
    const unsigned int letterIndex = (unsigned int)letter - 97;
    unsigned int currentSignal;
    for (unsigned int i = 0; (i < MORSE_MAX_CHAR_LEN && (currentSignal = morseCode[letterIndex][i])); i++) {
        ledOn(PIN_G);

        unsigned int delayTime = currentSignal * DOT_DELAY_TIME;
        delay(delayTime);

        ledOff(PIN_G);

        // delay for the next signal
        delay(DOT_DELAY_TIME);
    }

    // delay for next letter
    // 3 * DOT
    delay(DOT_DELAY_TIME * 3);
}

static unsigned int morseTextLength = 0;

void setup() {
    pinMode(PIN_R, OUTPUT);
    pinMode(PIN_G, OUTPUT);
    pinMode(PIN_B, OUTPUT);

    morseTextLength = strlen(morseText);
}

void loop() {

    ledOn(PIN_R);
    delay(1000);
    ledOff(PIN_R);
    delay(1000);

    for (unsigned int i = 0; i < morseTextLength; i++) {
        showMorseLetter(morseText[i]);
    }
}