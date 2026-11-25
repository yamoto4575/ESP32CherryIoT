//https://www.haruirosoleil.com/entry/2020/02/02/101937

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <DHT20.h> //DHT20 by RobTillaart
#include <Wire.h>

DHT20 DHT;

// WiFi Setting
const char* ssid = "";
const char* password = "";

void setup() {
  Serial.begin(115200);
  Wire.begin(1, 3); //1,3:ConnectorA 5,4:ConnectorB
}

void loop() {
  sendData();
  delay(10000);
}

void connectWiFi(){
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  //Start WiFi connection
  WiFi.begin(ssid, password);

  //Check WiFi connection status
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void sendData(){

  WiFiClientSecure sslclient;

  const char* server = "script.google.com";
  String url = "https://script.google.com/macros/s/AKfycbwc2fOYzTgqVfB3uLAMwdhzUhWnmq0UdfH9UYdf52pNjmPDRL_1DlmEe95MKXH18p2D/exec";  //googlescript web app url

DHT.read();
  float Temperature = DHT.getTemperature();
  float Humidity = DHT.getHumidity();
  //Look at the serial monitor
  Serial.print(String(Temperature) + "℃");
  Serial.print(" / ");
  Serial.println(String(Humidity) + "%");
  delay(500);

  //Prepare measurements
  float sensor_data1= Temperature; //dammy data
  float sensor_data2= Humidity; //dammy data

  //Connect WiFi
  connectWiFi();

  //Display of measured values
  Serial.println(sensor_data1);
  Serial.println(sensor_data2);

  //Add measurement value to the end of the URL
  url += "?";
  url += "&1_cell=";
  url += sensor_data1;
  url += "&2_cell=";
  url += sensor_data2;

  //Access server
  Serial.println("Access server...");
  sslclient.setInsecure(); //skip verification
  
  //Send data
  if (!sslclient.connect(server, 443)) {
    Serial.println("Connection failed!");
    Serial.println("");
    return;
  }

  Serial.println("Connected to server");

  sslclient.println("GET " + url);
  delay(1000); //Waiting for stabilization
  sslclient.stop();

  Serial.println("Data transmission completed");
  Serial.println("");

  //Disconnect WiFi
  WiFi.mode(WIFI_OFF);
}
