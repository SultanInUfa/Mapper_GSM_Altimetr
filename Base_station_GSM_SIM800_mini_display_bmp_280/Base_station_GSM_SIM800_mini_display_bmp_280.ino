
//uint8_t	signal(void); uint8_t	_num(char); добавить в GSMSimSMS.h

//AT+COPS?\r\n

// #include <SPI.h>
// #include <LoRa.h>
#include <Tiny4kOLED.h>
#include <Wire.h>
#include <font16x32digits.h>
#include <font11x16.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp; // I2C
#include <EEPROM.h>
    #define pinPWR 9                                                                          // Вывод Arduino используемый для включения  GSM/GPRS Shield A6.
    #define pinTX  3                                                                          // Вывод Arduino TX подключаемый к выводу RX GSM/GPRS Shield A6.
    #define pinRX  2    
    #define RESETPIN 10                                                                      // Вывод Arduino RX подключаемый к выводу TX GSM/GPRS Shield A6.
    #include <SoftwareSerial.h>    
    #include <GSMSimSMS.h>
                                                           // Подключаем библиотеку SoftwareSerial для программной реализации шины UART, до подключения библиотеки iarduino_GSM.
    SoftwareSerial softSerial(pinRX, pinTX);                                                  // Создаём объект softSerial указав выводы RX и TX Arduino используемые для программной шины UART.

GSMSimSMS sms(softSerial,RESETPIN );
//    #include <iarduino_GSM.h>                                                                 // Подключаем библиотеку iarduino_GSM для работы с GSM/GPRS Shield.
//    iarduino_GSM gsm(pinPWR);                                                                 // Создаём объект gsm для работы с функциями и методами библиотеки iarduino_GSM, указав вывод PWR.
float Altitude;
int Delta =0; 
static volatile int num = 0;
//String znak;
char MapperNumberPhone[13];
char MayBeMapperNumberPhone[13] ;
//static String type_hw_sw = "1010";
unsigned long startTime=0; //время начала работы
    // char     SMStxt[161];                                                                     // Объявляем строку для хранения текста принятых SMS сообщений.
    // char     SMSnum[ 13];                                                                     // Объявляем строку для хранения номера отправителя SMS сообщений.
    // char     SMStim[ 18];                                                                     // Объявляем строку для хранения даты и времени отправки SMS сообщений.
    // uint16_t SMSlongID;                                                                       // Объявляем переменную для хранения идентификатора составного SMS сообщения.
    // uint8_t  SMSlongSUM;                                                                      // Объявляем переменную для хранения количества SMS в составном сообщении.
    // uint8_t  SMSlongNUM;                                                                      
char Restart[8]= "Restart";
char restart[8] = "restart";
char clean[6] = "clean";
char Clean[6] = "Clean";
char mapper[6] = "mapper";
char Mapper[6] = "Mapper";
//bool isNumberStored =true;
bool RecievNewNumber =false;
//char NewMapperNumber[13];
bool f=false;

void setup() {
oled.begin();  oled.clear();  oled.on(); oled.setFont(FONT8X16);
  Serial.begin(9600);
  Wire.begin();
  //Serial.println("GSM Base ver.22.12.24");
  oled.print("GSM Base v221224");
  Serial.print( "Init ... " );                                    // Выводим текст.
  error_jamp:                                                                                             //
//  Инициируем GSM/GPRS Shield и проверяем его готовность к работе:   
oled.setCursor(0,2); oled.print("Start GSM       ");
//if( !gsm.begin(softSerial)){ /*Serial.println("Error!");*/ oled.setCursor(0,2); oled.print("GSM start erorr ");}//   while(1);}
                // Инициируем работу GSM/GPRS Shield, указывая объект шины UART.
// switch( gsm.status() ){                                                                   // 
//       case GSM_OK          :                                                           break; // Модуль готов к работе.
//       case GSM_REG_NO      :                                                           break; // Требуется время ...,      на данный момент модем не зарегистрирован в сети оператора связи.
//       case GSM_SPEED_ERR   : Serial.println("UART speed setting error.");        f=1;  break; // Модуль не может работать, не удалось согласовать скорость UART.
//       case GSM_UNAVAILABLE : Serial.println("Module is not available.");         f=1;  break; // Модуль не может работать, он недоступен и не выполят AT-команды.
//       case GSM_UNKNOWN     : Serial.println("Unknown module status.");           f=1;  break; // Модуль не может работать, его статус неизвестен и корректное выполнение AT-команд не гарантируется.
//       case GSM_SLEEP       : Serial.println("Module is in sleep mode.");         f=1;  break; // Модуль не может работать, он находится в режиме ограниченной функциональности.
//       case GSM_SIM_NO      : Serial.println("No SIM-card.");                     f=1;  break; // Модуль не может работать, нет SIM-карты.
//       case GSM_SIM_FAULT   : Serial.println("Defective SIM-card.");              f=1;  break; // Модуль не может работать, SIM-карта неисправна.
//       case GSM_SIM_ERR     : Serial.println("SIM-card is not working");          f=1;  break; // Модуль не может работать, SIM-карта не прошла проверку.
//       case GSM_REG_FAULT   : Serial.println("Registration rejected");            f=1;  break; // Модуль не может работать, оператор сотовой связи отклонил регистрацию модема в своей сети.
//       case GSM_REG_ERR     : Serial.println("Registration status is undefined"); f=1;  break; // Модуль не может работать, статус регистрации в сети оператора не читается.
//       case GSM_SIM_PIN     : if( !gsm.pin("0123") )                             {f=1;} break; // Требуется ввод PIN-кода,  если PIN-код не принят, то устанавливаем флаг f.
//       case GSM_SIM_PUK     : Serial.println("Enter PUK-code");                   f=1;  break; // Требуется ввод PUK1,      данный статус свидетельствует о некорректном вводе PIN-кода 3 раза подряд, тогда нужно ввести PUK1 и новый PIN-код: gsm.puk("01234567","1234");
//       default              : /* неизвестное состояние */                         f=1;  break; // Требуется ввод PIN2, требуется ввод PUK2, ...
//     }    
 sms.init(); // use for init module. Use it if you dont have any valid reason.

  Serial.print("Set Phone Function... ");
  Serial.println(sms.setPhoneFunc(1));
  delay(1000);
//oled.setCursor(0,2); oled.print("GSM start erorr ");}//   while(1);
  Serial.print("is Module Registered to Network?... ");
  Serial.println(sms.isRegistered());
  delay(1000);

  Serial.print("Signal Quality... ");
  Serial.println(sms.signalQuality());
  delay(1000);

  Serial.print("Operator Name... ");
  Serial.println(sms.operatorNameFromSim());
  delay(1000);



  Serial.print("Init SMS... ");
  Serial.println(sms.initSMS()); // Its optional but highly recommended. Some function work with this function.
  delay(1000);

//while(gsm.status()==GSM_REG_NO ){ /*Serial.print(".");*/ delay(1000);  oled.setCursor(0,2); oled.print("waiting up GSM  ");}                      // Ждём завершения регистрации модема в сети оператора связи.
//  Если модуль не может работать, то не даём скетчу выполняться дальше:                      // 
    if(f){Serial.println( "Stop!" );} while(f){;}                                 // Предупреждаем об "остановке" программы и входим цикл while который будет выполняться бесконечно, следовательно, дальнейший код и цикл loop() не запустятся.
//  Если модуль может работать, то информируем об успешной инициализации:                     // 
    // Serial.println("Ok.");                                                                    //
    // Serial.println( "program running" );    
  oled.setCursor(0,2);
  oled.print("GSM start-OK    "); 
  delay(1000);                                                            //
    // Serial.println( F("--------------------") );                                              //
                                                                                              //
//  Установка кодировки для символов Кириллицы:                                               //
  //  gsm.TXTsendCodingDetect("п");                                                             // Выполняем автоопределение кодировки скетча для отправки текста на Русском языке.

if (!bmp.begin(0x76)) {
//Serial.println(F("Erorr BMP280"));
oled.setCursor(0,0);
oled.print(" Barometr erorr ");
goto  error_jamp;
}

bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_63); /* Standby time. */
oled.setCursor(0, 2);
oled.println("Baromet init -OK");
delay (1000);

Altitude = bmp.readAltitude(1013.25);   

oled.setCursor(0, 2);
oled.print("                ");
oled.setCursor(0, 2);
oled.print("Start h=");
oled.print(Altitude);
oled.print("m");
Serial.print("Altitude =");
Serial.println(Altitude);

//считываем сохраненный номер
 for( int k=0; k<11; k++ )
 {
  MayBeMapperNumberPhone[k]= EEPROM.read(k);
  if (((k==0) & (MayBeMapperNumberPhone[0] !=43)) || ((k==1) & (MayBeMapperNumberPhone[1] !=55)) || ((k==2) & (MayBeMapperNumberPhone[2])!=57) || ((k>2) & (!isDigit(MayBeMapperNumberPhone[k]))))  // 43 - это символ +, Российские номера 55-это код 7, 57- это код 9
  //если нет сохраненного номера - 79 и далее цифры... 
  {
//        Serial.println(MayBeMapperNumberPhone);
//        Serial.println("Not find phone number, wait sms from mapper with word 'Start/start'");  
        oled.setCursor(0, 0);
        oled.println("Send me SMS with");
        oled.print(" word - Mapper"); 
      while (!readSMS()) 
      {      //пока не получу смс с mapper|Mapper  ждем 
           delay(1500);
      }
       // strcpy(MapperNumberPhone ,NewMapperNumber);
       // oled.clear();
       
   }
  else strcpy(MapperNumberPhone,MayBeMapperNumberPhone);
}
//delay(1500);
//String hello = "New mapping day";
// Serial.println(hello);
// Serial.println("SMS to my number... ");
// Serial.println(MapperNumberPhone);
//bool firstSMS = (gsm.SMSsend("Start new mapping day", MapperNumberPhone)); 
//delay(6000);
// разобраться с плюсом в номере

if (sms.send(MapperNumberPhone, "Start new mapping day")==0)
//if ((gsm.SMSsend("Start new mapping day", MapperNumberPhone)) ==0)
{
oled.clear();
oled.setCursor(0, 0);
oled.print("error send SMS  ");
delay (3000);
goto  error_jamp;
}

oled.setCursor(0, 2);
oled.print("                ");
oled.setCursor(0, 2);
oled.print("mapN");
oled.print(MapperNumberPhone);
}

void loop() {

  float  NewAlt[10], NewAlt1 = 0;
  for (int i=0; i<10; i++) //делаем десять измерений через 6 сек
   {
    NewAlt[i] = bmp.readAltitude(1013.25);
    NewAlt1 = NewAlt1 + NewAlt[i];
    delay (1000);
    };
   NewAlt1 = NewAlt1*0.1;

  if ((abs( Altitude - NewAlt1 - Delta)) > 1.1 ) //если  изменение барометрической высоты на 1,1 м 
    {
      Delta =  Altitude - NewAlt1;
      //String delta_str = std::to_string(Delta);
      char delta_ch[3];
      itoa(Delta,(char*)delta_ch,10);
      char SMS21[20];
      String SMS2 = "New delta = " + String(Delta);
     strcpy(SMS21,SMS2.c_str());
      sms.send(MapperNumberPhone,SMS21);
      //gsm.SMSsend(SMS21, MapperNumberPhone);  
      startTime = millis();
      delay(5000);
    }  
  if ((millis() - startTime) >= 1200000 ) // каждые 20 минут передаем текущую поправку
    {
     char SMS31[25];
     String SMS3 = "I'am OK, delta = " + String(Delta);
     strcpy(SMS31,SMS3.c_str());
       sms.send(MapperNumberPhone,SMS31);
     //gsm.SMSsend(SMS31, MapperNumberPhone); 
     startTime = millis();
    }
   readSMS();
   

  // Получаем уровень приёма сигнала
  //uint8_t i = gsm.signal();
  uint8_t i = sms.signal();
  oled.setCursor(0, 0);
  oled.print("                ");
  oled.setCursor(0, 0);
  if (i == 0)
  {
   // При уровне приёма ниже или равном -113дБм
   Serial.println("    ");
   oled.print("no signal GSM!!!");
  }
  else if (i < 8)
  {
    // При уровне приёма ниже -97дБм
    oled.print("low signal GSM");
  } 
  else if (i < 16) 
  {
   // При уровне приёма ниже -81дБм
   oled.print("normal signalGSM");
  }
  else 
  {
    // При уровне приёма ниже -65дБм, выше или равном -65дБм
    oled.print("good signal GSM");
  } 
}

bool readSMS()  //чтение СМС и поиск текста reStart|restart , mapper\Mapper, сохнанеие нового номера в EEPROM  
{
RecievNewNumber =false;

  // Use your Serial interface...
  if(softSerial.available()) {
      String buffer = "";
      buffer = softSerial.readString();
      num = num + 1;
      Serial.print(num);
      Serial.print(". ");
      //Serial.println(buffer);

      /**/
      // This example for how you catch incoming calls.
      if(buffer.indexOf("+CMTI:") != -1) {
        
        Serial.print("SMS Index No... ");
        int indexno = sms.indexFromSerial(buffer);
        Serial.println(indexno);
         Serial.print("buffer1");
         Serial.println(buffer);
        Serial.print("Who send the message?...");
        String SMSnum = sms.getSenderNo(indexno);
        char* SMSnumber =  SMSnum.c_str();
        Serial.println(SMSnum);
         Serial.print("buffer2");
         Serial.println(buffer);
        Serial.print("Read the message... ");
        String message = sms.readFromSerial(buffer);
         //Serial.println(sms.readFromSerial(buffer));
         Serial.print("message:");
         Serial.println(message);
       //if(message.indexOf(F("|MESSAGE:"))==-1)
         // {
           // Serial.println("NO MESSAGE");
         // }
        //else {
          int indexStart = message.indexOf("|MESSAGE:");
          Serial.println(indexStart);
          String SMStxt = message.substring(indexStart+9,indexStart+30);
          SMStxt.trim();
          char* SMStext = SMStxt.c_str();
          Serial.println("SMS:");
          Serial.print(SMStxt);



            if ((millis() <= 300000 )&((strcmp(SMStext,Mapper)==0) || (strcmp(SMStext,mapper)==0)))// mapper слушаем в течении 5 минут после включения
            { strcpy (MapperNumberPhone,SMSnumber);
              // Serial.print("My new mapper number");
              // Serial.println(NewMapperNumber);
               oled.clear();
              oled.setCursor(0, 0);
              oled.print("new mapper numb");
              oled.setCursor(0, 2);
              oled.print(MapperNumberPhone);
              sms.send(MapperNumberPhone,"You is my new mapper"); 
              
              //сохраняем в энергонезависимой памяти новый номер 
               for (int i = 0; i < 11; i++) {
              EEPROM.update(i, MapperNumberPhone[i]);
              }
              delay(4000);
              oled.setCursor(0, 0);
              oled.print("rebooting  ...  ");
              delay(3000);
                // Записываем нуль-терминатор в конец строки
                //EEPROM.write(12, '\0');
              RecievNewNumber = true;  
                void(* softReset) (void) = 0;
                softReset();
            }
          else if((strcmp(SMSnumber,MapperNumberPhone)==0)&((strcmp(SMStext,Clean)==0) || (strcmp(SMStext,clean)==0)))
            {
               for (int i = 0; i < 11; i++)
              {
                EEPROM.update(i,i);
               }
               // RecievNewNumber = true;
                oled.clear();
                oled.setCursor(0,0); 
                oled.println("Clean mapper num") ;
                oled.print("rebooting  ...");
                sms.send(MapperNumberPhone,"Clean mapper Number" ); 
                delay(5000);
                void(* softReset) (void) = 0;
                softReset();
            }
          else if((strcmp(SMSnumber,MapperNumberPhone)==0)&((strcmp(SMStext,Restart)==0)||strcmp(SMStext,restart)==0))
          {
            sms.send("Restart base", MapperNumberPhone);
              delay(5000); 
              oled.clear();
              oled.setCursor(0,0); 
              oled.println("Restart base") ;
              oled.print("rebooting  ...");
              delay(5000);
             void(* softReset) (void) = 0;
             softReset();
          }  
           else RecievNewNumber= false;
  }  
  return RecievNewNumber;



       } 
      else {
      //  Serial.println(buffer);
      }
        sms.deleteAll();
    }








//  if(gsm.SMSavailable())
//    {                                                               // Функция SMSavailable() возвращает количество входящих непрочитанных SMS сообщений.
// //      Если есть входящие непрочитанные SMS сообщения:                                       //
//             Serial.println( F("SMS came, I read ...") );                                      // Выводим текст "Пришла SMS, читаю ... ".
//             gsm.SMSread(SMStxt, SMSnum, SMStim, SMSlongID, SMSlongSUM, SMSlongNUM);           // Читаем SMS сообщение в ранее объявленные переменные (текст SMS сообщения, адрес отправителя, дата отправки, идентификатор SMS, количество SMS, номер SMS).
//             Serial.print  ( F("SMS ")                   ); Serial.print  ( SMSlongNUM );      //
//             Serial.print  ( F(" in ")                   ); Serial.print  ( SMSlongSUM );      //
//             Serial.print  ( F(", ID=")                  ); Serial.print  ( SMSlongID );       //
//             Serial.print  ( F(", sent on ")             ); Serial.print  ( SMStim );          //
//             Serial.print  ( F(" from number ")          ); Serial.println  ( SMSnum );          //
//             Serial.print( F(", message text:")        ); Serial.println( SMStxt );          //
// //          gsm.SMSsend( F("Ваше сообщение получено, спасибо!"), SMSnum);                     // Данная строка будет отвечать отправителю указанным SMS сообщением.
// //            Serial.println( F("--------------------")   );           
            

																														//	
//}
uint8_t	GSMSimSMS::_num(char symbol){																													//	Аргументы функции:	символ 0-9,a-f,A-F.
			uint8_t i = uint8_t(symbol);																													//	Получаем код символа
			if ( (i>=0x30) && (i<=0x39) )	{ return i-0x30; }else																							//	0-9
			if ( (i>=0x41) && (i<=0x46) )	{ return i-0x37; }else																							//	A-F
			if ( (i>=0x61) && (i<=0x66) )	{ return i-0x57; }else																							//	a-f
											{ return      0; }																								//	остальные символы вернут число 0.
}
  //		ФУНКЦИЯ ПОЛУЧЕНИЯ УРОВНЯ СИГНАЛА:																							//	Функция возвращает:	целочисленное значение uint8_t от 0 до 31 соответствующее уровню сигнала.
uint8_t	GSMSimSMS::signal(void){																								//	Аргументы функции:	отсутствуют.
			int i; uint8_t j=0;																													//	Объявляем временные переменные.
			gsm.print("AT+CSQ\r");
      //runAT(F("AT+CSQ\r\n"));
      _readSerial();
      																												//	Выполняем команду получения уровня сигнала.
			i = _buffer.indexOf("+CSQ:"); if(i<0){return 0;}											//	Получаем позицию начала текста "+CSQ:" в ответе "ЭХО\r\n+CSQ: УРОВЕНЬ,ОШИБКИ\r\nOK\r\n".
			i+= 6;																																			//	Получаем позицию первого символа числа указвающего на уровень сигнала.
			j = _num(_buffer.charAt(i)); i++;																												//	Получаем первую цифру уровня сигнала.
			if( _buffer.charAt(i)!=','  ){j*=10; j+= _num(_buffer.charAt(i));}				//	Если за первой цифрой не стоит знак ',', значит там вторая цифра числа, учитываем и её.
			return j;				
}
