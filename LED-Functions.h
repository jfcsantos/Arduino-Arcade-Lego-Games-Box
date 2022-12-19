// Init LED Array
bool status_leds[4] = {false, false, false, false};

// Power On Button LEDs
void PowerOnButtonLED()
{
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(pin_leds[i], (status_leds[i]) ? HIGH : LOW);
  }
}

// Set Active Button LED
void SetButtonLED(byte LED_color, bool power = true)
{
  int i = -1;
  i = GetColorPin(LED_color);
  if (i >= 0)
  {
    status_leds[i] = !status_leds[i];
  }
  if (power)
  {
    PowerOnButtonLED();
  }
}

// Power Off Button LEDs
void PowerOffButtonLED()
{
  for (int i = 0; i < 4; i++)
  {
    status_leds[i] = false;
  }
  PowerOnButtonLED();
}

// Play Color and Blink Button
void PlayColor(byte LED_color)
{
  SetButtonLED(LED_color);

  // BUZZ sound
  int note = 0;

  switch (LED_color)
  {
  case BLU_LED:
    note = BLU_SOUND;
    break;
  case YEL_LED:
    note = YEL_SOUND;
    break;
  case RED_LED:
    note = RED_SOUND;
    break;
  case GRN_LED:
    note = GRN_SOUND;
    break;
  }

  tone(PIEZO, note, 100);
}

int getPressedButton()
{

  if (digitalRead(RED_BTN) == LOW && digitalRead(YEL_BTN) == LOW)
  {
    return -1;
  }
  if (digitalRead(GRN_BTN) == LOW)
  {
    return GRN_LED;
  }
  if (digitalRead(RED_BTN) == LOW)
  {
    return RED_LED;
  }
  if (digitalRead(YEL_BTN) == LOW)
  {
    return YEL_LED;
  }
  if (digitalRead(BLU_BTN) == LOW)
  {
    return BLU_LED;
  }

  return 0;
}
