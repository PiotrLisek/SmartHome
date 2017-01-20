#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial RFID = SoftwareSerial(4,5);  //lewy dol-zlacze 5pinowe -- 1 = pin4; 4=GND ; 5- 5V; 
Servo servo1; 
char readString;

int d0 = 8 ;  //pilot B
int d1 = 9 ;  //pilot D
int d2 = 10 ; //pilot A
int d3 = 11 ; //pilot C
int lock=1;
char c;
String msg;

void servo_move(int angle) {
  servo1.attach(3); //servo PIN3
  servo1.write(angle); 
  delay(500);
  servo1.detach();
  Serial.println(angle);
} 

void setup()  
{
  Serial.begin(9600);
  Serial.println("Serial Ready");
  servo_move(10); 
  RFID.begin(9600);
  Serial.println("RFID Ready");
  //pinMode(d0,INPUT) ;
  //pinMode(d1,INPUT) ;
  //pinMode(d2,INPUT) ;
}
 
void loop(){
 
  while(RFID.available()>0){
    c=RFID.read(); 
    msg += c;
  }
 
  if (msg.length() > 10) {
    msg = msg.substring(1,13);
    Serial.println(msg);


if (msg == "01063B3AAAAC") {
      if(lock == 0) {
        servo_move(140);
        lock = 1;
      } else if(lock == 1) { 
        servo_move(170);  
        lock = 0;
      }
    }
    
    msg = "";
  }

  if(digitalRead(d0) == HIGH)
  {
    servo_move(40);
    Serial.println("D0 = B   ") ;
  }
  else if(digitalRead(d1) == HIGH)
  {
    servo_move(140);
    Serial.println("D1 = D    ") ;
  }
  else if(digitalRead(d2) == HIGH)
  {

    Serial.println("D2 = A   ") ;
  }
  else if(digitalRead(d3) == HIGH)
  {

    Serial.println("D3 = C    ") ;
  }
    delay(200);
}
