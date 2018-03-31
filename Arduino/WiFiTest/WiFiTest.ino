//172.20.80.181

#include <SoftwareSerial.h>
#include <string.h>

#define TIMEOUT 5000 // mS
#define LED 5
SoftwareSerial mySerial(0, 1); // RX, TX
int ind1, ind2;
 
void setup()
{
 pinMode(0, INPUT);
 pinMode(1, OUTPUT);
 
 Serial.begin(9600);
 mySerial.begin(115200);
 Serial.println("INITIATION");
 //SendCommand("AT+RST", "Ready");
 //delay(5000);
 //SendCommand("AT+CWMODE=1","OK");
 //SendCommand("AT+CIFSR", "OK");
 //SendCommand("AT+CIPMUX=1","OK");
 //SendCommand("AT+CIPSERVER=1,80","OK");
}
 
void loop(){
 String IncomingString="";
 String output = "";
 int data;
 ind1 = ind2 = -1;
 //StringReady= true;
 if (mySerial.available()){
   IncomingString=mySerial.readString();
   data = IncomingString.toInt();
   if (data > -10 && data < 10){
    output = IncomingString.substring(11, 15);
    Serial.println("DATA : " + output);
    
   }
    /*
      for (int i = 0; i<IncomingString.length(); i++){
        if (IncomingString.charAt(i) == ':' && ind1 == -1){
          ind1 = i;
        }
        else if(IncomingString.charAt(i) == ':' && ind2 == -1){
          ind2 = i;
        }
      }
      
      if(ind1 != -1 && ind2!=-1){
       Serial.println("DATA : " + IncomingString.substring(ind1, ind2));
      }
     }
     */
 }
 if (Serial.available()){
    SendCommand(Serial.readString(), "ok");
 }
 
 delay(10);
}
 
boolean SendCommand(String cmd, String ack){
  mySerial.println(cmd); // Send "AT+" command to module
  if (!echoFind(ack)) // timed out waiting for ack string
    return true; // ack blank or ack found
}
 
boolean echoFind(String keyword){
 byte current_char = 0;
 byte keyword_length = keyword.length();
 long deadline = millis() + TIMEOUT;
 while(millis() < deadline){
  if (mySerial.available()){
    char ch = mySerial.read();
    Serial.write(ch);
    if (ch == keyword[current_char])
      if (++current_char == keyword_length){
       Serial.println();
       return true;
    }
   }
  }
 return false; // Timed out
}
