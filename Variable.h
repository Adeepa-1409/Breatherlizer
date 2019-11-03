int TIME_UNTIL_WARMUP = 10;
unsigned long time;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display



// Measurement
int TIME_UNTIL_MEASURE = 1;
unsigned long measurement_start;
unsigned long time1;

//Timer
float pre_min=0;
float pre_sec=0;
float now_sec=0;
float now_min=0;
float new_cycle=0;

//DHT 
DHT dht(8, DHT22);
float int_temp=0;
float int_hum=0;
float final_temp=0;
float final_hum=0;

//timer activation
#include <RTClib.h>
RTC_DS1307 RTC;

// Sensor readings
int analogPin = A0;
float val = 0.00;

// Buzzer
const int buzzerPin = 6;

// Button
const int buttonPin = 2;


//Relay
const int relay = 5;
int t_in = 5;

//MQ3
const int mq3 = 4;

// Modes
bool measurement_mode;
bool measurement_done;
bool printas = false;
volatile bool start1 = true;

int count=0;
