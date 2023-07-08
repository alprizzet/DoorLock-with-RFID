#include<MFRC522.h>
#include<SPI.h>
#include<Servo.h>

const byte buzzer=8, rLed=7, gLed=6;
MFRC522 rfidSensor(10,9);
Servo motor;


void setup() {
pinMode(buzzer,OUTPUT);
pinMode(rLed,OUTPUT);
pinMode(gLed,OUTPUT);
Serial.begin(9600);
SPI.begin();
rfidSensor.PCD_Init();
Serial.println();
Serial.println("Please scan your card.");
Serial.println();
motor.attach(5);
}

void loop() {
  digitalWrite(buzzer,LOW);digitalWrite(gLed,LOW);digitalWrite(rLed,LOW);motor.write(0);
  if(!rfidSensor.PICC_IsNewCardPresent()){
    return;
  }
  if(!rfidSensor.PICC_ReadCardSerial()){
    return;
  }
  //Serial.print("UID of your card:");
  String cardID="";
  for(byte i=0;i<rfidSensor.uid.size;i++){
    cardID.concat(String(rfidSensor.uid.uidByte[i],HEX));
  }
  cardID.toUpperCase();
  //Serial.println(cardID);
  if(cardID=="4332C31F82180")
  {
    openLock();
  }else
  {
    dontOpen();
  }
}
void openLock()
{
  Serial.println();
  Serial.println("Scan succeeded. Welcome!"); 
  digitalWrite(gLed,HIGH);
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(gLed,LOW);
  digitalWrite(buzzer,LOW);
  motor.write(120);
  delay(10000);
}
void dontOpen()
{
  Serial.println();
  Serial.println("Scan rejected!!"); 
  for(byte j=0;j<3;j++)
  {
    digitalWrite(rLed,HIGH);
    digitalWrite(buzzer,HIGH); 
    delay(200);
    digitalWrite(rLed,LOW);
    digitalWrite(buzzer,LOW); 
    delay(200);
  }
}