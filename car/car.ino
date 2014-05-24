#define fb1 8
#define fb2 9
#define leng 10
#define reng 11
#define trig 2
#define echo 3
#define antiinetriondelay 200
int pwm=100;
void forvard()
{
  digitalWrite(fb1,LOW);
  analogWrite(fb2,pwm);
  digitalWrite(leng,LOW);
  digitalWrite(reng,LOW);
}

void backvard()
{
  analogWrite(fb1,pwm);
  digitalWrite(fb2,LOW);
  digitalWrite(leng,LOW);
  digitalWrite(reng,LOW);
}

void left(int direction1)
{
  if (direction1==1)
  {
  digitalWrite(fb1,LOW);
  analogWrite(fb2,pwm);
  analogWrite(leng,pwm);
  digitalWrite(reng,LOW);
  }
  else if(direction1==2)
  {
  analogWrite(fb1,pwm);
  digitalWrite(fb2,LOW);
  analogWrite(leng,pwm);
  digitalWrite(reng,LOW);
  }
  
}
void right(int direction1)
{
    if(direction1==1)
  {
  digitalWrite(fb1,LOW);
  analogWrite(fb2,pwm);
  digitalWrite(leng,LOW);
  analogWrite(reng,pwm);
  }
  else if(direction1==2)
  {
  analogWrite(fb1,pwm);
  digitalWrite(fb2,LOW);
  digitalWrite(leng,LOW);
  analogWrite(reng,pwm);
  }
}
void stopp()
{
  digitalWrite(fb1,LOW);
  digitalWrite(fb2,LOW);
  digitalWrite(leng,LOW);
  digitalWrite(reng,LOW);
}
float sensor()
{
  int time_us, distance_sm;
digitalWrite(trig, HIGH); // Подаем сигнал на выход микроконтроллера 
delayMicroseconds(10); // Удерживаем 10 микросекунд 
digitalWrite(trig, LOW); // Затем убираем 
time_us=pulseIn(echo, HIGH); // Замеряем длину импульса 
distance_sm=time_us/58; // Пересчитываем в сантиметры 
Serial.println(distance_sm); // Выводим на порт 
return distance_sm;
}
int middlesensorvalue()
{ //int sum=0;
  //for (int i=0;i<3;i++)
  {
//    sum+=sensor();
  //  delay(50);
  }
  return 30;
}
int get_direction()
{ 
  int val=Serial.read()-48;
  Serial.println(val);
  return val;
}
void setup()
{
 Serial.begin(9600);
 pinMode(fb1,OUTPUT);
 pinMode(fb2,OUTPUT);
 pinMode(leng,OUTPUT);
 pinMode(reng,OUTPUT);
 pinMode(trig,OUTPUT);
 pinMode(echo,INPUT);
}


void loop()
{
static int cardirection=0;
static int previosdirection=0;
if (Serial.available()>0)
   cardirection=get_direction();
   switch (cardirection)
   {
   case 0: 
    if (previosdirection==8)
{   
   backvard();
   delay( antiinetriondelay );
}
   else if (previosdirection==2)
   {   
   forvard();
   delay( antiinetriondelay );
}
   stopp();
   break;  
   case 8: 
   
     if (middlesensorvalue()>5)
      forvard();
      else stopp();
      break;
   case 4: 
     if (middlesensorvalue()>5)
     left(1);
     else stopp();
     break;
   case 6: 
     if (middlesensorvalue()>5)
     right(1);
     else stopp();
     break;
   case 1: left(2); break;
   case 3: right(2); break;
   case 2: backvard(); break;
   case 9: if (pwm<250) pwm+=10; break;
   case 7: if (pwm>10) pwm-=10; break;
   default: stopp();
   }
   previosdirection=cardirection;
 
}


