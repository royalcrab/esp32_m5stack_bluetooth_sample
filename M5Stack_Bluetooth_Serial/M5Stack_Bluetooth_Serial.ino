//#include <M5Stack.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
String device_name = "M5Stack-Core2-Serial";

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name); //Bluetooth device name
  //SerialBT.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
}


void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if ( SerialBT.available() ){
    Serial.write(SerialBT.read());
  }
  delay(20);
}