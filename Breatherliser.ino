/*Name: Adeepa Rajamanthri
 * Purpose: A Breatherlizer
 * Date: 3/11/2019
 * 
 */

// Libraries
#include <Wire.h> 
#include <TroykaDHT.h>
#include <LiquidCrystal_I2C.h>
#include"LCD.h"

void setup()   {  
  
  // Serial
  Serial.begin(57600);
  Wire.begin();
  RTC.begin(); // load the time from your computer.
  dht.begin(); //initialise the temp sensor
  
  // intialise output pins
  pinMode(buzzerPin, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(relay, OUTPUT);//relay select
  pinMode(mq3, OUTPUT);//Alcohol select
  
  // Init LCD
  lcd.begin(); //initilise lcd
  lcd.backlight(); // turn on backlight
  pinMode(7, INPUT);//sets the pin as an input to the arduino

  //Checking if the timer is working
  if (! RTC.isrunning())
  {
    Serial.println("RTC is NOT running!");// This will reflect the time that your sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

}


void loop() {
  
  int button_state = digitalRead(buttonPin);// reading the button pin

  // if button is pressed
  if (button_state && !measurement_mode) 
  {
    lcd.clear();
    lcd.backlight();
    measurement_mode = true;
    measurement_start = millis()/1000;
    measurement_done = false;
    printas == false;
  }
  
  // Wait
  delay(100);

  // Get time
  time = millis()/1000;

  // if button is not pressed 
   if (measurement_mode == false && !measurement_done) {
     
     // Instruction    
     printPress();  
            printas == true;
   }

   //If button is pressed but measurement is not done
   if (measurement_mode && !measurement_done) 
   {
      // Instruction       
      printMeasure();  
      
      // powering up the alcohol sensor and dht
      digitalWrite(mq3, HIGH);
      dht.read();
      // get initial values for temp and hum
      int_temp = dht.getTemperatureC()/20;
      int_hum = dht.getHumidity()/20;

      //waiting to read
      waiting();
      
      // read measurements
      tone(buzzerPin, 2000);
      printMeasure(); 
      val = readAlcohol();
      
      //turning off measurement mode
      measurement_mode = false;
      measurement_done = true;
      noTone(buzzerPin);
      lcd.clear();
     
   }
   
   //measurement is done but not printed
   if(measurement_done && printas == false )
   { 
    // if the temperature change is positive
     if(final_temp >= 0.01)
     {
      val = val/10;
      Serial.print("BAC = ");
      printAlcohol(val);
      printas == true;
      if (start1 = true)
      {
       printAlcoholLevel(val);
       start1 = false;
      }
      wait_time();
     }
     else // if there is no temp change
     {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Please press the");
      lcd.setCursor(0,1);
      lcd.print("button again");
      delay(5000);
     }
    measurement_mode == false;
    measurement_done = false;
   }


}

void waiting()
{
  int i=0;
  lcd.clear();
  float progress_time=0;
  float time_at_start = 0;
  
  time1 = millis()/1000;
  time_at_start = time1;
  //count up for progress
  for (i=0 ; i<TIME_UNTIL_WARMUP; i++)
  {
    lcd.setCursor(0,0);
    progress_time = map(i , 0, TIME_UNTIL_WARMUP , 0, 100);
    printWarming(progress_time);
    delay(500);
  }
   lcd.clear();
  count++;
}


/*
 * Name: Adeepa 
 * function input:
 * function output: float
 * Purpose: reading the values and converting them
 * 
 */
float readAlcohol()
{
   
  // Number measurements
  int nb_measurements = 20;
  float measurements=0;
  float temp = 0;
  float humid = 0;
  float check =0;
  
  delay(1000);
  
  // Measure 2o times for accuracy
  for (int i = 0; i < nb_measurements; i++) 
  {
    dht.read();
    measurements = measurements + analogRead(analogPin);
    temp += dht.getTemperatureC();
    humid +=  dht.getHumidity();

    delay(100);
  } 
  // converting raw data into BAC values
  measurements = measurements/nb_measurements/1024.0*5.0;
  final_temp = (temp/18.5/nb_measurements) - int_temp;
  final_hum = (humid/18.5/nb_measurements) - int_hum;
  digitalWrite(mq3, LOW);

  return measurements;
 }
