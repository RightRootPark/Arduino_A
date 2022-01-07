/*
Recive PWM at rc_reciver(trotle+stearing)
and translate to 2Whill platform controll(Left whill, Right whill)
*/
#define pulseInput1 2 //stear pwm in pin number
#define pulseInput2 3 //Throtle pwm in pin number

#define Rthro 6 //Right Moter pwm Output pin number
#define Lthro 5 //Left Moter Output pin number

int pulseInput1_value; //PWM Value Reed
int pulseInput2_value; //PWM Value Reed
int Rthro_value;       //Moter PWM Value
int Lthro_value;

void setup()
{
  Serial.begin(9600);           //serial setting
  pinMode(LED_BUILTIN, OUTPUT); //chack LED setup
  pinMode(pulseInput1, INPUT);  //stear pwm in pin setup
  pinMode(pulseInput2, INPUT);  //Throtle Pwm in pin setup
  pinMode(Rthro, OUTPUT);       //Right PWM out pin setup
  pinMode(Lthro, OUTPUT);       //Left PWM out pin setup
}

void loop()
{
  pulseInput1_value = pulseIn(pulseInput1, HIGH);
  pulseInput2_value = pulseIn(pulseInput2, HIGH);
  // Rthro_value = pulseIn(Rthro, HIGH); !!!!this code is make delay
  // Lthro_value = pulseIn(Lthro, HIGH); !!!!pwm in pin is just 2/ the ic waiting the pwm in

  transmishion();

  Serial.print(pulseInput1_value);
  Serial.print(",");
  Serial.println(pulseInput2_value);
}

int excelconfig(int excel) //configration rc to excelation or decelation
{
  excel = constrain(excel, 1270, 1880); //constrain a in b~c
  switch (excel)
  {
  case 1270 ... 1475:                        // Drive
    excel = map(excel, 1270, 1475, -127, 0); //excel(pwm)
    digitalWrite(LED_BUILTIN, LOW);
    break;
  case 1495 ... 1880:                       // Reverce
    excel = map(excel, 1495, 1880, 0, 127); //excel(pwm)
    digitalWrite(LED_BUILTIN, LOW);
    break;
  default: // stop or PV
    excel = 0;
    digitalWrite(LED_BUILTIN, HIGH);
    break;
  }
  return excel;
}

int stearconfig(int stear) //configration rc to excelation or decelation
{
  stear = constrain(stear, 1080, 1870);
  switch (stear)
  {
  case 1080 ... 1475:                        // Left
    stear = map(stear, 1080, 1475, -127, 0); //(pwm)
    break;
  case 1495 ... 1870:                       // Right
    stear = map(stear, 1495, 1870, 0, 127); //(pwm)
    break;
  default: // idle
    stear = 0;
    break;
  }
  return stear;
}

int transmishion() //config 2whill drection 0~127,128~255
{
  int a = excelconfig(pulseInput2_value);
  int stear = stearconfig(pulseInput1_value);
  float Lex;
  float Rex;

  switch (a) //r, n, d gear switch
  {
  case 10 ... 127: // Drive
    switch (stear) //stear choice
    {
    case -127 ... - 1: // Left
      Lex = a;
      Rex = a * (128 + stear) / 127;
      break;
    case 1 ... 127: // Right
      Lex = a * (128 - stear) / 127;
      Rex = a;
      break;
    default: // idle
      Lex = a;
      Rex = a;
      break;
    }
    break;
  case -127 ... - 10: // Reverce
    switch (stear)    //stear choice
    {
    case -127 ... - 1: // Left
      Lex = a;
      Rex = a * (128 + stear) / 127;
      break;
    case 1 ... 127: // Right
      Lex = a * (128 - stear) / 127;
      Rex = a;
      break;
    default: // idle
      Lex = a;
      Rex = a;
      break;
    }
    break;
  default: // stop or PV
    stear = stear / 4;
    switch (stear) //stear choice
    {
    case -127 ... - 1: // Left
      Lex = -stear;
      Rex = stear;
      break;
    case 1 ... 127: // Right
      Lex = -stear;
      Rex = stear;
      break;
    default: // idle
      Lex = 0;
      Rex = 0;
      break;
    }
    break;
  }
  analogWrite(Lthro, PWMform(Lex));
  analogWrite(Rthro, PWMform(Rex));
  Serial.print(PWMform(Lex));
  Serial.print(",");
  Serial.print(PWMform(Rex));
  Serial.print(",");
}

int PWMform(int a) //trams PWM form to moterdriver 0~127(reverse),128~255(Drive)
{

  switch (a) //r, n, d gear switch
  {
  case 10 ... 127:                 // Drive
    a = map(a, 10, 127, 137, 254); //(pwm)
    break;
  case -127 ... - 10:              // Reverce
    a = map(a, -127, -10, 1, 118); //(pwm)
    break;
  default: // stop or PV
    a = 127;
    break;
  }
  return a;
}
