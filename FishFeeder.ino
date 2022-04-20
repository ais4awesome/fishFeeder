#include <Dusk2Dawn.h>
#include <RTClib.h>

RTC_DS1307 rtc;

// Multiple instances can be created. Arguments are longitude, latitude, and
// time zone offset in hours from UTC.
// The first two must be in decimal degrees (DD), e.g. 10.001, versus the more
// common degrees, minutes, and seconds format (DMS), e.g. 10° 00′ 3.6″. The
// time zone offset can be expressed in decimal fractions, e.g. "5.75" for
// Nepal Standard Time, in the few cases where the zones are offset by 30 or
// 45 minutes.
// HINT: An easy way to find the longitude and latitude for any arbitrary
// location is to find the spot in Google Maps, right click the place on the
// map, and select "What's here?". At the bottom, you’ll see a card with the
// coordinates.
Dusk2Dawn chickenCoop(38.515710, -90.318972, -6);

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
      feedDay = 19,
      feedHr = 22,
      feedMin = 21;
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
    Serial.println("feeding fish!");
    int i;
    i=0;
    while(i<NUMBER_OF_STEPS_PER_REV)
      {
      onestep();
      i++;
      }
  }
}
