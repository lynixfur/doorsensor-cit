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

int connectArtemis(String api) {
    // This feature is not implemented

    // This Function dumps the Raw Memory of both device into
    // a HTTP Request and sends it to the Artemis API
 
  	delay(150);
  
    //while (WiFi.status() != WL_CONNECTED) {
      //delay(500);
      //Serial.print(".");
    //}
    //Serial.println("");
    //Serial.println("INFO : WiFi connected");
  
    //Connect to Artemis API
    //if(client.connect(server, 80)) {
      //Serial.println("INFO : Connected to Artemis");
      //client.print("GET https://artemis.longhorn.ga/api/dump_testproject.php HTTP/1.1");
      //client.println("ARTEMIS : "); client.print(server);
      //client.println("INFO : Connection closed");
      //client.println();
      //client.println();
    //}
  
  
  	clearScreen();
    lcd.setCursor(0, 0);
    lcd.print("Artemis API");
  	lcd.setCursor(0, 1);
  	lcd.print("Offline");
  	return 0;
}

int connectUSB() {
	return 0;
}

int memoryManagement() {

}

void setup() {  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(13,OUTPUT);
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
     lcd.setCursor(0, 0);
     lcd.print("Longhorn STW");
     lcd.setCursor(0, 1);
     lcd.print("Initializing...");
  	 delay(500);
  	 clearScreen();
     lcd.setCursor(0, 0);
     lcd.print("Artemis API");
     lcd.setCursor(0, 1);
     lcd.print("Connecting...");
  	 connectArtemis("https://artemis.longhorn.ga/api");
  	 //Allows time for the connection to initialize
     delay(350);
}

void clearScreen() {
     lcd.setCursor(0, 0);
     lcd.print("                ");
     lcd.setCursor(0, 1);
     lcd.print("                ");
     lcd.setCursor(0, 0);
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

	clearScreen();
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
