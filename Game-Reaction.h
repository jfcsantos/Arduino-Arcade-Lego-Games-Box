void ReactionGame()
{
  GameType = 2;
  bool GameOver = false;
  byte CurrColor = 0;
  unsigned long previousMillis = 0;
  unsigned long currentMillis = 0;
  int GameScore = 0;
  int interval = 2000;
  int a = 0;

  displayMessage(F("Preparado..."));
  delay(2000);
  displayMessage(F("VAI!!"));

  while (!GameOver)
  {
    PowerOffButtonLED();

    // Get Random Button
    CurrColor = random(0, 4);
    // and Play Color
    PlayColor(pin_leds[CurrColor]);
    currentMillis = previousMillis = millis();

    // Waiting User Action
    a = 0;
    int progress = 0;
    display.clearDisplay();
    while (currentMillis - previousMillis <= interval)
    {
      SetButtonLED(pin_leds[CurrColor]);
      // // Fill Line
      if ((currentMillis - previousMillis) % (interval / 16) == 0)
      {
        progress = (progress + 10) % 110;
        drawProgressbar(0, 20, 110, 10, progress); // declare the graphics fillrect(int x, int y, int width, int height)
        display.display();

        delay(10);
      }

      if (a == 0)
      { // Get Button Status
        a = getPressedButton();

        if (a == -1)
        {
          CloseGame();
          return;
        }

        if (a > 0)
        {
          break;
        }
      }
      currentMillis = millis();
    }

    // Show Status Slogan
    if ((a != 0) && (a != pin_leds[CurrColor]))
    {
      GameOver = true;
      displayMessage(F("Ohh :( "));
      if (GameSound)
      {
        tone(PIEZO, BAD_SOUND, 500);
      }
    }
    if (a == pin_leds[CurrColor])
    {
      GameScore++;
      interval = interval - 100;
    }
    else if (a == 0)
    {
      GameOver = true;
      displayMessage(F("Tenta outra vez!"));
      if (GameSound)
      {
        tone(PIEZO, BAD_SOUND, 500);
      }
    }

    delay(1000);
    //  Show Current Score
    displayMessage(F("Resultado: "));
    displayMessage(GameScore, false);
    delay(interval);
  } // end while Game

  // Show Final Score
  displayMessage(F("Resultado final: "));
  displayMessage(GameScore, false);
  delay(3000);

  bool replayPrompt = false;
  displayMessage("Outra vez?");
  SetButtonLED(pin_leds[GRN_LED]);
  SetButtonLED(pin_leds[RED_LED]);
  delay(2000);
  while (!replayPrompt)
  {
    a = getPressedButton();
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
  if (GameOver)
  {
    CloseGame();
  }
  return;
}
