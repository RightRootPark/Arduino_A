#define daylight 11
#define uplight 2
#define downlight 3
#define right 4
#define left 5
#define stoplight 6
#define stoplightN 7
#define inside 8

#define door 9
byte mode = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode( daylight, OUTPUT);
  pinMode(uplight, OUTPUT);
  pinMode(downlight, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(stoplight, OUTPUT);
  pinMode(stoplightN, OUTPUT);

  pinMode(door, INPUT_PULLUP);
  Serial.begin(9600);
   alloff();
  emergency();
}

// the loop function runs over and over again forever
void loop() {

  if(digitalRead(door) == HIGH){
    digitalWrite(LED_BUILTIN, HIGH); 
    Serial.print(digitalRead(door));
    led++;
  }
  else{
   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  Serial.print(digitalRead(door));
  if(led>0)led--;
  }

switch(mode){
       case 0:
       alloff();
       break;
       case 1:
       
       break;
       case 2:
       
       break;
       case 3:
       
       break;
       case 4:
       
       break;
       case 5:
       
       break;
       case 6:
       
       break;
       case 7:
       
       break;
       case 8:
       
       break;
       default:
          delay(400);
}
   emergency();
}

void alloff(){
      digitalWrite(LED_BUILTIN, HIGH); 
      digitalWrite(daylight, HIGH);
      digitalWrite(uplight, HIGH);
      digitalWrite(downlight, HIGH);
      digitalWrite(right, HIGH);
      digitalWrite(left, HIGH);
      digitalWrite(stoplight, HIGH);
      digitalWrite(stoplightN, HIGH);
      digitalWrite(inside, HIGH);
}
void emergency(){
      digitalWrite(right, HIGH);
      digitalWrite(left, HIGH);
      delay(500);
      digitalWrite(right, LOW);
      digitalWrite(left, LOW);
      delay(500);
}
