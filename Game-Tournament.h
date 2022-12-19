void TournamentGame()
{
  GameType = 3;
  GameLevel = 0;
  int GameRate[4] = {0, 0, 0, 0};
  int interval = 10000;
  unsigned long previousMillis = 0;
  unsigned long currentMillis = 0;

  while (GameLevel < 5)
  {
    GameLevel++;

    // Init state
    PowerOffButtonLED();

    displayMessage(F("Quem vai mais rapido?"));
    delay(2000);
    if (GameLevel == 5)
    {
      displayMessage(F("Ultima ronda..."));
    }
    else
    {
      displayMessage(F("Preparados..."));
    }
    delay(random(1000, 3000)); // random delay

    displayMessage(F(" VAI!! "));
    if (GameSound)
    {
      tone(PIEZO, GRN_SOUND, 500);
    }
    int a = 0;
    currentMillis = previousMillis = millis();

    while (a == 0 && (currentMillis - previousMillis) <= interval)
    {
      currentMillis = millis();
      a = getPressedButton();
    }

    if ((currentMillis - previousMillis) > interval)
    {
      CloseGame();
      return;
    }

    // Play Color if Press Button
    if (a != 0)
    {
      PlayColor(a);
      delay(1000);
    }

    // Level Result
    displayMessage(F("Vencedor: "));

    switch (a)
    {
    case YEL_LED:
      displayMessage(F("Amarelo"), false);
      break;
    case GRN_LED:
      displayMessage(F("Verde"), false);
      break;
    case RED_LED:
      displayMessage(F("Vermelho"), false);
      break;
    case BLU_LED:
      displayMessage(F("Azul"), false);
      break;
    }
    delay(2000);

    SetButtonLED(a);
    GameRate[GetColorPin(a)]++;
    PowerOnButtonLED();
    delay(1000);
  } // end for WHILE game

  // Show Absolute Winner
  PowerOffButtonLED();
  int maxscore = 0;
  for (int i = 0; i < 4; i++)
  {
    if (GameRate[i] > maxscore)
    {
      maxscore = GameRate[i];
    }
  }
  for (int i = 0; i < 4; i++)
  {
    if (GameRate[i] == maxscore)
    {
      status_leds[i] = true;
    }
  }
  displayMessage(F("O campeao!"));
  PowerOnButtonLED();
  delay(3000);
  PowerOffButtonLED();
  CloseGame();
}
