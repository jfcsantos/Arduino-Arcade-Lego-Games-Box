// Main Game Function
void MelodyGame()
{
  int GAME_OVER = 0;
  GameType = 4;
  // Welcome
  displayMessage(F("  Musica   "));
  PowerOffButtonLED();
  delay(1000);
  while (GAME_OVER == 0) // BLACK button press
  {

    int a = 0;
    while (a == 0)
    {
      if (digitalRead(GRN_BTN) == LOW)
      {
        a = GRN_LED;
      }
      if (digitalRead(RED_BTN) == LOW)
      {
        a = RED_LED;
      }
      if (digitalRead(YEL_BTN) == LOW)
      {
        a = YEL_LED;
      }
      if (digitalRead(BLU_BTN) == LOW)
      {
        a = BLU_LED;
      }
      if (digitalRead(RED_BTN) == LOW && digitalRead(YEL_BTN) == LOW)
      {
        GAME_OVER = 1;
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

  displayMessage(F("   Adeus ;)   "));
  delay(3000);
  CloseGame();
  return;
}
