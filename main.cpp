#include <EEPROM.h>
#include <IRremote.h>

String memory_0xF3 = "DisableLED=0;DisableSOUND=0;14-MAY-2021;00:00:00am;10MAY2021:2;11MAY2021:5;12MAY2021:6;13MAY2021:8;14MAY2021:3";
int memory_0x00 = 1; // Idle
int memory_0x01 = 0; // Status

int memory_1x00 = 0; // Doorway UltraSonic Sensor Echo
int memory_1x01 = 0; // Doorway UltraSonic Sensor Trig
int memory_2x00 = 0; // Distance UltraSonic Sensor Echo
int memory_2x01 = 0; // Distance UltraSonic Sensor Trig
int memory_3x01 = 2; // IR


long memory_1xF2 = 0;
int memory_1xF3 = 0;
long memory_2xF2 = 0;
int memory_2xF3 = 0; 

int memory_0xA1 = 0; // Last Distance for DW
int memory_0xA2 = 0; // Last Distance for D

int memory_0xFE = 0; // Today's Counter

IRrecv recv(memory_3x01);
decode_results results;

void setup() {
    Serial.begin(9600);

    // Configure Pins

  	pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, INPUT);
    
  	// Enable IR
  	recv.enableIRIn();
  
}

void loop() { 
  // Set Current Status LED
  setStatus(); 
  
  // Read Sensors
  //get_1xFF();
  //get_2xFF();
  
  //Read IR
  irCommand();
  
  // Store Data
  
  // Send Data to Serial
  
}

void addCounter() {
    memory_0xFE++;
}

void removeCounter() {
    memory_0xFE++;
}

void statusColor(int r, int g, int b)
{
  analogWrite(9, r);
  analogWrite(11, g);
  analogWrite(10, b);
}

void setStatus() {
  if(memory_0x00 == 1) statusColor(0,255,0);
  if(memory_0x00 == 2) statusColor(255,0,0);
  
  if(memory_0x01 > 0) {
  	memory_0x00 = 0; // Remove Idle State
    
    // Sending Data
    if(memory_0x01 == 3) {
    	statusColor(255,75,0);
        delay(50);
      	memory_0x01 = 0;
    }
    
    // Motion Detected
    if(memory_0x01 == 6) {
    	statusColor(0,0,255);
      	sendFeedback();
        delay(500);
      	memory_0x01 = 0;
    }
    
    // Error Exception
    while (memory_0x01 == 9) {
      statusColor(255,0,0);
      delay(500);
      statusColor(0,0,0);
      delay(500);
    }
    
  } else {
    if(memory_0x00 != 2) {
      memory_0x00 = 1; // Restore Idle State
    }
  }
}

void sendFeedback() {
  // We create the tone manually
  if(memory_0x01 == 6) {
    unsigned long startTime=millis();
    unsigned long halfPeriod= 1000000L/150/2;
    pinMode(3,OUTPUT);
    while (millis()-startTime< 10)
    {
      digitalWrite(3,HIGH);
      delayMicroseconds(halfPeriod);
      digitalWrite(3,LOW);
      delayMicroseconds(halfPeriod);
    }
    pinMode(3,INPUT);
  }
}

// Handle Sensors
int get_1xFF() {
  digitalWrite(5, LOW);
  delayMicroseconds(2);
  digitalWrite(5, HIGH);
  delayMicroseconds(10);
  digitalWrite(5, LOW);
  memory_1xF2 = pulseIn(4, HIGH);
  memory_1xF3 = memory_1xF2 * 0.034 / 2;
  Serial.println(memory_1xF3 - memory_0xA1);
  if(memory_0xA1 != 0) {
      if((memory_1xF3 - memory_0xA1) > 25) {
          memory_0xA1 = memory_1xF3;
        memory_0x01 = 6;
      }
      if((memory_1xF3 - memory_0xA1) < 0) {
          memory_0xA1 = memory_1xF3;
        memory_0x01 = 6;
      }
  } else {
    memory_0xA1 = memory_1xF3;
  }
}

int get_2xFF() {
	
}


// IR
void irCommand() {
  if(recv.decode(&results)) {
    if(results.value == 16580863) {
      if(memory_0x00 == 1) {
        memory_0x00 = 2;
      } else { 
        memory_0x00 = 1;
      }
    }
    Serial.println(results.value);
    Serial.println(memory_0x00);
    recv.resume();
  }
}

// Data Storage

void storeDataROM(String data) {
    byte len = data.length();
    EEPROM.write(0, len);
    for (int i = 0; i < len; i++)
    {
        EEPROM.write(0 + 1 + i, data[i]);
    }
}

void storeDataSERIAL(String data) {

}

void storeDataUSB(String data) {

}

void storeDataARTEMIS(String data) {

}