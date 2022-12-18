
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Game-Settings.h"
#include "LED-Functions.h"
#include "Game-Memory.h"

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

  displayMessage(" Boica diz!! ");
  delay(2000);
}

///////////////// Main Loop ///////////////////////////

void loop()
{
  // Let's Get It Started
  switch (GameState)
  {
  case 0:
    // GameState = GameType;
    displayMessage(" Carrega no verde!! ");

    Serial.println(digitalRead(GRN_BTN));
    Serial.println(GameState);

    // Flash the LEDs in sequence
    for (int i = RED_LED; i >= BLU_LED; i--)
    {
      digitalWrite(i, HIGH);
      delay(100);
      digitalWrite(i, LOW);
    }

    // Start game with Green button
    if (digitalRead(GRN_BTN) == LOW)
    {
      GameState = 1;
    }
    break;
  case 1: // Memory game
    MemoryGame();
    break;
  } // end GameState while
}
