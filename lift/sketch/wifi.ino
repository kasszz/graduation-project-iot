/*
 * https://diyhacking.com/esp8266-tutorial/
 */

WiFiClient esp_client;

const char* wifi_network_name = "Osso";
const char* wifi_network_password = "twijfelachtig123";

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_network_name);

  WiFi.begin(wifi_network_name, wifi_network_password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to wifi with the name: ");
    Serial.println(wifi_network_name);

    delay(5000);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void check_wifi() {
  if(WiFi.status() != WL_CONNECTED) {
    WiFi.begin(wifi_network_name, wifi_network_password);

    while (WiFi.status() != WL_CONNECTED) {
      Serial.print("Attempting to connect to wifi with the name: ");
      Serial.println(wifi_network_name);
      
      delay(2500);
    }

    Serial.println("Reconnected to wifi");
  }
}

PubSubClient&& get_wifi_client() {
  return esp_client;
}

