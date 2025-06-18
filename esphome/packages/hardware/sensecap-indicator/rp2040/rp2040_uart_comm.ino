// original RP2040 examples on GitHub: https://github.com/Seeed-Solution/SenseCAP_Indicator_RP2040

#include <Arduino.h>

#define DEBUG 1

#define BUZZER_PIN 19  //Buzzer GPIO

#define CMD_UART_RX_PIN 17  //ESP32 command received communication
#define CMD_UART_TX_PIN 16  //ESP32 command response communication
#define CMD_UART_BAUD 115200

#define BEEP_DURATION 50

/************************ beep ****************************/
void buzzer_init(void) {
  pinMode(BUZZER_PIN, OUTPUT);
}

void buzzer_pwm_beep(int pwmValue) {
  analogWrite(BUZZER_PIN, pwmValue);
  delay(BEEP_DURATION);
  analogWrite(BUZZER_PIN, 0);
}

void buzzer_tone_beep(int freq) {
  tone(BUZZER_PIN, freq);
  delay(BEEP_DURATION);
  noTone(BUZZER_PIN);
}

#define CMD_TYPE_BEEP_SYSTEM 0xB0
void buzzer_beep_system(void) {
  buzzer_pwm_beep(127);
}

#define CMD_TYPE_BEEP_PRESSED 0xB1
void buzzer_beep_pressed(void) {
  buzzer_pwm_beep(254);
}

#define CMD_TYPE_BEEP_ALERT 0xBB
void buzzer_beep_alert(void) {
  buzzer_tone_beep(4000);
  delay(100);
  buzzer_tone_beep(4000);
}

void setup() {
  // When sending data over USB, we use Serial. This data can be viewed in the Serial Monitor in the Arduino IDE. (https://docs.arduino.cc/learn/communication/uart)
  Serial.begin(115200);

  // setup internal UART communication with ESP32
  Serial1.setRX(CMD_UART_RX_PIN);
  Serial1.setTX(CMD_UART_TX_PIN);
  Serial1.begin(CMD_UART_BAUD);

  // setup buzzer
  buzzer_init();
  
  // signal setup end using a beep
  buzzer_beep_system();
}

int incomingByte = 0;
void loop() {
  if (Serial1.available() > 0) {
    // read the incoming one byte:
    incomingByte = Serial1.read();

    switch (incomingByte) {
      case CMD_TYPE_BEEP_SYSTEM:
        buzzer_beep_system();
        break;
      case CMD_TYPE_BEEP_PRESSED:
        buzzer_beep_pressed();
        break;
      case CMD_TYPE_BEEP_ALERT:
        buzzer_beep_alert();
        break;
      default:
        // say what you got:
        Serial.printf("Command not implemented! Received byte: 0x%x\n", incomingByte);
        break;
    }
    delay(100);
  } else {
    delay(10);
  }
}