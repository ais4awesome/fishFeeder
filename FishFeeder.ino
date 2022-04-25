#include <RTClib.h>

RTC_DS1307 rtc;

void setup() 
{
  // Clear the Serial buffer
  Serial.flush();
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);
  rtc.begin();
  Serial.begin(9600);

  #define A 2
  #define B 3
  #define C 4
  #define D 5
  #define NUMBER_OF_STEPS_PER_REV 512

  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  pinMode(8, OUTPUT);

  // Arduino is dumb and cant detect usb connection. Uncomment to set time after changing rtc battery.
  // set time to current system time.
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
  // Following is to set specific date and time
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

}

//*****************************************************************************************

void feedFish(const int hr, const int min, const int feedHr, const int feedMin);


//*****************************************************************************************

void loop() 
{
  DateTime currTime = rtc.now();
  int mon = (currTime.month()),
      day = (currTime.day()),
      hr = (currTime.hour()),
      min = (currTime.minute()),
      sec = (currTime.second()),
      feedMon = 4,
      feedDay = 25,
      feedHr = 8,
      feedMin = 3;
  String
    feedMonStr = String(feedMon),
    feedDayStr = String(feedDay),
    feedHrStr = String(feedHr),
    feedMinStr = String(feedMin),
    monStr = String(mon),
    dayStr = String(day),
    hrStr = String(hr),
    minStr = String(min),
    currStr = String("Current date and time: \t" + monStr + "/" + dayStr + "  " + hrStr + ":" + minStr),
    feedStr = String("Feeding date and time: \t" + feedMonStr + "/" + feedDayStr + "  " + feedHrStr + ":" + feedMinStr);

  Serial.println(currStr);
  Serial.println(feedStr);
  Serial.println("**************************************");

  feedFish(mon, day, hr, min, feedMon, feedDay, feedHr, feedMin);
     
  delay(15000);
}

//*********************************************************************************************

void write(int a,int b,int c,int d){
digitalWrite(A,a);
digitalWrite(B,b);
digitalWrite(C,c);
digitalWrite(D,d);
}

//*********************************************************************************************

void onestep(){
write(1,0,0,0);
delay(5);
write(1,1,0,0);
delay(5);
write(0,1,0,0);
delay(5);
write(0,1,1,0);
delay(5);
write(0,0,1,0);
delay(5);
write(0,0,1,1);
delay(5);
write(0,0,0,1);
delay(5);
write(1,0,0,1);
delay(5);
}

//*********************************************************************************************

void feedFish(const int mon, const int day, const int hr, const int min, const int feedMon, const int feedDay, const int feedHr, const int feedMin)
{
  if(mon == feedMon && day == feedDay && hr == feedHr && min == feedMin)
  {
    digitalWrite(8, HIGH);
    delay(1000);
    Serial.println("Feeding fish!");
    int i;
    i=0;
    while(i<NUMBER_OF_STEPS_PER_REV)
      {
      onestep();
      i++;
      }
     digitalWrite(13, LOW);
  }
}