#define pulseInput1 2 //direction
#define pulseInput2 3 //Throtle

#define thro 6
#define dire 7
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pulseInput1, INPUT);
  pinMode(pulseInput2, INPUT);
  pinMode(thro, OUTPUT);
  pinMode(dire, OUTPUT);
}

unsigned int duration1;
unsigned int duration2;

void loop()
{

  duration1 = pulseIn(pulseInput1, HIGH);
  duration2 = pulseIn(pulseInput2, HIGH);

  Serial.print(duration1);
  Serial.print(",");
  Serial.println(duration2);
}

void dir()
{
  if (duration1 < 1100)
  {
  }
  else if (duration1 > 1700)
  {
  }
  else
  {
  }
}
void thr()
{
}
