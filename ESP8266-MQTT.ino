/*

                  ESP8266 MQTT x EMQX

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *wifi_ssid = "xxxxxxxxxxxxx";  // Enter your WiFi name
const char *wifi_pass = "xxxxxxxxxxxxx";  // Enter WiFi password

const char *mqtt_broker = "broker.emqx.io";  // broker address
const char *mqtt_topic = "esp8266/test";     // define topic
const char *mqtt_username = "emqx";          // username for authentication
const char *mqtt_password = "public";        // password for authentication
const int mqtt_port = 1883;                  // port of MQTT over TCP

WiFiClient espClient;
PubSubClient client(espClient);

//==========================================================================
void setup() {
  Serial.begin(115200);
  WiFi.begin(wifi_ssid, wifi_pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    uint32_t chipId = ESP.getChipId();
    String client_id = "esp8266-client-" + String(chipId);
    Serial.printf("The client %s connects to the mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Connected to MQTT broker.");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds.");
      delay(5000);
    }
  }

  client.publish(mqtt_topic, "Hi EMQX I'm ESP8266 ^^");  // publish to the topic
  client.subscribe(mqtt_topic);                          // subscribe from the topic
}

//==========================================================================
void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(mqtt_topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}

//==========================================================================
void reconnect() {
  while (!client.connected()) {
    Serial.println("Reconnecting to MQTT broker...");
    uint32_t chipId = ESP.getChipId();
    String client_id = "esp8266-client-" + String(chipId);
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Reconnected to MQTT broker.");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("Failed to reconnect to MQTT broker, rc = ");
      Serial.print(client.state());
      Serial.println("Retrying in 5 seconds.");
      delay(5000);
    }
  }
}

//==========================================================================
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

//==========================================================================