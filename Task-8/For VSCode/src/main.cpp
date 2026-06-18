#include <Adafruit_NeoPixel.h>

#define LED_PIN        6   
#define BUTTON_PIN     2   
#define MATRIX_WIDTH   8   
#define MATRIX_HEIGHT  8   
#define NUMPIXELS      (MATRIX_WIDTH * MATRIX_HEIGHT) 

Adafruit_NeoPixel matrix = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

volatile int currentPattern = 0; 
const int TOTAL_PATTERNS = 5;

void setup() {
  matrix.begin();           
  matrix.setBrightness(50); 
  matrix.show();            
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

bool checkButtonAndDelay(int ms) {
  for (int i = 0; i < ms; i++) {
    if (digitalRead(BUTTON_PIN) == LOW) {
      delay(50); 
      while (digitalRead(BUTTON_PIN) == LOW) {
        delay(10);
      }
      currentPattern = (currentPattern + 1) % TOTAL_PATTERNS;
      matrix.clear(); 
      matrix.show();
      return true; 
    }
    delay(1); 
  }
  return false; 
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) return matrix.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  if(WheelPos < 170) { WheelPos -= 85; return matrix.Color(0, WheelPos * 3, 255 - WheelPos * 3); }
  WheelPos -= 170; return matrix.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

int getPixelIndex(int x, int y) {
  if (x < 0 || x >= MATRIX_WIDTH || y < 0 || y >= MATRIX_HEIGHT) return -1;
  return y * MATRIX_WIDTH + x;
}

void scannerEffect() {
  for (int x = 0; x < MATRIX_WIDTH; x++) {
    matrix.clear();
    uint32_t color = Wheel(x * 30);
    for (int y = 0; y < MATRIX_HEIGHT; y++) matrix.setPixelColor(getPixelIndex(x, y), color);
    matrix.show();
    if (checkButtonAndDelay(60)) return;
  }
  for (int x = MATRIX_WIDTH - 2; x > 0; x--) {
    matrix.clear();
    uint32_t color = Wheel(x * 30);
    for (int y = 0; y < MATRIX_HEIGHT; y++) matrix.setPixelColor(getPixelIndex(x, y), color);
    matrix.show();
    if (checkButtonAndDelay(60)) return;
  }
}

void centerWaves() {
  for (int wave = 0; wave < 4; wave++) {
    matrix.clear();
    uint32_t color = Wheel(wave * 60);
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
      for (int x = 0; x < MATRIX_WIDTH; x++) {
        int layer = min(min(x, MATRIX_WIDTH - 1 - x), min(y, MATRIX_HEIGHT - 1 - y));
        if (layer == (3 - wave)) matrix.setPixelColor(getPixelIndex(x, y), color);
      }
    }
    matrix.show();
    if (checkButtonAndDelay(150)) return;
  }
}


void loop() {
  switch (currentPattern) {
    case 0:
      centerWaves();
      break;
    case 1:
      scannerEffect(); 
      break;
  }
}