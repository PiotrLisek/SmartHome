
//===========================================LCD=========================================================
#include <LiquidCrystal.h> //Dołączenie bilbioteki
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza
//======================================================SETUP============================================
void setup() 
{
  Serial.begin(9600);
  pinMode(8, OUTPUT); //ustawienie pinu 8 jako output
  lcd.begin(16, 2); //Deklaracja typu
  lcd.setCursor(0, 0); //Ustawienie kursora
  lcd.print("TEMP 21,7");
  lcd.print((char)223);
  lcd.print(" 21:25"); //Wyświetlenie tekstu
  lcd.setCursor(0, 1); //Ustawienie kursora
  lcd.print("sob 21 STY 2016"); //Wyświetlenie tekstu
  digitalWrite(8, HIGH);
}
//==========================================Zmienne Globalne=============================================
const char* menuItems[]=
{
  "      MENU",
  "Otwarcie szafki", 
  "Zmiana pinu", 
  "Buzzer on/off",
  "----------------",
};
char incomingByte = 0; 
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
//=====================================================Wyświetlanie_menu=================================
void lcd_menu(int x)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(menuItems[0]);
  lcd.setCursor(0, 1);
  lcd.print(menuItems[x]);  
}
//======================================================MENU=============================================
void menu()
{
  lcd_menu(1);
  while(1)
  {
    czytaj();
    switch(incomingByte)
    {
      case 'p':
      {
        Serial.println(incomingByte);
        Serial.println(ileRazy);
        Serial.println(czyOn);
        incomingByte = '~';
      }
      break;
      case 'A':
      {
        if(czyOn == false)
        {
          digitalWrite(8, HIGH);
          czyOn = true;
          ileRazy = 0;
        }
        // menu();
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
      case 'C':
      case 'D':
      {
        if(czyOn == false)
        {
          digitalWrite(8, HIGH);
          czyOn = true;
          ileRazy = 0;
        }
        incomingByte = '~';
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
  }
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
  czytaj();
  switch(incomingByte)
  {
    case 'p':
    {
      Serial.println(incomingByte);
      Serial.println(ileRazy);
      Serial.println(czyOn);
      incomingByte = '~';
    }
    break;
    case 'A':
    {
      if(czyOn == false)
      {
        digitalWrite(8, HIGH);
        czyOn = true;
        ileRazy = 0;
      }
      menu();
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
    case 'C':
    case 'D':
    {
      if(czyOn == false)
      {
        digitalWrite(8, HIGH);
        czyOn = true;
        ileRazy = 0;
      }
      incomingByte = '~';
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
      czyOn = false;
      digitalWrite(8, LOW);
    }
}
