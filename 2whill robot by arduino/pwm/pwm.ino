#define pulseInput1 2 //stear
#define pulseInput2 3 //Throtle

#define Rthro 6 //Moter Output
#define Lthro 5

void straight(int excel);
void left(int excel);
void right(int excel);
 
int pulseInput1_value;  // Analog Value
int pulseInput2_value;
int Rthro_value;  //Moter PWM Value
int Lthro_value;
int stear;  //Mapping Value(-100~100)
int excel;  //Mapping Value(-100~130)
 
void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pulseInput1, INPUT); //stear
  pinMode(pulseInput2, INPUT); //Throtle
  pinMode(Rthro, OUTPUT);
  pinMode(Lthro, OUTPUT);

}
 
void loop() {
  pulseInput1_value = pulseIn(pulseInput1, HIGH);
  pulseInput2_value = pulseIn(pulseInput2, HIGH);
  Rthro_value = pulseIn(Rthro, HIGH);
  Lthro_value = pulseIn(Lthro, HIGH);

  int stear = map(pulseInput1_value, 1050, 1950, -100, 100);  //L, R
  int excel = map(pulseInput2_value, 1200, 1900, -100, 130); //excel(pwm)

  switch(stear)
  {
  case -100 ... -30:  // 좌회전
    left(excel);
    Serial.println("left");
    Serial.println(excel);
    break;
  case 40 ... 100:  // 우회전
    right(excel);
    Serial.println("right");
    Serial.println(excel);
    break;
  default:  // 직진
    straight(excel);
    Serial.println("straight");
    Serial.println(excel);
    digitalWrite(LED_BUILTIN, HIGH);
    break;
  }
  
  Serial.print(pulseInput1_value);
  Serial.print(",");
  Serial.print(pulseInput2_value);
  Serial.print(",");
  Serial.print(Rthro_value);
  Serial.print(",");
  Serial.println(Lthro_value);
  digitalWrite(LED_BUILTIN, LOW);
}

void straight(int excel){
//  moter r, l front
  if(excel >= 10){
  analogWrite(Lthro_value, excel*2);
  analogWrite(Rthro_value, excel*2);
  }
  else{
  analogWrite(Lthro_value, 0);
  analogWrite(Lthro_value, 0);
  Serial.println("stop");
  }
}

void left(int excel){
//  moter l front //쓰로틀만큼 더 빠르게 회전
//  moter r zero? //쓰로틀만큼 느리게 회전
  analogWrite(Lthro_value, excel*2);
  analogWrite(Rthro_value, excel/2);

}

void right(int excel){
  analogWrite(Lthro_value, excel/2);
  analogWrite(Rthro_value, excel*2);
  ;
}
