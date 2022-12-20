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
        progress = (progress + 10);
        displayMessage("Tempo: ");
        drawProgressbar(0, 20, progress); // declare the graphics fillrect(int x, int y, int width, int height)
        display.display();

        delay(10);
      }

      if (a == 0)
      { // Get Button Status
        a = getPressedButton();

        if (a == -1)
        {
          GameOver = true;
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
      if (interval < 1000)
      {
        interval = interval - 20;
      }
      if (interval < 500)
      {
        interval = interval - 10;
      }

      else
      {

        interval = interval - 100;
      }
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

    PowerOffButtonLED();
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

  GameOver = shouldReplay();
  if (GameOver)
  {
    displayMessage(F(" Adeus "));
    delay(1000);
    CloseGame();
  }
  else
  {
    displayMessage(F(" Vamos la! "));
    delay(1000);
  }
  return;
}
