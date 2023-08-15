/// CODE for an 11 sided toy for June's 2nd birthday, August 25, 2023
//// first pass, 8.14.23
/// william kennedy

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <FastLED.h>


// GUItool: begin automatically generated code
AudioPlaySdWav           sound0;         //xy=142,116
AudioPlaySdWav           sound1;         //xy=158,190
AudioPlaySdWav           sound2;         //xy=172,252
AudioPlaySdWav           sound3;         //xy=208,308
AudioPlaySdWav           sound4; //xy=218.1999969482422,368.1999816894531
AudioPlaySdWav           sound5; //xy=229.1999969482422,422.1999816894531
AudioPlaySdWav           sound6; //xy=238.1999969482422,475.1999816894531
AudioPlaySdWav           sound7; //xy=247.1999969482422,518.2000122070312
AudioPlaySdWav           sound8; //xy=248.1999969482422,559.2000122070312
AudioMixer4              mixL1;           //xy=414.99999237060547,140.00000190734863
AudioMixer4              mixR1; //xy=423.1999740600586,317.1999702453613
AudioMixer4              mixL2; //xy=448.1999816894531,411.1999816894531
AudioMixer4              mixR2; //xy=463.1999816894531,530.2000122070312
AudioMixer4              mixL3; //xy=597.2000350952148,243.19998741149902
AudioMixer4              mixR3; //xy=623.2001609802246,396.1999740600586
AudioOutputI2S           i2s1;           //xy=790.0000267028809,274.99997329711914
AudioConnection          patchCord1(sound0, 0, mixL1, 0);
AudioConnection          patchCord2(sound0, 1, mixR1, 0);
AudioConnection          patchCord3(sound1, 0, mixL1, 1);
AudioConnection          patchCord4(sound1, 1, mixR1, 1);
AudioConnection          patchCord5(sound2, 0, mixL1, 2);
AudioConnection          patchCord6(sound2, 1, mixR1, 2);
AudioConnection          patchCord7(sound3, 0, mixL1, 3);
AudioConnection          patchCord8(sound3, 1, mixR1, 3);
AudioConnection          patchCord9(sound4, 0, mixL2, 0);
AudioConnection          patchCord10(sound4, 1, mixR2, 0);
AudioConnection          patchCord11(sound5, 0, mixL2, 1);
AudioConnection          patchCord12(sound5, 1, mixR2, 1);
AudioConnection          patchCord13(sound6, 0, mixL2, 2);
AudioConnection          patchCord14(sound6, 1, mixR2, 2);
AudioConnection          patchCord15(sound7, 0, mixL2, 3);
AudioConnection          patchCord16(sound7, 1, mixR2, 3);
AudioConnection          patchCord17(sound8, 0, mixL3, 2);
AudioConnection          patchCord18(sound8, 1, mixR3, 2);
AudioConnection          patchCord19(mixL1, 0, mixL3, 0);
AudioConnection          patchCord20(mixR1, 0, mixR3, 0);
AudioConnection          patchCord21(mixL2, 0, mixL3, 1);
AudioConnection          patchCord22(mixR2, 0, mixR3, 1);
AudioConnection          patchCord23(mixL3, 0, i2s1, 0);
AudioConnection          patchCord24(mixR3, 0, i2s1, 1);
// GUItool: end automatically generated code

/// LED SETUP //////


#define NUM_LEDS 30  // Change this to the number of LEDs in your strip
#define LED_PIN 9    // Change this to the data pin for your LED strip
CRGB leds[NUM_LEDS];

///////////////

// Create an object to control the audio shield.
//
AudioControlSGTL5000 audioShield;

// Bounce objects to read six pushbuttons (pins 0-6)
//
Bounce button0 = Bounce(0, 5);
Bounce button1 = Bounce(1, 5);  // 5 ms debounce time
Bounce button2 = Bounce(2, 5);
Bounce button3 = Bounce(3, 5);
Bounce button4 = Bounce(4, 5);
Bounce button5 = Bounce(5, 5);
Bounce button6 = Bounce(6, 5);
Bounce button7 = Bounce(10, 5);
Bounce button8 = Bounce(11, 5);


void setup() {
  // Configure the pushbutton pins for pullups.
  // Each button should connect from the pin to GND.
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);

  // Initialize FastLED
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(128); // Set the initial brightness
  fill_solid(leds, NUM_LEDS, CRGB::Black); // Turn off all LEDs
  FastLED.show();

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(10);

  // turn on the output
  audioShield.enable();
  audioShield.volume(0.5);

  // by default the Teensy 3.1 DAC uses 3.3Vp-p output
  // if your 3.3V power has noise, switching to the
  // internal 1.2V reference can give you a clean signal
  //dac.analogReference(INTERNAL);

  // reduce the gain on mixer channels, so more than 1
  // sound can play simultaneously without clipping
  mixL1.gain(0, 0.4);
  mixL1.gain(1, 0.4);
  mixL1.gain(2, 0.4);
  mixL1.gain(3, 0.4);
  mixR1.gain(0, 0.4);
  mixR1.gain(1, 0.4);
  mixR1.gain(2, 0.4);
  mixR1.gain(3, 0.4);
  mixL2.gain(0, 0.4);
  mixL2.gain(1, 0.4);
  mixL2.gain(2, 0.4);
  mixL2.gain(3, 0.4);
  mixR2.gain(0, 0.4);
  mixR2.gain(1, 0.4);
  mixR2.gain(2, 0.4);
  mixR2.gain(3, 0.4);
  mixL3.gain(0, 0.4);
  mixL3.gain(1, 0.4);
  mixL3.gain(2, 0.4);
  mixR3.gain(0, 0.4);
  mixR3.gain(1, 0.4);
  mixR3.gain(2, 0.4);
}


void loop() {
  // Update all the button objects
  button0.update();
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  button5.update();
  button6.update();
  button7.update();
  button8.update();

  // When the buttons are pressed, just start a sound playing.
  // The audio library will play each sound through the mixers
  // so any combination can play simultaneously.
  //
  if (button0.risingEdge()) {
    sound0.play("sound0.wav");
    rainbowAnimation(); // Start the rainbow animation
    //    fill_solid(leds, NUM_LEDS, CRGB::Amethyst);
    //    FastLED.show();
  }
  if (button1.fallingEdge()) {
    sound1.play("sound1.wav");
    colorWipeAnimation(CRGB::Green); // Start the color wipe animation with green color
    //    fill_solid(leds, NUM_LEDS, CRGB::Aquamarine);
    //    FastLED.show();
  }
  if (button2.fallingEdge()) {
    sound2.play("sound2.wav");
    fill_solid(leds, NUM_LEDS, CRGB::Chartreuse);
    FastLED.show();
  }
  if (button3.fallingEdge()) {
    sound3.play("sound3.wav");
    fill_solid(leds, NUM_LEDS, CRGB::Coral);
    FastLED.show();
  }
  if (button4.fallingEdge()) {
    sound4.play("sound4.wav");
    fill_solid(leds, NUM_LEDS, CRGB::DeepPink);
    FastLED.show();
  }
  if (button5.fallingEdge()) {
    sound5.play("sound5.wav");
    fill_solid(leds, NUM_LEDS, CRGB::SlateBlue);
    FastLED.show();
  }
  if (button6.fallingEdge()) {
    sound6.play("sound6.wav");
    fill_solid(leds, NUM_LEDS, CRGB::Yellow);
    FastLED.show();
  }

  if (button7.fallingEdge()) {
    sound7.play("sound7.wav");
    fill_solid(leds, NUM_LEDS, CRGB::OrangeRed);
    FastLED.show();
  }

  if (button8.risingEdge()) {
    sound8.play("sound8.wav");
    fill_solid(leds, NUM_LEDS, CRGB::LavenderBlush);
    FastLED.show();
  }

}

void rainbowAnimation() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(i * 255 / NUM_LEDS, 255, 255);
  }
  FastLED.show();
}

void colorWipeAnimation(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
    FastLED.show();
    delay(50);
  }
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}
