/* Build a focusing unit for the William Optics RedCat 51
 * Created by Marcus Vasi
 * www.eifeltwister.space
 */

 /* Configure type of steps
  *            MS1 MS2 MS3
  * Full step   0   0   0
  * 1/2 step    1   0   0
  * 1/4 step    0   1   0
  * 1/8 step    1   1   0
  * 1/16 step   1   1   1
  */

// definition of stepper motor parameter
#define stepPin 6
#define dirPin 5
#define enabledPin 8
#define stepsPerRevolution 5
#define stepDelay 2000
#define MS1 11
#define MS2 10
#define MS3 9

// definition of input pins
#define pinForward 2
#define pinBackward 3


void setup() {
  Serial.begin(9600);
  delay(200);
  Serial.println("Serial established");
  // declare motor pins as output
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enabledPin, OUTPUT);

  // set enabled pin to low, to prevent starting the motor during boot or reset
  digitalWrite(enabledPin, LOW);
  
  // set internal PullUps
  pinMode(pinForward, INPUT_PULLUP);
  pinMode(pinBackward, INPUT_PULLUP);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);

  // initial settings for type of steps (1/16)
  setSpeed(16);
}

void loop() {
  // check which button is pressed. Avoidto move motor if both buttons are pressed simultaneous
  if (digitalRead(pinForward) == LOW && digitalRead(pinBackward) != LOW) {
    Serial.println("Focus forward");
    for (int i = 0; i < stepsPerRevolution; i++) {
      // set the dir pin clockwise
      digitalWrite(dirPin, HIGH);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(stepDelay);
    }
  }

  if (digitalRead(pinBackward) == LOW && digitalRead(pinForward) != LOW) {
    Serial.println("Focus backward");
    for (int i = 0; i < stepsPerRevolution; i++) {
      // set the dir pin counterclockwise
      digitalWrite(dirPin, LOW);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(stepDelay);
    }
  }
}

void setSpeed(int stepType) {
  switch (stepType) {
    case 1:
      digitalWrite(MS1, LOW);
      digitalWrite(MS2, LOW);
      digitalWrite(MS3, LOW);
      break;
    case 2:
      digitalWrite(MS1, HIGH);
      digitalWrite(MS2, LOW);
      digitalWrite(MS3, LOW);
      break;
    case 4:
      digitalWrite(MS1, LOW);
      digitalWrite(MS2, HIGH);
      digitalWrite(MS3, LOW);
      break;
    case 8:
      digitalWrite(MS1, HIGH);
      digitalWrite(MS2, HIGH);
      digitalWrite(MS3, LOW);
      break;
    case 16:
      digitalWrite(MS1, HIGH);
      digitalWrite(MS2, HIGH);
      digitalWrite(MS3, HIGH);
      break;
    default:
      digitalWrite(MS1, HIGH);
      digitalWrite(MS2, HIGH);
      digitalWrite(MS3, HIGH);
      break;
  }
}
