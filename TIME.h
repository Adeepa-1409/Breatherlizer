#include "Variable.h"

 /* Name: print_date_time()
 * input; void
 * output: void
 * Reason: Print the date and time and the BAC value on serial
 */
void print_date_time()
{
  //get the time now
  DateTime now = RTC.now();
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print(' ');
  Serial.print("BAC Value: ");
  Serial.print(val);
  Serial.println();
}

 /* Name: wait_time()
 * input; void
 * output: void
 * Reason: Countdown to the next measure
 */
void wait_time()
{
  DateTime now = RTC.now();
  pre_min = now.minute();
  pre_sec = now.second();
  int sound = 0;

  for(int r=600; r>0 ; r--)//counting down for 10 min until the next read
  {
    now_sec = r % 60;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Time to measure");

    lcd.setCursor(0,1);
    
    lcd.print("min: ");
    Serial.print("min: ");
    lcd.print(int(r/60));
    Serial.print(int(r/60));

    lcd.print(" ");
    lcd.print("sec: ");
    Serial.print("  sec: ");
    lcd.print(int(now_sec));
    Serial.println(int(now_sec));
    delay(1000);

    if(r >= 60)
    {
      
      lcd.noBacklight();
    }
    else // the buzzer increase in volume and frequency as the timer goes down
    {
      lcd.backlight();
      if ( (r % 2) == 0)
      {
        tone(buzzerPin, sound);
      }
      else
      {
        noTone(buzzerPin);
        sound += 100;
      }
      int button_state = digitalRead(buttonPin);
      measurement_mode = true;
      measurement_done = false;
      printas == false;

    }
    
  }
}
