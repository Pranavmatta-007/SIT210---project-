#include <Arduino.h>
#include <PubSubClient.h>
#include <FlowSensor.h>
#include <WiFiNINA.h>
#include <ThingSpeak.h>
#define type YFS201
#define pin1 2
#define pin2 3
#define WIFI_SSID "Yugam"
#define WIFI_PASS "12345678"
#define THINGSPEAK_CHANNEL_ID 2300766
#define API_KEY "VB0GOB9XKG1VHVOW"

onst char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttClientId = "nano_33_iot";
const char* mqttTopic1 = "pranav";
int data1 = 0;
const char* mqttTopic2 = "pranav1";
int data2 = 0;
const char* mqttTopic3 = "pranav2";
String data3 = "";
const char* mqttTopic4 = "pranav3";
String data4 = "";

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
const int analogInPin = A0;
unsigned long avgValue;
int buf[10];
int temp = 0;
float offset = -8; // Adjust this offset based on calibration
float slope = 1.0;   // Adjust this slope based on calibration

int enA = 9;
int in1 = 8;
int in2 = 7;
int enB = 10;
int in3 = 11;
int in4 = 12;
FlowSensor Sensor1(type, pin1);
FlowSensor Sensor2(type, pin2);

void count1()
{
  Sensor1.count();
}
void count2()
{
  Sensor2.count();
}

void setup() {
  Serial.begin(115200);
  Sensor1.begin(count1);
  Sensor2.begin(count2);
    connectWiFi();

  // Initialize ThingSpeak
  ThingSpeak.begin(wifiClient);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
    pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
 
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
    digitalWrite(in4, LOW);
  digitalWrite(in3, LOW);
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
  client.subscribe(mqttTopic2);
  client.subscribe(mqttTopic3);
  client.subscribe(mqttTopic4);
}
}

//void loop() {
    //Serial.println(Sensor.getVolume());
    //Sensor.resetVolume();
      // Turn on motors
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, HIGH);
//    analogWrite(enA, 100);
//    digitalWrite(in3, LOW);
//  digitalWrite(in4, HIGH);
//    analogWrite(enB, 100);
//  // Now turn off motors
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, LOW);

//}
void loop() {

  client.loop();
  while(Sensor1.getVolume() < data2)
  {
    
  }
  while(Sensor2.getVolume() < data1)
  {
    
  }
  for (int i = 0; i < 10; i++) {
    buf[i] = analogRead(analogInPin);
    delay(10);
  }

  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }

  avgValue = 0;
  for (int i = 2; i < 8; i++)
    avgValue += buf[i];

  float pHVol = (float)avgValue * 5.0 / 1024 / 4.3;
  float phValue = -5.70 * pHVol + 25.8;
  phValue = 14.2 - phValue;

  // Apply calibration
  phValue = slope * phValue + offset;

  Serial.print("pH Value: ");
  Serial.println(phValue);
  delay(900);
  sendDataToThingSpeak(phValue);
}
void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.println("Connected to WiFi");
}
void sendDataToThingSpeak(float ph) {
  // Set the fields for temperature and humidity
  ThingSpeak.setField(1, ph);

  // Write the fields to the ThingSpeak channel
  int httpCode = ThingSpeak.writeFields(THINGSPEAK_CHANNEL_ID, API_KEY);

  // Check if the data was sent successfully
  if (httpCode == 200) {
    Serial.println("Data sent to ThingSpeak");
  } else {
    Serial.println("Error sending data to ThingSpeak");
  }
}
