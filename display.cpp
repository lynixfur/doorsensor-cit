#include <LiquidCrystal.h> 
int Contrast = 15;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// initial Time display is 00:00:00 PM
int h = 00;
int m = 00;
int s = 00;
int f = 0; //AM

//EXAMPLE DISPLAY OUTPUTS

// 31-MAY-2021
// 12:00:00PM [000]




void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(13,OUTPUT);
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
}

void loop() {
   s=s+1;
   if(s==60){
    s=0;
    m=m+1;
   }
   if(m==60)
   {
    m=0;
    h=h+1;
   }
   if(h==13)
   {
    h=1;
    f=f+1;
    if(f==2)f=0;
   }

  
     lcd.setCursor(0, 0);
     lcd.print("                ");
     lcd.setCursor(0, 0);
     if(h<10)lcd.print("0");
  lcd.print(h);
     lcd.print(":");
	 if(m<10)lcd.print("0");
  lcd.print(m);
     lcd.print(":");
     if(s<10)lcd.print("0");
  lcd.print(s);
     if(f==0) lcd.print("AM");
     if(f==1) lcd.print("PM");
 
     lcd.print(" [000]");
     lcd.setCursor(0, 1);
     lcd.print("Standby");
	 delay(1000);
}
