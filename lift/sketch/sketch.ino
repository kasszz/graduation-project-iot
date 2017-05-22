#include <ESP8266WiFi.h>
#include <PubSubClient.h>

bool dormant = false;
unsigned long prev_millis_elevator_check = 0;
const long interval_elevator_check = 500;
bool evelator_left_turn = true;

unsigned long prev_millis_mqtt_loop = 0;
const long interval_mqtt_loop = 100;

unsigned long prev_millis_connection_alive = 0;
const long interval_connection_alive = 5000;

void setup() {
  Serial.begin(9600);
  setup_distance();
  setup_wifi();
  setup_mqtt();
}

void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - prev_millis_elevator_check >= interval_elevator_check) {
    prev_millis_elevator_check = currentMillis;

    if(!dormant) {
      elevator_check();
    }
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

