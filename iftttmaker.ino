include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>

//
// Ethernet MAC address to use.
//     Usually Arduino Ethernet shields come with an address printed on
//     them (sometimes on underside of the board). Use that one here.
//
byte mac[] = { 0x66, 0x55, 0x44, 0x33, 0x22, 0x11 };  // REPLACE WITH REAL ADDR

//
// IFTTT Maker parameters:
//     Key -- Obtained when setting up/connecting the Maker channel in IFTTT
//   Event -- Arbitrary name for the event; used in the IFTTT recipe.
//
char MakerIFTTT_Key[] = "r8X-blahblahYourKeyGoesHere";
char MakerIFTTT_Event[] = "arduino_example";

//
// The IFTTT/Maker channel allows for three values to be reported
// which can be used as "ingredients" in the IFTTT recipe.
//
// In this simple example the values come from:
//    reading a PIN                    (reported as value1)
//    reporting uptime in milliseconds (reported as value2)
//    the string "hello, world!"       (reported as value3)
//
//
#define READ_THIS_PIN       3      // will be reported as "value1"

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
// This is called once per iteration to read the pins
// and send a POST to trigger the IFTTT/Maker event
//

void update_event() {
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

    // As described - this example simply reads three pins and reports them
    p = append_str(p, "{\"value1\":\"");
    p = append_ul(p, analogRead(READ_THIS_PIN));
    p = append_str(p, "\",\"value2\":\"");
    p = append_ul(p, millis());
    p = append_str(p, "\",\"value3\":\"");
    p = append_str(p, "hello, world!");
    p = append_str(p, "\"}");

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
    pinMode(READ_THIS_PIN, INPUT_PULLUP);
}

// how often to read the pins and update IFTTT
#define LOOP_DELAY_MSEC     (300*1000L)   // 5 minutes

// main body; called over and over if it ever returns
void loop() {

    // DHCP lease check/renewal (library only sends request if expired)
    Ethernet.maintain();

    // read the pins, send to IFTTT/Maker
    update_event();

    // only "this often"
    delay(LOOP_DELAY_MSEC);
}