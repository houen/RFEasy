/*
  RFEasy.h - Library for listening / sending
  incoming RF messages over RF.

  Copyright (c) 2014 Søren Houen

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include "Arduino.h"
#include <RFEasy.h>

const int led = 13;

const int frequency = 2000;
const String handshake = "=/*RFEasy*//=";

RFEasy listener("Listener 1", frequency, handshake);

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  listener.init_listener(2);
}

void loop() {
  delay(100);
  digitalWrite(led, LOW);
  String msg = listener.listen();
  Serial.println("Listener returned with: " + msg);
  digitalWrite(led, HIGH);
  delay(100);
}