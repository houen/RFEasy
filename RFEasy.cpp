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
const String default_handshake = "***";
const bool log_msgs = true;

/* 
  RFEasy is an Arduino library to make RF communication as easy as possible
    
    - name:      The name of this listener / transmitter. 
                Used for logging and identification

    - frequency: The frequency VirtualWire will use to send messages. 
                Must be the same for transmitter and listener

    - handshake: A key that the transmitter will send along with the message, which the listener will check for in order to

    - log_msgs:  A bool value determining whether log output will be shown or not
*/

RFEasy::RFEasy(String name, int frequency, String handshake) {
  _construct(name, frequency, handshake, log_msgs);
}
RFEasy::RFEasy(String name, int frequency) {
  _construct(name, frequency, default_handshake, log_msgs);
}
RFEasy::RFEasy(String name) {
  _construct(name, default_frequency, default_handshake, log_msgs);
}
RFEasy::RFEasy() {
  _construct(default_name, default_frequency, default_handshake, log_msgs);
}

/* 
  Initialise as a listener. Must be done in the setup() function
*/
void RFEasy::init_listener(int pin) {
  _init(); //Initialization common to both transmitter and listener
  vw_set_rx_pin(pin); // Set transmit pin in VirtualWire
  vw_rx_start(); // Init as listener with VirtualWire
  _type = listener_type; // Set the type to listener
  //_logln("init"); //DEBUG
}

/* 
  Initialise as a transmitter. Must be done in the setup() method
*/
void RFEasy::init_transmitter(int pin) {
  _init(); //Initialization common to both transmitter and listener
  vw_set_tx_pin(pin); // Set listen pin in VirtualWire
  _type = transmitter_type; // Set the type to transmitter
  //_logln("init"); //DEBUG
}

/*
  Transmit a message. Used in the loop() method
*/
void RFEasy::transmit(String msg) {
  if(_type == transmitter_type) {
    msg = msg + _handshake;
    char transmitCharArr[msg.length()];  msg.toCharArray(transmitCharArr, msg.length() + 1);
    vw_send((uint8_t *)transmitCharArr, strlen(transmitCharArr));
    vw_wait_tx();
    //_logln("transmitted '" + msg + "'"); //DEBUG    
  }
  else {
    //_logln("Is not initialized as a transmitter. Please call init_transmitter first");  
  }
}

/*
  Listen for an incoming message. Used in the loop() method

  - return: Returns received message as a string. Returns empty string if no message was received
*/
String RFEasy::listen() {
  String out = ""; //Return message string variable
  if(_type == listener_type) {    
    uint8_t buflen = VW_MAX_MESSAGE_LEN; //Set buffer length to maximum for VirtualWire
    uint8_t buf[buflen]; //Initialise char array of size buffer length
    String msg = ""; //Variable for storing the received message (with handshake) in
    if(vw_get_message(buf, &buflen)) { //Get message from VirtualWire, scaling buffer length down to message size      
      for(int i = 0; i < buflen; i++) { //Loop through all characters in the buffer
        char c = char(buf[i]); //Get character
        msg = msg + c; //Concatenate to string
      }    
      //_logln("received '" + msg + "'"); //DEBUG
    }
    //_logln((String)msg.endsWith(_handshake)); //DEBUG
    if(msg.endsWith(_handshake)) {
      int len = msg.length();
      out = msg.substring(0, len - _handshake.length());  
    }
  }
  else {
    //_logln("Is not initialized as a listener. Please call init_listener first."); //DEBUG    
  }
  return out;
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

/*
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
*/