#include<MFRC522.h>
#include<SPI.h>

MFRC522 rfidSensor(10,9);


void setup() {
Serial.begin(9600);
SPI.begin();
rfidSensor.PCD_Init();
Serial.println();
Serial.println("Please scan your card.");
Serial.println();
}

void loop() {
  if(!rfidSensor.PICC_IsNewCardPresent()){
    return;
  }
  if(!rfidSensor.PICC_ReadCardSerial()){
    return;
  }
  Serial.print("UID of your card:");
  String cardID="";
  for(byte i=0;i<rfidSensor.uid.size;i++){
    cardID.concat(String(rfidSensor.uid.uidByte[i],HEX));
  }
  cardID.toUpperCase();
  Serial.println(cardID);
}