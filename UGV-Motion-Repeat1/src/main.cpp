#include <Arduino.h>

#include <esp32PWMUtilities.h>
#include <DabbleESP32.h>
#include <time.h>


Motor Motor1;
Motor Motor2;

int H=0,i=0,state=0,pdur=0,first,range=0,loop1=0,ttime=0,endt=0,start,RState=0,dur,prstate=0,Motion[5000][2];
void setup() {
  Motor1.attach(14, 16, 17);
  Motor2.attach(15, 18, 19);
  Dabble.begin("ToyCar");
  Serial.begin(9600);
}

 void loop() {
Dabble.processInput();

if(GamePad.isTrianglePressed())
{ 
  i=0;
  first=0;
  RState=0;
  if(state==0)
    {
        Serial.println("started recording");
        state=1;
        range=1;
    }
}
if(GamePad.isCrossPressed())
{
if(state==1)
{Serial.println("Stopped recording");
state=0;
}
i=0;
loop1=0;
}

if (GamePad.isUpPressed()) {
Forward();
RState=1;
}
else {
if (GamePad.isDownPressed()) {
Backward();
RState=2;
}
else {
if (GamePad.isLeftPressed()) {
Left();
RState=3;
}
else {
if (GamePad.isRightPressed()) {
Right();
RState=4;
}
else {
Lock();
RState=0;
}
}
}
}
if(state==1)
{
  if(i==0 && RState!=0 && first==0)
  {
  ttime=clock();
  prstate=RState;
  first=1;
  }
//Checks if state of button is changed
if(prstate != RState)
{
  if(i!=0)
  {
  ttime = start;
  }
  start = clock();
  dur = start - ttime;
  if(prstate!=0)
  {
  i=i+1;
  Motion[i][0] = prstate;
  Motion[i][1] = dur;
  range=range+1;
  Serial.print(Motion[i][0]);
  Serial.print(" ");
  Serial.println(Motion[i][1]);
  }
  prstate =RState;
}
}

//if start is pressed it must start moving based on sample
if(GamePad.isStartPressed())
{
  if(loop1==0)
  {
  i=0;
  while(i<range||GamePad.isCrossPressed())
{
  start = clock();

  do{
    endt=clock();
  switch(Motion[i][0])
  {
    case 1:
    Serial.println("Forward");
    Forward();
    break;
    case 2:
    Serial.println("Backward");
    Backward();
    break;
    case 3:
    Serial.println("Left");
    Left();
    break;
    case 4:
    Serial.println("Right");
    Right();
    break;
  }}while((endt-start)<Motion[i][1]);
  Serial.print(Motion[i][0]);
  Serial.print(" ");
  Serial.println(endt-start);
  i=i+1;
}
}
loop1=1;
}
 }

void Forward()
{
  
    Motor1.moveMotor(0.55 * 100);
    Motor2.moveMotor(0.55 * 100);
}
void Backward()
{
  
    Motor1.moveMotor(-0.55 * 100);
    Motor2.moveMotor(-0.55 * 100);
}
void Left()
{
  
    Motor1.moveMotor(0.55 * 100);
    Motor2.moveMotor(-0.55 * 100);
}
void Right()
{
  
    Motor1.moveMotor(-0.55 * 100);
    Motor2.moveMotor(0.55 * 100);
}
void Lock()
{
Motor1.lockMotor();
Motor2.lockMotor();
}