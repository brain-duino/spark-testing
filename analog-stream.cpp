#include "SparkIntervalTimer.h"

IntervalTimer myTimer;

void blinkLED(void);

const uint8_t ledPin = D7;

void setup(void) {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  
  myTimer.begin(blinkLED, 100, hmSec);  // blinkLED to run every 50ms (100 * .5ms period)

}

int ledState = LOW;
volatile unsigned long blinkCount = 0; // use volatile for shared variables


void blinkLED(void) {
  if (ledState == LOW) {
    ledState = HIGH;
    blinkCount = blinkCount + 1;
    PIN_MAP[ledPin].gpio_peripheral->BSRR = PIN_MAP[ledPin].gpio_pin; // LED High
  }
  else {
    ledState = LOW;
    PIN_MAP[ledPin].gpio_peripheral->BRR = PIN_MAP[ledPin].gpio_pin; // LED low
  }
}



void loop(void) {
  unsigned long blinkCopy;

  noInterrupts();
  blinkCopy = blinkCount;
  interrupts();

  if (blinkCopy >= 100)
    { myTimer.end(); }

  Serial.print("blinkCount = ");
  Serial.println(blinkCopy);
  delay(200);
}
