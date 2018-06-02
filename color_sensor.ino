int S0 = 3, S1 = 4, S2 = 5, S3 = 6;
int a = 7, b = 8, c = 9, d = 10;
int taosOutPin = 2;
int LED = 12;
int debug = 99;
int temp = 99;

void setup() {
  TCS3200setup();
  Serial.begin(9600);
  Serial.println("-ready-");
  delay(100);
}

// primary loop takes color readings from all four channels and displays the raw values once per second.  What you might wish to do with those values is up to you...
void loop() {
  detectColor(taosOutPin);
  Serial.println("-");
  delay(1000);
}

int detectColor(int taosOutPin){
  float white = colorRead(taosOutPin,0,1);
  float red = colorRead(taosOutPin,1,1);
  float blue = colorRead(taosOutPin,2,1);
  float green = colorRead(taosOutPin,3,1);
  Serial.print("white ");
  Serial.println(white);
  Serial.print("red ");
  Serial.println(red);
  Serial.print("blue ");
  Serial.println(blue);
  Serial.print("green ");
  Serial.println(green);
  debug = 100;
  //Serial.print("debug ");
  //Serial.println(debug);
  if((white>6 && white<10) &&(red>20 && red<26)&&(blue>20 && blue<26)&&(green>23 && green<28)){//coke - white:8,red:23-24,blue:23,green:26-27
    digitalWrite(b, HIGH);
    debug = 1;
    Serial.print("debug ");
    Serial.println(debug);
  }
  else if((white>3 && white<6) &&(red>10 && red<16)&&(blue>10 && blue<15)&&(green>7 && green<15)){//orange juice - white:6,red:18-19,blue:18,green:16-17
    digitalWrite(c, HIGH);
    debug = 2;
    Serial.print("debug ");
    Serial.println(debug);
  }
  else if((white>5 && white<9) &&(red>17 && red<24)&&(blue>17 && blue<24)&&(green>15 && green<24)){//greenapple gatorade - white:7,red:22,blue:22,green:16
    digitalWrite(d, HIGH);
    debug = 3;
    Serial.print("debug ");
    Serial.println(debug);
  }
  else{
    debug = 5;
    Serial.print("debug ");
    Serial.println(debug);
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
  }
  /*
  if (temp == 0) {
    Serial.println("0인가봉가");
  }
  else if (temp == 1){
    Serial.println("1인가봉가");
  }
  else{
    Serial.println("뭔가잘못됐댜봉가");
  }*/
  debug = 106;
  //Serial.print("debug ");
  //Serial.println(debug);
}
//coke,orange,powerade

/*
This section will return the pulseIn reading of the selected color.  
It will turn on the sensor at the start taosMode(1), and it will power off the sensor at the end taosMode(0)
color codes: 0=white, 1=red, 2=blue, 3=green
if LEDstate is 0, LED will be off. 1 and the LED will be on.
taosOutPin is the ouput pin of the TCS3200.
*/
float colorRead(int taosOutPin, int color, boolean LEDstate){ 
  //turn on sensor and use highest frequency/sensitivity setting
  taosMode(1);
  //setting for a delay to let the sensor sit for a moment before taking a reading.
  int sensorDelay = 100;
  //set the S2 and S3 pins to select the color to be sensed 
  if(color == 0){//white
    digitalWrite(S3, LOW); //S3
    digitalWrite(S2, HIGH); //S2
    // Serial.print(" w");
  }
  else if(color == 1){//red
    digitalWrite(S3, LOW); //S3
    digitalWrite(S2, LOW); //S2
    // Serial.print(" r");
  }
  else if(color == 2){//blue
    digitalWrite(S3, HIGH); //S3
    digitalWrite(S2, LOW); //S2 
    // Serial.print(" b");
  }
  else if(color == 3){//green
    digitalWrite(S3, HIGH); //S3
    digitalWrite(S2, HIGH); //S2 
    // Serial.print(" g");
  }
  // create a var where the pulse reading from sensor will go
  float readPulse;
  delay(sensorDelay);
  // now take a measurement from the sensor, timing a low pulse on the sensor's "out" pin
  readPulse = pulseIn(taosOutPin, LOW, 80000);
  //if the pulseIn times out, it returns 0 and that throws off numbers. just cap it at 80k if it happens
  if(readPulse < .1){
    readPulse = 80000;
  }
  //turn off color sensor and LEDs to save power 
  taosMode(0);
  // return the pulse value back to whatever called for it... 
  return readPulse;
}

// Operation modes area, controlled by hi/lo settings on S0 and S1 pins.
//setting mode to zero will put taos into low power mode. taosMode(0);
void taosMode(int mode){
  if(mode == 0){
    //power OFF mode-  LED off and both channels "low"
    digitalWrite(LED, HIGH);
    digitalWrite(S0, LOW);
    digitalWrite(S1, LOW);
    //  Serial.println("mOFFm");
  }
  else if(mode == 1){
    //this will put in 1:1, highest sensitivity
    digitalWrite(S0, HIGH);
    digitalWrite(S1, HIGH);
    // Serial.println("m1:1m");
  }
  else if(mode == 2){
    //this will put in 1:5
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    //Serial.println("m1:5m");
  }
  else if(mode == 3){
    //this will put in 1:50
    digitalWrite(S0, LOW);
    digitalWrite(S1, HIGH);
  //Serial.println("m1:50m");
  }
  return;
}

void TCS3200setup(){
  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(d,OUTPUT);
  pinMode(LED,OUTPUT);
  //communication freq (sensitivity) selection
  pinMode(S0,OUTPUT);
  pinMode(S1,OUTPUT);
  //color mode selection
  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);
  //color response pin (only actual input from taos)
  pinMode(taosOutPin, INPUT);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  return;
}
