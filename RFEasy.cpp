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
#include "RFEasy.h"
#include "../VirtualWire/VirtualWire.cpp"

const int listener_type = 1;
const int transmitter_type = 2;
const String default_name = "RFEasy";
const int default_frequency = 2000;
const String default_handshake = "";

RFEasy::RFEasy(String name, int frequency, String handshake, bool log_msgs) {
  _construct(name, frequency, handshake, log_msgs);
}
RFEasy::RFEasy(String name, int frequency, String handshake) {
  _construct(name, frequency, handshake, false);
}
RFEasy::RFEasy(String name, int frequency) {
  _construct(name, frequency, default_handshake, false);
}
RFEasy::RFEasy(String name) {
  _construct(name, default_frequency, default_handshake, false);
}
RFEasy::RFEasy() {
}

void RFEasy::init_listener(int pin) {
  _init();
  vw_set_rx_pin(pin);
  vw_rx_start();
  _type = listener_type;
  _logln("init");
}

void RFEasy::init_transmitter(int pin) {
  _init();
  vw_set_tx_pin(pin);
  _type = transmitter_type;
  _logln("init");
}

void RFEasy::transmit(String msg) {
  if(_type == transmitter_type) {
    char transmitCharArr[msg.length()];  msg.toCharArray(transmitCharArr, msg.length() + 1);
    vw_send((uint8_t *)transmitCharArr, strlen(transmitCharArr));
    vw_wait_tx();
    _logln("transmitted '" + msg + "'");      
  }
  else {
    _logln("Is not initialized as a transmitter. Please call init_transmitter first");  
  }
}

void RFEasy::listen() {
  if(_type == listener_type) {
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    uint8_t buf[buflen];
    
    if(vw_get_message(buf, &buflen)) {
      String full = "";
      for(int i = 0; i < buflen; i++) {        
        char c = char(buf[i]);
        full = full + c;
      }    
      _logln("received '" + full + "'");
    }
  }
  else {
    _logln("Is not initialized as a listener. Please call init_listener first.");
  }
}

//private

void RFEasy::_construct(String name, int frequency, String handshake, bool log_msgs) {
  _name = name;
  _rx_frequency = frequency;  
  _handshake = handshake;  
  _type = 0; //1 = Listener, 2 = transmitter
  _log_msgs = log_msgs;
}

void RFEasy::_init() {
  vw_setup(_rx_frequency);
}

void RFEasy::_logln(String msg) {
  if(_log_msgs) {
    _log(msg + "\r\n");
  }
}

void RFEasy::_log(String msg) {
  if(_log_msgs) {
    Serial.print("[" + _name + "] " + msg);  
  }
}