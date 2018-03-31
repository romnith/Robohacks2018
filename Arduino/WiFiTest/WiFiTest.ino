#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOSC.h>

WiFiUDP udp;
ArduinoOSC<WiFiUDP> osc;

const char* ssid = "Private-Notman";
const char* pwd = "3S6MpezhnHd";
//const IPAddress ip(192, 168, 1, 201);
//const IPAddress gateway(192, 168, 1, 1);
//const IPAddress subnet(255, 255, 255, 0);
const char* host = "172.20.80.27";
const int recv_port = 52193;
const int send_port = 12000;

void setup()
{
    Serial.begin(115200);
//    WiFi.disconnect(true);
//    WiFi.onEvent(onWiFiEvent);
    WiFi.begin(ssid, pwd);
//    WiFi.config(ip, gateway, subnet);

    // check for the presence of the shield:
    if (WiFi.status() == WL_NO_SHIELD) {
      Serial.println("WiFi shield not present");
      // don't continue:
      while (true);
    }

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println(WiFi.status());
    }

//    osc.begin(udp, recv_port);
//    osc.addCallback("/ard/aaa", &callback);
//    osc.addCallback("/ard", &callback);
}

void loop()
{
//    osc.parse();

      if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("connected!");
   
  }
  Serial.println(WiFi.status());
}
//
//void callback(OSCMessage& m)
//{
//    //create new osc message
//    OSCMessage msg;
//    //set destination ip address & port no
//    msg.beginMessage(host, send_port);
//    //set argument
//    msg.setOSCAddress(m.getOSCAddress());
//    msg.addArgInt32(m.getArgAsInt32(0));
//    msg.addArgFloat(m.getArgAsFloat(1));
//    msg.addArgString(m.getArgAsString(2));
//    //send osc message
//    osc.send(msg);
//}

//void onWiFiEvent(WiFiEvent_t event)
//{
//    switch (event)
//    {
//        case SYSTEM_EVENT_STA_START:
//        {
//            Serial.println("STA Started");
//            break;
//        }
//        case SYSTEM_EVENT_STA_CONNECTED:
//        {
//            Serial.println("STA Connected");
//            break;
//        }
//        case SYSTEM_EVENT_STA_GOT_IP:
//        {
//            Serial.print("STA IPv4: ");
//            Serial.println(WiFi.localIP());
//            break;
//        }
//        case SYSTEM_EVENT_STA_DISCONNECTED:
//        {
//            Serial.println("STA Lost Connection");
//            break;
//        }
//        case SYSTEM_EVENT_STA_STOP:
//        {
//            Serial.println("STA Stopped");
//            break;
//        }
//        default:
//        {
//            break;
//        }
//    }
//}
