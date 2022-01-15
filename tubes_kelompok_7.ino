#include <LiquidCrystal.h>
#define LEDR 1
#define LEDG 12
#define LEDB 13

int r = 0,g = 0,b = 0,buzz=5,ping=6,pir=10,ping2=11,i;
int status_but=0,status_ping=0,status_ping2=0,status_pir=0,status_but2=0;
double inch=0,nilai_ping1=0,nilai_ping2=0;
const int D1_p=A0,D1_n=A1,D2_p=A2,D2_n=A3, but1=A5,but2=A4;
bool din=LOW; 
  
LiquidCrystal lcd(9, 8, 7, 4, 3, 2);

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(ping, INPUT);
  pinMode(ping2, INPUT);
  pinMode(pir, INPUT);
  pinMode(D1_p, OUTPUT);
  pinMode(D1_n, OUTPUT);
  pinMode(D2_p, OUTPUT);
  pinMode(D2_n, OUTPUT);
  pinMode(but1, OUTPUT);
  pinMode(but2, OUTPUT);
  lcd.clear();
  for(int i=0; i<=16; i++)
  {
  	lcd.setCursor(i,0);
    lcd.print("Selamat Datang");
    delay(100);
    lcd.clear();
    lcd.setCursor(i,1);
    lcd.print("  7_GARAGE  ");
  }
  for(int i=16; i>=0; i--)
  {
  	lcd.clear();
    lcd.setCursor(i,1);
    lcd.print("    7_GARAGE  ");
    lcd.setCursor(i,0);
    lcd.print(" Selamat Datang");
    delay(100);
  }
}

void loop() 
{
  nilai_ping1 = 0.01723 * readUltrasonicDistance(ping);
  nilai_ping2= 0.01723 * readUltrasonicDistance(ping2);
  inch = (nilai_ping1 / 2.54);
  /*
  lcd.setCursor(0, 0);
  lcd.print("P1: ");
  lcd.print(nilai_ping1);
  lcd.print(" ");
  lcd.print(inch);
  
  lcd.setCursor(0,1);
  lcd.print("P2: ");
  lcd.print(nilai_ping2);
  */
  
  status_pir = digitalRead(pir);
  status_ping=nilai_ping1;
  status_ping2=nilai_ping2;
  status_but=digitalRead(but1);
  status_but2=digitalRead(but2);
  if ((status_pir == LOW && status_ping < 50) || status_but == HIGH) 
  {
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, LOW);
    delay(100);
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, HIGH);
    delay(100);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, HIGH);
    delay(100);
    tone(buzz, 5000, 50);
    analogWrite(D1_p, 255);
    analogWrite(D1_n, 0);
    analogWrite(D2_p, 0);
    analogWrite(D2_n, 255);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Pintu dibuka");
    lcd.setCursor(i++,1);
    lcd.print(".");
    lcd.scrollDisplayRight();
    delay(100);
  }
  
  else if(status_pir ==HIGH && status_ping >50 && status_ping2 <20)
  {
    analogWrite(D1_p, 0);
    analogWrite(D1_n, 0);
    analogWrite(D2_p, 0);
    analogWrite(D2_n, 0);
    noTone(buzz);
    digitalWrite(LEDB, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDG, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    7_GARAGE  ");
  }
         
  else if(status_but2 == HIGH && status_pir ==LOW && status_ping > 50 && status_ping2 <20)
  {
    
    digitalWrite(LEDG, HIGH);
    analogWrite(D1_p, 0);
    analogWrite(D1_n, 255);
    analogWrite(D2_p, 255);
    analogWrite(D2_n, 0);
    tone(buzz, 5000, 1000);
    i=16;
    lcd.setCursor(0,0);
    lcd.print(" Pintu ditutup ");
    delay(100);
    lcd.clear();
  }
  else 
  {
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, LOW);
    analogWrite(D1_p, 0);
    analogWrite(D1_n, 0);
    analogWrite(D2_p, 0);
    analogWrite(D2_n, 0);
    noTone(buzz);
  }
  delay(10);
}

long readUltrasonicDistance(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  return pulseIn(pin, HIGH);
}