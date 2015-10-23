#include "Timer.h"                     //http://github.com/JChristensen/Timer

const int LED1 = 13;                    //connect one LED to this pin (with appropriate current-limiting resistor of course)
const int LED2 = 13;                    //connect another LED to this pin (don't forget the resistor)
const unsigned long PERIOD1 = 1000;    //one second
const unsigned long PERIOD2 = 10000;   //ten seconds
Timer t;                               //instantiate the timer object

void setup(void)
{
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    t.oscillate(LED1, PERIOD1, HIGH);
    t.oscillate(LED2, PERIOD2, HIGH);
}

void loop(void)
{
    t.update();
}

