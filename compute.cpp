//Sender Code

//Memory
int idle = 0;
int active_status = 5;
int low_power_mode = 0;
int dw_distance = 0;
int dw_duration = 0;
int dw_last_value = 0;
int p_last_value = 0;

// Sensors
const int dw_pingPin = 6; // Doorway Ping
const int dw_echoPin = 7; // Doorway Echo
const int p_pingPin = 5; // Passage Ping
const int p_echoPin = 4; // Passage Echo

// Indicators
const int dw_speaker = 8;

void setup() {
  Serial.begin(9600);
  
  // Set Output for Sensors
  pinMode(dw_pingPin, OUTPUT);
  pinMode(p_pingPin, OUTPUT);
  
  
  // Set Output for Indicators
  pinMode(dw_speaker, OUTPUT);
}

// Status LED
//	-> Green : High Power / Idle
//	-> Blinking Red : Error
//	-> Blue : Detected Movement
//	-> Orange : Transfer Data
//  -> Red : Low Power / Idle

void status() {
  if(idle == 1) {
    RGB_color(0,255,0);
  }
  
  // Startup
  if(active_status == 15) {
  	RGB_color(255,0,255);
    delay(500);
    RGB_color(0,0,0);
    delay(100);
    active_status = 0;
    idle = 1;
  }
  
  // Error
  if(active_status == 1) {
    RGB_color(255,0,0);
    delay(500);
    RGB_color(0,0,0);
    delay(500);
    active_status = 1;
    idle = 0;
  }
  
  // Send Data
  if(active_status == 3) {
  	RGB_color(255,70,0);
    delay(100);
    RGB_color(0,0,0);
    active_status = 0;
    idle = 1;
  }
  
  // Detect Motion
  if(active_status == 5) {
	RGB_color(0,0,255);
    tone(dw_speaker, 1000);
    delay(100);
    RGB_color(0,0,0);
    noTone(dw_speaker);
    active_status = 0;
    idle = 1;
  }
  
}

void RGB_color(int r_led, int g_led, int b_led)
 {
  analogWrite(11, r_led);
  analogWrite(9, g_led);
  analogWrite(10, b_led);
}

void loop() {
  // Clears the trigPin
  digitalWrite(dw_pingPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(dw_pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(dw_pingPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  dw_duration = pulseIn(dw_echoPin, HIGH);
  // Calculating the distance
  dw_distance= dw_duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance DW: ");
  Serial.println(dw_distance);
  if(dw_distance != dw_last_value) {
  	active_status = 5;
    idle = 0;
  }
  dw_last_value = dw_distance;
  
  //Serial.write("13,MAY,2021,0,1\n");
  //delay(1000);
  status();
}
