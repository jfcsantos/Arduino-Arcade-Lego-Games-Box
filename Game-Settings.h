#define GAME_VER "v.4"

#define RANDOM_PIN 26

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3C

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
bool GameSound = true;
int GameLevel = 0;
unsigned int GameRand = 777;

String GameTitle[] = {"Memoria", "Tempo", "Torneio", "Musica"};
String GuideMsg[] = {"Azul: muda jogo >", "Amarelo: muda jogo <", "Verde: jogar", "Vermelho: som on/off"};

// number of items in an array
#define ARRCOUNT(arg) ((unsigned int)(sizeof(arg) / sizeof(arg[0])))

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

// Init LED Array
bool status_leds[4] = {false, false, false, false};

// Power On Button LEDs
void PowerOnButtonLED()
{
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(pin_leds[i], (status_leds[i]) ? HIGH : LOW);
  }
}

// Set Active Button LED
void SetButtonLED(byte LED_color, bool power = true)
{
  int i = -1;
  i = GetColorPin(LED_color);
  if (i >= 0)
  {
    status_leds[i] = !status_leds[i];
  }
  if (power)
  {
    PowerOnButtonLED();
  }
}

// Power Off Button LEDs
void PowerOffButtonLED()
{
  for (int i = 0; i < 4; i++)
  {
    status_leds[i] = false;
  }
  PowerOnButtonLED();
}

// Play Color and Blink Button
void PlayColor(byte LED_color)
{
  SetButtonLED(LED_color);

  // BUZZ sound
  int note = 0;

  switch (LED_color)
  {
  case BLU_LED:
    note = BLU_SOUND;
    break;
  case YEL_LED:
    note = YEL_SOUND;
    break;
  case RED_LED:
    note = RED_SOUND;
    break;
  case GRN_LED:
    note = GRN_SOUND;
    break;
  }
  if (GameSound)
  {
    tone(PIEZO, note, 100);
  }
}

int getPressedButton()
{

  if (digitalRead(RED_BTN) == LOW && digitalRead(YEL_BTN) == LOW)
  {
    return -1;
  }
  if (digitalRead(GRN_BTN) == LOW)
  {
    return GRN_LED;
  }
  if (digitalRead(RED_BTN) == LOW)
  {
    return RED_LED;
  }
  if (digitalRead(YEL_BTN) == LOW)
  {
    return YEL_LED;
  }
  if (digitalRead(BLU_BTN) == LOW)
  {
    return BLU_LED;
  }

  return 0;
}

void displayMessage(int text, bool clearDisplay = true)
{
  if (clearDisplay == true)
  {
    display.clearDisplay();
  }

  display.setCursor((SCREEN_WIDTH - 2) / 2, SCREEN_HEIGHT / 2 + 2);
  display.print(text);
  display.display(); // Show text
}

void displayMessage(String text, bool clearDisplay = true)
{
  int16_t x1;
  int16_t y1;
  uint16_t width;
  uint16_t height;

  display.getTextBounds(text, 0, 0, &x1, &y1, &width, &height);

  if (clearDisplay == true)
  {
    display.clearDisplay();
    display.setCursor((SCREEN_WIDTH - width) / 2, 0);
  }

  display.println(text); // text to display
  display.display();     // Show text
}

void drawProgressbar(int x, int y, int progress)
{
  progress = progress > 100 ? 100 : progress; // set the progress value to 100
  progress = progress < 0 ? 0 : progress;     // start the counting to 0-100
  float bar = ((float)(SCREEN_WIDTH - 1) / 100) * progress;
  display.drawRect(x, y, SCREEN_WIDTH, 10, WHITE);
  display.fillRect(x + 2, y + 2, bar, 10 - 4, WHITE); // initailize the graphics fillRect(int x, int y, int width, int height)
}

// Set Default Values
void CloseGame()
{
  GameState = 0;
  GameLevel = 0;
}

bool shouldReplay()
{
  bool replayPrompt = false;
  bool GameOver = true;
  displayMessage("Outra vez?");
  SetButtonLED(pin_leds[GRN_LED]);
  SetButtonLED(pin_leds[RED_LED]);
  delay(2000);
  while (!replayPrompt)
  {
    int a = getPressedButton();
    if (a == GRN_LED)
    {
      GameOver = false;
      replayPrompt = true;
    }
    if (a == RED_LED)
    {
      replayPrompt = true;
    }
  }
  PowerOffButtonLED();
  delay(1000);
  return GameOver;
}