//czytanie z klawiatury
#include <Keypad.h> //biblioteka od klawiatury
 
const byte ROWS = 4; // ile wierszy
const byte COLS = 4; //ile kolumn
 
byte rowPins[ROWS] = {9, 8, 7, 6}; //piny wierszy
byte colPins[COLS] = {5, 4, 3, 2}; //piny kolum
 
char keys[ROWS][COLS] = 
{ //mapowanie klawiatury
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
 
Keypad klawiatura = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //inicjalizacja klawiatury

//czytanie portu szeregowego
char incomingByte = 0; 
char czytaj()
{
    if (Serial.available() > 0) 
  {    
    // czytanie nadchodzącej wiadomości
    incomingByte = Serial.read();
    return incomingByte;
  }
}

//funkcje

char pin[4] = {'5', '4', '3', '2'};

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
  }
}

void getPin()
{
  Serial.println("podaj pin");
  char pinto[4];
  char klawisz;
  int i = 0;
  for(i=0 ; i<4 ; i++)
  {
    while(1)
    {
      klawisz = klawiatura.getKey();
      if (klawisz)
      {
        buzzerSound(0);
        break;
      }
    }
    pinto[i] = klawisz;
  }
  if(pin[0]==pinto[0] && pin[1]==pinto[1] && pin[2]==pinto[2] && pin[3]==pinto[3])
  {
    Serial.println("pin ok");
    buzzerSound(1);
  }
  else
  {
    Serial.println("bad pin");
    buzzerSound(2);
  }
}

void setup() 
{
  Serial.begin(9600);
  pinMode(13, INPUT_PULLUP);
  pinMode(A5, OUTPUT);
}
  
void loop() 
{
  czytaj();
  switch(incomingByte)
  {
    case 't':
    {
      Serial.println("test ok");
      incomingByte = 0;
    }
    break;
    case 'p':
    {
      getPin();
      incomingByte = 0;
    }
    break;
  }
  if (digitalRead(13) == LOW)                          
  {
    getPin();
        /*Serial.println("on");          // send the data
        while(digitalRead(13) != HIGH)
        {
          delay(50);
        }
        Serial.println("off");*/
  }  
}
