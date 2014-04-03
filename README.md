# RFEasy
A lightweight Arduino library to make RF communication as easy as possible.

## Usage
RFEasy aims to help you send messages with Arduino over RF. A string can be sent and received wirelessly as easily as below:

#### Transmitter Arduino sketch

    #include "Arduino.h"
    #include <RFEasy.h>

    RFEasy transmitter();

    void setup() {
      transmitter.init_transmitter(7); //Transmit on pin 7. Can be any pin you want
    }

    void loop() {
      transmitter.transmit("Hello World");
    }

#### Receiver Arduino sketch

    #include "Arduino.h"
    #include <RFEasy.h>

    RFEasy listener();

    void setup() {
      listener.init_listener(2); //Receive on pin 2. Can be any pin you want
    }

    void loop() {
      String message = listener.listen();
    }

Grab a cofffe. The above two sketches is everything you need to have two Arduino's talking to each other.

## Installation
- [Download as a zip file](https://github.com/houen/RFEasy/archive/master.zip), or Git clone this github repository in your Arduino Library folder. See the official guide on [Installing Additional Arduino Libraries](http://arduino.cc/en/Guide/Libraries) for more details.


## Hardware
RFEasy has been tested to work with the very common and easy WRL-10534 transmitter and WRL-10532 receiver, but should function with any transmitter / receiver pair supported by VirtualWire.

To purchase WRL-10534 and WRL-10532, see below:
### US
- Transmitter: https://www.sparkfun.com/products/10534
- Receiver: https://www.sparkfun.com/products/10532


### Europe
- Transmitter: https://www.tinkersoup.de/wireless/rf-link-transmitter-434mhz/a-49/
- Receiver: https://www.tinkersoup.de/wireless/rf-link-receiver-4800bps-434mhz/a-824/
