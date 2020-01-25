/* GE 1500/1501 Final Project Arduino Component*/
/* Measuring, Calcultaing, and Displaying Electrical Output */

#include <LiquidCrystal.h>

byte V[] = {
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001,
  B10001,
  B00000,
};


byte o[] = {
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01110,
  B00000,
  B00000,
};

byte l[] = {
  B00000,
  B01110,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00110,
};

byte t[] = {
  B00000,
  B01100,
  B10010,
  B00010,
  B00010,
  B00111,
  B00010,
  B00010,
};

byte a[] = {
  B00000,
  B11110,
  B10001,
  B11110,
  B10000,
  B01110,
  B00000,
  B00000,
};

byte g[] = {
  B01110,
  B10000,
  B11110,
  B10001,
  B10001,
  B11110,
  B00000,
  B00000,
};

byte e[] = {
  B00000,
  B01110,
  B00001,
  B11111,
  B10001,
  B01110,
  B00000,
  B00000,
};

byte P[] = {
  B00000,
  B00001,
  B00001,
  B00001,
  B01111,
  B10001,
  B10001,
  B01111,
};

byte w[] = {
  B00000,
  B01010,
  B10101,
  B10101,
  B10001,
  B10001,
  B00000,
  B00000,
};

byte r[] = {
  B00000,
  B00001,
  B00001,
  B00001,
  B10011,
  B01101,
  B00000,
  B00000,
};

byte n[][8] = {
{
  B01110,
  B10001,
  B10011,
  B10101,
  B11001,
  B10001,
  B01110,
  B00000,
},{
  B01110,
  B00100,
  B00100,
  B00100,
  B00100,
  B00110,
  B00100,
  B00000,

},{
    B11111,
  B00010,
  B00100,
  B01000,
  B10000,
  B10001,
  B01110,
  B00000,

},{
    B01110,
  B10001,
  B10000,
  B01000,
  B00100,
  B01000,
  B11111,
  B00000,

},{
  
  B01000,
  B01000,
  B11111,
  B01001,
  B01010,
  B01100,
  B01000,
  B00000,
},{
    B01110,
  B10001,
  B10000,
  B01111,
  B00001,
  B00001,
  B11111,
  B00000,

},{
    B01110,
  B10001,
  B10001,
  B01111,
  B00001,
  B10010,
  B01100,
  B00000,

},{
  B00100,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000,
  B11111,
  B00000,

},{
    B01110,
  B10001,
  B10001,
  B01110,
  B10001,
  B10001,
  B01110,
  B00000,

},{
  B00110,
  B01001,
  B10000,
  B11110,
  B10001,
  B10001,
  B01110,
  B00000,

}
};

byte period[] = {
  B01100,
  B01100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
long previousTime = 0;
int dt = 0;
float highestVoltage = 0;
float voltage = 0;
float energy = 0;
float accumulatedElectricity = 0;

float load = .5;

long start = 0;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  lcd.begin(16, 2);

  lcd.createChar(0, n[1]);
  lcd.createChar(1, n[2]);
  lcd.createChar(2, n[3]);
  lcd.createChar(3, n[4]);
  lcd.createChar(4, n[5]);
  lcd.createChar(5, n[7]);
  lcd.createChar(6, V);
  lcd.createChar(7, period);
}

void loop() {
  
  voltage = (analogRead(0) / 1023.0) * 5;
  
  if (voltage > highestVoltage)
    highestVoltage = voltage;

  if (millis() - start > 100) {
    lcd.clear();
  
  // print v
    lcd.setCursor(15, 1);
    lcd.write((uint8_t) 6);
      
    lcd.setCursor(14, 1);
    lcd.print(":");
    
    displayFloat(highestVoltage, 1, 12);
    
    lcd.setCursor(8, 1);
    lcd.write((uint8_t) 6);
  
  // print p
    lcd.setCursor(15, 0);
    lcd.print("d");
    
    lcd.setCursor(14, 0);
    lcd.print(":");
    
    displayFloat((highestVoltage * highestVoltage) / load, 0, 12);
    
    lcd.setCursor(8, 0);
    lcd.print("M");
    
  // print I
    lcd.setCursor(6, 1);
    lcd.print("I");
    
    lcd.setCursor(5, 1);
    lcd.print(":");
    
    displayFloat(highestVoltage / load, 1, 3);
    
    analogWrite(3, (int) (voltage * 255));

    start = millis();
  
  }
 
  energy=voltage*voltage/load ; 

  Serial.print(micros());
  Serial.print(" ");
  Serial.println(energy);
}

void displayFloat(float f, int r, int c) {
  int d = (int) (f * 100);
  
  displayDigit(d / 100, r, c);

// period
  lcd.setCursor(c - 1, r);
  lcd.write((uint8_t) 7);
    
  displayDigit((d % 100) / 10, r, c - 2);
  
  displayDigit((d % 10), r, c - 3);
  
}

void displayDigit(int d, int r, int c) {
  lcd.setCursor(c, r);

  switch (d) {
    case 0:
      lcd.print("0");
      break;
    case 1:
      lcd.write((uint8_t) 0);
      break;
    case 2:
      lcd.write((uint8_t) 1);
      break;
    case 3:
      lcd.write((uint8_t) 2);
      break;
    case 4:
      lcd.write((uint8_t) 3);
      break;
    case 5:
      lcd.write((uint8_t) 4);
      break;
    case 6:
      lcd.print("9");
      break;
    case 7:
      lcd.write((uint8_t) 5);
      break;
    case 8:
      lcd.print("8");
      break;
    case 9:
      lcd.print("6");
      break;
  }
}
