#define recv_pin 2
#define IRdis A0
#define PIR  12        // 센서 변수 선언하고 연결한 핀 번호로 초기화

//------------------------IR================
int rel1 = 11; //relay1
int rel2 = 13; //relay2
int distance = 0;
int b;
int Fanflag = 0;
int Lightflag = 0;
bool state = 0;      // 센서 상태 값 저장 변수(0: LOW, 1: HIGH)

// the setup routine runs once when you press reset:
void setup() {
  pinMode(13, OUTPUT);//릴레이2
  pinMode(11, OUTPUT);//릴레이1
  pinMode(PIR, INPUT);      // RIP센서를 입력으로 설정
  Serial.begin(9600);// initialize serial communication at 9600 bits per second:
  pinMode (IRdis, INPUT); 
  //  Serial.println("1. All on");
  //  Serial.println("2. LED on & Fan off");
  //  Serial.println("3. LED off & Fan on");
  //  Serial.println("4. LED auot & Fan auto");
  //  Serial.println("5. LED auto& Fan off");
  //  Serial.println("6. All off");
  //  Serial.println("9. help");
}
//LOOP========================================
void loop() {
//   IRsens ();
  if (Serial.available()>0)
  {
    b = int(Serial.read());
        Serial.write(b);
  }
  RIP();
//          seorder();
          delay(100);
}

//-----IR Distance----------
void IRsens (){
    int data = analogRead(IRdis); 
  //측정한 volt값을 0에서 5000사이의 값으로 변환
  int volt = map(data, 0, 1023, 0, 5000);
  //측정값을 통해 거리를 계산
  distance = data;
  //(21.61/(volt-0.1696))*1000; 
  Serial.println(distance);
  if (distance > 534){
    b++;
    delay(1000);
  }
  if(b>4) b=1;
}
void RIP(){
    state = digitalRead(PIR);   // PIR 센서값 입력받음
    if (state == 0){              // 센서 값이 0 이라면
    Serial.println("ON");       // 시리얼 통신에 센서값 출력
    allon();    
    Lightflag=0;
  }
  
  else {                        // 센서 값이 1 이라면
    Serial.println("OFF");      // 시리얼 통신에 센서값 출력
    Lightflag++;
    Serial.println(Lightflag);
  }
      if (Lightflag>300){
        onlyFAN();
      }

}

void seorder() {
  switch (b) {
    case 1:
      allon();
      break;
    case 2:
      onlyFAN();
      break;
    case 3:
      allon();
      break;
    case 4:
      onlyFAN();
      break;
    default:
//      Serial.println("1:all on");
//      Serial.println("2:all off");
//      Serial.println("5:only LED");
//      Serial.println("6:only fan");
      break;
  }
}

//------sub function---------------------------------
void allon() {
  digitalWrite(rel1, LOW);
  digitalWrite(rel2, LOW);
  Serial.println("allon");
}
void onlyLED() {
  digitalWrite(rel1, HIGH);
  digitalWrite(rel2, LOW);
  Serial.println("onlyLED");
}
void onlyFAN() {
  digitalWrite(rel1, LOW);
  digitalWrite(rel2, HIGH);
  Serial.println("onlyFAN");
}
void alloff() {
  digitalWrite(rel1, HIGH);
  digitalWrite(rel2, HIGH);
  Serial.println("alloff");
}
