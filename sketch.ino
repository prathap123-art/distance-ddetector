#include <Servo.h>

Servo myServo;

int trigPin = 2;
int echoPin = 3;
int buzzer = 4;
int distance;

void setup() {
  Serial.begin(9600);

  myServo.attach(9);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);

  myServo.write(0);
  digitalWrite(buzzer, LOW);
}

int getdistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  int duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    return -1;
  }

  int distance = duration * 0.034 / 2;
  return distance;
}

void beep(int times) {
  for (int i = 0; i < times; i++) {
    tone(buzzer, 1000, 500);
    delay(1000);
    noTone(buzzer);
  }
}

void loop() {
  distance = getdistance();

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance <= 10) {
    Serial.println("Object detected!");

    myServo.write(90);
    beep(5);

    delay(3000);

    myServo.write(0);
  }
  else {
    Serial.println("No object detected.");
    noTone(buzzer);
    myServo.write(0);
  }

  delay(1000);
}
