#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>

char ssid[] = "Private-Notman";                     // your network SSID (name)
char key[] = "3S6MpezhnHd";       // your network key
int keyIndex = 0;                                // your network key Index number
int status = WL_IDLE_STATUS;                     // the Wifi radio's status
const char* host = "172.20.80.27";
const int recv_port = 52193;
const int send_port = 12000;

WiFiUDP Udp;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

//  // check for the presence of the shield:
//  if (WiFi.localIP().toString() == "0.0.0.0") {
//    Serial.println("WiFi shield not present");
//    // don't continue:
//    while (true);
//  }

  // attempt to connect to Wifi network:
  //while ( status != WL_CONNECTED) {
    //Serial.print("Attempting to connect to WEP network, SSID: ");
    //Serial.println(ssid);
    status = WiFi.begin(ssid, keyIndex, key);

    // wait 10 seconds for connection:
    delay(10000);
  //}

  // once you are connected :
  Serial.print("You're connected to the network");
}

void loop() {
  // check the network status connection once every 10 seconds:
  delay(10000);
  printWifiStatus();

 // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(host, recv_port);
    Udp.write("HI");
    Udp.endPacket();
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
