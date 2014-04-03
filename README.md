# RFEasy
A lightweight Arduino library to make RF communication as easy as possible.

## Usage
RFEasy aims to help you send messages with Arduino over RF. Instead of dealing with VirtualWire, a string can be sent and received as easily as:

### Transmitter Arduino sketch

    #include "Arduino.h"
    #include <RFEasy.h>

    RFEasy transmitter();

    void setup() {
      transmitter.init_transmitter(7); //Pin 7
    }

    void loop() {
      transmitter.transmit("Hello World");
    }

### Receiver Arduino sketch

    #include "Arduino.h"
    #include <RFEasy.h>

    RFEasy listener();

    void setup() {
      Serial.begin(9600);
      listener.init_listener(2); //Pin 2
    }

    void loop() {
      String msg = listener.listen();
      Serial.println("Listener returned with: " + msg);
    }

## Installation


## Hardware
### US
- Transmitter: https://www.sparkfun.com/products/10534
- Receiver: https://www.sparkfun.com/products/10532


### Europe
- Transmitter: https://www.tinkersoup.de/wireless/rf-link-transmitter-434mhz/a-49/
- Receiver: https://www.tinkersoup.de/wireless/rf-link-receiver-4800bps-434mhz/a-824/
