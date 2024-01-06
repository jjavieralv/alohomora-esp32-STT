#include <Arduino.h>
// Use board library esp32 by Espressif Systems version 1.0.6
// Additional boards manager URL: https://github.com/espressif/arduino-esp32/releases/download/1.0.6/package_esp32_index.json

#include "VL53L0X.h"
#include "Audio.h"
#include "CloudSpeechClient.h"

// motor
#define MOTOR_NORMAL_PIN 12
#define MOTOR_REVERSE_PIN 13
#define MOTOR_SPEED 100
#define TIME_MOVING 3000

VL53L0X dist_sensor;
String door_password="campurrianas de chocolate";
const int freq = 500;
const int resolution = 8;


void setup() {
  delay(2000);
  Serial.begin(115200);
  dist_sensor.check_start();

  //Indicator led
  pinMode(32, OUTPUT);
  digitalWrite(32, LOW);

  // Motor
  pinMode(MOTOR_NORMAL_PIN, OUTPUT);
  digitalWrite(MOTOR_NORMAL_PIN, LOW);
  pinMode(MOTOR_REVERSE_PIN, OUTPUT);
  digitalWrite(MOTOR_REVERSE_PIN, LOW);

  //pinMode(MOTOR_NORMAL_PIN, OUTPUT);
  //ledcSetup(MOTOR_NORMAL_PIN, freq, resolution);
  //ledcAttachPin(MOTOR_NORMAL_PIN, 0);
  //ledcWrite(0, 0);
  //ledcSetup(MOTOR_REVERSE_PIN, freq, resolution);
  //ledcAttachPin(MOTOR_REVERSE_PIN, 1);
  //ledcWrite(1, 0);


  Serial.println("--------System start--------");


  delay(200);
}


void loop() {
  // check distance in order
  if(dist_sensor.measure(400,5)){
    Serial.println("--------close enough--------");
    delay(500);

    // Recording audio
    digitalWrite(32, HIGH);
    Serial.println("\r\nRecord start!\r\n");
    Audio* audio = new Audio(ADMP441);
    //Audio* audio = new Audio(M5STACKFIRE);
    audio->Record();
    digitalWrite(32, LOW);

    // Transcription
    Serial.println("Recording Completed. Now Processing...");
    CloudSpeechClient* cloudSpeechClient = new CloudSpeechClient(USE_APIKEY);
    String transcription=cloudSpeechClient->Transcribe(audio);
    Serial.println(transcription);
    delete cloudSpeechClient;
    delete audio;

    //Compare transcription and
    if(door_password.equals(transcription)){
      Serial.println("clave correcta");
      digitalWrite(MOTOR_NORMAL_PIN, HIGH);
      delay(TIME_MOVING);
      digitalWrite(MOTOR_NORMAL_PIN, LOW);
      delay(TIME_MOVING*2);
      digitalWrite(MOTOR_REVERSE_PIN, HIGH);
      delay(TIME_MOVING);
      digitalWrite(MOTOR_REVERSE_PIN, LOW);
      ////move forward
      //ledcWrite(0, MOTOR_SPEED);
      //delay(TIME_MOVING);
      //ledcWrite(0, 0);
//
      ////delay 
      //delay(TIME_MOVING);
//
      ////move backwards
      //ledcWrite(1, MOTOR_SPEED);
      //delay(TIME_MOVING);
      //ledcWrite(1, 0);
    }

    Serial.println("--------System Finished--------");
  }
  delay(3000);
}


/*
#include "Audio.h"
#include "CloudSpeechClient.h"

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\r\nRecord start!\r\n");
  Audio* audio = new Audio(ICS43434);
  //Audio* audio = new Audio(M5STACKFIRE);
  audio->Record();
  Serial.println("Recording Completed. Now Processing...");
  CloudSpeechClient* cloudSpeechClient = new CloudSpeechClient(USE_APIKEY);
  cloudSpeechClient->Transcribe(audio);
  delete cloudSpeechClient;
  delete audio;

}

void loop() {
}
*/

