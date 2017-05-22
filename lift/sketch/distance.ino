/*
 * http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
 */

const int elevator_left_trigger_pin = 14;
const int elevator_left_echo_pin = 12;
const int elevator_right_trigger_pin = 5;
const int elevator_right_echo_pin = 4;
const int distance_max = 200;

void setup_distance() {
  pinMode(elevator_left_trigger_pin, OUTPUT);
  pinMode(elevator_left_echo_pin, INPUT);
  pinMode(elevator_right_trigger_pin, OUTPUT);
  pinMode(elevator_right_echo_pin, INPUT);
}

int elevator_left_get_distance() {
  digitalWrite(elevator_left_trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(elevator_left_trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(elevator_left_trigger_pin, LOW);

  //calculate distance
  int elevator_left_distance = pulseIn(elevator_left_echo_pin, HIGH) / 58.2;

  if(elevator_left_distance > distance_max) {
    elevator_left_distance = distance_max;
  }

  return elevator_left_distance; 
} 

int elevator_right_get_distance() {
  digitalWrite(elevator_right_trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(elevator_right_trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(elevator_right_trigger_pin, LOW);

  //calculate distance
  int elevator_right_distance = pulseIn(elevator_right_echo_pin, HIGH) / 58.2;

  if(elevator_right_distance > distance_max) {
    elevator_right_distance = distance_max;
  }

  return elevator_right_distance;
 }

