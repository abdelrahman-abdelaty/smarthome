#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
int getFingerprintIDez();
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{
   Serial.begin(9600);
  pinMode(9,OUTPUT);
   finger.begin(57600);
}

void loop()                     // run over and over again


{
  getFingerprintIDez();
  delay(50);            //don't ned to run this at full speed.
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  

  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
if(finger.fingerID=2){
  digitalWrite(9,HIGH);
  delay(3000);
  digitalWrite(9,LOW);
}
  
  return finger.fingerID; 
}
