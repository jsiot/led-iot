/**
*
*
*/

char inData[2];

char inChar;

byte index=0;

int LED = 13;

void setup(){
  pinMode(LED, OUTPUT);
  
  Serial.begin(57600);
  Serial.println('Serial IO');
  Serial.println('---------');
  Serial.println();
}

void loop(){
if (Serial.available() > 0) {
 
                 // Baca karakter dari Tx/Rx (USB)
                 inChar = Serial.read(); 
                 Serial.print(inChar);
                 
                 digitalWrite(LED, HIGH);
                 if(inChar == '1'){
                     digitalWrite(LED, HIGH);
                     delay(1000); 
                 }else {
                     digitalWrite(LED, LOW);
                     delay(1000); 
                 }   
        }
}
