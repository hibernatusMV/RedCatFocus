// definition of stepper motor parameter
#define stepPin 5
#define dirPin 6
#define stepsPerRevolution 5
#define stepDelay 2000

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
  
  // set internal PullUps
  pinMode(pinForward, INPUT_PULLUP);
  pinMode(pinBackward, INPUT_PULLUP);
}

void loop() {
  // check which button is pressed. Avoid both buttons are pressed simultaneous
  if (digitalRead(pinForward) == LOW && digitalRead(pinBackward) != LOW)
  {
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

  if (digitalRead(pinBackward) == LOW && digitalRead(pinForward) != LOW)
  {
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
