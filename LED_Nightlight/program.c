#include <IRremote.h>

// Define pins
const int RECV_PIN = 11;
const int ledPin2 = 12;
const int ledPin3 = 13;
const int displayStartPin = 2;  // Start PIN for display (we use startPin, startPin + 1, ..., startPin + 7)

// Remote control's buttons
const unsigned long Button_Power = 0xFD00FF;
const unsigned long Button_0 = 0xFD30CF;
const unsigned long Button_1 = 0xFD08F7;
const unsigned long Button_2 = 0xFD8877;
const unsigned long Button_3 = 0xFD48B7;
const unsigned long Button_4 = 0xFD28D7;
const unsigned long Button_5 = 0xFDA857;
const unsigned long Button_6 = 0xFD6897;
const unsigned long Button_7 = 0xFD18E7;
const unsigned long Button_8 = 0xFD9867;
const unsigned long Button_9 = 0xFD58A7;

// Define varables 
boolean ledState = LOW;
boolean ledState2 = HIGH;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);        
              
  digitalWrite(ledPin2, ledState);
  digitalWrite(ledPin3, ledState);

  for(int pin = 0; pin <= 7 ; pin++){   
      pinMode(displayStartPin + pin, OUTPUT);
      digitalWrite(displayStartPin + pin, HIGH);
  }
}

int number[10][8] =            //the array is used to store the number 0~9
{
  {0,0,0,1,0,0,0,1},//0
  {0,1,1,1,1,1,0,1},//1
  {0,0,1,0,0,0,1,1},//2
  {0,0,1,0,1,0,0,1},//3
  {0,1,0,0,1,1,0,1},//4
  {1,0,0,0,1,0,0,1},//5
  {1,0,0,0,0,0,0,1},//6
  {0,0,1,1,1,1,0,1},//7
  {0,0,0,0,0,0,0,1},//8
  {0,0,0,0,1,1,0,1} //9
};

// this function is used to display numbers
void showNumber(int i) {
  int lastDigit = i % 10;
  for(int pin = 0; pin <= 6 ; pin++){
     digitalWrite(displayStartPin + pin, number[lastDigit][pin]);
  }

  const int dpPin = displayStartPin + 7;

  if ( i > 9 )
  {
     digitalWrite(dpPin, 0);
  }
  else 
  {
     digitalWrite(dpPin, 1);
  }
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    switch (results.value){
      case Button_Power:
        ledState = !ledState;
        digitalWrite(ledPin2, ledState);
        digitalWrite(ledPin3, ledState);
        
        int countDown = 19;
        while ( countDown >= 0 ) {
          showNumber(countDown);
          delay(1000);
          --countDown;
        }
        ledState = !ledState;
        digitalWrite(ledPin2, ledState);
        digitalWrite(ledPin3, ledState);
        
        for(int pin = 0; pin <= 7 ; pin++){   
          digitalWrite(displayStartPin + pin, HIGH);
        }
        
        break;
    }

    irrecv.resume();
  }
}