#define pulseInput1 2 //direction
#define pulseInput2 3 //Throtle

#define thro 6
#define dire 7
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pulseInput1, INPUT);
  pinMode(pulseInput2, INPUT);
  pinMode(thro, OUTPUT);
  pinMode(dire, OUTPUT);

}

unsigned int duration1 ;
unsigned int duration2 ;
unsigned int A = 0;


void loop() {

duration1 = pulseIn(pulseInput1,HIGH);
dir();
Serial.print(duration1);
Serial.print(",");
Serial.println(duration2);
}

void dir () //방향값 읽고 중립 아니면 쓰로틀값 읽기
{
  if(duration1<1100) //drive gear
  {
    digitalWrite(dire,HIGH);
    thr();
    }
    else if(duration1>1700)//reverse gear
    {
      digitalWrite(dire,LOW);
      thr();
      }
    else //nutral gear
    {
      digitalWrite(thro,LOW);
      digitalWrite(LED_BUILTIN, LOW);
      } 
  }
  
void thr () //쓰로틀값 읽기
{
  duration2 = pulseIn(pulseInput2,HIGH);
  int throMap = map(duration2,1490,1900,0,255);
    Serial.print(throMap);
  if(throMap>7) //excel
  {
  Serial.print(",");
  if (A<20) 
  {
    analogWrite(thro,throMap);
    digitalWrite(LED_BUILTIN, LOW);
    if (throMap>245) A++;      
    }
     else 
   {
      digitalWrite(thro,HIGH);
      digitalWrite(LED_BUILTIN, HIGH);
      if (throMap<245) A=0;
   }  
  }
  else //break
  {
  Serial.print("!");
  analogWrite(thro,1);
    }
  }
