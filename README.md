#DuinoButton

A physical IFTTT Button, using Arduino.

![End build](img/built.jpg)

#Hot to build

You will need the following:

* a 10k Resistor
* wire
* a push button
* Ethernet Cable
* Arduino Ethernet Shield
* Arduino Uno

![Materials](img/materials.jpg)

Ok so the resistor can be actually any one between 2k and 20k Ohm.
The wire I'm using was cut from another ethernet cable I had.

Now connect the resistor between GND and Arduino pin 2 (on Ethernet Shield!).
Place the legs of the push button between Arduino pin 2 and the 5V input.
This is the [same connection](https://www.arduino.cc/en/uploads/Tutorial/button_schem.png) from the [Arduino Button Tutorial](https://www.arduino.cc/en/Tutorial/Button).

You should have something similar to the following - I soldered instead of using a breadboard, but breadboard is fine.
Remember to place the Ethernet Shield on the Arduino.

![Done!](img/building.jpg)

So everything is in place. I built a lego enclosure, but you can do what suits you best.

#The code

So for this to work, first you have to be registered in IFTTT and connect to the Maker Channel.

![The Key from the Maker Channel on IFTTT](img/makerchannel.jpg)

On the [Maker Channel page](https://ifttt.com/maker) there is a key available. Copy it, we will need it!