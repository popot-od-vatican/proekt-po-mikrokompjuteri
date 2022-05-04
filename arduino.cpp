#include <LiquidCrystal.h>

#define FIRST_ROW 0
#define SECOND_ROW 1

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char current[16]{'B', 'T', 'C', ' ', '3', '8', '4', '3', '2', '.',
                '2', '1', '$', ' ', ' ', ' '};
char random_chars[] = "#!@$%&()[]*=";
String coin_price = "39980.21";

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

inline void set_price()
{
  // get price
  if(Serial.available() > 0)
  {
    coin_price = "";
    char bit;
    while(Serial.available() > 0)
    {
      bit = Serial.read();
      coin_price += bit;
    }
  }
  // set price
  int i, j;
  for(i = 4, j = 0; i < 16 && j < coin_price.length(); ++i, ++j)
    current[i] = coin_price[j];
  current[i++] = '$';
  while(i < 16)
    current[i++] = ' ';
}

void move()
{
  char prev = current[15], tmp;
  for(int i = 14; i >= 0; --i)
  {
    tmp = current[i];
    current[i] = prev;
    prev = tmp;
  }
  current[15] = tmp;
}

inline void blink()
{
  lcd.clear();
  delay(400);
  lcd.print(current);
  delay(400);
}

inline void up_down()
{
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(current);
  delay(400);
  lcd.clear();
  lcd.print(current);
  delay(400);
}

inline void form()
{
  int i = 0, j = 0;
  lcd.clear();
  
  while(i < 16)
  {
    //Down Fill
    lcd.setCursor(0, 1);
    for(int k = 0; k < i; ++k)
      lcd.print(' ');
    for(j = i; j < 16; ++j)
      lcd.print(random_chars[random(0, 12)]);
    delay(50);
    // Random Char Effect
    for(int t = 0; t < 24; ++t)
    {
    	lcd.setCursor(0+i, 0);
      	lcd.print(random_chars[random(0, 12)]);
      	delay(20);
    }
    lcd.setCursor(0+i, 0);
    lcd.print(current[i++]);
    while(current[i] == ' ' && i < 16)
      ++i;
    delay(100);
  }
  lcd.clear();
}

inline void move_down()
{
	int row1 = 0, row2 = 0;
  
  	for(; row1 < 16; ++row1, ++row2)
    {
      lcd.setCursor(0, FIRST_ROW);
      for(int i = row1; i < 16; ++i)
        lcd.print(current[i]);
      lcd.setCursor(15-row2, SECOND_ROW);
      for(int i = 0; i < row1; ++i)
        lcd.print(current[i]);
      delay(100);
    }
  lcd.clear();
}


void loop()
{
  set_price();
  // move animation
  for(int t = 0; t < 3; ++t)
    for(int i = 0; i < 16; ++i)
    {
      lcd.setCursor(0, 0);
      lcd.print(current);
      move();
      delay(200);
    }
  set_price();
  // blink animation
  for(int t = 0; t < 4; ++t)
	blink();
  set_price();
  // up down animation
  for(int t = 0; t < 4; ++t)
    up_down();
  set_price();
  // form animation
  form();
  set_price();
  // move down animation
  move_down();
}
 
