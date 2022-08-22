// constants
const int frontCamButtonPin = 2; // custom button to trigger Front Camera
const int frontCamIndicatorPin = 4; // custom indicator to show state of relay
const int frontCamRelayPin = 7; // relay to control video feed
const int parktronicButtonPin = 3; // OEM Parktronic button
const int parktronicIndicatorPin = 5; // OEM Parktronic indicator
const int reverseSignalPin = 6; //reverse gear engaged signal

// variables
int frontCamButtonState = 0;
int parktronicIndicatorState = 0;
int reverseSignalState = 0;

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

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (frontCamButtonState == HIGH) {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
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
