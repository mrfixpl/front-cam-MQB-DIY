/* Front Camera Controller for MQB Golf MK7 by mr-fix
 * Requires RVC-High to be installed and working in the vehicle
 * https://github.com/mrfixpl/front-cam-MQB-DIY
 * NOT FOR COMMERCIAL USE
 * 
 * https://github.com/mathertel/OneButton library was used. And the library is awesome!
 * 
 * Might be cool to use WS2812 as the indicator and dynamicly control the color of the button.
 * not sure what's the actual function RGB light here, but still would be cool
 * 
 * Need to thing about the parktronic system being triggered when driving forward slowly and approaching obsticle. this turns on sensors display, but not the camera
 * 
 */

#include <Arduino.h>
#include <OneButton.h>

/* constants */
const String softwareIdentification = "Front Camera Controller for MQB Golf MK7 v0.4 by mr-fix";
#define FRONT_CAM_BUTTON_PIN 2 // custom button to trigger Front Camera
const int frontCamIndicatorPin = 3; // custom indicator to show state of relay
const int frontCamRelayPin = 4; // relay to control video feed
const int parktronicButtonPin = 5; // OEM Parktronic button - planning to use this as output to trigger parktronic system, when front cam button is pressed but RVC is off
const int parktronicIndicatorPin = 6; // OEM Parktronic indicator
const int reverseSignalPin = 7; //reverse gear engaged signal

/* variables */
boolean frontCamState = LOW;
boolean frontCamRequest = LOW;
boolean frontCamIndicatorState = LOW;
boolean frontCamRelayState = LOW;
boolean parktronicState = LOW;
boolean reverseSignalState = LOW;
boolean frontCamOffByUser = LOW;

/* settings */
OneButton frontCamButton = OneButton(FRONT_CAM_BUTTON_PIN,true,true); // I/O pin, LOW state when active, internal pull-up
const int parktronicButtonPressDuration = 100; //how long press the parktronic button to force start the system
// TODO? frontCamIndicatorPin might need PWM control for brightness adjustment

void setup() {
  //for development purposes
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("");
  Serial.println(softwareIdentification);
  
  // outputs
  pinMode(frontCamIndicatorPin, OUTPUT);
  pinMode(frontCamRelayPin, OUTPUT);
  pinMode(parktronicButtonPin, OUTPUT);
  setInitialStates();
  
  // inputs
  pinMode(parktronicIndicatorPin, INPUT);
  pinMode(reverseSignalPin, INPUT);

  //events
  frontCamButton.attachClick(toggleFrontCamRequest);
  //frontCamButton.attachLongPressStart([]() {Serial.println("New button long-pressing!");});
  //frontCamButton.attachLongPressStop([]() {Serial.println("New button long-pressing stopped!");});
}

void loop() {
  checkInputPinStates();
  frontCamButton.tick();

  handleFrontCamRequest();
  handleAutomaticFrontCamTrigger();
  handleFrontCamOffByUser();
  
  updateFrontCamRelayPin();
  updateFrontCamIndicatorPin();
}

void setInitialStates() {
  Serial.println("Setting initial states of output pins...");
  digitalWrite(frontCamIndicatorPin, LOW);
  digitalWrite(frontCamRelayPin, LOW);
  digitalWrite(parktronicButtonPin, LOW);
}

void checkInputPinStates() {
  parktronicState = digitalRead(parktronicIndicatorPin);
  reverseSignalState = digitalRead(reverseSignalPin);
}

void handleFrontCamRequest() {
  if(frontCamRequest != frontCamState)
  {
    if(frontCamRequest == HIGH)
    {
      Serial.println("handleFrontCamRequest(): ON request");
      frontCamOffByUser = LOW;
      frontCamOn();
    }
    else
    {
      Serial.println("handleFrontCamRequest(): OFF request");
      frontCamOffByUser = HIGH;
      frontCamOff();
    }
  }
}

void handleAutomaticFrontCamTrigger() {
  //if camear is off, parktronic indicator is on, reverse gear is off, user did not force turned it off
  if(parktronicState == HIGH && reverseSignalState == LOW && frontCamState == LOW && frontCamOffByUser == LOW) {
    Serial.println("handleAutomaticFrontCamTrigger(): ON request");
    frontCamOn();
  }
  if(parktronicState == HIGH && reverseSignalState == HIGH && frontCamState == HIGH) {
    Serial.println("handleAutomaticFrontCamTrigger(): OFF request");
    frontCamOff();
  }
}

void frontCamOn() {
   Serial.println("frontCamOn(): ON");
   frontCamState = HIGH;
   frontCamRelayState = HIGH;
   frontCamIndicatorState = HIGH;
   forceParktronicOn();
}

void frontCamOff() {
  Serial.println("frontCamOff(): OFF");
  frontCamState = LOW;
  frontCamIndicatorState = LOW;
  frontCamRelayState = LOW;
}

void forceParktronicOn() {
  if(parktronicState == LOW)
  {
    Serial.println("forceParktronicOn(): Parktronic ON request");
    digitalWrite(parktronicButtonPin, HIGH);
    delay(parktronicButtonPressDuration);
    digitalWrite(parktronicButtonPin, LOW);
  }
  
  checkInputPinStates();
  
  if(parktronicState == HIGH) {
    Serial.println("forceParktronicOn(): Parktronic ON successfully");
  }
  else
  {
    Serial.println("forceParktronicOn(): Parktronic is stayed OFF");
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

void toggleFrontCamRequest() {
  frontCamRequest = frontCamRequest ? LOW : HIGH;
  Serial.print("toggleFrontCamRequest(): FrontCam requested state: ");
  Serial.println(frontCamRequest);
}
