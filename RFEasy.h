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

#ifndef RFEasy_h
#define RFEasy_h

#include "Arduino.h"
#include "../VirtualWire/VirtualWire.h"

class RFEasy
{
  public:
    RFEasy(int frequency, String handshake);
    RFEasy(int frequency);
    RFEasy();
    void init_listener(int pin);
    void init_transmitter(int pin);
    String listen();
    void transmit(String msg);
  private:
    void _construct(int frequency, String handshake);
    String _getMessage();
    void _init();
    void _logln(String msg);
    void _log(String msg);
    String _name;
    int _frequency;
    String _handshake;
    int _rx_frequency;
    int _rx_pin;
    int _tx_pin;
    int _baud_rate;
    int _type;
    bool _log_msgs;
};

#endif