/* Front Camera Controller for MQB Golf MK7 v0.1 by mr-fix
 * Requires RVC-High to be installed and working in the vehicle
 * https://github.com/mrfixpl/front-cam-MQB-DIY
 * NOT FOR COMMERCIAL USE
 * 
 * Good luck!
 * 
 * Might be cool to use WS2812 as the indicator and dynamicly control the color of the button.
 * not sure what's the actual function RGB light here, but still would be cool
 * 
 * Need to thing about the parktronic system being triggered when driving forward slowly and approaching obsticle. this turns on sensors display, but not the camera
 * 
 */

/* constants */
#include <Arduino.h>
#include <OneButton.h>

const int frontCamButtonPin = 2; // custom button to trigger Front Camera
const int frontCamIndicatorPin = 3; // custom indicator to show state of relay
const int frontCamRelayPin = 4; // relay to control video feed
const int parktronicButtonPin = 5; // OEM Parktronic button - planning to use this as output to trigger parktronic system, when front cam button is pressed but RVC is off
const int parktronicIndicatorPin = 6; // OEM Parktronic indicator
const int reverseSignalPin = 7; //reverse gear engaged signal

/* variables */
boolean frontCamState = LOW;
boolean frontCamButtonState = LOW;
boolean frontCamButtonStateOld = LOW;
boolean frontCamIndicatorState = LOW;
boolean frontCamRelayState = LOW;
boolean parktronicState = LOW;
boolean reverseSignalState = LOW;
boolean frontCamOffByUser = LOW;

/* settings */
const boolean frontCamButtonEvent = LOW; // LOW for "on press", HIGH for "on release"
const int parktronicButtonPressDuration = 100; //how long press the parktronic button to force start the system
// TODO? frontCamIndicatorPin might need PWM control for brightness adjustment

void setup() {
  // outputs
  pinMode(frontCamIndicatorPin, OUTPUT);
  pinMode(frontCamRelayPin, OUTPUT);
  pinMode(parktronicButtonPin, OUTPUT);
  
  // inputs
  pinMode(frontCamButtonPin, INPUT_PULLUP);
  pinMode(parktronicIndicatorPin, INPUT);
  pinMode(reverseSignalPin, INPUT);

  //for development purposes
  pinMode(LED_BUILTIN, OUTPUT); 

  setInitialStates();
}

void loop() {
  checkInputPinStates();

  handleFrontCamButton();
  handleAutomaticFrontCamTrigger();
  handleForceParktronicOn();
  handleFrontCamOffByUser();
  
  updateFrontCamRelayPin();
  updateFrontCamIndicatorPin();
}

void setInitialStates() {
  digitalWrite(frontCamIndicatorPin, LOW);
  digitalWrite(frontCamRelayPin, LOW);
  digitalWrite(parktronicButtonPin, LOW);
}

void checkInputPinStates() {
  frontCamButtonState = digitalRead(frontCamButtonPin);
  parktronicState = digitalRead(parktronicIndicatorPin);
  reverseSignalState = digitalRead(reverseSignalPin);
}

void handleFrontCamButton() {
  if(frontCamButtonState != frontCamButtonStateOld)
  {
    if(frontCamButtonState == frontCamButtonEvent)
    {
      if (frontCamState == LOW)
      {
        frontCamOffByUser = LOW;
        frontCamOn();
      }
      else
      {
        frontCamOffByUser = HIGH;
        frontCamOff();
      }
    }
    frontCamButtonStateOld = frontCamButtonState;
  }
}

void handleAutomaticFrontCamTrigger() {
  //if parktronic indicator is on, and reverse gear is off, and u turn on front camera
  if(parktronicState == HIGH && reverseSignalState == LOW && frontCamState == LOW && frontCamOffByUser == LOW) {
    frontCamOn();
  }
  if(parktronicState == HIGH && reverseSignalState == HIGH && frontCamState == HIGH) {
    frontCamOff();
  }
}

void frontCamOn() {
   frontCamState = HIGH;
   frontCamRelayState = HIGH;
   frontCamIndicatorState = HIGH;
}

void frontCamOff() {
  frontCamState = LOW;
  frontCamIndicatorState = LOW;
  frontCamRelayState = LOW;
}

void handleForceParktronicOn() {
  if(parktronicState == LOW && frontCamState == HIGH)
  {
    digitalWrite(parktronicButtonPin, HIGH);
    delay(parktronicButtonPressDuration);
    digitalWrite(parktronicButtonPin, LOW);
  }
}

void handleFrontCamOffByUser() {
  if(frontCamOffByUser == HIGH && parktronicState == LOW) {
    frontCamOffByUser == LOW;
  }
}

void updateFrontCamRelayPin() {
  digitalWrite(frontCamRelayPin, frontCamRelayState);
}

void updateFrontCamIndicatorPin() {
  digitalWrite(frontCamIndicatorPin, frontCamIndicatorState);
  digitalWrite(LED_BUILTIN, frontCamIndicatorState);
}
