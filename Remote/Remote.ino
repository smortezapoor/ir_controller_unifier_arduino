int analogPin = A0; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int val = 0;  // variable to store the value read
int pin = 7;
int threshold = 30;

void setup() {
  Serial.begin(9600);           //  setup serial
  pinMode(pin, OUTPUT);  
  pinMode(LED_BUILTIN, OUTPUT);
  
  delay(500);
  
  digitalWrite(pin, LOW);

  delay(1000);
}

bool is_on = false;

void wait_for_constant_voltage(){

  int count = 0;
  
  while(true){
    Serial.println("Trying to detect constant voltage...");
    val = analogRead(analogPin);



    if(val == 1023){
      Serial.println("High spike detected.");

      if(count > threshold){
        return;
      }

      Serial.print("Count: ");
      Serial.println(count);
      count ++;
      
    }
    else{
      count = 0;
    }

    delay(500);    
  }
}

void wait_for_low_voltage(){
   while(true){
    Serial.println("Trying to detect low voltage...");
    
    val = analogRead(analogPin);

    int minus_count = 0;
    int minus_threshold = 10;

    if(val < 1023){
      Serial.println("Low spike detected.");
      
      for(int i = 0 ; i < minus_threshold; i++){
        val = analogRead(analogPin);
        if(val < 1023){
          Serial.print("Minus count: ");
          Serial.println( minus_count);

        }
        minus_count ++;
        delay(200);
      }
    }

    if(minus_count > minus_threshold * 2.0 /3.0)
      return;
    else
      minus_count = 0;

    delay(2500);    
  }
}

void loop() {

  wait_for_constant_voltage();
  Serial.println("Constant voltage detected. Going to on..."); 
  digitalWrite(pin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);

  wait_for_low_voltage();
  Serial.println("Low voltage detected. Going to off..."); 
  digitalWrite(pin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  
         // debug value
}
