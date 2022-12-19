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
      displayMessage(F(" OHH :( "));
      tone(PIEZO, BAD_SOUND, 500);
    }
    if (a == pin_leds[CurrColor])
    {
      GameScore++;
      displayMessage(F(" BOA!! "));
    }
    else if (a == 0)
    {
      GameOver = true;
      displayMessage(F(" PERDESTE! "));
      tone(PIEZO, BAD_SOUND, 500);
    }

    // Change Level
    switch (GameScore)
    {
    case 5:
      interval = interval - 100;
      displayMessage(F(" !SUBAA! "));
      break;
    case 10:
      interval = interval - 100;

      displayMessage(F("  !OUTRO NIVEL!  "));
      break;
    case 20:
      interval = interval - 50;
      displayMessage(F(" !SUBAA! "));
      break;
    case 30:
      interval = interval - 50;

      displayMessage(F("BOA!"));
      break;
    case 50:
      interval = interval - 50;

      displayMessage(F("  IMPRESSIONANTE!  "));
      break;
    case 100:
      interval = interval - 50;
      displayMessage(F("  !100 CLIQUES!  "));

      break;
    case 200:
      interval = interval - 50;

      displayMessage(F("CALMA!!!"));
      break;
    case 500:
      interval = interval - 50;

      displayMessage(F(" LOUCURA!!! "));
      break;
    }

    //  Show Current Score
    displayMessage(F("RESULTADO: "));
    displayMessage(GameScore, false);
    delay(interval);

  } // end while Game

  // Show Final Score
  displayMessage(F("ACABOU"));

  displayMessage(F("RESULTADO FINAL:"));
  displayMessage(GameScore, false);

  delay(3000);
  CloseGame();
  return;
}
