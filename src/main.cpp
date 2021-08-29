/* #include <Arduino.h> //Already inclued in my files
#include <FastLED.h> */
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

//My files
#include "addresableLED.h" //includes definitions.h
#include "clasicLEDStrip.h"
#include "proccesingFunctions.h"

//Variables and Classes-------------------------------------------------------------
bool preState = 0; //for the button
uint8_t currentMode;

ClasicLEDStrip _classicLEDStrip1;
AddresableLED _addresableLED;

class ModeSelect: public BLECharacteristicCallbacks
{
	//Called when data is sent to ESP32 for process
    void onWrite(BLECharacteristic *pCharacteristic2)
	{
		switch (ProccesingFunctions::InputIDProcessing(pCharacteristic2->getValue()))
		{
		case 1: //Classic strip
			currentMode = 1;
			break;

		case 2: //Addressable strip whole
			currentMode = 2;
			break;

		case 3: //Addressable strip zones
			currentMode = 3;
			break;

		default:
			break;
		}
    }
};

class ZoneSelect: public BLECharacteristicCallbacks
{
	//Called when data is sent to ESP32 for process
    void onWrite(BLECharacteristic *pCharacteristic)
	{
		if (currentMode == 3)
		{
			switch (ProccesingFunctions::InputIDProcessing(pCharacteristic->getValue()))
			{
				case 1: //Right side of the bed
				
					break;

				case 2: //Front side

					break;

				case 3: //Left side

					break;

				default:

					break;
			}
		}
    }
};

class EffectSelect: public BLECharacteristicCallbacks
{
	//Called when data is sent to ESP32 for process
    void onWrite(BLECharacteristic *pCharacteristic3)
	{
		_classicLEDStrip1.currentEffectID = ProccesingFunctions::InputIDProcessing(pCharacteristic3->getValue());
    }
};

class ColorSelect: public BLECharacteristicCallbacks
{
	//Called when data is sent to ESP32 for process
    void onWrite(BLECharacteristic *pCharacteristic4)
	{
		Serial.println("Barva přijata");
		_classicLEDStrip1.currentColor = ProccesingFunctions::InputColorProcessing(pCharacteristic4->getValue());

		Serial.print("Hue: ");
		Serial.println(_classicLEDStrip1.currentColor.hue);
		Serial.print("Satur: ");
		Serial.println(_classicLEDStrip1.currentColor.saturation);
		Serial.print("Value: ");
		Serial.println(_classicLEDStrip1.currentColor.value);
    }
};

class SpeedSelect: public BLECharacteristicCallbacks
{
	//Called when data is sent to ESP32 for process
    void onWrite(BLECharacteristic *pCharacteristic5)
	{
		_classicLEDStrip1.currentSpeed = ProccesingFunctions::InputIDProcessing(pCharacteristic5->getValue());
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
	BLEServer *pServer = BLEDevice::createServer(); //Create a server
	BLEService *pService = pServer->createService(SERVICE_UUID); //Create a server

	BLECharacteristic *pCharacteristic = pService->createCharacteristic(LED_ZONE_SELECT,BLECharacteristic::PROPERTY_WRITE);
	pCharacteristic->setCallbacks(new ZoneSelect());

	pCharacteristic = pService->createCharacteristic(LED_MODE_SELECT,BLECharacteristic::PROPERTY_WRITE);
	pCharacteristic->setCallbacks(new ModeSelect());

	pCharacteristic = pService->createCharacteristic(LED_EFFECT_SELECT,BLECharacteristic::PROPERTY_WRITE);
	pCharacteristic->setCallbacks(new EffectSelect());

	pCharacteristic = pService->createCharacteristic(LED_COLOR,BLECharacteristic::PROPERTY_WRITE);
	pCharacteristic->setCallbacks(new ColorSelect());

 	pCharacteristic = pService->createCharacteristic(LED_SPEED,BLECharacteristic::PROPERTY_WRITE);
	pCharacteristic->setCallbacks(new SpeedSelect());

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
		preState = 1;
		ESP.restart();
	}
	else if (digitalRead(BUTTON_PIN) == LOW)
		preState = 0;

	EVERY_N_MILLISECONDS(20) //20ms = 50FPS
	{
		//FastLED.show();
		//_classicLEDStrip1.SolidColor(_classicLEDStrip1.currentColor);
		
  	}

	EVERY_N_SECONDS(5)
	{
		Serial.print("Free heap: ");
		Serial.print(ESP.getFreeHeap());
		Serial.println("kB");
	}
};