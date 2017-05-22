#include <ESP8266WiFi.h>
#include <PubSubClient.h>

unsigned long prev_millis_mqtt_loop = 0;
const long interval_mqtt_loop = 100;

unsigned long prev_millis_connection_alive = 0;
const long interval_connection_alive = 5000;

const int button_one_pin = 14;
int button_one_state = LOW;
int button_one_pressed = false;

const int button_two_pin = 12;
int button_two_state = LOW;
int button_two_pressed = false;

const int button_three_pin = 13;
int button_three_state = LOW;
int button_three_pressed = false;

void setup() {
  Serial.begin(9600);
  setup_wifi();
  setup_mqtt();
  pinMode(button_one_pin, INPUT);
  pinMode(button_two_pin, INPUT);
  pinMode(button_three_pin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  button_one_state = digitalRead(button_one_pin);
  button_two_state = digitalRead(button_two_pin);
  button_three_state = digitalRead(button_three_pin);

  if(button_one_state == HIGH && !button_one_pressed) {
    button_one_pressed = true;
    send_message("button_pressed", "1");
  } else if(button_one_state == LOW && button_one_pressed) {
    button_one_pressed = false;
  }

  if(button_two_state == HIGH && !button_two_pressed) {
    button_two_pressed = true;
    send_message("button_pressed", "2");
  } else if(button_two_state == LOW && button_two_pressed) {
    button_two_pressed = false;
  }

  if(button_three_state == HIGH && !button_three_pressed) {
    button_three_pressed = true;
    send_message("button_pressed", "3");
  } else if(button_three_state == LOW && button_three_pressed) {
    button_three_pressed = false;
  }

  if(currentMillis - prev_millis_mqtt_loop >= interval_mqtt_loop) {
    prev_millis_mqtt_loop = currentMillis;
 
    loop_mqtt();
  }

  if(currentMillis - prev_millis_connection_alive >= interval_connection_alive) {
    prev_millis_connection_alive = currentMillis;

    check_wifi();    
    ping_mqtt();
  }
  
}
