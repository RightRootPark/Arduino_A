// RC 수신기에서 PWM신호를 받아서 2바퀴 조향을위해 모터드라이버에 PWM신호로 속도 명령
//조종기는 자동차 조종기로 엑셀과 스티어링 조작을 함
#define pulseInput1 2 //stear
#define pulseInput2 3 //Throtle

#define Rthro 6
#define Lthro 5
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pulseInput1, INPUT); //stear
  pinMode(pulseInput2, INPUT); //Throtle
  pinMode(Rthro, OUTPUT);
  pinMode(Lthro, OUTPUT);
}

unsigned int durationL;
unsigned int durationR;
unsigned int thro;
unsigned int stear;

void loop()
{
  stear = pulseIn(pulseInput1, HIGH);
  thro = pulseIn(pulseInput2, HIGH);
  switch (thro)
  {
  case 0 ... 1460: //후진
    transR();
    break;
  case 1490 ... 1900: //전진
    transD();
    break;
  default: //정지
    transPV();
    digitalWrite(LED_BUILTIN, HIGH);
    break;
  }

  Serial.print(",");
  Serial.print(stear);
  Serial.print(",");
  Serial.println(thro);
}

void transD() //전진 쓰로틀값 읽고 왼쪽 오른쪽 속도비중 분배
{
  unsigned int excel = thro - 1490;
  unsigned int stearrate; //조향 비율 변수
  switch (stear)
  {
  case 0 ... 1460:                              // 좌회전
    stearrate = map(stear, 1080, 1460, 300, 0); // 좌회전조향 비율 맵핑
    durationL = excel - stearrate;
    durationR = excel;
    break;
  case 1490 ... 1999:                           // 우회전
    stearrate = map(stear, 1900, 1460, 300, 0); //우회전 조향비율 맵핑
    durationL = excel;
    durationR = excel - stearrate;
    break;
  default: // 직진
    durationL = excel;
    durationR = excel;
    break;
  }
  unsigned int throMapL = map(durationL, 0, 390, 127, 255); //127~255 전진대역
  unsigned int throMapR = map(durationR, 0, 390, 127, 255); //analogwrite = 0~255

  analogWrite(Lthro, throMapL);
  analogWrite(Rthro, throMapR);

  Serial.print(throMapL);
  Serial.print(",");
  Serial.print(throMapR);
  Serial.print(",");
  Serial.print(durationL);
  Serial.print(",");
  Serial.print(durationR);
  digitalWrite(LED_BUILTIN, LOW);
}
void transR() //후진 쓰로틀값 읽고 왼쪽 오른쪽 속도비중 분배
{
  unsigned int excel = 1480 - thro;
  switch (stear)
  {
    unsigned int stearrate;                     //조향 비율 변수
  case 0 ... 1460:                              // 좌회전
    stearrate = map(stear, 1080, 1460, 300, 0); // 좌회전조향 비율 맵핑
    durationL = excel - stearrate;
    durationR = excel;
    break;
  case 1490 ... 1999:                           // 우회전
    stearrate = map(stear, 1900, 1460, 300, 0); //우회전 조향비율 맵핑
    durationL = excel;
    durationR = excel - stearrate;
    break;
  default: // 직진
    durationL = excel;
    durationR = excel;
    break;
  }
  unsigned int throMapL = map(durationL, 0, 230, 127, 0); //0~127이 후진 대역
  unsigned int throMapR = map(durationR, 0, 230, 127, 0); //analogwrite = 0~255

  analogWrite(Lthro, throMapL);
  analogWrite(Rthro, throMapR);

  Serial.print(throMapL);
  Serial.print(",");
  Serial.print(throMapR);
  Serial.print(",");
  Serial.print(durationL);
  Serial.print(",");
  Serial.print(durationR);
  digitalWrite(LED_BUILTIN, LOW);
}
void transPV() //제자리회전 왼쪽 오른쪽 속도비중 분배
{
  switch (stear)
  {
  case 0 ... 1460:                              // 좌회전
    durationL = map(stear, 1080, 1460, 255, 0); // 좌회전조향 비율 맵핑;
    durationR = map(stear, 1080, 1460, 0, 255); // 좌회전조향 비율 맵핑
    break;
  case 1490 ... 1999:                           // 우회전
    durationL = map(stear, 1900, 1460, 255, 0); //우회전 조향비율 맵핑
    durationR = map(stear, 1900, 1460, 0, 255); //우회전 조향비율 맵핑
    break;
  default: //정지
    durationL = 0;
    durationR = 0;
    break;
  }

  unsigned int throMapL = durationL; //0~127이 후진 대역 127~255 가 전진
  unsigned int throMapR = durationR; //analogwrite = 0~255

  analogWrite(Lthro, throMapL);
  analogWrite(Rthro, throMapR);

  Serial.print(",");
  Serial.print(durationL);
  Serial.print(",");
  Serial.print(durationR);
  digitalWrite(LED_BUILTIN, LOW);
}
