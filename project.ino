#include <WiFiNINA.h>
#include <PubSubClient.h>

// Replace with your Wi-Fi credentials
const char* ssid = "Yugam";
const char* password = "12345678";

// MQTT Broker information
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttClientId = "nano_33_iot";
const char* mqttTopic1 = "pranav";
int data1 = 0;
int concentrationValue = 0;
const char* mqttTopic2 = "pranav1";
int data2 = 0;
const char* mqttTopic3 = "pranav2";
String data3 = "";
const char* mqttTopic4 = "pranav3";
String data4 = "";



// Initialize the Wi-Fi client and MQTT client
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void callback(char* topic, byte* payload, unsigned int length) {
  // Handle the incoming MQTT messages
  if (strcmp(topic, mqttTopic1) == 0) {
    // Handle data from topic1 (concentration 2)
    
    for (int i = 0; i < length; i++) {
      data1 += (char)payload[i];
    }
    Serial.print("Received data from topic1: ");
    Serial.println(data1);
    // Process the data as needed
  }
  else if (strcmp(topic, mqttTopic2) == 0) {
    // Handle data from topic2 (concentration 1)
    
    for (int i = 0; i < length; i++) {
      data2 += (char)payload[i];
    }
    Serial.print("Received data from topic2: ");
    Serial.println(data2);
    // Process the data as needed
  }
  else if (strcmp(topic, mqttTopic3) == 0) {
    // Handle data from topic3 (chemical 1)
    
    for (int i = 0; i < length; i++) {
      data3 += (char)payload[i];
    }
    Serial.print("Received data from topic3: ");
    Serial.println(data3);
    // Process the data as needed
  }
  else if (strcmp(topic, mqttTopic4) == 0) {
    // Handle data from topic4 (chemical 2)
    
    for (int i = 0; i < length; i++) {
      data4 += (char)payload[i];
    }
    Serial.print("Received data from topic4: ");
    Serial.println(data4);
    // Process the data as needed
  }
}

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Set MQTT server and callback
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  // Connect to MQTT
  while (!client.connect(mqttClientId)) {
    delay(1000);
    Serial.println("Connecting to MQTT...");
  }
  Serial.println("Connected to MQTT");

  // Subscribe to the MQTT topics
  client.subscribe(mqttTopic1);
  if(concentrationValue > 33)
  {
    Serial.println("it worked");
  }
  client.subscribe(mqttTopic2);
  client.subscribe(mqttTopic3);
  client.subscribe(mqttTopic4);
}

void loop() {
  client.loop();
  if(data1 > 33)
  {

  }
  if(data2 > 98)
  {

  }
}
