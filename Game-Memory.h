///////////////////// Memory game ////////////////////////
void MemoryGame()
{
  GameType = 1;
  GameLevel = 0;
  bool GameOver = false;
  byte CurrColor = 0;
  int interval = 650;
  int a = 0;

  while (!GameOver)
  {
    PowerOffButtonLED();
    GameLevel++;
    displayMessage("Nivel #");
    displayMessage(GameLevel, false);
    delay(2000);

    // Change Spped via Interval
    if ((GameLevel % 5 == 0) && (GameLevel <= 30))
    {
      interval = interval - (GameLevel / 5) * 50;
    }

    // Generate Melody
    randomSeed(GameRand); // Get Current Random Series

    for (int i = 0; i < GameLevel; i++)
    {
      // Get Random Button
      CurrColor = random(0, 4);
      PlayColor(pin_leds[CurrColor]);
      delay(interval);
      PowerOffButtonLED();
      delay(100);
    }

    // Show Check Screen
    displayMessage("Agora repete! ");

    // Check Melody
    randomSeed(GameRand);
    for (int i = 0; i < GameLevel; i++)
    {
      // Get Random Button
      CurrColor = random(0, 4);

      a = 0;
      while (a == 0)
      {
        a = getPressedButton();
      }
      // Play Color if Press Button
      if (a != 0)
      {
        PlayColor(a);
        delay(interval);
      }

      PowerOffButtonLED();

      if ((a == pin_leds[CurrColor]) && (i == GameLevel - 1))
      {
        displayMessage(F(" Boa!! "));
      }

      if ((a != 0) && (a != pin_leds[CurrColor]))
      {
        GameOver = true;
        if (GameSound)
        {

          tone(PIEZO, BAD_SOUND, 500);
        }
        displayMessage(F(" Ohh :( "));
      }

      // Clear Button Status
      a = 0;
      if (GameOver)
      {
        GameLevel--;
        break;
      } // Exit from Attempt if GameOver
    }
    delay(1500); // Get PAUSE
  }

  // Show Final Score
  displayMessage(F(" Fim "));

  displayMessage(F("Resultado: "));
  displayMessage(GameLevel, false);
  delay(3000);

  GameOver = shouldReplay();
  if (GameOver)
  {
    displayMessage(F(" Adeus "));
    CloseGame();
    delay(2000);
  }
  else
  {
    displayMessage(F(" Vamos la! "));
    delay(1000);
  }
  return;
}
