#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "hacker"; // Enter your WiFi name
const char *password = "123123123";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "minion/childsectiondata";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;


WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
 
  Serial.begin(115200);
 
//  pinMode(1,OUTPUT);
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
  }
  delay(1000);
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
  Serial.println("Connected to the WiFi network");
 
  
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
      String client_id = "esp8266-client-";
      client_id += String(WiFi.macAddress());
      if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      } else {
          delay(2000);
      }
  }
//   publish and subscribe and  connection status sending to mqtt broker
  client.publish(topic,"200");
  client.subscribe(topic);
}

//void callback(char *topic, byte *payload, unsigned int length) {
//  Serial.print("Message arrived in topic: ");
// Serial.println(topic);
// Serial.print("Message:");
// for (int i = 0; i < length; i++) {
//     Serial.print((char) payload[i]); 
//
// }
// Serial.println();
// Serial.println("-----------------------");
//
//}


void loop() {
//  client.loop();
  //delay(2000);
  //Serial.print("RRSI: ");
  int val=WiFi.RSSI();
 // Serial.println(val);
  if(val<=-70){
//    delay(2000);
//    Serial.print("Out of range");
    client.publish(topic,"500");
    client.subscribe(topic);
  }else{
//   delay(2000);
//   Serial.print("connection ok");
    delay(1000);
    client.publish(topic,"300");
    
  }
  
  
}
