#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET    -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int angle = 0;
bool up = true;

void drawPerson(int x, int y, int legSwing) {
  int headSize = 3;
  int bodyHeight = 8;
  int legOffset = 2;

  // Head
  display.drawCircle(x, y - bodyHeight - headSize, headSize, SSD1306_WHITE);

  // Body
  display.drawLine(x, y - bodyHeight, x, y, SSD1306_WHITE);

  // Legs
  display.drawLine(x, y, x - legOffset - legSwing, y + 6, SSD1306_WHITE); 
  display.drawLine(x, y, x + legOffset + legSwing, y + 6, SSD1306_WHITE); 

  // Arms
  display.drawLine(x, y - bodyHeight / 2, x - 3, y - bodyHeight / 2 - 2, SSD1306_WHITE); 
  display.drawLine(x, y - bodyHeight / 2, x + 3, y - bodyHeight / 2 - 2, SSD1306_WHITE); 
}

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  display.clearDisplay();
  display.drawLine(16, 48, 112, 48, SSD1306_WHITE); 
  display.drawLine(64, 48, 64, 63, SSD1306_WHITE);  
  int y1 = 48 - (angle / 2);
  int y2 = 48 + (angle / 2);

  display.drawLine(16, y1, 112, y2, SSD1306_WHITE);
  int legSwing = (angle / 6); 
  drawPerson(16, y1, legSwing);
  drawPerson(112, y2, -legSwing);

  display.display();

  if (up) {
    angle++;
    if (angle >= 30) up = false;
  } else {
    angle--;
    if (angle <= -30) up = true;
  }

  delay(50); 
}

