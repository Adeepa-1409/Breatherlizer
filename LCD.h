
#include"TIME.h"


void relay_on();

/*Name: PrintWarming
 * input; float
 * output: void
 * Reason: print the warming up sign
 */
void printWarming(float progress)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Warming up: ");
  lcd.print(progress);
  lcd.print("%");
}

/* Name: PrintPress
 * input; vaid
 * output: void
 * Reason: print the press to start
 */
void printPress()
{
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Press to start ...");
}

/* Name: PrintMeasure
 * input; vaid
 * output: void
 * Reason: print the Measuring sign
 */
void printMeasure()
{
  lcd.setCursor(0,0);
  lcd.print("Breathe until");
  lcd.setCursor(0,1);
  lcd.print("the sound stops ...");
}

/* Name: Print Alcohol
 * input; float
 * output: void
 * Reason: print the Alcohol value
 */
void printAlcohol(float value)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BAC:");
  lcd.print(val);
  print_date_time();
}

/* Name: printAlcoholLevel
 * input; float
 * output: void
 * Reason: print the Alcohol level
 */
void printAlcoholLevel(float value)
{
  lcd.setCursor(0,1);
  if(value < 0.05)
  {
      lcd.print("You are sober.");
      delay(5000);
      digitalWrite(relay, HIGH);
      relay_on();
      noTone(buzzerPin);
      digitalWrite(relay, LOW);
  }
  if (value >= 0.05)
  {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Driving is ");
      lcd.setCursor(0,1);
      lcd.print("Prohibited");
      delay(5000);
  }

}

 /* Name: relay_on()
 * input; void
 * output: void
 * Reason: Sets the relay on or off depending on the BAC value
 */
void relay_on()
{
  lcd.clear();
  int display_time;
  int count;
  int sound1 = 10;
  
  lcd.setCursor(0,0);
  lcd.print("pls start Car");
  
  for(int i=0;i<(t_in+1);i++)
  {
    lcd.setCursor(0,1);
    //sound on
    tone(buzzerPin, 1000);
    sound1 = sound1 + i*((1000-10)/t_in); //changing the sound tone
    delay(500);
    //sound off
    noTone(buzzerPin);
    delay(500);
    display_time = t_in - i;
    lcd.print(display_time);
  }
  
  lcd.clear();
}
 
