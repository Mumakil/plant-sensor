#define FLIP1 D1
#define FLIP2 D2
#define SENSOR A0

#define RED D5
#define YELLOW D6

#define MEASUREMENT_INTERVAL 5000

#define THRESHOLD_WARN 600
#define THRESHOLD_BAD 300

int flipTimer = 200;

int val1 = 0;
int val2 = 0;
int avg = 0;

void setSensorPolarity(boolean flip){
  if (flip){
    digitalWrite(FLIP1, HIGH);
    digitalWrite(FLIP2, LOW);
  } else {
    digitalWrite(FLIP1, LOW);
    digitalWrite(FLIP2, HIGH);
  }
}

void setSensorOff() {
  digitalWrite(FLIP1, LOW);
  digitalWrite(FLIP2, LOW);
}

void setColor(int red, int yellow) {
  analogWrite(RED, red * 4);
  analogWrite(YELLOW, yellow* 4);
}

void setLedStatus() {
  if (avg > THRESHOLD_WARN) {
    setColor(0, 32);
  } else if (avg > THRESHOLD_BAD) {
    setColor(0, 255);
  } else {
    setColor(255, 0);
  }
}

void readValues() {
  setSensorPolarity(true);
  delay(flipTimer);
  val1 = analogRead(SENSOR);
  setSensorPolarity(false);
  delay(flipTimer);
  val2 = 1023 - analogRead(SENSOR);
  avg = (val1 + val2) / 2;
  setSensorOff();
}

void setup(){
  #ifndef NO_SERIAL
  Serial.begin(9600);
  #endif
  // Power for flip-flop
  pinMode(FLIP1, OUTPUT);
  pinMode(FLIP2, OUTPUT);
  // analog in
  pinMode(SENSOR, INPUT);
  // output leds
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  setColor(0, 0);
}

void loop(){
  readValues();
  #ifndef NO_SERIAL
  reportLevels();
  #endif
  setLedStatus();
  delay(MEASUREMENT_INTERVAL);
}

#ifndef NO_SERIAL
void reportLevels(){
  String msg = "avg: ";
  msg += avg;
  msg += ", val1: ";
  msg += val1;
  msg += ", val2: ";
  msg += val2;
  Serial.println(msg);
}
#endif
