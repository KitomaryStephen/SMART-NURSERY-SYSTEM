#define pumppin 12
#define heaterpin 2
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <dht.h>

const int AirValue = 600; 
const int WaterValue = 350;
int soilMoistureValue = 0;
int soilmoisturepercent=0;
char keypressed;
int i1,i2,i3,i4,i5,i6,moist,humid,temp;
char c1,c2,c3,c4,c5,c6;
int pos =1;
#define outPin 11
dht DHT; 
#include <Keypad.h>

const int ROW_NUM = 4; 
const int COLUMN_NUM = 3; 

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6};  
byte pin_column[COLUMN_NUM] = {5, 4, 3}; 

Keypad myKeypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
void setup() {
  pinMode(heaterpin,OUTPUT);
  pinMode(pumppin, OUTPUT);
  lcd.begin(16,2); 
  lcd.init();
  lcd.backlight();
  newsettings();
}

void loop() {
  while(keypressed == NO_KEY){ 
  keypressed = myKeypad.getKey();
  lcd.clear();
  soil();
  dhtsensor();
  delay(100);

}
if (keypressed == '*') {
  newsettings();
  }
}

void soil(){
soilMoistureValue = analogRead(A2); 
Serial.println(soilMoistureValue);
soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
if(soilmoisturepercent >= 100)
{
  Serial.println("100 %");
  lcd.setCursor(1, 0);
  lcd.print("Soil Moisture");
  lcd.setCursor(1, 1);
  lcd.print("100 %");
  delay(2000);
  lcd.clear();
}
else if(soilmoisturepercent <=0)
{
  Serial.println("0 %");
  lcd.setCursor(1, 0);
  lcd.print("Soil Moisture");
  lcd.setCursor(1, 1);
  lcd.print("0 %");
  delay(2000);
  lcd.clear();
}
else if(soilmoisturepercent >0 && soilmoisturepercent < 100)
{
  Serial.print(soilmoisturepercent);
  Serial.println("%");
  lcd.setCursor(1, 0);
  lcd.print("Soil Moisture");
  lcd.setCursor(1, 1);
  lcd.print(soilmoisturepercent);
  lcd.print(" %");
  if (soilmoisturepercent < moist){
    digitalWrite(pumppin,1);
    
  }
  else{
    digitalWrite(pumppin,0);
  }
  delay(2000);
  lcd.clear();
}
}
void dhtsensor(){
  int readData = DHT.read11(outPin);
  
  int t = DHT.temperature;
  int h = DHT.humidity;
  if (t < temp){
    digitalWrite(heaterpin,1);
  }
  else{
    digitalWrite(heaterpin,0);
  }
  lcd.setCursor(1,0);
  lcd.print("Temp.: ");
  lcd.print(t);
  lcd.print((char)223); //shows degrees character
  lcd.print("C");

  lcd.setCursor(1,1);
  lcd.print("Humi.: ");
  lcd.print(h);
  lcd.print("%");

  delay(2000);
  lcd.clear();
}

void pump(){
  digitalWrite(pump,1);
  delay(1000);
  digitalWrite(pump,0);
}
void heater(){
  digitalWrite(heater,1);
  delay(1000);
  digitalWrite(heater,0);
}

void newsettings(){

  lcd.setCursor(1,0);
  lcd.print("Temperature");
             char keypressed2 = myKeypad.waitForKey();  
                    if (keypressed2 != NO_KEY && keypressed2 !='*' && keypressed2 !='#' )
                      {
                       c1 = keypressed2;
                       lcd.setCursor(1, 1);
                       lcd.print(c1);
                       }
                 char      keypressed3 = myKeypad.waitForKey();
                    if (keypressed3 != NO_KEY && keypressed3 !='*' && keypressed3 !='#' )
                      {
                       c2 = keypressed3;
                       lcd.setCursor(2, 1);
                       lcd.print(c2);
                       }
                  i1=(c1-48)*10;
                  i2=c2-48;
                  temp = i1 +i2;
                  delay(500);
                  lcd.clear();
                  lcd.setCursor(1,0);
             lcd.print("Humidity");
             char keypressed4 = myKeypad.waitForKey();  
                    if (keypressed4 != NO_KEY && keypressed4 !='*' && keypressed4 !='#' )
                      {
                       c3 = keypressed4;
                       lcd.setCursor(1, 1);
                       lcd.print(c3);
                       }
                 char      keypressed5 = myKeypad.waitForKey();
                    if (keypressed5 != NO_KEY && keypressed5 !='*' && keypressed5 !='#'  )
                      {
                       c4 = keypressed5;
                       lcd.setCursor(2, 1);
                       lcd.print(c4);
                       }
                  i3=(c3-48)*10;
                  i4=c4-48;
                  humid = i3 +i4;

                  delay(500);
                  lcd.clear();
                  lcd.setCursor(1,0);
                  lcd.print("Moisture:");
                  char keypressed6 = myKeypad.waitForKey();  
                    if (keypressed6 != NO_KEY && keypressed6 !='*' && keypressed6 !='#' )
                      {
                       c5 = keypressed6;
                       lcd.setCursor(1, 1);
                       lcd.print(c5);
                       }
                 char      keypressed7 = myKeypad.waitForKey();
                    if (keypressed7 != NO_KEY && keypressed7 !='*' && keypressed7 !='#'  )
                      {
                       c6 = keypressed7;
                       lcd.setCursor(2, 1);
                       lcd.print(c6);
                       }
                  i5=(c5-48)*10;
                  i6=c6-48;
                  moist = i5 +i6;
                  delay(500);
                  lcd.clear();
                  lcd.setCursor(1, 0);
                  lcd.print(temp);
                   delay(500);
                   lcd.clear();
                  lcd.setCursor(1, 0);
                  lcd.print(humid);
                   delay(500);
                   lcd.clear();
                  lcd.setCursor(1, 0);
                  lcd.print(moist);
                   delay(500);
                   lcd.clear();
                   keypressed=NO_KEY;
  }

  
