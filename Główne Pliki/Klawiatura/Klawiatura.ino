//czytanie z klawiatury
#include <Keypad.h> //biblioteka od klawiatury
#include <Servo.h>
#include <SoftwareSerial.h>
//===================================================klawiatura=====================================================
const byte ROWS = 4; // ile wierszy
const byte COLS = 4; //ile kolumn
 
byte rowPins[ROWS] = {9, 8, 7, 6}; //piny wierszy
byte colPins[COLS] = {5, 4, 3, 2}; //piny kolum
 
char keys[ROWS][COLS] = 
{ //mapowanie klawiatury
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'z','0','#','D'}
};
 
Keypad klawiatura = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //inicjalizacja klawiatury
//================================================zmienne globalne=================================================

char pin[4] = {'5', '4', '3', '2'};
char incomingByte = 0;
char klawisz;
int ile = 0;
int lock = 1;

//================================================czytanie portu szeregowego========================================
char czytaj()
{
    if (Serial.available() > 0) 
  {    
    // czytanie nadchodzącej wiadomości
    incomingByte = Serial.read();
    return incomingByte;
  }
}

//==============================================lisa dzwiekow buzzera===============================================
void buzzerSound(int x)
{
  int i;
  switch(x)
  {
    case 0:  //dzwiek wczytania klawisza
    {
      digitalWrite(A5,HIGH);
      delay(10);
      digitalWrite(A5,LOW);
      break;
    }
    case 1:   // kod poprawny
    {
        for(i=0 ; i<3 ; i++)
        {
          digitalWrite(A5,HIGH);
          delay(50);
          digitalWrite(A5,LOW);
          delay(50);
        }
        break;
    }
    case 2:   // kod błędny
    {
        for(i=0 ; i<3 ; i++)
        {
          digitalWrite(A5,HIGH);
          delay(500);
          digitalWrite(A5,LOW);
          delay(50);
        }
        break;
    }
    case 3:   // drzwi otwarte
    {
        for(i=0 ; i<500 ; i++)
        {
          digitalWrite(A5,HIGH);
          delay(5);
          digitalWrite(A5,LOW);
          delay(5);
        }
        break;
    }
  }
}

//==============================================wczytywanie pinu=====================================================
int getPin()
{
  //Serial.println("podaj pin");
  char pinto[4];
  int i = 0;
  for(i=0 ; i<4 ; i++)
  {
    while(1)
    {
      klawisz = klawiatura.getKey();
      if (klawisz)
      {
        buzzerSound(0);
        if (klawisz >= '0' && klawisz <= '9')
        {
          Serial.print(klawisz);
          break;
        }
        else if(klawisz == 'B')
        {
          Serial.print(klawisz);
          return 0;
        }
      }
    }
    pinto[i] = klawisz;
  }
  if(pin[0]==pinto[0] && pin[1]==pinto[1] && pin[2]==pinto[2] && pin[3]==pinto[3])
  {
    Serial.print('o');
    buzzerSound(1);
    return 1;
  }
  else
  {
    delay(100);
    Serial.print('z');
    buzzerSound(2);
    return 0;
  }
}
//==============================================zmiana pinu=========================
void changePin()
{
  char pinto[4];
  int i;
  char pintocheck[4];
  if(getPin())
  {
    for(i=0 ; i<4 ; i++)
    {
      while(1)
      {
        klawisz = klawiatura.getKey();
        if (klawisz)
        {
          buzzerSound(0);
          if (klawisz >= '0' && klawisz <= '9')
          {
            Serial.print(klawisz);
            break;
          }
          else if(klawisz == 'B')
          {
            Serial.print(klawisz);
            return;
          }
        }
      }
      pinto[i] = klawisz;
    }
    Serial.print('o');
    buzzerSound(1);
    for(i=0 ; i<4 ; i++)
    {
      while(1)
      {
        klawisz = klawiatura.getKey();
        if (klawisz)
        {
          buzzerSound(0);
          if (klawisz >= '0' && klawisz <= '9')
          {
            Serial.print(klawisz);
            break;
          }
          else if(klawisz == 'B')
          {
            Serial.print(klawisz);
            return;
          }
        }
      }
      pintocheck[i] = klawisz;
    }
    if(pinto[0]==pintocheck[0] && pinto[1]==pintocheck[1] && pinto[2]==pintocheck[2] && pinto[3]==pintocheck[3])
    {
       for(i=0 ; i<4 ; i++)
       {
         pin[i]=pinto[i];        
       }
       buzzerSound(1);
       Serial.print('o');
    }
    else
    {
       buzzerSound(2);
       Serial.print('z');      
    }
  }
}
//===========================================================Czujnik gazu========================================
int gaz() 
{
  int gasPin = A0;
  if (analogRead(gasPin) > 600) 
  {
    ile++;
  }
  else 
  {
    ile = 0;  
  }
  return (ile>10000) ? 1 : 0;
}


//===========================================================Servo================================================
Servo servo1;
void servo_move(int angle) {

  servo1.attach(10); //servo PIN3
  servo1.write(angle);
  delay(500);
  servo1.detach();
}
//===========================================================Kontaktron===================================
void kontaktron() 
{
  if (digitalRead(12) == HIGH) 
  {
  } 
  else if (lock == 0 && digitalRead(12) == LOW) 
  {
    lock = 1;
    servo_move(20);
  }
}
//===========================================================RFID================================================
SoftwareSerial RFID = SoftwareSerial(11, 12);

void rfid() 
{
  char readString;

  char c;
  String msg;

  while (RFID.available() > 0) 
  {
    c = RFID.read();
    msg += c;
  }

  if (msg.length() > 10) 
  {
    msg = msg.substring(1, 13);
    Serial.println(msg);
    if (msg == "01063B3AAAAC") 
    {
      if (lock == 1) 
      {
        lock = 0;
        servo_move(120);
      }
    }
    msg = "";
    delay(500);
  }
}
//==============================================setup=============================
void setup() 
{
  Serial.begin(9600);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(A5, OUTPUT);
  RFID.begin(9600);
}
  
void loop() 
{
  rfid();
  kontaktron();
  if(gaz())
  {
    Serial.println('l');
    digitalWrite(A5,HIGH);
    while(!klawisz)
    {
      klawisz = klawiatura.getKey();
    }
     digitalWrite(A5,LOW);
     Serial.println('k');
  }
  czytaj();
  if(incomingByte!='~')
  {
    switch(incomingByte)
    {
      case 's':
      {
        if (getPin() && lock == 1) 
         {
           lock = 0;
           servo_move(120);
           buzzerSound(3);
         }
        incomingByte = '~';
      }
      break;
      case 'z':
      {
        changePin();
        incomingByte = '~';
      }
      break;
    }
  }
  klawisz = klawiatura.getKey();
  if (klawisz)
  {
    buzzerSound(0);
    Serial.print(klawisz);
  } 
}
