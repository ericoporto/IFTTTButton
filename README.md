#IFTTTButton
A physical IFTTT Button, using Arduino.

![End build](https://raw.githubusercontent.com/ericoporto/IFTTTButton/master/img/built.jpg)

How to build
------------

You will need the following:

* a 10k Resistor
* wire
* a push button
* Ethernet Cable
* Arduino Ethernet Shield
* Arduino Uno

![Materials](https://raw.githubusercontent.com/ericoporto/IFTTTButton/master/img/materials.jpg)

Ok so the resistor can be actually any one between 2k and 20k Ohm.
The wire I'm using was cut from another ethernet cable I had.

Now connect the resistor between GND and Arduino pin 2 (on Ethernet Shield!).
Place the legs of the push button between Arduino pin 2 and the 5V input.
This is the [same connection](https://www.arduino.cc/en/uploads/Tutorial/button_schem.png) from the [Arduino Button Tutorial](https://www.arduino.cc/en/Tutorial/Button).

You should have something similar to the following - I soldered instead of using a breadboard, but breadboard is fine.
Remember to place the Ethernet Shield on the Arduino.

![Done!](https://raw.githubusercontent.com/ericoporto/IFTTTButton/master/img/building.jpg)

So everything is in place. I built a lego enclosure, but you can do what suits you best.

The code
--------

So for this to work, first you have to be registered in IFTTT and connect to the Maker Channel.

![The Key from the Maker Channel on IFTTT](https://raw.githubusercontent.com/ericoporto/IFTTTButton/master/img/makerchannel.jpg)

On the [Maker Channel page](https://ifttt.com/maker) there is a key available. Copy it, we will need it!

Next, get the code [iftttbutton.ino](https://raw.githubusercontent.com/ericoporto/IFTTTButton/master/iftttbutton.ino) on top of this page. With it open on your pc, go on the following lines (use Ctrl+F):

    char MakerIFTTT_Key[] = "blahblahYourKeyGoesHere";
    char MakerIFTTT_Event[] = "button_pressed";

Place the key you got where it's written `blahblahYourKeyGoesHere`.
In the line below it's the name of the event, which is `button_pressed`.

Test
----

Add this recipe: https://ifttt.com/recipes/319945-track-a-button-to-spreadsheet

You will have to connect the Google Drive Channel. The spreadsheet will be created in `IFTTT/Maker/button_pressed` .
Now if you open the spreadsheet, it will add a new row when you click the button!

![it works!](https://raw.githubusercontent.com/ericoporto/IFTTTButton/master/img/itworksyey.gif)

Do whatever you want
--------------------

Seriously, you can trigger anything you want that's available on IFTTT.

#Credits

The original code was made by [Outofmbufs](https://github.com/outofmbufs) and it's
available in his [Gist page](https://gist.github.com/outofmbufs/d6ced37b49a484c495f0).
This code is a Fork!
