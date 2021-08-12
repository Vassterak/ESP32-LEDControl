#include <Arduino.h>
#include <FastLED.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

//My files
#include "addresableLED.h" //includes definitions.h
#include "clasicLEDStrip.h"

//Variables and Classes-------------------------------------------------------------
uint16_t btIDCode;
uint8_t preState = 0;
uint8_t counter = 0;

ClasicLEDStrip _classicLEDStrip;
AddresableLED _addresableLED;

class MyCallbacks: public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic)
	{
		std::string value = pCharacteristic->getValue();
		if (value.length() > 0)
		{
			Serial.println("*********");
			Serial.print("Raw value: ");
			char outputString[value.length()];
			for (int i = 0; i < value.length(); i++)
			{
				Serial.print(value[i]);
				outputString[i] = value[i];
			}
			btIDCode = atoi(outputString);
			Serial.println();
			Serial.print("Output after parsing: ");
			Serial.println(btIDCode);
			Serial.println("*********");
		}
    }
};

void setup()
{
	pinMode(BUTTON_PIN, INPUT_PULLDOWN); //input for the test button

//SETUP for clasic led strip controlled by MOSFET, Gate is driven by PWM from defined pins
	pinMode(LED_R, OUTPUT);
	pinMode(LED_G, OUTPUT);
	pinMode(LED_B, OUTPUT);

	ledcSetup(PWMChannelR, PWMFreq, PWMResolution); //RED
	ledcAttachPin(LED_R, PWMChannelR);
	ledcSetup(PWMChannelG, PWMFreq, PWMResolution); //GREEN
	ledcAttachPin(LED_G, PWMChannelG);
	ledcSetup(PWMChannelB, PWMFreq, PWMResolution); //BLUE
	ledcAttachPin(LED_B, PWMChannelB);

//Bluetooth setup----------------------------------------------------------------
	Serial.begin(115200);

	BLEDevice::init(BLE_DEV_NAME); //Bluetooth device name
	BLEServer *pServer = BLEDevice::createServer();
	BLEService *pService = pServer->createService(SERVICE_UUID);
	//BLECharacteristic *pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID,BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
	BLECharacteristic *pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID,BLECharacteristic::PROPERTY_WRITE);
	//pCharacteristic->setAccessPermissions(ESP_GATT_PERM_READ_ENCRYPTED | ESP_GATT_PERM_WRITE_ENCRYPTED);
	pCharacteristic->setCallbacks(new MyCallbacks());

	pService->start();
	BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
	//BLEAdvertising *pAdvertising = pServer->getAdvertising();

	//functions that help with iPhone connections issue
/* 	pAdvertising->setMinPreferred(0x06);  
	pAdvertising->setMinPreferred(0x12); */
	pAdvertising->start();

	BLESecurity *pSecurity = new BLESecurity();
	pSecurity->setStaticPIN(BLE_PASSCODE);

};

void loop() 
{
  //Button-------------------------------------------------------------------
	if (digitalRead(BUTTON_PIN) == HIGH && preState == 0)
	{
/* 		counter++;
		Serial.println(String(counter)); */
		preState = 1;
		ESP.restart();
	}
	else if (digitalRead(BUTTON_PIN) == LOW)
	{
		preState = 0;
	}

	EVERY_N_MILLISECONDS(20) //20ms = 50FPS
	{
		for (uint8_t i = 0; i < 255; i +=5)
		{
			ledcWrite(PWMChannelR, i);
			ledcWrite(PWMChannelG, 255-i);
		}
	
	switch (btIDCode)
	{
		case 110:
			_addresableLED.FallingStars(10, CRGB(10,100,250));
			break;

		case 111:
			_addresableLED.FallingStars(20, CRGB(200,10,2));
			break;

		case 112:
			_addresableLED.AnimeRainbow(20, 1);
			break;

		case 113:
			_addresableLED.AnimeRainbow(40, 1);
		break;

		case 114:
			_addresableLED.AnimeRainbow(60, 2);
		break;

		case 115:
		break;

		default:
/* 			Serial.print("Hodnota je: ");
			Serial.println(btIDCode); */
			break;
	}

	FastLED.show();
  }

};