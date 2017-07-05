/*
  Multple Serial test

 Receives from the main serial port, sends to the others.
 Receives from serial port 1, sends to the main serial (Serial 0).

 This example works only with boards with more than one serial like Arduino Mega, Due, Zero etc

 The circuit:
 * Any serial device attached to Serial port 1
 * Serial monitor open on Serial port 0:

 created 30 Dec. 2008
 modified 20 May 2012
 by Tom Igoe & Jed Roach
 modified 27 Nov 2015
 by Arturo Guadalupi

 This example code is in the public domain.

 */ 


void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
}

int cnt = 0;
int cnt2 = 0;
int cnt3 = 0;
byte arr2[200];
char arr [200];
bool flag = false;
bool flag2 = false;
int data = 0;
void loop() {
  // read from port 1, send to port 0:
  if (Serial1.available()) {
    byte inByte = Serial1.read();
    if(inByte =='\n' && flag) {
      flag = false;
      flag2 = false;
      Serial.print(" * 2 = ");
      data = data * 2;
      Serial.print(data);
      cnt3 = -1;
      data = 0;
    }
    if(flag && flag2 && inByte != 13) {
      data = data * 10;
      data += int(inByte) - 48;
    }
    if(inByte =='A' && cnt3 == 0) {
      flag = true;
      Serial.print("Type - Analog");
      inByte = '\n';
    }
    if(inByte == 'C' && cnt3 == 0) {
      Serial.print("Type - Chat");
      inByte = '\n';
    }
    if(cnt3 == 1){
      Serial.print("Size - ");
    }
    if(inByte == ':'){
      Serial.write('\n');
      Serial.print("Data -");
      inByte = ' ';
      flag2 = true;
    }
    Serial.write(inByte);
    cnt3++;
  }

  if(cnt > 30000) {
    int sensorValue = analogRead(A0);
    int dataSize = 0;
    int a = 1;
    for(int i = 1; i <= 5; i++){
      if(sensorValue / a > 0){
        dataSize = i;
      }
      a  = a * 10;
    }
    Serial1.write("A");
    Serial1.print(dataSize);
    Serial1.write(":");
    Serial1.print(sensorValue);
    Serial1.println();
    cnt = 0;
  }
  

  // read from port 0, send to port 1:
  if (Serial.available()) {
    if(cnt2 == 0) {
      Serial1.write("C");
    }
    byte inByte = Serial.read();
    arr2[cnt2] = inByte;
    cnt2++;
    if(inByte == '\n') {
      for(int i = 0; i < cnt2; i++){
        if(i == 0) {
          Serial1.print(cnt2 - 2);
          Serial1.write(":");
        }
        Serial1.write(arr2[i]);
      }
      cnt2 = 0;
    }
  }
  cnt++;  
}
