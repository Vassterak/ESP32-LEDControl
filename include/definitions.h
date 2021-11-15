#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//Clasic LED strip settings-----------------------------------------------------
#define LED_R 25 //pins
#define LED_G 26
#define LED_B 27

const int PWMFreq = 100;                                               // 100Hz frequency is double of speed of animation which is in 50FPS so the flickering is not visible. If your grid uses 60Hz and you see flickering. Change it to 120Hz and refresh rate to 60FPS
const int PWMChannelR = 0, PWMChannelG = 1, PWMChannelB = 2;           //Channel for each color
const int PWMResolution = 8;                                           // 8bits, from 0 (off state) to 255 (max brightness)
const int MAX_DUTY_CYCLE = (int)((PWMResolution * PWMResolution) - 1); //calculates duty cicle from resolution

//Addressable LED strip---------------------------------------------------------
#define LEDS_DATA_PIN 22      //IO pin
#define LEDS_TOTAL_NUMBER 149 //for addresable LED, 149 because one LED is dead on my strip with 150 leds
#define LEDS_ZONE_PART1 60
#define LEDS_ZONE_PART2 89
//#define LEDS_ZONE_PART3 149 //Not required because 149 is total number of leds (so it's also the last one in the strip)

//Timing------------------------------------------------------------
// In the mobile app there is settings for speed (controls transition and speed of effects)
// In the app you can change it from 20ms to 5000ms THIS IS WHAT APP IS SENDING! SO IF YOU WANT TO CHANGE THE RANGE, YOU NEED TO CHANGE IT HERE ALSO.
// But when you look up the Rainbow() you will see that the speed is controlled by addition to hue that will overflow to 0 so it's repeating indefinitely.
// So here you can set how agressive it will be. For more understanding open proccessingFuctions.cpp and look for EffectSpeedRemap()
#define SPEED_VALUE_MIN 1
#define SPEED_VALUE_MAX 40

#define SPEED_TIME_MIN 20   //ms
#define SPEED_TIME_MAX 5000 //ms

//Bluetooth----------------------------------------------------------
#define BUTTON_PIN 32                 //IO14 Pin nuber 13
#define BLE_DEV_NAME "LED Controller" //Visible bluetooth name of the ESP32
#define BLE_PASSCODE 123456           //Set your own passcode for pairing
#define SERVICE_UUID "265c24be-020f-11ec-9a03-0242ac130003"

//CHARACTERISTIC_UUIDs
#define LED_ZONE_SELECT "265c2752-020f-11ec-9a03-0242ac130003"   //zones for addresable led strip
#define LED_MODE_SELECT "265c2860-020f-11ec-9a03-0242ac130003"   //modes to switch (addreable/classic strip/zone mode/whole strip)
#define LED_EFFECT_SELECT "265c293c-020f-11ec-9a03-0242ac130003" //effect code to apply
#define LED_COLOR "265c2a9a-020f-11ec-9a03-0242ac130003"         //color for effect, including brightness
#define LED_SPEED "265c30bc-020f-11ec-9a03-0242ac130003"         //speed of the effect/additional variable for usage of complex effects

#endif