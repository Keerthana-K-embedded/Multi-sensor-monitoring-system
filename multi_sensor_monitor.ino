#include <DHT.h>   // Install "DHT sensor library" by Adafruit

// Pin assignments (change to match your wiring)
#define DHTPIN 4
#define DHTTYPE DHT11
const int TRIG_PIN   = 5;    // HC-SR04 trigger
const int ECHO_PIN   = 18;   // HC-SR04 echo
const int IR_PIN     = 19;   // IR obstacle sensor output
const int PIR_PIN    = 21;   // PIR motion sensor output
const int BUZZER_PIN = 25;
const int LED_PIN    = 2;    // on-board LED

// Alert thresholds
const float TEMP_LIMIT_C   = 35.0;
const int   DISTANCE_LIMIT = 20;   // cm

DHT dht(DHTPIN, DHTTYPE);

long readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);  // 30 ms timeout
  if (duration == 0) return -1;                    // no echo
  return duration * 0.034 / 2;
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  dht.begin();
  Serial.println("Multi-sensor monitoring system started");
}

void loop() {
  float temp = dht.readTemperature();
  long distance = readDistanceCm();
  bool irDetected = (digitalRead(IR_PIN) == LOW);  // most IR modules go LOW on detection
  bool motion = (digitalRead(PIR_PIN) == HIGH);

  bool alert = false;
  if (!isnan(temp) && temp > TEMP_LIMIT_C) alert = true;
  if (distance > 0 && distance < DISTANCE_LIMIT) alert = true;
  if (irDetected || motion) alert = true;

  digitalWrite(BUZZER_PIN, alert);
  digitalWrite(LED_PIN, alert);

  Serial.printf("Temp: %.1f C | Distance: %ld cm | IR: %s | Motion: %s | ALERT: %s\n",
                temp, distance,
                irDetected ? "YES" : "no",
                motion ? "YES" : "no",
                alert ? "YES" : "no");

  delay(1000);
}
