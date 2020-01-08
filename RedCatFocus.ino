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

#include <IRremote.h>

// configuration for remote control
int RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);
decode_results results;

// definition of stepper motor parameter
#define stepPin 6
#define dirPin 5
#define enabledPin 11
#define stepsPerRevolution 40
#define MS1 10
#define MS2 9
#define MS3 8

// definition of input pins
#define pinForward 2
#define pinBackward 3

int    stepDelay = 6000; // Default setting is 6000
String previousVal = "";


void setup() {
  Serial.begin(9600);
  delay(200);
  Serial.println("Serial established");

  // Start the receiver
  irrecv.enableIRIn();
  
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
  setMicrostep(4);
}

void loop() {
  if (irrecv.decode(&results)) {
    String buttonPress = decodeIR(results.value);

    if (buttonPress == "REP") {
      buttonPress = previousVal;
    } else {
      previousVal = buttonPress;
    }
    
    // check which button is pressed. Avoidto move motor if both buttons are pressed simultaneous
    if (buttonPress == "UP") {
      Serial.println("Run clockwise");
      for (int i = 0; i < stepsPerRevolution; i++) {
        // set the dir pin clockwise
        runMotor("CW", stepDelay);
      }
    }
  
    if (buttonPress == "DOWN") {
      Serial.println("Run counterclockwise");
      for (int i = 0; i < stepsPerRevolution; i++) {
        // set the dir pin counterclockwise
        runMotor("CCW", stepDelay);
      }
    }

    if (buttonPress == "1") {
      stepDelay = 1000;
    }

    if (buttonPress == "2") {
      stepDelay = 2000;
    }

    if (buttonPress == "3") {
      stepDelay = 3000;
    }

    if (buttonPress == "4") {
      stepDelay = 4000;
    }

    if (buttonPress == "5") {
      stepDelay = 5000;
    }

    if (buttonPress == "6") {
      stepDelay = 6000;
    }
    
    Serial.println("stepDelay is " + String(stepDelay));
    irrecv.resume(); // Receive the next value
  }
}

void runMotor(String dir, int stepDelay) {
  if (dir == "CW") {
    digitalWrite(dirPin, LOW);
  } else if (dir == "CCW") {
     digitalWrite(dirPin, HIGH);
  }
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(stepDelay);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(stepDelay);
}

void setMicrostep(int stepType) {
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

String decodeIR (long x) {
  String hexCode = String(x, HEX);
  if (hexCode == "fd10ef") {
      return "DOWN";
  } else if (hexCode == "fd50af") {
      return "UP";
  } else if (hexCode == "fd30cf") {
      return "0";
  } else if (hexCode == "fd08f7") {
      return "1";
  } else if (hexCode == "fd8877") {
      return "2";
  } else if (hexCode == "fd48b7") {
      return "3";
  } else if (hexCode == "fd28d7") {
      return "4";
  } else if (hexCode == "fda857") {
      return "5";
  } else if (hexCode == "fd6897") {
      return "6";
  } else if (hexCode == "fd18e7") {
      return "7";
  } else if (hexCode == "fd9867") {
      return "8";
  } else if (hexCode == "fd58a7") {
      return "9";
  } else if (hexCode == "ffffffff") {
      return "REP";
  } else {
    return "NA";
  }
}
