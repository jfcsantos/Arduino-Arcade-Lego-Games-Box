
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Game-Settings.h"
#include "LED-Functions.h"
#include "Game-Memory.h"
#include "Game-Reaction.h"
#include "Game-Melody.h"
#include "Game-Tournament.h"

///////////////////// Setup ////////////////////////
void setup()
{
  Serial.begin(9600);

  // LEDs are Outputs
  pinMode(GRN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YEL_LED, OUTPUT);
  pinMode(BLU_LED, OUTPUT);

  // Pushbuttons are Inputs with internal pullup resistors
  pinMode(GRN_BTN, INPUT_PULLUP);
  pinMode(RED_BTN, INPUT_PULLUP);
  pinMode(YEL_BTN, INPUT_PULLUP);
  pinMode(BLU_BTN, INPUT_PULLUP);

  // Buzzer is an Output
  pinMode(PIEZO, OUTPUT);

  GameRand = analogRead(RANDOM_PIN); // Select pseudo-random sequences

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);

  displayMessage("Simao diz");
  int count = 0;
  while (count < 10)
  {
    // Flash the LEDs in sequence
    for (int i = RED_LED; i >= BLU_LED; i--)
    {
      digitalWrite(i, HIGH);
      delay(100);
      digitalWrite(i, LOW);
    }
    count++;
  }
  delay(2000);
}

///////////////// Main Loop ///////////////////////////
void loop()
{

  // Let's Get It Started
  switch (GameState)
  {
  case 0:
  {
    unsigned long previousMillis = 0; // will store last time guide message was played
    int msgCount = 0;
    bool showGuide = true;
    GameState = GameType;

    while (digitalRead(GRN_BTN) == HIGH)
    {
      if (digitalRead(GRN_BTN) == LOW || digitalRead(YEL_BTN) == LOW || digitalRead(RED_BTN) == LOW || digitalRead(BLU_BTN) == LOW)
      {
        showGuide = false;
      }

      // Sound OFF/ON
      if (digitalRead(RED_BTN) == LOW)
      {
        GameSound = !GameSound;
        if (GameSound)
        {
          displayMessage(F("Som ON"));
        }
        else
        {
          displayMessage(F("Som OFF"));
        }
        delay(2000);
      }

      // Change game with Blue button
      if (digitalRead(BLU_BTN) == LOW)
      {
        GameState++;
        if (GameState > ARRCOUNT(GameTitle))
        {
          GameState = 1;
        }
      }
      // Change game with Yellow button
      if (digitalRead(YEL_BTN) == LOW)
      {
        GameState--;
        if (GameState < 1)
        {
          GameState = ARRCOUNT(GameTitle);
        }
      }

      if (showGuide)
      {
        // check to see if it's time to blink the LED; that is, if the difference
        // between the current time and last time you blinked the LED is bigger than
        // the interval at which you want to blink the LED.
        unsigned long currentMillis = millis();

        if (currentMillis - previousMillis >= 2000)
        {
          // save the last time you blinked the LED
          previousMillis = currentMillis;

          displayMessage(GuideMsg[msgCount]);
          msgCount++;
          if (msgCount >= ARRCOUNT(GuideMsg))
          {
            msgCount = 0;
          }
        }
      }
      else
      {
        displayMessage(GameTitle[GameState - 1]);
      }
    }
    break;
  }
  case 1: // Memory game
    MemoryGame();
    break;
  case 2: // Reaction game
    ReactionGame();
    break;
  case 3: // Tournament game
    TournamentGame();
    break;
  case 4: // Music game
    MelodyGame();
    break;
  default:
    GameState = 0;
    delay(3000);
    break;
  } // end GameState while
}
