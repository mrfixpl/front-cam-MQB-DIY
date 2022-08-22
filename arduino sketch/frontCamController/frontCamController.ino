/* Front Camera Controller for MQB Golf MK7 v0.1 by mr-fix
 * Requires RVC-High to be installed and working in the vehicle
 * https://github.com/mrfixpl/front-cam-MQB-DIY
 * NOT FOR COMMERCIAL USE
 */

// constants
const int frontCamButtonPin = 2; // custom button to trigger Front Camera
const int frontCamIndicatorPin = 4; // custom indicator to show state of relay
const int frontCamRelayPin = 7; // relay to control video feed
const int parktronicButtonPin = 3; // OEM Parktronic button
const int parktronicIndicatorPin = 5; // OEM Parktronic indicator
const int reverseSignalPin = 6; //reverse gear engaged signal

const boolean frontCamButtonEvent = LOW; // LOW for "on press", HIGH for "on release"

// variables
boolean frontCamButtonState = LOW;
boolean frontCamButtonStateOld = LOW;
boolean frontCamIndicatorState = LOW;
boolean frontCamRelayState = LOW;
boolean parktronicIndicatorState = LOW;
boolean reverseSignalState = LOW;


void setup() {
  // outputs
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(frontCamIndicatorPin, OUTPUT);
  pinMode(frontCamRelayPin, OUTPUT);
  pinMode(parktronicButtonPin, OUTPUT);
  
  // inputs
  pinMode(frontCamButtonPin, INPUT_PULLUP);
  pinMode(parktronicIndicatorPin, INPUT);
  pinMode(reverseSignalPin, INPUT);

  setInitialStates();
}

void loop() {
  checkPinStates(); // check

  handleFrontCamButton();
  
  updateFrontCamRelayPin();
  updateFrontCamIndicatorPin();
}

void setInitialStates() {
  digitalWrite(frontCamIndicatorPin, LOW);
  digitalWrite(frontCamRelayPin, LOW);
  digitalWrite(parktronicButtonPin, LOW);
}

void checkPinStates() {
  frontCamButtonState = digitalRead(frontCamButtonPin);
  parktronicIndicatorState = digitalRead(parktronicIndicatorPin);
  reverseSignalState = digitalRead(reverseSignalPin);
}

void handleFrontCamButton() {
  if(frontCamButtonState != frontCamButtonStateOld)
  {
    if(frontCamButtonState == frontCamButtonEvent)
    {
      frontCamRelayState ? frontCamOff() : frontCamOn();
    }
    frontCamButtonStateOld = frontCamButtonState;
  }
}

void frontCamOn() {
   digitalWrite(LED_BUILTIN, HIGH);
   frontCamIndicatorState = HIGH;
   frontCamRelayState = HIGH;
}

void frontCamOff() {
  digitalWrite(LED_BUILTIN, LOW);
  frontCamIndicatorState = LOW;
  frontCamRelayState = LOW;
}

void updateFrontCamRelayPin() {
  digitalWrite(frontCamRelayPin, frontCamRelayState);
}

void updateFrontCamIndicatorPin() {
  digitalWrite(frontCamIndicatorPin, frontCamIndicatorState);
}
