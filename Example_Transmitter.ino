//// SimpleTx - the master or the transmitter
//
//#include <SPI.h>
//#include <nRF24L01.h>
//#include <RF24.h>
//
//
//#define CE_PIN  22
//#define CSN_PIN 21
//
//const byte slaveAddress[5] = {'R','x','A','A','A'};
//
//
//RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
//
//char dataToSend[10] = "Message 0";
//char txNum = '0';
//
//
//unsigned long currentMillis;
//unsigned long prevMillis;
//unsigned long txIntervalMillis = 1000; // send once per second
//
//
//void setup() {
//
//    Serial.begin(115200);
//
//    Serial.println("SimpleTx Starting");
//    delay(1000);
//    radio.begin();
//    radio.setDataRate( RF24_250KBPS );
//    radio.setRetries(3,5); // delay, count
//    radio.openWritingPipe(slaveAddress);
//}
//
////====================
//
//void loop() {
//    currentMillis = millis();
//    if (currentMillis - prevMillis >= txIntervalMillis) {
//        send();
//        prevMillis = millis();
//    }
//}
//
////====================
//
//void send() {
//
//    bool rslt;
//    rslt = radio.write( &dataToSend, sizeof(dataToSend) );
//        // Always use sizeof() as it gives the size as the number of bytes.
//        // For example if dataToSend was an int sizeof() would correctly return 2
//
//    Serial.print("Data Sent ");
//    Serial.print(dataToSend);
//    if (rslt) {
//        Serial.println("  Acknowledge received");
//        updateMessage();
//    }
//    else {
//        Serial.println("  Tx failed");
//    }
//}
//
////================
//
//void updateMessage() {
//        // so you can see that new data is being sent
//    txNum += 1;
//    if (txNum > '9') {
//        txNum = '0';
//    }
//    dataToSend[8] = txNum;
//}







/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(22,21); // CE, CSN
const byte address[6] = "00001";
void setup() {
  radio.begin();
  delay(100);
  Serial.begin(9600);
  delay(100);
  radio.setDataRate(RF24_1MBPS);
  delay(100);
  radio.openWritingPipe(address);
  delay(100);
  radio.setPALevel(RF24_PA_LOW);
  delay(100);
  radio.stopListening();
}
void loop() {
  const char text[] = "Hello World, Hell yeah!";
  delay(100);
  radio.write(&text, sizeof(text));
  delay(100);
  Serial.println(text);
  delay(100);
}
