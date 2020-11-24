#include <SharpIR.h>
#include "ardupin.h"

int setDefaultSpeedMotor = 150;
int dspeed = setDefaultSpeedMotor;

void motorKanan(int myspeed = setDefaultSpeedMotor);
void motorKiri(int myspeed = setDefaultSpeedMotor);

//
SharpIR sensorkiri( SharpIR::GP2Y0A21YK0F, A1 );
SharpIR sensortengah( SharpIR::GP2Y0A21YK0F, A2 );
SharpIR sensorkanan( SharpIR::GP2Y0A21YK0F, A3 );

void setup() {

  Serial.begin(9600);
  //MOTOR
  pinMode(kiriA, OUTPUT);
  pinMode(kiriIN1, OUTPUT);
  pinMode(kiriIN2, OUTPUT);

  pinMode(kananA, OUTPUT);
  pinMode(kananIN1, OUTPUT);
  pinMode(kananIN2, OUTPUT);

  pinMode(cahaya, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(buzzer,OUTPUT);
  
  digitalWrite(relay, LOW);
}

void loop() {
  int dkiri = sensorkiri.getDistance();
  int dtengah = sensortengah.getDistance();
  int dkanan = sensorkanan.getDistance();
  //Serial.print(dkiri); Serial.print(",");
  //Serial.print(dtengah); Serial.print(",");
  //Serial.print(dkanan); Serial.println(",");
  delay(100);
  //Serial.println(digitalRead(tanah));
  //Serial.println(digitalRead(cahaya));
  //cahaya terang
  if (digitalRead(cahaya) == HIGH) {
    digitalWrite(buzzer,HIGH);
    int setKiri = dspeed, setKanan = dspeed;
    if (dtengah <= 18) {
      setKiri = -230;
      setKanan = 230;

    } else if (dkiri <= 20 || dkanan <= 20) {
      setKiri = -200;
      setKanan = 200;
    }
    setMotor(setKiri, setKanan);

  } else {
    stops();
    digitalWrite(buzzer,LOW);
  }

  if (digitalRead(tanah) == HIGH) {
    stops();
    siram();
  }


}
void siram() {

  digitalWrite(relay, HIGH);
  delay(5000);
  digitalWrite(relay, LOW);

}
void motorKanan(int myspeed) {
  if (myspeed == 0) {
    analogWrite(kananA, 0);
    digitalWrite(kananIN1, LOW);
    digitalWrite(kananIN2, LOW);
  } else if (myspeed < 0) {
    myspeed = abs(myspeed);
    analogWrite(kananA, myspeed);
    digitalWrite(kananIN1, LOW);
    digitalWrite(kananIN2, HIGH);
  } else {
    analogWrite(kananA, myspeed);
    digitalWrite(kananIN1, HIGH);
    digitalWrite(kananIN2, LOW);
  }

}
void motorKiri(int myspeed) {
  if (myspeed == 0) {
    analogWrite(kiriA, 0);
    digitalWrite(kiriIN1, LOW);
    digitalWrite(kiriIN2, LOW);
  }
  else if (myspeed < 0) {
    myspeed = abs(myspeed);
    analogWrite(kiriA, myspeed);
    digitalWrite(kiriIN1, HIGH);
    digitalWrite(kiriIN2, LOW);
  } else {
    analogWrite(kiriA, myspeed);
    digitalWrite(kiriIN1, LOW);
    digitalWrite(kiriIN2, HIGH);
  }

}
void setMotor(int motorKiriSpeed, int motorKananSpeed) {
  motorKiri(motorKiriSpeed);
  motorKanan(motorKananSpeed);
}
void stops() {
  setMotor(0, 0);
}
