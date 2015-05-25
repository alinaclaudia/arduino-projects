int led_status[11];

#include <SoftwareSerial.h>
void setup() {
    // open the serial port:
  Serial.begin(9600);

  // initialize digital pins as an output.
  int i ;
    for(i=3; i<=13; i++){
     pinMode(i, OUTPUT);
     digitalWrite(i, LOW);
     led_status[i-2]=0;
    }
  status = LOW;
}

void commute(int led_number)
{
  if (led_number >0 && led_number <11)
  {
    if(led_status[led_number] == LOW) led_status[led_number] = HIGH;
   else led_status[led_number] = LOW;
  }
}

char x; // current character received
char lc; // last character received

void light_leds()
{
  int i;
  for(i=1; i<=10; i++)
  {
    // 14 -i = LED number
    // LED 1: 14-1 = 13 (Pin 13)
    // LED 5: 14-5 = 9  (Pin  9)
    digitalWrite(14-i, led_status[i]);
  }  
}

void project(){
  x= Serial.read();

  if(x!=lc)
  {
     if(x=='0') 
     	commute(10);
     // Getting digits from ASCII code --> '5' - '0' = 5
     if(x>='1' && x<= '9')  
     	commute(x-'0'); 
  }
  lc=x;
  //  Light the leds !!! (as in led_status[])
  light_leds();
}

// the loop function runs over and over again forever
void loop() {
  // keeping it tidy
  project();
}