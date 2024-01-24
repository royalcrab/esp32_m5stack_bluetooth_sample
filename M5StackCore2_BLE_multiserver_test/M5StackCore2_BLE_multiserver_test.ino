//#include <M5Core2.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

//#define SERVICE_UUID        "5c627b1e-717b-4231-9ddf-727f14f58724"
//#define CHARACTERISTIC_UUID "6c16e57f-7200-4228-af80-30547b37bea3"

#define SERVICE_UUID        "84ff873e-d73b-40a7-b493-497b62f8bbf1"
#define CHARACTERISTIC_UUID "1d0d5c5a-cafc-4fc5-a957-6d909d39e281"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      BLEDevice::startAdvertising();
      Serial.println("Connected");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class RequestCallbacks : public BLECharacteristicCallbacks
{
  public:
    void onWrite(BLECharacteristic *pCharacteristic)
    {
      uint8_t *request = pCharacteristic->getData();
      for(int i = 0; i < 256; i++){
        Serial.print(i,HEX);
      }
      Serial.println(".");
    }
    void onRead(BLECharacteristic *pCharacteristic){
      
    }
};


void setup() {
  //M5.begin();
  //M5.Lcd.print("Hello World");
  Serial.begin(115200);
  

  // Create the BLE Device
  BLEDevice::init("M5STACK-MPLPL-TEST");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );

  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setCallbacks(new RequestCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  //pAdvertising->setScanResponse(false);
  pAdvertising->setScanResponse(true); // これをしないと macos と ios ではスキャン結果に出てこない。
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
  //M5.Lcd.print("Waiting");
}

void loop() {
    // notify changed value
    if (deviceConnected) {
        //pCharacteristic->setValue((uint8_t*)&value, 4);
        //pCharacteristic->notify();
        //value++;
        //delay(10); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
    }
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}
