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
CHSV receivedColors[3];
uint8_t receivedNumberOfColors = 0;
TaskHandle_t taskOnCore0;

CRGB AddresableLED::leds[LEDS_TOTAL_NUMBER]; //static variable initialization

ClassicLEDStrip _classicLEDStrip1;
AddresableLED _addresableLED;	//Instance for whole strip / first zone
AddresableLED _addresableLED2; 	//second zone
AddresableLED _addresableLED3;	//third zone

class ModeSelect : public BLECharacteristicCallbacks //BLECharacteristicCallbacks runs on CORE 0
{
	//Called when data is sent to ESP32 for process
    void onWrite(BLECharacteristic *pCharacteristic2)
	{
		currentMode = ProccesingFunctions::inputIDProcessing(pCharacteristic2->getValue());

		Serial.print("Current Mode: ");
		Serial.println(currentMode);
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
					_addresableLED.zoneActive = true;
					Serial.print("Selected Zone: ");
					Serial.println("1");
					break;

				//Center side of the bed
				case 2:
					_addresableLED2.zoneActive = true;
					Serial.print("Selected Zone: ");
					Serial.println("2");
					break;

				//Left side
				case 3:
					_addresableLED3.zoneActive = true;
					Serial.print("Selected Zone: ");
					Serial.println("3");
					break;

				//when zero is received
				default:
					_addresableLED3.zoneActive = false;
					_addresableLED2.zoneActive = false;
					_addresableLED.zoneActive = false;
					Serial.print("Selected Zone: ");
					Serial.println("None");
					break;
			}
		}
	}
};

class EffectSelect : public BLECharacteristicCallbacks //BLECharacteristicCallbacks runs on CORE 0
{
    void onWrite(BLECharacteristic *pCharacteristic3)
	{
		uint8_t outputValue = ProccesingFunctions::inputIDProcessing(pCharacteristic3->getValue());

		switch (currentMode)
		{
		case 1:
			_classicLEDStrip1.currentEffectID = outputValue;
			break;

		case 2:
			_addresableLED.currentEffectID = outputValue;
			_addresableLED.fromLED = 0;
			_addresableLED.toLED = LEDS_TOTAL_NUMBER;
			break;

		case 3:
			if (_addresableLED.zoneActive)
			{
				_addresableLED.fromLED = 0;
				_addresableLED.toLED = LEDS_ZONE_PART1;
				_addresableLED.currentEffectID = outputValue;
			}
			else if (_addresableLED2.zoneActive)
			{
				_addresableLED2.fromLED = LEDS_ZONE_PART1+1;
				_addresableLED2.toLED = LEDS_ZONE_PART2;
				_addresableLED2.currentEffectID = outputValue;
			}
			else if (_addresableLED3.zoneActive)
			{
				_addresableLED3.fromLED = LEDS_ZONE_PART2+1;
				_addresableLED3.toLED = LEDS_TOTAL_NUMBER; //-1 is removed in functions inside class
				_addresableLED3.currentEffectID = outputValue;
			}
			break;

		default:
			break;
		}

		Serial.print("Selected Effect: ");
		Serial.println(outputValue);
	}
};

class ColorSelect : public BLECharacteristicCallbacks //BLECharacteristicCallbacks runs on CORE 0
{
    void onWrite(BLECharacteristic *pCharacteristic4)
	{
		std::tie(receivedColors[0], receivedColors[1], receivedColors[2], receivedNumberOfColors) = ProccesingFunctions::inputMultipleColorProcessing(pCharacteristic4->getValue());
		
		switch (currentMode)
		{
			case 1:
			_classicLEDStrip1.setColors[0] = receivedColors[0];
			_classicLEDStrip1.setColors[1] = receivedColors[1];
			_classicLEDStrip1.setColors[2] = receivedColors[2];
			_classicLEDStrip1.numberOfColors = receivedNumberOfColors;
			_classicLEDStrip1.newColor = true;
			break;

			case 2:
				_addresableLED.setColors[0] = receivedColors[0];
				_addresableLED.setColors[1] = receivedColors[1];
				_addresableLED.setColors[2] = receivedColors[2];
				_addresableLED.numberOfColors = receivedNumberOfColors;
				_addresableLED.newColor = true;
				break;

			case 3:
				if (_addresableLED.zoneActive)
				{
					_addresableLED.setColors[0] = receivedColors[0];
					_addresableLED.setColors[1] = receivedColors[1];
					_addresableLED.setColors[2] = receivedColors[2];
					_addresableLED.numberOfColors = receivedNumberOfColors;
					_addresableLED.newColor = true;
				}

				else if (_addresableLED2.zoneActive)
				{
					_addresableLED2.setColors[0] = receivedColors[0];
					_addresableLED2.setColors[1] = receivedColors[1];
					_addresableLED2.setColors[2] = receivedColors[2];
					_addresableLED2.numberOfColors = receivedNumberOfColors;
					_addresableLED2.newColor = true;
				}

				else if (_addresableLED3.zoneActive)
				{
					_addresableLED3.setColors[0] = receivedColors[0];
					_addresableLED3.setColors[1] = receivedColors[1];
					_addresableLED3.setColors[2] = receivedColors[2];
					_addresableLED3.numberOfColors = receivedNumberOfColors;
					_addresableLED3.newColor = true;
				}
				break;

			default:
				break;
		}

		for (uint8_t i = 0; i < 3; i++)
		{
			Serial.print("Hue: ");
			Serial.println(receivedColors[i].hue);

			Serial.print("Satur: ");
			Serial.println(receivedColors[i].saturation);

			Serial.print("Value: ");
			Serial.println(receivedColors[i].value);
			Serial.println("------------------------------------------");
		}

		Serial.print("Number of colors: ");
		Serial.println(receivedNumberOfColors);
	}
};

class SpeedSelect : public BLECharacteristicCallbacks //BLECharacteristicCallbacks runs on CORE 0
{
    void onWrite(BLECharacteristic *pCharacteristic5)
	{
		uint8_t outputSpeed = ProccesingFunctions::inputIDProcessing(pCharacteristic5->getValue());

		switch (currentMode)
		{
		case 1:
			_classicLEDStrip1.currentSpeed = outputSpeed;
			break;

		case 2:
			_addresableLED.currentSpeed = outputSpeed;
			break;

		case 3:
			if (_addresableLED.zoneActive)
				_addresableLED.currentSpeed = outputSpeed;

			else if (_addresableLED2.zoneActive)
				_addresableLED2.currentSpeed = outputSpeed;

			else if (_addresableLED3.zoneActive)
				_addresableLED3.currentSpeed = outputSpeed;

			break;

		default:
			break;
		}

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

/* 		EVERY_N_SECONDS(2)
		{
			Serial.print("Free heap: ");
			Serial.print(ESP.getFreeHeap());
		} */
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

//FastLED initialization-----------------------------------------------------------

	FastLED.addLeds<NEOPIXEL, LEDS_DATA_PIN>(AddresableLED::leds, LEDS_TOTAL_NUMBER);
	FastLED.clear(true);

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

		switch (_classicLEDStrip1.currentEffectID) //Clasic LED Strip
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

		switch (_addresableLED.currentEffectID) //Addresable strip whole/zone1
		{
			case 1:
				_addresableLED.solidPart();
				break;

			case 2:
				_addresableLED.staticRainbow();
				break;

			case 3:
				_addresableLED.animeRainbow();
				break;

			case 4:
				_addresableLED.fallingStars();
				break;

			case 5:
				_addresableLED.breathing();
				break;

			case 6:
				_addresableLED.pulsing();
				break;

			case 7:
				_addresableLED.pointTravel();
				break;

			case 8:
				_addresableLED.blending();
				break;

			default:
				FastLED.clear(true);
				break;
		}

		_classicLEDStrip1.update();
		FastLED.show();
	}
};