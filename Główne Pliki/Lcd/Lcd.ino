//===========================================LCD=========================================================
#include <LiquidCrystal.h> 
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//==========================================Zmienne Globalne=============================================
const char* menuItems[]=
{
  "      MENU",
  "Otwarcie szafki", 
  "Zmiana pinu", 
  "Buzzer on/off",
  "Ust daty/godziny",
};
char incomingByte = '~'; 
bool czyOn = true;
double ileRazy = 0;
//==========================================czytanie portu szeregowego===================================
char czytaj()
{
    if (Serial.available() > 0) 
  {    
    // czytanie nadchodzącej wiadomości
    incomingByte = Serial.read();
    return incomingByte;
  }
}
//=====================================================Otwieranie szafki=================================
void szafka()
{
  incomingByte = '~';
  Serial.println('s');
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Otwarcie szafki");
  lcd.setCursor(0, 1);
  lcd.print("Podaj Pin: ");
  while(1)
  {
    czytaj();
    if(incomingByte == 'B')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Anulowano");
      delay(1000);
      return;
    }
    else if(incomingByte == 'z')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bledny Pin");
      delay(1000);
      return;      
    }
    else if(incomingByte == 'o')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Otworzono");
      delay(1000);
      return;
    }
    else if(incomingByte != '~')
    {
      lcd.print("*");
      incomingByte = '~';
    }
  }
}
//=====================================================Zmiana Pinu=======================================
void zmPin()
{
  incomingByte = '~';
  ileRazy = 0;
  Serial.println('z');
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Zmiana Pinu");
  lcd.setCursor(0, 1);
  lcd.print("Stary Pin: ");
  while(1)
  {
    czytaj();
    if(incomingByte == 'B')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Anulowano");
      delay(1000);
      return;
    }
    else if(incomingByte == 'z')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bledny Pin");
      delay(1000);
      return;      
    }
    else if(incomingByte == 'o' && ileRazy == 0)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Stary Pin OK!");
      lcd.setCursor(0, 1);
      lcd.print("Nowy Pin: ");
      ileRazy++;
    }
    else if(incomingByte == 'o' && ileRazy == 1)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Powtorz Pin");
      lcd.setCursor(0, 1);
      lcd.print("Nowy Pin: ");
      ileRazy++;
    }
    else if(incomingByte == 'o' && ileRazy == 2)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Zmieniono Pin");
      delay(1000);
      ileRazy = 0;
      return;      
    }
    else if(incomingByte != '~')
    {
      lcd.print("*");
    }
    incomingByte = '~'; 
  }
}
//=====================================================Buzzer on/off=====================================
/*void buzzer()
{
  int i = 1;
  Serial.println('b');
  while(1)
  {
    czytaj();
    switch(incomingByte)
    {
      case 'A':
      {
        Serial.println(i);
        ileRazy = 0;
        incomingByte = '~';
      }
      break;
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '0':
      case '*':
      case '#':
      case 'B':
      {
        ileRazy = 500000;
        incomingByte = '~';
      }
      break;
      case 'C':
      {
        i=1;
      }
      break;
      case 'D':
      {
        i=0;
      }
      break;
      default:
      {
        if(ileRazy<=500000 && czyOn == true)
        {
          ileRazy ++;
        }
      }
      break;
    }
    if(ileRazy==500000&& czyOn == true)
    {
      ileRazy = 0;
   //   lcd_print(0);
      break;
    }
  }
}*/

//=====================================================Wybór funkcji=====================================
void wybor(int x)
{
  switch(x)
  {
    case 1:
      szafka();
    break;
    case 2:
      zmPin();
    break;
    case 3:
   //   buzzer();
    break;
    case 4:
   //   setTime();
    break;      
    
  }
}
//=====================================================Wyświetlanie_menu=================================
void lcd_print(int x)
{
  ileRazy = 0;
  switch(x)
  {
    case 0:
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("TEMP 21,7");
      lcd.print((char)223); 
      lcd.print(" 21:25");
      lcd.setCursor(0, 1);
      lcd.print("sob 21 STY 2016");
      incomingByte = '~';
    }
    break;
    default:
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(menuItems[0]);
      lcd.setCursor(0, 1);
      lcd.print(menuItems[x]);  
      incomingByte = '~';
    }
    break;
  }
}
//======================================================MENU=============================================
void menu()
{
  int i = 1;
  lcd_print(i);
  while(1)
  {
    czytaj();
    switch(incomingByte)
    {
      case 'A':
      {
        if(czyOn == false)
        {
          digitalWrite(8, HIGH);
          czyOn = true;
          ileRazy = 0;
        }
        wybor(i);
        incomingByte = '~';
      }
      break;
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '0':
      case '*':
      case '#':
      case 'B':
      {
        ileRazy = 500000;
        incomingByte = '~';
      }
      break;
      case 'C':
      {
        if(i>1)
        {
          i--;
        }
        lcd_print(i);
      }
      break;
      case 'D':
      {
         if(i<((sizeof menuItems/sizeof *menuItems)-1))
        {
          i++;
        }
        lcd_print(i);
      }
      break;
      default:
      {
        if(ileRazy<=500000 && czyOn == true)
        {
          ileRazy ++;
        }
      }
      break;
    }
    if(ileRazy==500000&& czyOn == true)
    {
      ileRazy = 0;
      lcd_print(0);
      break;
    }
  }
}

//===========================================================Czujnik gazu========================================
void gaz() {
  int gasPin = A0;
  if(analogRead(gasPin) > 200) {
    digitalWrite(13, HIGH);
    Serial.println(analogRead(gasPin));
    //delay(1000);
  }
  else{
    //digitalWrite(13, LOW);
  }
}

//===========================================================Servo================================================
#include <Servo.h>
Servo servo1; 
void servo_move(int angle) {
  
  servo1.attach(10); //servo PIN3
  servo1.write(angle); 
  delay(500);
  servo1.detach();
  Serial.println(angle);
}

//===========================================================RFID================================================
#include <SoftwareSerial.h>
SoftwareSerial RFID = SoftwareSerial(9,10);

void rfid(){
  char readString;
  int lock=1;
  char c;
  String msg;
  
  while(RFID.available()>0){
    c=RFID.read(); 
    msg += c;
  }
 
  if (msg.length() > 10) {
    msg = msg.substring(1,13);
    Serial.println(msg);


  if (msg == "01063B3AAAAC") {
      if(lock == 0) {
        lock = 1;
        servo_move(20);
      } else if(lock == 1) {   
        lock = 0;
        servo_move(120);
      }
    }
    
    msg = "";
  }
  delay(100);
}

//===========================================================Kontaktron===================================
void kontaktron(){
  if (digitalRead(12) == 1) {
    digitalWrite(13, HIGH);
    //Serial.println("Kontaktron otwarty");
  } else {
    digitalWrite(13, LOW);
  }
}

//======================================================SETUP============================================
void setup() 
{
  Serial.begin(9600);
  RFID.begin(9600);
  Serial.println("RFID Ready");
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0); 
  lcd.print("TEMP 21,7");
  lcd.print((char)223);
  lcd.print(" 21:25"); 
  lcd.setCursor(0, 1);
  lcd.print("sob 21 STY 2016");
  digitalWrite(8, HIGH);
  pinMode(12, INPUT_PULLUP);
  
}

//===========================================================LOOP========================================
void loop() 
{
  /*
  //Włączanie i wyłączanie podświetlenia lcd
  digitalWrite(8, LOW);
  delay(1000);
  digitalWrite(8, HIGH);
  delay(1000);
  */
  gaz();
  rfid();
  kontaktron();
  czytaj();
  while(incomingByte!='~')
  {
    gaz();
    if(incomingByte == 'p')
    {
      Serial.println(sizeof menuItems/sizeof *menuItems);
      Serial.println(ileRazy);
      Serial.println(czyOn);
      incomingByte = '~';
    }
    else if(incomingByte == 'A')
    {
      if(czyOn == false)
      {
        digitalWrite(8, HIGH);
        czyOn = true;
        ileRazy = 0;
      }
      menu();
    }
    else
    {
      if(czyOn == false)
      {
        digitalWrite(8, HIGH);
        czyOn = true;
        
      }
      ileRazy = 0;
      incomingByte = '~';
    }
  }
  if(ileRazy<=500000 && czyOn == true)
  {
    ileRazy ++;
  }
  else if(ileRazy>=500000&& czyOn == true)
    {
      ileRazy = 0;
      czyOn = false;
      digitalWrite(8, LOW);
    }
}
