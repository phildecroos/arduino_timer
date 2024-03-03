#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

int currentTime = 0, referenceTime = 0, adjustmentFromRef = 0, timeInSettings = 0;
int hours = 0, minutes = 0, seconds = 0;
int setting = 3, selection = 1;

void displayTime(int hours, int minutes, int seconds)
{
  // display the current time on the display

  if (hours > 9)
  {
    lcd.print(hours);
  }
  else
  {
    lcd.print("0");
    lcd.print(hours);
  }

  lcd.print(":");

  if (minutes > 9)
  {
    lcd.print(minutes);
  }
  else
  {
    lcd.print("0");
    lcd.print(minutes);
  }

  lcd.print(":");

  if (seconds > 9)
  {
    lcd.print(seconds);
  }
  else
  {
    lcd.print("0");
    lcd.print(seconds);
  }
}

int updateTime()
{
  // update the time values

  seconds--;

  if (seconds < 0)
  {
    minutes--;
    if (minutes < 0)
    {
      hours--;
      if (hours < 0)
      {
        setting = 2;
        return 1;
      }
      minutes = 59;
    }
    seconds = 59;
  }

  return 1;
}

void changeTime(int unit, int change)
{
  if (unit == 1)
  {
    seconds += change;

    if (seconds >= 60)
    {
      seconds = 0;
    }
    else if (seconds <= 0)
    {
      seconds = 59;
    }
  }
  else if (unit == 2)
  {
    minutes += change;

    if (minutes >= 60)
    {
      minutes = 0;
    }
    else if (minutes <= 0)
    {
      minutes = 59;
    }
  }
  else if (unit == 3)
  {
    hours += change;

    if (hours >= 25)
    {
      hours = 0;
    }
    else if (hours <= 0)
    {
      hours = 24;
    }
  }
}

void setup()
{
  // initial program loop

  lcd.begin(16, 2);

  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
}

void loop()
{
  // main program loop

  for (int i = 0; i < 5; i++)
  {

    // display the pause screen
    if (setting == 1)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Paused  ");
      displayTime(hours, minutes, seconds);

      lcd.setCursor(0, 1);
      lcd.print("Cont.      Reset");

      if (selection == 1)
      {
        lcd.setCursor(5, 1);
        lcd.print("<-");

        if (digitalRead(9) == HIGH)
        {
          setting = 0;
        }
      }
      else if (selection == 2)
      {
        lcd.setCursor(9, 1);
        lcd.print("->");

        if (digitalRead(9) == HIGH)
        {
          seconds = 0;
          minutes = 0;
          hours = 0;

          selection = 1;
          setting = 3;
        }
      }

      if (digitalRead(8) == HIGH)
      {
        selection = 1;
      }

      if (digitalRead(10) == HIGH)
      {
        selection = 2;
      }
    }

    // display the done screen
    else if (setting == 2)
    {

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    00:00:00    ");
      lcd.setCursor(0, 1);
      lcd.print("      Done!     ");

      if (digitalRead(9) == HIGH)
      {
        seconds = 0;
        minutes = 0;
        hours = 0;
        selection = 1;
        setting = 3;
      }
    }

    // display the set time screen
    else if (setting == 3)
    {

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Set the ");
      displayTime(hours, minutes, seconds);

      lcd.setCursor(0, 1);
      lcd.print("Timer");

      if (selection == 1)
      {
        lcd.setCursor(14, 1);
        lcd.print("^^");

        if (digitalRead(9) == HIGH)
        {
          selection = 2;
        }
      }
      else if (selection == 2)
      {
        lcd.setCursor(11, 1);
        lcd.print("^^");

        if (digitalRead(9) == HIGH)
        {
          selection = 3;
        }
      }
      else if (selection == 3)
      {
        lcd.setCursor(8, 1);
        lcd.print("^^");

        if (digitalRead(9) == HIGH)
        {
          setting = 0;
        }
      }

      if (digitalRead(8) == HIGH)
      {
        changeTime(selection, -1);
      }

      if (digitalRead(10) == HIGH)
      {
        changeTime(selection, 1);
      }
    }

    // display the time remaining screen
    else
    {
      lcd.clear();
      lcd.setCursor(4, 0);
      displayTime(hours, minutes, seconds);

      if (digitalRead(9) == HIGH)
      {
        setting = 1;
        selection = 1;
      }
    }

    delay(200);
  }

  if (setting == 0)
  {
    updateTime();
  }
}
