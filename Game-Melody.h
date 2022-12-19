// Main Game Function
void MelodyGame()
{
  bool GameOver = false;

  GameType = 4;
  // Welcome
  displayMessage(F("  Musica   "));
  PowerOffButtonLED();
  delay(1000);
  while (!GameOver) // BLACK button press
  {
    int a = 0;
    while (a == 0)
    {
      a = getPressedButton();

      if (a == -1)
      {
        GameOver = true;
        break;
      }
    }

    // Play Color if Press Button
    if (a != 0)
    {
      PlayColor(a);
      delay(100);
    }

    PowerOffButtonLED();
  }

  displayMessage(F("Adeus ;)"));
  delay(3000);
  CloseGame();
  return;
}
