
#include <ESP8266WiFi.h>
#include <Ticker.h> //Ticker Library

#ifndef STASSID
#define STASSID "bindsoft"
#define STAPSK  "88088808"
#endif



const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "10.10.11.62";
const uint16_t port = 7000;
WiFiClient client;
Ticker blinker;
  
void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

//   if(client.connected()){// 타임인터럽트 
//    //client.println("client.connected ");
//    blinker.attach(1, send_msg); 
//    
//  }

  Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
 
  
}

void loop() {
  static bool wait = false;

  //연결 tcp 
  if (!client.connect(host, port)) { 
    //Srial.println("connection failed");
    client.println("!client.connect ");
    delay(5000);
    return;
  }

 
  // wait for data to be available 데이터기다리는거구 
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      //client.println("client.available > 0");
      client.stop();
      delay(10000); //ms 
      return;
    }
  }

  if (client.connected()){
    client.println("timer interrupt");
  }

  char buf[1024];
  int nread;
  while (client.available()) {
    nread = client.read(buf, 1024);
    Serial.write(buf, nread);
    
  }

  //Serial.println();
//  Serial.flush();
//  client.flush();
  client.stop();

//  if (wait) {
//    delay(300000); // execute once every 5 minutes, don't flood remote service 5분에 한번씩 
//  }
  wait = true;
}

void send_msg(){
  client.println("timer interrupt");
}
