/* Front Camera Controller for MQB Golf MK7 v0.1 by mr-fix
 * Requires RVC-High to be installed and working in the vehicle
 * https://github.com/mrfixpl/front-cam-MQB-DIY
 * NOT FOR COMMERCIAL USE
 */

// constants
const int frontCamButtonPin = 2; // custom button to trigger Front Camera
const int frontCamIndicatorPin = 4; // custom indicator to show state of relay
const int frontCamRelayPin = 7; // relay to control video feed
const int parktronicButtonPin = 3; // OEM Parktronic button - planning to use this as output to trigger parktronic system, when front cam button is pressed
const int parktronicIndicatorPin = 5; // OEM Parktronic indicator
const int reverseSignalPin = 6; //reverse gear engaged signal

const boolean frontCamButtonEvent = LOW; // LOW for "on press", HIGH for "on release"

// variables
boolean frontCamState = LOW;
boolean frontCamButtonState = LOW;
boolean frontCamButtonStateOld = LOW;
boolean frontCamIndicatorState = LOW;
boolean frontCamRelayState = LOW;
boolean parktronicIndicatorState = LOW;
boolean reverseSignalState = LOW;


void setup() {
  // outputs
  pinMode(frontCamIndicatorPin, OUTPUT);
  pinMode(frontCamRelayPin, OUTPUT);
  pinMode(parktronicButtonPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT); //for developer purposes
  
  // inputs
  pinMode(frontCamButtonPin, INPUT_PULLUP);
  pinMode(parktronicIndicatorPin, INPUT);
  pinMode(reverseSignalPin, INPUT);

  setInitialStates();
}

void loop() {
  checkInputPinStates();

  handleFrontCamButton();
  handleAutomaticFrontCamTrigger();
  
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
  parktronicIndicatorState = digitalRead(parktronicIndicatorPin);
  reverseSignalState = digitalRead(reverseSignalPin);
}

void handleFrontCamButton() {
  if(frontCamButtonState != frontCamButtonStateOld)
  {
    if(frontCamButtonState == frontCamButtonEvent)
    {
      frontCamState ? frontCamOff() : frontCamOn();
    }
    frontCamButtonStateOld = frontCamButtonState;
  }
}

void handleAutomaticFrontCamTrigger() {
  //if parktronic indicator is on and reverse gear is off, turn on front camera
  if(parktronicIndicatorState == HIGH && reverseSignalState == LOW && frontCamState == LOW) {
    frontCamOn();
  }
  if(parktronicIndicatorState == HIGH && reverseSignalState == HIGH && frontCamState == HIGH)
  frontCamOff();
}


void frontCamOn() {
   frontCamState = HIGH;
   frontCamIndicatorState = HIGH;
   frontCamRelayState = HIGH;
}

void frontCamOff() {
  frontCamState = LOW;
  frontCamIndicatorState = LOW;
  frontCamRelayState = LOW;
}




void updateFrontCamRelayPin() {
  digitalWrite(frontCamRelayPin, frontCamRelayState);
}

void updateFrontCamIndicatorPin() {
  digitalWrite(frontCamIndicatorPin, frontCamIndicatorState);
  digitalWrite(LED_BUILTIN, frontCamIndicatorState);
}
