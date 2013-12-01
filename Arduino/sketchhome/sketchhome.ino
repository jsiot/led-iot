/*
 - Controls an RGB LED whose R, G and B legs are connected to pins 9, 5, and 6
 - Temperature sensor connected to pins Ground, A0, 5V + led connected to pin 2
 - LED control on/off connected on pin 8. 
 - 
 */

// LED RGB:
const int greenPin = 9;
const int bluePin = 5;
const int redPin = 6;

//TMP36 Temperature Pin:
int temperaturePin = 0; 
int ledPin = 2;

//LED Control on/off
int togglePin = 8;

void setup() {
  // initiate serial communication:
  Serial.begin(9600);
  // initialize the LED pins as outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  // use the anode pin as ground and set it low:
  //pinMode(anode, OUTPUT);
  //digitalWrite(anode, HIGH);
  pinMode(ledPin, OUTPUT);
  pinMode(togglePin, OUTPUT);
}


void loop() {

  int currentPin = 0; // current pin to be faded
  //--------LED RGB SETTING----------------------------------------------------------
  // if there's any serial data in the buffer, read a byte:
  if (Serial.available() > 0) {
    int inByte = Serial.read(); 
    switch (inByte) {
    case'r':     // red
      currentPin = redPin; 
      break;
    case 'g':    // green
      currentPin = greenPin; 

      break;
    case 'b':    // blue
      currentPin = bluePin; 
      break;
    }

    if (currentPin != 0){
      int brightness = Serial.parseInt();

   
      // input range 0-100 akan diubah menjadi 0-255
      brightness = map(brightness, 0, 100, 0, 255);

      // set the brightness for this color:
      analogWrite(currentPin, brightness);    
    }
  }

//-------------LED TOGGLE SETTING--------------------------------------------------------------------------------------
  // MENERIMA data dari node dan menuliskan ke dalam string
  if (Serial.available() > 0){
    int dataIn = Serial.read();

    if (dataIn == 1){
      digitalWrite(togglePin, HIGH);
    }
    else if (dataIn == 0){
      digitalWrite(togglePin, LOW);
    }
  }
//-------------TEMP SENSOR SETTING-------------------------------------------------------------------------  
  float temperature = getVoltage(temperaturePin);  
  temperature = (temperature - 0.5) * 100;          
                                                  
  Serial.println(temperature);                     
  Serial.println(" degrees centrigrade");
  if (temperature > 34)
 
  {
    digitalWrite(ledPin, HIGH);
  }
 
  else
  {
    digitalWrite(ledPin, LOW);
  }
  delay(2000); //waiting a second
}


float getVoltage(int pin){
return (analogRead(pin) * 0.004882814); //converting from a 0 to 1023 digital range
                                        // to 0 to 5 volts (each 1 reading equals ~ 5 millivolts)
}
