#include <Tiny4kOLED.h>
#include <Wire.h>
#include <font16x32digits.h>
#include <font11x16.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp; // I2C
unsigned long startTime = 0;  // Время начала отсчета
float StartAlter = 0;
int Delta = 0;
// const int BUTTON1_PIN = 6;  // пин первой кнопки
// const int BUTTON2_PIN = 7;  // пин второй кнопки
int reverse;
float curAlt, altitude;
unsigned long Timer2 = 0;
void setup() {
  oled.begin();
  oled.clear();
  oled.on();
  oled.invertOutput(false);
  oled.setFont(FONT6X8);
  oled.print("Altimetr ver.181124");
  delay(1000);
  oled.clear();
  //--
  Serial.begin(9600);
  Wire.begin();


if (!bmp.begin(0x76)) {
Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
while (1);}

bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_63); /* Standby time. */

//--BMPE280 setup end
oled.println("Barometric sensor-OK");
delay (1000);
oled.clear();
  Serial.println("Done with setup!");

 altitude = bmp.readAltitude(1013.25);   
}

void loop() {
if ((millis() - Timer2) > 250) {
 
 altitude = bmp.readAltitude(1013.25);
  
  oled.setFont(FONT16X32DIGITS);
  oled.setCursor(0, 0);
  float curAlt = altitude + Delta - StartAlter;
  int display = curAlt ;
  float decimalPart =  curAlt - display;
  if((curAlt <0)& (curAlt>-1)) {oled.print("-");}
  oled.print(display);
  oled.print(".");
if (decimalPart < 0) {
  decimalPart *= -1;
}
String numberString = String (decimalPart*10);
oled.print(numberString.charAt(0));
Timer2 = millis();
  // отработка очищения дисплея при изменении значения высоты с минус на плюс
}

  if ((curAlt > 0)  & (reverse == -1)) {
    oled.clear();
    reverse = 1;
  }
  if ((curAlt < 0) & (reverse == 1)) { 
     oled.clear();
    reverse = -1;
  }
  // Очитска дисплея каждую минуту
 if ((millis() - startTime) > 60000) {
   oled.clear();
   startTime = millis();
 }; 
 
   oled.setFont(FONT8X16);
  oled.setCursor(65, 0);
   // обображение высоты на какой был сброс, "нулевая" высота
   int intStartAlter = round(StartAlter);
   oled.println(intStartAlter);
   oled.setCursor(90, 0);
 
// отображение введенной поправки
  
if (Delta > -9)
{
  oled.setFont(FONT16X32DIGITS);
}
else {
oled.setFont(FONT8X16);
}
oled.println(Delta);


// отработка нажатия кнопок
  int buttonBlueState = digitalRead(10);
  int buttonRedState = digitalRead(6);


  if (buttonBlueState && !buttonRedState) {  // если нажата только первая кнопка
    
    if (buttonBlueState && !buttonRedState) {  // если первая кнопка все еще нажата и вторая не нажата
      Delta = Delta - 1;                      
      oled.clear();
      oled.setFont(FONT16X32DIGITS);
      oled.setCursor(0,0);
      oled.print("D=");
      oled.setCursor(15,0);
      oled.print(Delta);
      delay(1000);  // ждем 1 секунду
      oled.clear();
    }
  } else if (!buttonBlueState && buttonRedState) {  // если нажата только вторая кнопка
                                                    
    if (!buttonBlueState && buttonRedState) {       // если вторая кнопка все еще нажата и первая не нажата
      Delta = Delta + 1;
      oled.clear();
      oled.setFont(FONT6X8);
      oled.setCursor(0,2);
      oled.print("D=");
      oled.setFont(FONT16X32DIGITS);
      oled.setCursor(15,0);
      oled.print(Delta);
      delay(1000);
      oled.clear();
    }
  } else if (buttonBlueState && buttonRedState) {  // если нажаты обе кнопки
    delay(2000);                                   // ждем 2 секунды
    if (buttonBlueState && buttonRedState) {       // если обе кнопки все еще нажаты
      Serial.println("Both buttons pressed!");     // Выводим сообщение в монитор порта (для отладки)
      StartAlter = altitude;
      Delta=0;
      Serial.println(StartAlter);
      oled.clear();
      oled.setFont(FONT8X16);
      oled.println("SET ZERO ALT");
      oled.print("= ");
      oled.print(StartAlter);
      delay(3000);
      oled.clear();
    }
  }
}
