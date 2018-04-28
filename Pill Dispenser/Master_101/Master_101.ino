//FINAL DEMO CODE V1.0
//7/28/2017
//PILL DISPENSER

#include <Wire.h>
#include <CurieTime.h>
#include <LiquidCrystal.h>

int LP; //LED PIN
int MP; //Monday Pin Variable
int FP; // Friday Pin Variable
//Instantiate the lcd
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Pill Dispenser");

  Serial.begin(9600);
  Wire.begin();  
}

void loop()
{ 
  RunPillDays();
}

void RunPillDays()
{
  MP = 2; //REED PIN
  FP = 9;
  LP = 13; //LED PIN

  digitalWrite(LP, HIGH); 

  do{
     if(digitalRead(LP == HIGH)) // If the pin reads low, the switch is closed.
     {
      if(digitalRead(FP) == HIGH)//open lid
      {
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.println("Sending Signal for Friday Lid Open");
        Wire.beginTransmission(1);
        Wire.write('F');
        Wire.endTransmission();
        delay(500);
        digitalWrite(LP, LOW); // Turn the LED on
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.println("Signal Sent");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.println("Pill Dispenser");
        delay(2000);
        break;
      }
      /*
       *Methods for all the other days will go here and pins will need to be instantiated!
      else if(digitalRead(MP) == HIGH)
      {
        Serial.println("Sending Signal for Monday Lid Open");
        Wire.beginTransmission(1);
        Wire.write('M');
        Wire.endTransmission();
        delay(500);
        digitalWrite(LP, LOW); // Turn the LED on
        break;
      }
      */
    } 
  }while(digitalRead(LP==LOW));
}
