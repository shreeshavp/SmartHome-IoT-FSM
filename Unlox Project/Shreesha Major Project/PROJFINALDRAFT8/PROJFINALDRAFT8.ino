#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Servo doorServo;

const uint8_t LDR_PIN       = A0;  
const uint8_t DOORBELL_PIN  = D1;  
const uint8_t PIR_PIN       = D2;  
const uint8_t HVAC_FAN_PIN  = D5;  
const uint8_t LIGHT_PIN     = D6;  
const uint8_t BUZZER_PIN    = D7;  
const uint8_t SERVO_PIN     = D8;  
const uint8_t MODE_PIN      = 16;  // GPIO16 is D0

const float TEMP_THRESHOLD = 30.0;             
const uint32_t DOOR_OPEN_TIME = 5000;          
const uint32_t ALARM_BLINK_INTERVAL = 250;     

uint32_t currentMillis = 0;
uint32_t doorOpenedAt = 0;
uint32_t lastAlarmBlink = 0;

bool isDoorOpen = false;
bool isArmed = false;
bool alarmLEDState = false;

void setup() {
  Serial.begin(115200); 
  pinMode(PIR_PIN, INPUT);
  pinMode(DOORBELL_PIN, INPUT_PULLUP); 
  pinMode(MODE_PIN, INPUT); 
  pinMode(HVAC_FAN_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  doorServo.attach(SERVO_PIN);
  doorServo.write(0); 
  Wire.begin(D3, D4); 
  mlx.begin();
}

void loop() {
  currentMillis = millis();
  isArmed = (digitalRead(MODE_PIN) == HIGH); 
  
  // HVAC Logic
  if (mlx.readAmbientTempC() > TEMP_THRESHOLD) {
    digitalWrite(HVAC_FAN_PIN, HIGH); 
    if (!isArmed || digitalRead(PIR_PIN) == LOW) digitalWrite(BUZZER_PIN, HIGH); 
  } else {
    digitalWrite(HVAC_FAN_PIN, LOW);  
    if (!isArmed || digitalRead(PIR_PIN) == LOW) digitalWrite(BUZZER_PIN, LOW); 
  }

  // Light Logic
  if (analogRead(LDR_PIN) < 400) digitalWrite(LIGHT_PIN, HIGH);
  else digitalWrite(LIGHT_PIN, LOW);

  // Security Logic
  if (isArmed && digitalRead(PIR_PIN) == HIGH) {
    if (currentMillis - lastAlarmBlink >= ALARM_BLINK_INTERVAL) {
      lastAlarmBlink = currentMillis;
      alarmLEDState = !alarmLEDState;
      digitalWrite(LIGHT_PIN, alarmLEDState);  
      digitalWrite(BUZZER_PIN, alarmLEDState); 
    }
  }

  // Door Logic
  if (digitalRead(DOORBELL_PIN) == LOW && !isDoorOpen) {
    doorServo.write(90); 
    isDoorOpen = true;
    doorOpenedAt = currentMillis; 
  }
  if (isDoorOpen && (currentMillis - doorOpenedAt >= DOOR_OPEN_TIME)) {
    doorServo.write(0); 
    isDoorOpen = false;
  }
}
