#include <FastLED.h>
#include <Control_Surface.h>

const byte _nLED = 32;  // Number of LEDs
const byte _dLED = 14;  // Data pin


CRGB _LED[_nLED];

const uint8_t MAX_BRIGHTNESS = 255;  // Adjust this value as needed

const unsigned long LED_UPDATE_INTERVAL = 10;
unsigned long lastUpdate = 0;

bool update = false;
//Factory palette
const byte _r[128] = {0, 28, 125, 255, 255, 255, 85, 24, 255, 255, 85, 36, 255, 255, 85, 24, 134, 81, 28, 16, 73, 0, 0, 0, 73, 0, 0, 0, 73, 0, 0, 0, 73, 0, 0, 0, 73, 0, 0, 0, 73, 0, 0, 0, 73, 0, 0, 0, 134, 81, 24, 12, 255, 255, 85, 24, 255, 255, 85, 32, 255, 150, 117, 65, 0, 0, 0, 0, 0, 36, 125, 28, 255, 186, 174, 97, 12, 0, 0, 0, 61, 121, 174, 61, 255, 134, 113, 0, 57, 85, 53, 89, 49, 134, 210, 255, 255, 182, 142, 130, 57, 16, 12, 20, 20, 101, 166, 219, 215, 255, 158, 101, 28, 219, 125, 154, 142, 61, 113, 223, 158, 53, 24, 4, 182, 61, 178, 73};
const byte _g[128] = {0, 28, 125, 255, 73, 0, 0, 0, 186, 81, 28, 24, 255, 255, 85, 24, 255, 255, 85, 40, 255, 255, 85, 24, 255, 255, 85, 24, 255, 255, 85, 28, 255, 255, 85, 24, 194, 166, 65, 12, 134, 85, 28, 4, 73, 0, 0, 0, 73, 0, 0, 0, 73, 0, 0, 0, 73, 0, 0, 0, 20, 53, 81, 97, 57, 85, 81, 0, 69, 0, 125, 28, 0, 255, 235, 255, 138, 255, 166, 40, 0, 0, 24, 32, 73, 223, 255, 255, 255, 255, 255, 138, 81, 125, 28, 0, 125, 174, 255, 89, 40, 73, 77, 20, 28, 57, 0, 81, 105, 223, 223, 178, 28, 255, 255, 150, 101, 61, 113, 255, 0, 0, 206, 65, 174, 49, 93, 20};
const byte _b[128] = {0, 28, 125, 255, 73, 0, 0, 0, 105, 0, 0, 0, 73, 0, 0, 0, 73, 0, 0, 0, 73, 0, 0, 0, 93, 24, 12, 0, 134, 85, 28, 16, 182, 150, 53, 16, 255, 255, 81, 24, 255, 255, 85, 24, 255, 255, 85, 24, 255, 255, 97, 45, 255, 255, 85, 24, 134, 81, 28, 16, 0, 0, 0, 0, 0, 53, 125, 255, 77, 202, 125, 28, 0, 45, 4, 8, 0, 134, 255, 255, 255, 255, 121, 0, 0, 4, 20, 0, 36, 109, 202, 255, 194, 231, 255, 89, 0, 0, 0, 4, 0, 12, 53, 40, 89, 24, 8, 61, 24, 36, 45, 12, 45, 105, 186, 255, 255, 61, 113, 255, 0, 0, 0, 0, 0, 0, 0, 0};
//Realism palette
const byte _r2[128] = {0, 109, 182, 255, 255, 255, 223, 170, 255, 255, 198, 190, 255, 255, 206, 174, 61, 24, 4, 20, 0, 0, 0, 0, 53, 0, 0, 0, 45, 0, 0, 0, 40, 0, 0, 0, 45, 0, 0, 0, 93, 0, 0, 0, 97, 0, 0, 0, 138, 32, 20, 8, 255, 255, 210, 158, 255, 255, 198, 178, 255, 255, 219, 81, 4, 0, 0, 0, 0, 4, 202, 49, 255, 182, 158, 69, 4, 0, 0, 0, 4, 81, 255, 85, 255, 162, 158, 0, 32, 32, 32, 65, 28, 77, 215, 255, 255, 210, 105, 170, 130, 0, 0, 40, 4, 113, 113, 186, 210, 255, 150, 101, 24, 255, 146, 142, 190, 105, 186, 202, 194, 125, 0, 0, 194, 154, 186, 134};
const byte _g2[128] = {0, 109, 182, 255, 45, 0, 0, 0, 182, 53, 45, 32, 202, 247, 202, 174, 255, 255, 206, 134, 255, 251, 219, 138, 255, 255, 206, 170, 255, 255, 198, 166, 255, 255, 202, 162, 255, 223, 202, 178, 210, 130, 97, 69, 130, 0, 0, 0, 113, 0, 0, 0, 101, 0, 0, 0, 65, 0, 0, 0, 4, 109, 166, 166, 117, 93, 20, 0, 130, 0, 186, 49, 0, 255, 198, 239, 194, 215, 206, 105, 0, 0, 45, 4, 24, 255, 255, 255, 255, 255, 255, 206, 138, 89, 24, 0, 53, 194, 255, 146, 85, 113, 101, 32, 32, 73, 0, 65, 101, 198, 255, 190, 20, 255, 255, 182, 162, 105, 190, 231, 0, 0, 202, 158, 202, 121, 101, 4};
const byte _b2[128] = {0, 109, 182, 255, 45, 0, 0, 0, 77, 0, 0, 0, 77, 0, 0, 0, 36, 0, 0, 0, 77, 0, 0, 0, 93, 28, 12, 8, 113, 101, 77, 81, 170, 170, 125, 105, 255, 255, 202, 182, 255, 255, 198, 138, 255, 251, 202, 146, 255, 255, 210, 174, 198, 198, 166, 85, 121, 113, 28, 12, 0, 0, 0, 0, 0, 8, 162, 210, 101, 210, 162, 49, 0, 0, 0, 0, 0, 73, 239, 239, 239, 239, 186, 0, 0, 0, 28, 0, 20, 105, 190, 255, 174, 215, 255, 113, 0, 0, 0, 0, 0, 4, 45, 65, 73, 16, 0, 45, 4, 4, 12, 0, 73, 134, 134, 251, 251, 105, 190, 202, 0, 0, 0, 0, 0, 0, 0, 0};
//Mat1 palette
const byte _r3[128] = {0, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 45, 93, 142, 223, 190, 28, 61, 93, 190, 125, 12, 28, 45, 158, 61, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 12, 28, 45, 158, 61, 28, 61, 93, 190, 125, 45, 93, 142, 223, 190, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 36, 73, 109, 146, 182, 219, 255};
const byte _g3[128] = {0, 0, 0, 0, 125, 0, 12, 28, 45, 158, 61, 28, 61, 93, 190, 125, 45, 93, 142, 223, 190, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 45, 93, 142, 223, 190, 28, 61, 93, 190, 125, 12, 28, 45, 158, 61, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 36, 73, 109, 146, 182, 219, 255};
const byte _b3[128] = {0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 0, 0, 0, 125, 0, 12, 28, 45, 158, 61, 28, 61, 93, 190, 125, 45, 93, 142, 223, 190, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 61, 125, 190, 255, 255, 45, 93, 142, 223, 190, 28, 61, 93, 190, 125, 12, 28, 45, 158, 61, 36, 73, 109, 146, 182, 219, 255};

USBMIDI_Interface midi;

struct MyMIDI_Callbacks : FineGrainedMIDI_Callbacks<MyMIDI_Callbacks> {
  void onNoteOn(Channel ch, uint8_t p, uint8_t v, Cable cable) {
    uint8_t channelNum = ch.getRaw();
    int ledIndex = -1;

    // Top row (LED 1~8) : 35~28
    if (p >= 28 && p <= 35) {
      ledIndex = 35 - p;
    }
    // Left column (LED 9~16) : 108~115
    else if (p >= 108 && p <= 115) {
      ledIndex = p - 100;
    }
    // Right column (LED 25~32) : 100~107
    else if (p >= 100 && p <= 107) {
      ledIndex = 131 - p;
    }
    // Bottom row (LED 17~24) : 116~123
    else if (p >= 116 && p <= 123) {
      ledIndex = p - 100;
    }

    if (ledIndex >= 0 && ledIndex < _nLED) {
      switch (channelNum) {
        case 0:
          _LED[ledIndex] = CRGB(_r[v], _g[v], _b[v]);
          break;
        case 1:
          _LED[ledIndex] = CRGB(_r2[v], _g2[v], _b2[v]);
          break;
        case 2:
          _LED[ledIndex] = CRGB(_r3[v], _g3[v], _b3[v]);
          break;
      }
      update = true;
    }
  }

  void onNoteOff(Channel ch, uint8_t p, uint8_t v, Cable cable) {
    uint8_t channelNum = ch.getRaw();
    int ledIndex = -1;

    // Top row (LED 1~8) : 35~28
    if (p >= 28 && p <= 35) {
      ledIndex = 35 - p;
    }
    // Left column (LED 9~16) : 108~115
    else if (p >= 108 && p <= 115) {
      ledIndex = p - 100;
    }
    // Right column (LED 25~32) : 100~107
    else if (p >= 100 && p <= 107) {
      ledIndex = 131 - p;
    }
    // Bottom row (LED 17~24) : 116~123
    else if (p >= 116 && p <= 123) {
      ledIndex = p - 100;
    }
    if (ledIndex >= 0 && ledIndex < _nLED) {
      switch (channelNum) {
        case 0:
          _LED[ledIndex] = CRGB::Black;
          break;
        case 1:
          _LED[ledIndex] = CRGB::Black;
          break;
        case 2:
          _LED[ledIndex] = CRGB::Black;
          break;
      }
      update = true;
    }
  }
} callback;

void setup() {
  FastLED.addLeds<NEOPIXEL, _dLED>(_LED, _nLED);
  FastLED.setBrightness(MAX_BRIGHTNESS);
  FastLED.show();
  
  midi.begin();
  midi.setCallbacks(callback);
  Serial.begin(115200);
}

void loop() {
  unsigned long currentMillis = millis();
  if (update && currentMillis - lastUpdate >= LED_UPDATE_INTERVAL) {
    FastLED.show();
    lastUpdate = currentMillis;
    update = false;
  }
  midi.update();
}
