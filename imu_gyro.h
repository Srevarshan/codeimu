#include <Wire.h>
float rateroll,ratepitch,rateyaw;
float ratecalibroll,ratecalibpitch,ratecalibyaw;
int calibnum;
float accx,accy,accz;
float AngleRoll,AnglePitch;
float looptimer;
void gyrosignal()
{
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x68,6);
  int16_t accxlsb=Wire.read()<<8|Wire.read();
  int16_t accylsb=Wire.read()<<8|Wire.read();
  int16_t acczlsb=Wire.read()<<8|Wire.read();
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x8);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0x68,6);
  int16_t gyrox=Wire.read()<<8|Wire.read();
  int16_t gyroy=Wire.read()<<8|Wire.read();
  int16_t gyroz=Wire.read()<<8|Wire.read();
  rateroll=(float)gyrox/65.5;
  ratepitch=(float)gyroy/65.5;
  rateyaw=(float)gyroz/65.5;
  accx=(float)accxlsb/4096;
  accy=(float)accylsb/4096;
  accz=(float)acczlsb/4096;
  AngleRoll=atan(accy/sqrt(accx*accx+accz*accz))*1/(3.14/180);
  AnglePitch=atan(accx/sqrt(accy*accy+accz*accz))*1/(3.14/180);
}
/*void setup()
{
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
  /*for(calibnum=0;calibnum<2000;calibnum++)
  {
    gyrosignal();
    ratecalibroll+=rateroll;
    ratecalibpitch+=ratepitch;
    ratecalibyaw+=rateyaw;
    delay(1);
  }
  ratecalibroll/=2000;
  ratecalibpitch/=2000;
  ratecalibyaw/=2000;*/
