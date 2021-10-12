/*
MIT License

Copyright (c) 2021 G.Products

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

// Port
#define PIN_LED_STATUS (GPIO_NUM_13)
#define PIN_LED_VFREAD (GPIO_NUM_14)

#define INA1 (GPIO_NUM_27)  // IC3
#define INA2 (GPIO_NUM_26)  // IC3
#define INB1 (GPIO_NUM_25)  // IC2
#define INB2 (GPIO_NUM_33)  // IC2
#define INC1 (GPIO_NUM_17)  // IC1
#define INC2 (GPIO_NUM_16)  // IC1

void setup() {
  delay(1000);

  // GPIO initialize for LED
  pinMode(PIN_LED_VFREAD, INPUT);
  pinMode(PIN_LED_STATUS, OUTPUT);
  digitalWrite(PIN_LED_STATUS, LOW);

  // GPIO initialize for Motor
  pinMode(INA1, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(INB2, OUTPUT);
  pinMode(INC1, OUTPUT);
  pinMode(INC2, OUTPUT);
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, LOW);
  digitalWrite(INB1, LOW);
  digitalWrite(INB2, LOW);
  digitalWrite(INC1, LOW);
  digitalWrite(INC2, LOW);

  SerialBT.begin("bt_uart");  // Bluetooth Device Name
}

uint8_t dat;

void loop() {
  if (SerialBT.available()) {
    dat = (uint8_t)SerialBT.read();
    SerialBT.write(dat);
    delay(10);
    digitalWrite(PIN_LED_STATUS, HIGH);
  } else {
    delay(100);
    digitalWrite(PIN_LED_STATUS, LOW);
  }
}
