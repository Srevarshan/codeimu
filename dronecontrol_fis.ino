#include "droneflcfis.h"
#include "imu_gyro.h"
int m1p1=3;
int m1p2=4;
int m2p1 = 5;
int m2p2 = 6;
int m3p1 = 9;
int m3p2 = 10;
int m4p1 =11;
int m4p2 =12;
int e11=2;
int e12 = 7;
int e21 = 8;
int e22 = 13;
float RV;
void setup()
{
  pinMode(e11,OUTPUT);
  pinMode(e12,OUTPUT);
  pinMode(e21,OUTPUT);
  pinMode(e21,OUTPUT);
  pinMode(m1p1,OUTPUT);
  pinMode(m1p2,OUTPUT);
  pinMode(m2p1,OUTPUT);
  pinMode(m2p2,OUTPUT);
  pinMode(m3p1,OUTPUT);
  pinMode(m3p2,OUTPUT);
  pinMode(m4p1,OUTPUT);
  pinMode(m4p2,OUTPUT);
   Serial.begin(57600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  Wire.setClock(400000);
  Wire.begin();
  delay(250);
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  Serial.begin(9600);
}
void loop()
{
   gyrosignal();
    // Read Input: roll
    g_fisInput[0] = abs(AngleRoll);
    // Read Input: pitch
    g_fisInput[1] = abs(AnglePitch);
    // Read Input: yaw
    g_fisInput[2] = 0;
     g_fisOutput[0] = RollV;
    g_fisOutput[1] = RollP;
        g_fisOutput[0] = 0;
    g_fisOutput[1] = 0;
    g_fisOutput[2] = 0;

    fis_evaluate();
  if(AngleRoll<0)
  {
    RV=map(RollV,0,5,0,255);
    motor1();
    motor2();
  }
  if(AngleRoll>0)
  {
  RV=map(RollV,0,5,0,255);
  motor3();
  motor4();
  }
 Serial.println(RV);
}
void motor1()
{
  analogWrite(m1p1,RV);
  digitalWrite(e11,HIGH);
  digitalWrite(m1p2,LOW);
}
void motor2()
{
  analogWrite(m2p2,RV);
  digitalWrite(e12,HIGH);
  digitalWrite(m2p1,LOW);
}

void motor3()
{
  analogWrite(m3p1,RV);
  digitalWrite(e21,HIGH);
  digitalWrite(m3p2,LOW);
}
void motor4()
{
  analogWrite(m4p2,RV);
  digitalWrite(e22,HIGH);
  digitalWrite(m4p1,LOW);
}