#include <EEPROM.h>

String memory_0xF3 = "DisableLED=0;DisableSOUND=0;14-MAY-2021;00:00:00am;10MAY2021:2;11MAY2021:5;12MAY2021:6;13MAY2021:8;14MAY2021:3";
int memory_0x00 = 1; // Idle
int memory_0x01 = 3; // Status

int memory_1x00 = 0; // Doorway UltraSonic Sensor Echo
int memory_1x01 = 0; // Doorway UltraSonic Sensor Trig
int memory_2x00 = 0; // Distance UltraSonic Sensor Echo
int memory_2x01 = 0; // Distance UltraSonic Sensor Trig

int memory_0xFE = 0; // Today's Counter

void setup() {
    Serial.begin(9600);
}

void loop() { 
  // Set Current Status LED
  setStatus(); 
  
  // Read Sensors
  
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
  	memory_0x00 = 1; // Restore Idle State
  }
}

void sendFeedback() {
	if(
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