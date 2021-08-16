#include <Arduino.h>
#include <FastLED.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

//My files
#include "addresableLED.h" //includes definitions.h
#include "clasicLEDStrip.h"

//Variables and Classes-------------------------------------------------------------
uint8_t preState = 0;
uint8_t counter = 0;

ClasicLEDStrip _classicLEDStrip;
AddresableLED _addresableLED;

class ADDROpMode: public BLECharacteristicCallbacks
{
	//Called when data is sent to ESP32 for process
    void onWrite(BLECharacteristic *pCharacteristic)
	{
		//InputProcessing(pCharacteristic->getValue());
    }
};

class ADDRBrightness: public BLECharacteristicCallbacks
{
	//Called when data is sent to ESP32 for process
    void onWrite(BLECharacteristic *pCharacteristic2)
	{
		
    }
};

class ADDRPart1: public BLECharacteristicCallbacks
{
	//Called when data is sent to ESP32 for process
    void onWrite(BLECharacteristic *pCharacteristic3)
	{
		InputProcessing(pCharacteristic3->getValue());
    }
};

class ADDRPart2: public BLECharacteristicCallbacks
{
	//Called when data is sent to ESP32 for process
    void onWrite(BLECharacteristic *pCharacteristic3)
	{

    }
};

class ADDRPart3: public BLECharacteristicCallbacks
{
	//Called when data is sent to ESP32 for process
    void onWrite(BLECharacteristic *pCharacteristic3)
	{

    }
};

uint16_t InputProcessing(std::string input)
{
	if (input.length() > 0)
	{
		Serial.print("*********\nRaw value: ");
		char outputString[input.length()];
		for (int i = 0; i < input.length(); i++)
		{
			Serial.print(input[i]);
			outputString[i] = input[i];
		}

		Serial.print("\nOutput after parsing: ");
		Serial.println(atoi(outputString));
		return atoi(outputString);
	}
}

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
	BLEServer *pServer = BLEDevice::createServer(); //Create a server
	BLEService *pService = pServer->createService(SERVICE_UUID); //Create a server

	BLECharacteristic *pCharacteristic = pService->createCharacteristic(ADDR_OPER_MODE,BLECharacteristic::PROPERTY_WRITE);
	pCharacteristic->setCallbacks(new (ADDROpMode));

	pCharacteristic = pService->createCharacteristic(ADDR_BRIGHTNESS,BLECharacteristic::PROPERTY_WRITE);
	pCharacteristic->setCallbacks(new ADDRBrightness());

 	pCharacteristic = pService->createCharacteristic(ADDR_ZONE1,BLECharacteristic::PROPERTY_WRITE);
	pCharacteristic->setCallbacks(new ADDRPart1());

	pCharacteristic = pService->createCharacteristic(ADDR_ZONE2,BLECharacteristic::PROPERTY_WRITE);
	pCharacteristic->setCallbacks(new ADDRPart2());

	pCharacteristic = pService->createCharacteristic(ADDR_ZONE3,BLECharacteristic::PROPERTY_WRITE);
	pCharacteristic->setCallbacks(new ADDRPart3());

	pService->start();
	//BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
	BLEAdvertising *pAdvertising = pServer->getAdvertising();

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
/* 		for (uint8_t i = 0; i < 255; i +=5)
		{
			ledcWrite(PWMChannelR, i);
			ledcWrite(PWMChannelG, 255-i);
		} */
	
	/* 	switch (btIDCode)
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
				break;
		} */



		FastLED.show();
  	}

	EVERY_N_SECONDS(5)
	{
		Serial.print("Free heap: ");
		Serial.print(ESP.getFreeHeap());
		Serial.println("kB");
	}
};