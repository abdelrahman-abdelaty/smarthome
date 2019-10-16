/*

       S.No: Component Pin Arduino Pin
    1 OLED – Vcc  5V 
    2 OLED – Gnd  Gnd
    3 OLED- SCK, D0,SCL,CLK 4
    4 OLED- SDA, D1,MOSI, Data  3
    5 OLED- RES, RST,RESET  7
    6 OLED- DC, A0  5
    7 OLED- CS, Chip Select 6
    8 DHT11 – Vcc 5V
    9 DHT11 – Gnd Gnd
    10  DHT11 – Signal  13
    11  TSOP – Vcc  5V
    12  TSOP – Gnd  Gnd
    13  IR Led – Anode  9
    14  IR Led – Cathode  Gnd
 */
 
 #include <IRremote.h> //Lib for IT Blaster and TSOP
 #include <SPI.h> // Inbuilt Lib
 #include <Wire.h> //Inbuilt Lib
 #include <Adafruit_GFX.h> //Lib for OLED
 #include <Adafruit_SSD1306.h> //Lib for OLED
 #include <dht.h> //Library for dht11 Temperature and Humidity sensor (Download from Link in article)
 
 // Assign pins for OLED (Software config.)
#define OLED_MOSI  3
#define OLED_CLK   4
#define OLED_DC    5
#define OLED_CS    6
#define OLED_RESET 7
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define SSD1306_LCDHEIGHT 64 //Change if you are using a Different OLED

#define DHT11_PIN 13 //Sensor output pin is connected to pin 13
dht DHT; //Sensor object named as DHT

#define Desired_temperature 27 //The desired temperature is 27*C at any time

//Decoded Remote Signals For my AC ##CHANGE IT FOR YOUR REMOTE
unsigned int ACoff[] =  {4600,2600, 350,400, 350,950, 400,900, 400,350, 400,950, 350,400, 350,400, 350,400, 350,350, 400,950, 350,400, 350,400, 350,400, 350,950, 400,350, 400,350, 350,950, 400,350, 400,350, 400,900, 400,950, 350,400, 350,400, 350,400, 350,950, 400,350, 400,350, 350,400, 350,400, 350,400, 350,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,900, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,900, 400,350, 400,350, 400,350, 400,900 };  // UNKNOWN 5B04E3C0 
unsigned int ACon[] =   {4550,2600, 400,350, 400,950, 350,950, 400,350, 400,900, 400,350, 400,350, 400,350, 400,350, 400,900, 400,350, 400,350, 400,350, 400,950, 350,350, 400,350, 400,950, 400,900, 400,950, 350,350, 400,950, 400,350, 350,400, 350,400, 350,950, 400,350, 400,350, 400,350, 400,350, 350,400, 350,400, 350,350, 400,350, 400,350, 400,350, 400,350, 400,950, 350,400, 350,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,900, 400,350, 400,350, 400,350, 400,950 };  // UNKNOWN EA45DAC8
unsigned int Temp22[] = {4650,2550, 400,350, 400,900, 400,950, 350,400, 350,950, 400,350, 400,350, 350,400, 350,400, 350,950, 400,350, 400,350, 400,350, 350,950, 400,350, 400,350, 400,350, 400,400, 350,350, 350,400, 350,400, 350,950, 400,350, 400,350, 400,900, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 350,400, 350,400, 350,400, 350,350, 400,350, 400,950, 350,400, 350,400, 350,400, 350,350, 400,350, 400,350, 400,350, 400,950, 350,400, 350,350, 400,350, 400,350 };  // UNKNOWN A7997CC1
unsigned int Temp23[] = {4550,2600, 400,350, 400,950, 350,950, 400,350, 400,900, 400,350, 400,350, 400,350, 400,350, 400,900, 400,400, 350,350, 400,350, 400,950, 350,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,900, 400,350, 400,350, 400,950, 350,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 350,950, 400,350, 400,350, 400,350, 400,350, 400,350, 350,400, 350,400, 350,950, 400,350, 400,350, 400,350, 350,950 };  // UNKNOWN A7997CC2
unsigned int Temp24[] = {4600,2600, 350,350, 400,950, 400,900, 400,350, 400,950, 350,350, 400,350, 400,350, 400,350, 400,950, 350,400, 350,350, 400,350, 400,950, 350,400, 350,400, 350,950, 400,350, 400,350, 400,350, 350,400, 350,950, 400,350, 400,400, 350,900, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 350,400, 350,400, 350,400, 350,350, 400,950, 400,350, 350,400, 350,400, 350,400, 350,350, 400,350, 400,350, 400,950, 350,400, 350,400, 350,350, 400,350 };  // UNKNOWN 36F17307
unsigned int Temp25[] = {4600,2600, 350,400, 350,950, 400,900, 400,350, 400,950, 350,400, 350,400, 350,350, 400,400, 350,950, 400,350, 350,400, 350,400, 350,950, 400,350, 400,350, 400,900, 400,950, 350,350, 400,350, 400,350, 400,950, 350,400, 350,400, 350,950, 400,350, 400,350, 400,350, 350,400, 350,400, 350,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,950, 350,350, 400,350, 400,350, 400,350, 350,400, 400,350, 400,350, 400,900, 400,350, 400,350, 350,400, 400,900 };  // UNKNOWN 97DD0400
unsigned int Temp26[] = {4600,2600, 400,350, 350,950, 400,950, 350,400, 350,950, 400,350, 350,400, 350,400, 350,350, 400,950, 400,350, 400,350, 350,400, 350,950, 350,450, 350,350, 350,400, 400,350, 350,950, 400,350, 400,350, 350,950, 400,350, 400,350, 400,950, 350,400, 350,350, 400,350, 400,350, 400,350, 400,350, 350,400, 350,400, 350,400, 350,400, 350,400, 350,950, 400,350, 400,350, 350,400, 350,400, 350,400, 350,400, 350,400, 350,950, 350,400, 350,400, 350,400, 350,400 };  // UNKNOWN 2186470A
unsigned int Temp27[] = {4600,2600, 350,400, 350,950, 400,900, 400,350, 400,950, 350,400, 350,400, 350,350, 400,350, 400,950, 350,400, 350,400, 350,400, 350,950, 400,350, 400,350, 350,400, 350,400, 350,950, 400,350, 350,400, 400,900, 400,350, 400,350, 350,950, 400,350, 400,350, 400,350, 400,350, 350,400, 350,450, 300,400, 350,400, 350,400, 350,400, 350,400, 350,950, 350,400, 350,400, 350,400, 350,400, 350,400, 350,400, 350,400, 350,950, 350,400, 350,400, 350,400, 350,950 };  // UNKNOWN 40C2F924
unsigned int Temp28[] = {4550,2600, 400,350, 400,950, 350,950, 400,400, 350,900, 400,350, 400,350, 400,350, 400,350, 400,900, 400,350, 400,350, 400,350, 400,950, 350,350, 400,350, 400,950, 350,400, 350,950, 400,350, 400,350, 400,900, 400,350, 400,350, 400,950, 350,350, 400,350, 400,350, 400,350, 400,350, 400,400, 350,350, 400,350, 400,350, 400,350, 350,400, 350,950, 400,350, 400,350, 400,350, 400,350, 350,400, 350,400, 350,400, 350,950, 400,350, 400,350, 350,400, 350,400 };  // UNKNOWN F1D819D9
unsigned int Temp29[] = {4600,2600, 400,350, 400,900, 400,950, 400,350, 350,950, 400,350, 400,350, 400,350, 400,350, 400,900, 400,350, 400,350, 400,350, 400,900, 400,350, 400,350, 400,350, 400,900, 400,950, 400,350, 350,400, 350,950, 400,350, 400,350, 400,900, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 350,400, 350,400, 350,350, 400,950, 400,350, 350,400, 350,400, 350,400, 350,350, 400,350, 400,350, 400,950, 350,400, 350,400, 350,350, 400,950 };  // UNKNOWN D6C4468C
unsigned int Temp30[] = {4650,2550, 400,350, 400,950, 350,950, 400,350, 400,900, 400,350, 400,350, 400,400, 350,350, 400,900, 400,350, 400,350, 400,400, 350,950, 350,350, 400,350, 400,350, 400,950, 350,950, 400,350, 400,350, 400,900, 400,350, 400,400, 350,950, 350,400, 350,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 400,350, 350,400, 350,950, 400,350, 400,350, 400,350, 400,350, 350,400, 350,400, 350,400, 350,950, 400,350, 400,350, 350,400, 350,400 };  // UNKNOWN D6C4468F
//Change it for your remote

IRsend irsend;

int Measured_temp;
int Measured_Humi;
int AC_Temp;
char temp_error = 2;
int Pev_value;
boolean AC = false;

int khz = 38; // 38kHz carrier frequency for the NEC protocol

void setup()
{
Serial.begin(9600);
display.begin(SSD1306_SWITCHCAPVCC);
display.clearDisplay();
}

void loop() {
  
  DHT.read11(DHT11_PIN); //Read the Temp and Humidity
  Measured_temp = DHT.temperature + temp_error;
  Measured_Humi = DHT.humidity;

// text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Temperature: "); display.print(Measured_temp);display.println("C");
  display.setCursor(0,10);
  display.print("Humidity: "); display.print(Measured_Humi);display.println("%");
  display.setCursor(0,20);
  display.print("AC Temperature: "); display.print(AC_Temp);display.println("C");

  display.display();
  delay(500);
  display.clearDisplay();
 
 if ((Measured_temp <= (Desired_temperature-3)) && AC == true) //If AC is turned on and temperature is less than 3 degree of Desired value #24 turn off
 {
  irsend.sendRaw(ACoff, sizeof(ACoff) / sizeof(ACoff[0]), khz);  delay(2000);//Send signal to Turn Off the AC
  AC_Temp = 0; AC=false;
 }

 if ((Measured_temp >= Desired_temperature+4) && AC == false) //If AC is off and measured Temp is greater than Desired Temp
 {
  irsend.sendRaw(ACon, sizeof(ACon) / sizeof(ACon[0]), khz); delay(2000); //Send Signal to Turn On the AC 
  delay(2000);
  irsend.sendRaw(Temp27, sizeof(Temp27) / sizeof(Temp27[0]), khz); //Send signal to set 27*C
  AC_Temp = 27; AC=true;
 }

if ( Measured_temp != Pev_value) //Change the temperature only if the measured voltage value changes
{

if (Measured_temp == Desired_temperature+3) //If AC is ON and measured temp is very very high than desired
{
   irsend.sendRaw(Temp24, sizeof(Temp24) / sizeof(Temp24[0]), khz); delay(2000);//Send signal to set 24*C
  AC_Temp = 24; 
}

if (Measured_temp == Desired_temperature+2) //If AC is ON and measured temp is very high than desired
{
   irsend.sendRaw(Temp25, sizeof(Temp25) / sizeof(Temp25[0]), khz); delay(2000);//Send signal to set 25*C
  AC_Temp = 25; 
}

if (Measured_temp == Desired_temperature+1) //If AC is ON and measured temp is very high than desired
{
   irsend.sendRaw(Temp26, sizeof(Temp26) / sizeof(Temp26[0]), khz); delay(2000);//Send signal to set 26*C
  AC_Temp = 26; 
}

if (Measured_temp == 27 ) //If AC is ON and measured temp is desired value
{
  irsend.sendRaw(Temp27, sizeof(Temp27) / sizeof(Temp27[0]), khz); //Send signal to set 27*C
  AC_Temp = 27; 
}

if (Measured_temp == Desired_temperature-1) //If AC is ON and measured temp is low than desired value
{
  irsend.sendRaw(Temp28, sizeof(Temp28) / sizeof(Temp28[0]), khz); delay(2000);//Send signal to set 28*C
  AC_Temp = 28; 
}

if (Measured_temp == Desired_temperature-2 ) //If AC is ON and measured temp is very low than desired value
{
  irsend.sendRaw(Temp29, sizeof(Temp29) / sizeof(Temp29[0]), khz); delay(2000);//Send signal to set 29*C
  AC_Temp = 29; 
}

if (Measured_temp == Desired_temperature-3 ) //If AC is ON and measured temp is very very low desired value
{
  irsend.sendRaw(Temp30, sizeof(Temp30) / sizeof(Temp30[0]), khz); delay(2000);//Send signal to set 30*C
  AC_Temp = 30; 
}

}
Pev_value = Measured_temp;
}
