#define GAME_VER "v.4"

#define RANDOM_PIN 26

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3C

// Define game constants and variables

const int MAX_LEVEL = 100;
int sequence[MAX_LEVEL];
int sound[MAX_LEVEL];
int player_sequence[MAX_LEVEL];
int level = 1;
int note = 0;
int velocity = 500;

// Piezo Sounds

#define GRN_SOUND 262
#define RED_SOUND 294
#define YEL_SOUND 330
#define BLU_SOUND 280
#define BAD_SOUND 350

// LED Definitions

#define BLU_LED 10
#define GRN_LED 11
#define YEL_LED 12
#define RED_LED 13

// Pushbutton Definitions

#define GRN_BTN 18
#define BLU_BTN 19
#define YEL_BTN 20
#define RED_BTN 21

// // Piezo Buzzer
#define PIEZO 22

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

byte GameState = 0;
byte GameType = 1;
int GameLevel = 0;
unsigned int GameRand = 777;
unsigned long ActiveTime; // Global Game Timer

bool ButtonStatus[7] = {false, false, false, false};

// Define the order of the pins in the display so that they are ordered according to the universal convention [OPTIONAL]
byte pin_leds[4] = {YEL_LED, GRN_LED, RED_LED, BLU_LED};

// Return Element Number for Color from "pin_leds"
int GetColorPin(byte LED_color)
{
  for (int i = 0; i < 4; i++)
  {
    if (pin_leds[i] == LED_color)
    {
      return i;
    }
  }
  return -1;
}

void displayMessage(int text, bool clearDisplay = true)
{
  if (clearDisplay == true)
  {
    display.clearDisplay();
    display.setCursor(0, 0);
  }
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);

  display.print(text);
  display.display(); // Show text
}

void displayMessage(String text, bool clearDisplay = true)
{
  if (clearDisplay == true)
  {
    display.clearDisplay();
    display.setCursor(0, 0);
  }
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);

  display.print(text);
  display.display(); // Show text
}

// Set Default Values
void CloseGame()
{
  GameState = 0;
  GameLevel = 0;
}