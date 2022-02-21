
#include <IRremote.h>

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

const int PUSH_DELAY = 250;
const int PowerPIN = 8;
const int VolUpPIN = 9;
const int VolDownPIN = 10;


void setup(){
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, true); // Start the receiver
  
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
}

void PushBtn(int pinNo){
  digitalWrite(pinNo, HIGH);
  delay(PUSH_DELAY);
  digitalWrite(pinNo, LOW); 
}

void loop(){
  if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

      switch(IrReceiver.decodedIRData.decodedRawData)
      {
        case 0x92:
          Serial.println("Vol up");
          PushBtn(VolUpPIN);
          break;
        case 0x93:
          Serial.println("Vol down");
          PushBtn(VolDownPIN);
          break;
        case 0x95:
          Serial.println("Turn on/off");
          PushBtn(PowerPIN);
          break;
      }
      
      IrReceiver.resume(); // Enable receiving of the next value
  } 

}
