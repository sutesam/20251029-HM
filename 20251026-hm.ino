const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;
const int buttonPin = 2;

int mood = 50;

unsigned long lastPetTime = 0;

const unsigned long sadDelay = 5000;

const int happyIncrement = 10;
const int sadDecrement = 1;

int currentR = 0, currentG = 255, currentB = 0; 
int targetR = 128, targetG = 0, targetB = 128; 

bool lastButtonState = HIGH;

void setup() {
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Interactive Toy (Green→Purple Gradient) ready!");
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

 
  if (buttonState == LOW && lastButtonState == HIGH) {
    mood += happyIncrement;
    if (mood > 100) mood = 100;
    lastPetTime = millis();
    Serial.println("You petted the toy! It's happier!");
    delay(200);
  }
  lastButtonState = buttonState;

  
  if (millis() - lastPetTime > sadDelay) {
    mood -= sadDecrement;
    if (mood < 0) mood = 0;
  }


  calculateTargetColor(mood);

  
  smoothTransition();

  
  Serial.print("Mood: ");
  Serial.println(mood);

  delay(50);
}


void calculateTargetColor(int moodValue) {
  
  targetR = map(moodValue, 0, 100, 0, 128);   
  targetG = map(moodValue, 0, 100, 255, 0);   
  targetB = map(moodValue, 0, 100, 0, 128);   
}

void smoothTransition() {
  int step = 5; 

  if (currentR < targetR) currentR += step;
  else if (currentR > targetR) currentR -= step;

  if (currentG < targetG) currentG += step;
  else if (currentG > targetG) currentG -= step;

  if (currentB < targetB) currentB += step;
  else if (currentB > targetB) currentB -= step;

  currentR = constrain(currentR, 0, 255);
  currentG = constrain(currentG, 0, 255);
  currentB = constrain(currentB, 0, 255);

  analogWrite(RledPin, currentR);
  analogWrite(GledPin, currentG);
  analogWrite(BledPin, currentB);
}
