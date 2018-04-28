//FINAL DEMO CODE V1.0
//7/28/2017
//PILL DISPENSER

#include <Wire.h>
#include <SPI.h>
#include <DS3231.h>
#include <SoftwareSerial.h>

Time t;
DS3231 rtc(SDA, SCL);
String DOW="";
String HOUR="";
String MIN="";
String RTCDOW="";
String RTCHour="";
String RTCMin ="";
String temp="";  // Temporary Variable to add time to as a string
String temp2="";  // Temporary Variable to add time to as a string
char timedatebuf[65]; // Temporary Variable to add time to as a string
const int buzzer = 9; // Buzzer to arduino pin 9
const byte slaveId = 1; // Slave ID for Arduino Uno for receiving

void setup()
{  
  Serial.begin(9600);
  rtc.begin();
  
  //setYourTime();
  showTime();
  
  //Wire.begin(slaveId); 
  //Wire.onReceive(receiveEvent);
 
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);    
  Serial.println("\n");
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an out

  setUserTime();
}
  ////////////////////////////////////////////////////////////////////

void loop()
{
  //FOR MORE THAN ONE DAY => Make variables for D2, D3 etc and in loop do check for either or days
  //Set the time for that specific day if its monday then change the hour and min vars
  showTime();
  setBuzzer();
}
  ////////////////////////////////////////////////////////////////////

void Buzzer()
{
    Serial.println("DOW BUZZER");
    tone(buzzer, 1000); // Send 1KHz sound signal...
    digitalWrite(13,HIGH );    
    delay(1000);        // ...for 1 sec
    digitalWrite(13,LOW);    
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec
}
  ////////////////////////////////////////////////////////////////////

void setYourTime()
{
  rtc.setDOW(FRIDAY);     // Set Day-of-Week to SUNDAY
  rtc.setTime(2, 23, 50);   // Set the time to 12:00:00 (24hr format)
  rtc.setDate(7, 28, 2017);   // Set the date to January 1st, 2014
  Serial.println("Time Set!");
}
  ////////////////////////////////////////////////////////////////////

void showTime()
{
  Serial.print("Time: ");
  Serial.print(rtc.getTimeStr());
  Serial.print(" ");
  Serial.print(rtc.getDOWStr());
}
  ////////////////////////////////////////////////////////////////////

void setUserTime()
{
  Serial.println("Enter Day:\n ");  
  while (Serial.available()==0)  
  {                                       //Wait for user input  
    
  }  
  DOW = Serial.readString();  //Reading the Input string from Serial port.
  DOW.trim();
  
  Serial.println("-------------------------");  //Showing the details

  while(Serial.available()==0)  
  {  
    break;
  } 

  Serial.println("Enter Hour:\n ");  

  while (Serial.available()==0)  
  {                                       //Wait for user input  

  }  
  HOUR = Serial.readString();  //Reading the Input string from Serial port.
  HOUR.trim();
  temp = HOUR;
  while(Serial.available()==0)  
  {  
    break;
  } 

  Serial.println("Enter Minutes:\n ");  

  while (Serial.available()==0)  
  {     
    //Wait for user input  
  }  
  MIN = Serial.readString();  //Reading the Input string from Serial port.
  MIN.trim();
  temp2 = MIN.toInt();
  while(Serial.available()==0)  
  {  
    break;
  } 
}
  ////////////////////////////////////////////////////////////////////

void setBuzzer()
{
  t = rtc.getTime();
  RTCDOW =  String(rtc.getDOWStr());
  RTCDOW.trim();
  RTCHour = String(t.hour);
  RTCHour.trim();
  RTCMin = String(t.min);
  RTCMin.trim();
  String RTCsec = String(t.sec);
  String SEC="0";

  RTCsec.trim();
  Serial.print(RTCHour + "<- Hour ->"+ HOUR + "\n");
  Serial.print(RTCMin + "<- MINS ->"+ MIN +"\n");

  if(RTCMin.toInt() == temp2.toInt()+1)
  {
    Serial.println("Setting MIN to: "+ temp2);
    MIN = temp2; 
  }

  if(RTCDOW.equalsIgnoreCase(DOW))
  { 
    if(RTCHour.equalsIgnoreCase(HOUR))
    { 
      if(RTCMin.equalsIgnoreCase(MIN))
      {  
        Buzzer();
        Wire.begin(slaveId); 
        Wire.onReceive(receiveEvent);
      }  
    }
  }//END LOOP
  delay(1000);
  Serial.println("\n");
}
  ////////////////////////////////////////////////////////////////////

void receiveEvent(int howMany)
{
  char inChar;
  
  while(Wire.available() > 0)
  {
    inChar = Wire.read(); 
    Serial.println(rtc.getDOWStr());

    if(rtc.getDOWStr() == "Monday")
    {
      if (inChar == 'M')
      {
        digitalWrite(13, HIGH);
        sendEmailSD();
      }//end if
    }
    if(rtc.getDOWStr() == "Tuesday")
    {
      if (inChar == 'T')
      {
        digitalWrite(13, HIGH);
        sendEmailSD();
      }
    }//end if
    if(rtc.getDOWStr() == "Wednesday")
    {
      if (inChar == 'W')
      {
        digitalWrite(13, HIGH);
        sendEmailSD();
      }
    }//end if

    if(rtc.getDOWStr() == "Thursday")
    {
      if (inChar == 'R')
      {
        digitalWrite(13, HIGH);
        sendEmailSD();
      }
    }//end if

    if(rtc.getDOWStr() == "Friday")
    {
      if (inChar == 'F')
      {
        digitalWrite(13, HIGH);
        sendEmailSD();
      }
    }//end if
    
    if(rtc.getDOWStr() == "Saturday")
    {
      if (inChar == 'S')
      {
        digitalWrite(13, HIGH);
        sendEmailSD();
      }
    }
    if(rtc.getDOWStr() == "Sunday")
    {
      if (inChar == 'U')
      {
        digitalWrite(13, HIGH);
        sendEmailSD();
      }
    }//end if
    
  }//end while
}//end method
  ////////////////////////////////////////////////////////////////////

void sendEmailSD()
{  
  t = rtc.getTime();
  sprintf(timedatebuf, "The pill was taken at the time: %02d:%02d:%02d on the day: %02d/%02d/%02d", t.hour, t.min, t.sec, t.date, t.mon, t.year);
  Serial.print(timedatebuf);
  Serial.println("SEND EMAIL AND SAVE ON SD CARD LOG");
  delay(1000);
  digitalWrite(13, LOW);
  //HOUR = "";
  MIN = "";
}//end methodThursd

