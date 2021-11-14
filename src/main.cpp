#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLESecurity.h>

//My files, these files also incule "definitions.h", <Arduino.h>, <FastLED.h>
#include "addresableLED.h"
#include "clasicLEDStrip.h"
#include "proccesingFunctions.h"

//Variables and Classes-------------------------------------------------------------
bool preState = 0; //for the button
uint8_t currentMode = 0;
TaskHandle_t taskOnCore0;
ClassicLEDStrip _classicLEDStrip1;
AddresableLED _addresableLED;


class ModeSelect : public BLECharacteristicCallbacks //BLECharacteristicCallbacks runs on CORE 0
{
	//Called when data is sent to ESP32 for process
    void onWrite(BLECharacteristic *pCharacteristic2)
	{
		switch (ProccesingFunctions::inputIDProcessing(pCharacteristic2->getValue()))
		{
		case 1: //Classic strip
			Serial.print("Selected Mode: ");
			Serial.println("1");
			currentMode = 1;
			break;

		case 2: //Addressable strip whole
			currentMode = 2;
			Serial.print("Selected Mode: ");
			Serial.println("2");
			break;

		case 3: //Addressable strip zones
			currentMode = 3;
			Serial.print("Selected Mode: ");
			Serial.println("3");
			break;

		default:
			break;
		}
	}
};

class ZoneSelect : public BLECharacteristicCallbacks //BLECharacteristicCallbacks runs on CORE 0
{
    void onWrite(BLECharacteristic *pCharacteristic)
	{
		if (currentMode == 3)
		{
			uint8_t outputValue = ProccesingFunctions::inputIDProcessing(pCharacteristic->getValue());
			switch (outputValue)
			{
				//Right side of the bed
				case 1:
					Serial.print("Selected Zone: ");
					Serial.println("1");
					break;

				//Center side of the bed
				case 2:
					Serial.print("Selected Zone: ");
					Serial.println("2");
					break;

				//Left side
				case 3:
					Serial.print("Selected Zone: ");
					Serial.println("3");
					break;

				default:
					Serial.print("Selected Zone: ");
					Serial.println("None");
					break;
			}
			_addresableLED.selectedZone = outputValue;
		}
	}
};

class EffectSelect : public BLECharacteristicCallbacks //BLECharacteristicCallbacks runs on CORE 0
{
    void onWrite(BLECharacteristic *pCharacteristic3)
	{
		uint8_t outputValue = ProccesingFunctions::inputIDProcessing(pCharacteristic3->getValue());
		
		if (currentMode == 1)
			_classicLEDStrip1.currentEffectID = outputValue;

		else
			_addresableLED.currentEffectID = outputValue;

		Serial.print("Selected Effect: ");
		Serial.println(outputValue);
	}
};

class ColorSelect : public BLECharacteristicCallbacks //BLECharacteristicCallbacks runs on CORE 0
{
    void onWrite(BLECharacteristic *pCharacteristic4)
	{
		if (currentMode == 1)
		{
			std::tie(_classicLEDStrip1.setColors[0], _classicLEDStrip1.setColors[1], _classicLEDStrip1.setColors[2], _classicLEDStrip1.numberOfColors) = ProccesingFunctions::inputMultipleColorProcessing(pCharacteristic4->getValue());
			_classicLEDStrip1.newColor = true;
		}
		else if (currentMode == 2)
		{
			std::tie(_addresableLED.setColors[0], _addresableLED.setColors[1], _addresableLED.setColors[2], _addresableLED.numberOfColors) = ProccesingFunctions::inputMultipleColorProcessing(pCharacteristic4->getValue());
		}


		Serial.print("Number of colors: ");
		Serial.println(_classicLEDStrip1.numberOfColors);

		for (uint8_t i = 0; i < 3; i++)
		{
			Serial.print("Hue: ");
			Serial.println(_classicLEDStrip1.setColors[i].hue);

			Serial.print("Satur: ");
			Serial.println(_classicLEDStrip1.setColors[i].saturation);

			Serial.print("Value: ");
			Serial.println(_classicLEDStrip1.setColors[i].value);
			Serial.println("------------------------------------------");
		}
	}
};

class SpeedSelect : public BLECharacteristicCallbacks //BLECharacteristicCallbacks runs on CORE 0
{
    void onWrite(BLECharacteristic *pCharacteristic5)
	{
		uint8_t outputSpeed = ProccesingFunctions::inputIDProcessing(pCharacteristic5->getValue());

		if (currentMode == 1)
			_classicLEDStrip1.currentSpeed = outputSpeed;

		else if (currentMode == 2)
			_addresableLED.currentSpeed = outputSpeed;

		Serial.print("Speed: ");
		Serial.println(outputSpeed);
	}
};

void functionOnCore0(void *parameter) //Runs on core 0 in loop
{
	while (1)
	{
		//Button-------------------------------------------------------------------
		if (digitalRead(BUTTON_PIN) == HIGH && preState == 0)
		{
			preState = 1;
			ESP.restart();
		}
		else if (digitalRead(BUTTON_PIN) == LOW)
			preState = 0;

		EVERY_N_SECONDS(5)
		{
			Serial.print("Free heap: ");
			Serial.print(ESP.getFreeHeap());
			Serial.println("Bytes");

			Serial.print("TaskRunsOnCore: ");
			Serial.println(xPortGetCoreID());
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
	BLEAdvertising *pAdvertising = pServer->getAdvertising();
	//BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

	//functions that help with iPhone connections issue (I HAVE NEVER TRIED.)
 	//pAdvertising->setMinPreferred(0x06);  
	//pAdvertising->setMinPreferred(0x12);

	pAdvertising->start();

	BLESecurity *pSecurity = new BLESecurity();
	pSecurity->setStaticPIN(BLE_PASSCODE);

	//TasksOnOtherCore setup---------------------------------------------------------------
	xTaskCreatePinnedToCore(
		functionOnCore0, 	/* Function to implement the task */
		"Task1",	  		/* Name of the task */
		10000,		  		/* Stack size in words */
		NULL,		  		/* Task input parameter */
		0,			  		/* Priority of the task */
		&taskOnCore0, 		/* Task handle. */
		0);			  		/* Core where the task should run */
};

void loop() //loop function works on CORE 1 (default settings)
{
	EVERY_N_MILLISECONDS(20) //20ms = 50FPS
	{

		switch (_classicLEDStrip1.currentEffectID)
		{
			case 1:
				_classicLEDStrip1.solidColor();
				break;

			case 2:
				_classicLEDStrip1.breathing2();
				break;

			case 3:
				_classicLEDStrip1.rainbow();
				break;
			case 4:
				_classicLEDStrip1.blending();
				break;

			case 5:
				_classicLEDStrip1.pulsing();
				break;

			default:
				break;
		}

		switch (_addresableLED.currentEffectID)
		{
		case 1:
			_addresableLED.solidPart();
			break;

		case 2:
		_addresableLED.staticRainbow();
			break;

		default:
			break;
		}

		_classicLEDStrip1.update();
		FastLED.show();
	}
};