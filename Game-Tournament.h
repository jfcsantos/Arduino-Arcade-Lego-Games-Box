void TournamentGame()
{
  GameType = 3;
  GameLevel = 0;
  int GameRate[4] = {0, 0, 0, 0};
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

    int a = 0;
    while (a == 0)
    {
      a = getPressedButton();

      if (a == -1)
      {
        CloseGame();
        return;
      }
    }

    // Play Color if Press Button
    if (a != 0)
    {
      PlayColor(a);
      delay(1000);
    }

    // Level Result
    displayMessage(F("Vencedor: "));
    delay(2000);

    switch (a)
    {
    case YEL_LED:
      displayMessage(F("Amarelo"));
      break;
    case GRN_LED:
      displayMessage(F("Verde"));
      break;
    case RED_LED:
      displayMessage(F("Vermelho"));
      break;
    case BLU_LED:
      displayMessage(F("Azul"));
      break;
    }
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
  displayMessage(F("O campeao: "));
  PowerOnButtonLED();
  delay(3000);
  PowerOffButtonLED();
  CloseGame();
}
