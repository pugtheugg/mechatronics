// Define pins
const int displayStartPin = 2;  // Start PIN for display (we use startPin, startPin + 1, ..., startPin + 7)

// Define varables 
boolean ledState = LOW;
boolean ledState2 = HIGH;

void setup(){
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
  for(int pin = 0; pin <= 6 ; pin++){
     digitalWrite(displayStartPin + pin, number[i][pin]);
  }
}

void loop() {
  int countDown = 9;
  while ( countDown >= 0 ) {
    showNumber(countDown);
    delay(1000);
    --countDown;
  }
}
