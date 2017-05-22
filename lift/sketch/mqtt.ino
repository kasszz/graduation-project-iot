/*
 * https://tuts.codingo.me/mqtt-and-esp8266
 */

PubSubClient client(get_wifi_client());

const char* mqtt_server = "192.168.1.102";
const int mqtt_server_port = 8001;

void setup_mqtt() {
  client.setServer(mqtt_server, mqtt_server_port);
  client.setCallback(recieve_message);
  connect_mqtt();
}

void loop_mqtt() {
  client.loop();
}

void connect_mqtt() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("NodeMCU elevator")) {
      Serial.println("connected");
      client.subscribe("dormant");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void ping_mqtt() {
  connect_mqtt();
  send_message("keep_alive", "");
}

void send_message(char* topic, char* msg) {
  client.publish(topic, msg);
}

void recieve_message(char* topic, byte* payload, unsigned int length) {
  String value = "";
  
  for (int i = 0; i < length; i++) {
    value += (char)payload[i];
  }

  if(value == "1") {
    reset_elevator_variables();
    dormant = false;
  }
}

