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

  displayMessage(F("Get Ready..."));
  delay(2000);
  displayMessage(F("START!"));

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
        drawProgressbar(0, 20, 120, 10, progress); // declare the graphics fillrect(int x, int y, int width, int height)
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
      displayMessage(F("    BOA!!    "));
    }
    else if (a == 0)
    {
      GameOver = true;
      displayMessage(F(" PERDESTE! "));
    }

    // Change Level
    switch (GameScore)
    {
    case 5:
      interval = interval - 100;
      displayMessage(F("   !LEVEL UP!   "));
      break;
    case 10:
      interval = interval - 100;

      displayMessage(F("  !NEXT LEVEL!  "));
      break;
    case 20:
      interval = interval - 50;

      displayMessage(F("   IT'S 100!!   "));
      break;
    case 30:
      interval = interval - 50;

      displayMessage(F("REGARDS FOR YOU!"));
      break;
    case 50:
      interval = interval - 50;

      displayMessage(F("  !200 CLICKZ!  "));
      break;
    case 100:
      interval = interval - 50;

      displayMessage(F("  PROFi LEVEL!  "));
      break;
    case 200:
      interval = interval - 50;

      displayMessage(F("DON'T BREAKE ME!"));
      break;
    case 500:
      interval = interval - 50;

      displayMessage(F(" YOU ARE CRAZY! "));
      break;
    }

    delay(interval); // Keep Calm and Eat TWIX
    //  Show Current Score
    displayMessage(F("RESULTADO: "));
    displayMessage(GameScore, false);
  } // end while Game

  // Show Final Score
  displayMessage(F("   ACABOU   "));

  displayMessage(F("RESULTADO FINAL:"));
  displayMessage(GameScore, false);

  delay(3000);
  CloseGame();
  return;
}
