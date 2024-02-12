#include "Sodaq_RN2483.h"

#define debugSerial SerialUSB
#define loraSerial Serial1

// OTAA
uint8_t DevEUI[8] = { 0x00, 0x04, 0xA3, 0x0B, 0x00, 0x1A, 0x20, 0x07 };
uint8_t AppEUI[8] = { 0x85, 0x14, 0x8F, 0xC6, 0xB8, 0x15, 0xE8, 0xFD };
uint8_t AppKey[16] = { 0x77, 0x1F, 0x1D, 0x49, 0x02, 0xEB, 0x07, 0xCF, 0x8C, 0xCE, 0x6F, 0xB6, 0xF4, 0x9B, 0xA1, 0xCB };

void setupLoRaOTAA(){
  if (LoRaBee.initOTA(loraSerial, DevEUI, AppEUI, AppKey, true))
  {
    debugSerial.println("Communication to LoRaWAN via OTAA successful.");
  }
  else
  {
    debugSerial.println("OTAA Setup failed!");
  }
}

void setup() {
  pinMode(ENABLE_PIN_IO, OUTPUT);
  digitalWrite(ENABLE_PIN_IO, HIGH);
  delay(3000);

  while ((!SerialUSB) && (millis() < 10000)){
  }
  //Set baud rate
  debugSerial.begin(57600);
  loraSerial.begin(LoRaBee.getDefaultBaudRate());

  //connect to the LoRa Network
  setupLoRa();
}

void setupLoRa(){
  setupLoRaOTAA();
}

void sendPacket(String packet){
  switch (LoRaBee.sendReqAck(1, (uint8_t*)packet.c_str(), packet.length(), 8))
    {
    case NoError:
      debugSerial.println("Successful transmission.");
      break;
    case NoResponse:
      debugSerial.println("There was no response from the device.");
      setupLoRa();
      break;
    case Timeout:
      debugSerial.println("Connection timed-out. Check serial connection to the device.");
      delay(20000);
      break;
    case PayloadSizeError:
      debugSerial.println("Transmission failed. The size of the payload is greater than allowed");
      break;
    case InternalError:
      debugSerial.println("Something went wrong. Restarting device\r\nThe network connection will reset.");
      setupLoRa();
      break;
    case Busy:
      debugSerial.println("The device is busy. Sleeping for 10 extra seconds.");
      delay(10000);
      break;
    case NetworkFatalError:
      debugSerial.println("There is a non-recoverable error with the network connection. You should re-connect.\r\nThe network connection will reset.");
      setupLoRa();
      break;
    case NotConnected:
      debugSerial.println("The device is not connected to the network. Please connect to the network before attempting to send data.\r\nThe network connection will reset.");
      setupLoRa();
      break;
    case NoAcknowledgment:
      debugSerial.println("There was no acknowledgment sent back!");
      break;
    default:
      break;
    }
}

void loop() {
  String packet = "ESA";
  sendPacket(packet);

  delay(30000);
}
