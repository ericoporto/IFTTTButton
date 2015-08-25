// This code makes a button connect on pin 2 of the Ethernet Shield 
// connected to an Arduino trigger a event named button_pressed on
// the IFTTT Maker Channel. Based on the Neil Webber analog read code.

// The MIT License
// 
// Copyright (c) 2015 Erico Porto
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

// Ethernet MAC address to use.
byte mac[] = { 0x66, 0x55, 0x44, 0x33, 0x22, 0x11 };  // REPLACE WITH REAL ADDR

// IFTTT Maker parameters:
//     Key -- Obtained when setting up/connecting the Maker channel in IFTTT
//   Event -- Arbitrary name for the event; used in the IFTTT recipe.
char MakerIFTTT_Key[] = "blahblahYourKeyGoesHere";
char MakerIFTTT_Event[] = "button_pressed";

#define READ_THIS_PIN       3      // the button pin

// helper functions for constructing the POST data
// append a string or int to a buffer, return the resulting end of string

char *append_str(char *here, char *s) {
    while (*here++ = *s++)
	;
    return here-1;
}

char *append_ul(char *here, unsigned long u) {
    char buf[20];       // we "just know" this is big enough

    return append_str(here, ultoa(u, buf, 10));
}


//
// This is called once per iteration to read the pin
// and send a POST to trigger the IFTTT/Maker event
//

void send_event() {

    EthernetClient client = EthernetClient();

    // connect to the Maker event server
    client.connect("maker.ifttt.com", 80);

    // construct the POST request
    char post_rqst[256];    // hand-calculated to be big enough

    char *p = post_rqst;
    p = append_str(p, "POST /trigger/");
    p = append_str(p, MakerIFTTT_Event);
    p = append_str(p, "/with/key/");
    p = append_str(p, MakerIFTTT_Key);
    p = append_str(p, " HTTP/1.1\r\n");
    p = append_str(p, "Host: maker.ifttt.com\r\n");
    p = append_str(p, "Content-Type: application/json\r\n");
    p = append_str(p, "Content-Length: ");

    // we need to remember where the content length will go, which is:
    char *content_length_here = p;

    // it's always two digits, so reserve space for them (the NN)
    p = append_str(p, "NN\r\n");

    // end of headers
    p = append_str(p, "\r\n");

    // construct the JSON; remember where we started so we will know len
    char *json_start = p;

    // go back and fill in the JSON length
    // we just know this is at most 2 digits (and need to fill in both)
    int i = strlen(json_start);
    content_length_here[0] = '0' + (i/10);
    content_length_here[1] = '0' + (i%10);

    // finally we are ready to send the POST to the server!
    client.print(post_rqst);
    client.stop();
}

// called once at system reset/startup time
void setup() {
    // this sets up the network connection, including IP addr via DHCP
    Ethernet.begin(mac);

    // the input pin for this example
    pinMode(READ_THIS_PIN, INPUT);
}

// how often to read the pins and update IFTTT
#define LOOP_DELAY_MSEC     (1*1000L)   // 1 second
#define BUTTON_DELAY_MSEC     (15*1000L)   // 15 seconds

// main body; called over and over if it ever returns
void loop() {

    // DHCP lease check/renewal (library only sends request if expired)
    Ethernet.maintain();

    buttonState = digitalRead(READ_THIS_PIN);
    if (buttonState == HIGH) {  
         // send to IFTTT/Maker
         send_event();
         delay(BUTTON_DELAY_MSEC);
    }

    // only "this often"
    delay(LOOP_DELAY_MSEC);
}