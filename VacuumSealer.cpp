//Vacuum sealer firmware
//possibly implement "step on" ... "step off"

int button = A0;
int valve = D0;
int sealer = D5;
int vacuum = D4;
int backward = D3;
int forward = D2;
int modeButton = D6;
unsigned long currentTime;
unsigned long startTime;
unsigned long duration;
int size = 1; //1 is sample

void setup()
{
    pinMode(valve, OUTPUT);              // sets pin as output
    pinMode(forward, OUTPUT);
    pinMode(backward, OUTPUT);
    pinMode(vacuum, OUTPUT);
    pinMode(sealer, OUTPUT);
    pinMode(button, INPUT);               // sets pin as input
    pinMode(modeButton, INPUT_PULLUP);      // sets pin with input pullup resistor
}

void loop()
{

if(digitalRead(modeButton) == HIGH){
    digitalWrite(sealer, HIGH);
}
else{
    digitalWrite(sealer, LOW);
}


if(digitalRead(button) == HIGH){
startTime = millis();

  while(digitalRead(button) == HIGH) {
    delay(1);
}

currentTime = millis();
    duration = currentTime - startTime;
    
    if (duration < 2000){
        size = 1;
    }
    else if(duration < 4000){
        size = 2;
    }
    else if(duration < 6000){
        size = 3;
    }
    else{
        size = 5;
    }
    
    digitalWrite(forward, HIGH);    //move tube forward
    delay(2000);                     //linear actuator takes a while, 3 seconds?
    digitalWrite(forward, LOW);     //stop moving
    delay(200);                     //wait briefly before next step
    
    digitalWrite(vacuum, HIGH);     //vacuum air out of bag
    delay(5000 * size);             //idk, 5 seconds?
    digitalWrite(vacuum, LOW);      //stop
    
    digitalWrite(valve, HIGH);      //open nitrogen
    delay(2000 * size);             //2 seconds short burst @ 15 PSI
    digitalWrite(valve, LOW);       //close nitrogen
    
    digitalWrite(vacuum, HIGH);     //vacuum air out of bag
    delay(5000 * size);             //idk, 5 seconds?
    digitalWrite(vacuum, LOW);      //stop
    
    digitalWrite(valve, HIGH);      //open nitrogen
    delay(2000 * size);             //Last fill before the seal, so keep nitrogen open while pulling back

    digitalWrite(backward, HIGH);   //move tube backward
    delay(3000);                    //longer, takes like 3 seconds
    
    digitalWrite(valve, LOW);       //close nitrogen
    
    digitalWrite(sealer, HIGH);     //seal bag
    delay(10000);                   //ten seconds for possible second sealing
    digitalWrite(sealer, LOW);      //shut off sealer
    
    digitalWrite(backward, LOW);    //stop moving
  }
}