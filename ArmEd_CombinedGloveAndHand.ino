/*
    ArmEd
    Combined glove and hand
    Created: 22/10/17
    TODO:
        Input filtering (moving average).
        Setup calibration improvement
        In-use calibration improvement (exploration of use cases)
        Addition of controls for actual use (i.e. delay,
          position freeze, mode changes, etc.)
        General performance improvements
    Current operation:
        Starts in calibration mode where the input range is
        expanded outwards from the values in inputRangeMax[]
        and inputRangeMin[]. Calibration is ended when button
        is pressed. Then the main loop of mirroring the glove
        position and on-the-fly calibration begins.
    N.B.:
        Only three inputs/output are implemented currently.
        Print statements have been commented out due to
          performance concerns. (Comment on this would be
          appreciated).
*/
#define array_len( x )  ( sizeof( x ) / sizeof( *x ) )

#include <Servo.h>

struct Mapping {
  int input;
  int output;
};

//Glove
const unsigned int inputPins[] = {A0, A1, A2};
unsigned int inputRangeMax[] = {700, 700, 700};
unsigned int inputRangeMin[] = {400, 400, 400};

//Hand
const unsigned int buttonPin = 5;
const unsigned int outputPins[] = {2, 3, 4};
const Servo servos[3];
unsigned int servoRangeMin[] = {0, 0, 0};
unsigned int servoRangeMax[] = {85, 75, 75};

//Mapping: Range(0,1023) -> Range(0,1023)
Mapping mapping[3] = {
  {256, 256},
  {512, 512},
  {768, 768}
};

void setup() {
  Serial.begin(9600);
  setup_pin_modes();
  setup_servos();
  calibrate(true);
  for (int i = 0; i < array_len(inputPins); i++) {
    setDigit(i, 512);
  }
}

void setup_pin_modes() {
  pinMode(buttonPin, INPUT_PULLUP);
  for (int i = 0; i < array_len(outputPins); i++) {
    pinMode(outputPins[i], OUTPUT);
  }
  for (int i = 0; i < array_len(inputPins); i++) {
    pinMode(inputPins[i], INPUT);
  }
}

void setup_servos() {
  for (int i = 0; i < array_len(outputPins); i++) {
    servos[i].attach(outputPins[i]);
  }
}

void setDigit(unsigned int index, unsigned int bend) {
  float angle = 180 - map(bend, 0, 1023, 0, 180);
  angle = constrain(angle, servoRangeMin[index], servoRangeMax[index]);
  //Serial.print("Setting servo to:");
  //Serial.println(angle);
  servos[index].write(angle);
}

int remap(unsigned int input) {
  int value = constrain(input, 0, 1023);
  //Serial.print("Remap: ");
  //Serial.print(value);
  int inputRangeMin = 0;
  int inputRangeMax = 1023;
  int outputRangeMin = 0;
  int outputRangeMax = 1023;
  int i;
  for (i = 0; i < array_len(mapping); i++) {
    if (value > mapping[i].input) {
      inputRangeMin = mapping[i].input;
      outputRangeMin = mapping[i].output;
    }
  }
  if (i < array_len(mapping) - 1) {
    inputRangeMax = mapping[i + 1].output;
    outputRangeMax = mapping[i + 1].output;
  }
  value = map(value, inputRangeMin, inputRangeMax, outputRangeMin, outputRangeMax);
  //Serial.print("\t to: ");
  //Serial.print(value);
  return value;
}

void calibrate(bool breakOnButton) {
  while (true) {
    if (digitalRead(buttonPin) == LOW || breakOnButton) {
      //Serial.println("Ending Calibration");
      break;
    }
    for (int i = 0; i < array_len(inputPins); i++) {
      unsigned int inputValue = analogRead(inputPins[i]);
      if (inputValue > inputRangeMax[i]) {
        inputRangeMax[i] = inputValue;
      }
      if (inputValue < inputRangeMin[i]) {
        inputRangeMin[i] = inputValue;
      }
      //Serial.print(i);
      //Serial.print(": Current: ");
      //Serial.print(inputValue);
      //Serial.print("\t Largest: ");
      //Serial.print(inputRangeMax[i]);
      //Serial.print("\t Smallest: ");
      //Serial.print(inputRangeMin[i]);
      //Serial.print("||\t");
    }
    //Serial.print('\n');
  }
}

void loop() {
  for (int i = 0; i < array_len(inputPins); i++) {
    unsigned int value = analogRead(inputPins[i]);
    value = remap(value);
    setDigit(i, value);
  }
  calibrate(false);
}

