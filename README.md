# RFEasy
An Arduino library to make RF communication as easy as possible.

## Usage
### Simple example
RFEasy aims to help you send messages with Arduino over RF. A string can be sent and received wirelessly as easily as below:

#### Transmitter Arduino sketch

    #include "Arduino.h"
    #include <RFEasy.h>

    RFEasy transmitter;

    void setup() {
      transmitter.init_transmitter(7); //Transmit on pin 7. Can be any pin you want
    }

    void loop() {
      transmitter.transmit("Hello World");
    }

#### Receiver Arduino sketch

    #include "Arduino.h"
    #include <RFEasy.h>

    RFEasy listener;

    void setup() {
      Serial.begin(9600); //For debug printing
      listener.init_listener(2); //Receive on pin 2. Can be any pin you want
    }

    void loop() {
      String message = listener.listen();
      Serial.println(message); //Print out response
    }

**Note:** This example does not set a custom Handshaking protocol. Please also see Handshaking section, and (slightly) more advanced example below.

Grab a cofffe! Pat yourself one the back. The above two sketches is everything you need to have two Arduino's talking to each other. You should add a little handshaking though. Should take about a minute more.

## Installation
- [Download as a zip file](https://github.com/houen/RFEasy/archive/master.zip), or Git clone this github repository in your Arduino Library folder. See the official guide on [Installing Additional Arduino Libraries](http://arduino.cc/en/Guide/Libraries) for more details.


## Hardware
RFEasy has been tested to work with the very common and easy 434 Mhz WRL-10534 transmitter and WRL-10532 receiver, but should function with any transmitter / receiver pair supported by VirtualWire.

To purchase WRL-10534 and WRL-10532, see below:
### US
- Transmitter: [From Sparkfun](https://www.sparkfun.com/products/10534)
- Receiver: [From Sparkfun](https://www.sparkfun.com/products/10532)


### Europe
- Transmitter: [From Tinkersoup](https://www.tinkersoup.de/wireless/rf-link-transmitter-434mhz/a-49/)
- Receiver: [From Tinkersoup](https://www.tinkersoup.de/wireless/rf-link-receiver-4800bps-434mhz/a-824/)

## Handshaking
RFEasy adds a simple handshaking protocol to your sent messages, simply by appending a preset string to all messages you send. This allows you to set your own handshake string and thus avoid receiving messages in your code that was not sent by your transmitter.

** It is strongly recommended to set your own handshaking string in the initialise code **

See the advanced example below for how to set a custom handshake.

**Note:** RFEasy will block waiting for a message to arrive with the correct handshake, as this is the desired result in most cases. If you need to be able to configure this behavior, please open an issue asking for it, or make a pull request adding it along with tests. Thank you.

## (Slightly) Advanced example
Here is a slightly more advanced example, showing how to set the handshaking protocol.

#### Transmitter Arduino sketch

    #include "Arduino.h"
    #include <RFEasy.h>

    const int led = 13;

    const int frequency = 2000;
    const String handshake = "=/*RFEasy*//=";

    RFEasy transmitter(frequency, handshake);

    void setup() {
      Serial.begin(9600);
      pinMode(led, OUTPUT);
      transmitter.init_transmitter(7);
    }

    void loop() {
      digitalWrite(led, LOW);
      transmitter.transmit("Hello World");
      digitalWrite(led, HIGH);  
      delay(100);
    }

#### Receiver Arduino sketch

    #include "Arduino.h"
    #include <RFEasy.h>

    const int led = 13;

    const int frequency = 2000;
    const String handshake = "=/*RFEasy*//=";

    RFEasy listener(frequency, handshake);

    void setup() {
      Serial.begin(9600);
      pinMode(led, OUTPUT);
      listener.init_listener(2);
    }

    void loop() {
      digitalWrite(led, LOW);
      String msg = listener.listen();
      Serial.println("Listener returned with: " + msg);
      digitalWrite(led, HIGH);
      delay(100);
    }