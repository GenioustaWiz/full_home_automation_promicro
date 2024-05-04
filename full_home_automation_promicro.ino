#include <EEPROM.h>

#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial myserial(8, 10);//rx and tx
Servo Door1; //creates a servo object to control a servo.
int relay1 = 2;//house lights on and off
int relay2 = 3;//electrical circuit on and off
int relay3 = 4;//its controlled by the pir motion sensor to light on outdoor lights.
//int relay4 = 5;//
//int relay5 = 6;
//int relay6 = 7;
//int relay7 = 8;
// int relay8 = 9;
int pirsensor = 12;
int buzzer = 13;
void setup() {
  Serial.begin(115200);
  myserial.begin(115200);
  Door1.attach(9);
  pinMode(pirsensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  //pinMode(relay4, OUTPUT);
  // pinMode(relay5, OUTPUT);
  // pinMode(relay6, OUTPUT);
  // pinMode(relay7, OUTPUT);
  //pinMode(relay8, OUTPUT);

  if (EEPROM.read(0) == 1) // Reads the EEPROM value stored to know what state the door lock was in before it was last turned off
  { // An EEPROM value of 1 means UNLOCKED and a value of 2 means LOCKED
    Door1.write(50); // Rotates the servo to the unlocked position
    delay(200);
  }
  else if (EEPROM.read(0) == 2)
  {
    Door1.write(180); // Rotates the servo to the locked position
    delay(200);
  }
  if (EEPROM.read(3) == 4) { //reads to get state of relay1
    digitalWrite(relay1, LOW);
    digitalWrite(buzzer, LOW);
    delay(200);
  }
  else if (EEPROM.read(3) == 5); { //reads to get of relay1
    digitalWrite(relay1, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(200);
  }
  if (EEPROM.read(6) == 7) { //reads to get state of relay1
    digitalWrite(relay2, LOW);
    delay(200);
  }
  else if (EEPROM.read(6) == 8); { //reads to get of relay1
    digitalWrite(relay2, HIGH);
    delay(200);
  }
  if (EEPROM.read(9) == 10) { //reads to get state of relay1
    digitalWrite(relay3, LOW);
    delay(200);
  }
  else if (EEPROM.read(9) == 11); { //reads to get of relay1
    digitalWrite(relay3, HIGH);
    delay(200);
  }
  /* if (EEPROM.read(12) == 13){//reads to get state of relay1
       digitalWrite(relay4, LOW);
       delay(200);
      }
       else if (EEPROM.read(12) == 14);{ //reads to get of relay1
              digitalWrite(relay4, HIGH);
                delay(200);
    }
    if (EEPROM.read(15) == 16){//reads to get state of relay1
       digitalWrite(relay5, LOW);
       delay(200);
      }
       else if (EEPROM.read(15) == 17);{ //reads to get of relay1
              digitalWrite(relay5, LOW);
                delay(200);
    }
    if (EEPROM.read(18) == 19){//reads to get state of relay1
       digitalWrite(relay6, LOW);
       delay(200);
      }
       else if (EEPROM.read(18) == 20);{ //reads to get of relay1
              digitalWrite(relay6, HIGH);
             delay(200);
     }
    if (EEPROM.read(21) == 22){//reads to get state of relay1
       digitalWrite(relay7, LOW);
       delay(200);
      }
       else if (EEPROM.read(21) == 23);{ //reads to get of relay1
              digitalWrite(relay7, HIGH);
                delay(200);
    }
    if (EEPROM.read(24) == 25){//reads to get state of relay1
       digitalWrite(relay8, LOW);
       delay(200);
      }
       else if (EEPROM.read(24) == 26);{ //reads to get of relay1
              digitalWrite(relay8, HIGH);
                delay(200);
       }*/
}
void loop() {
  int sensorvalue = digitalRead(pirsensor);
  if (sensorvalue == 1) {
    digitalWrite(relay1, LOW);
    digitalWrite(buzzer, HIGH);
  }
  if (myserial.available()) {
    char c = myserial.read();
    Serial.println(c);
    if (c == 'a') {

      Door1.write(180);
      delayMicroseconds(100);
      EEPROM.update(0, 2);
    }

    if (c == 'b') {

      Door1.write(50);
      delayMicroseconds(100);
      EEPROM.update(0, 1);
    }
    if (c == 'c' ) {
      digitalWrite(relay2, LOW);
      EEPROM.update(6, 7);
    }
    else if (c == 'd') {
      digitalWrite(relay2, HIGH);
      EEPROM.update(6, 8);
    }
    if (c == 'f') {
      digitalWrite(relay3, LOW);
      EEPROM.update(9, LOW);
    }
    else if (c == 'g') {
      digitalWrite(relay3, HIGH);
    }
  }
}

