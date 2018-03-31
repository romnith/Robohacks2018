//172.20.80.181

#include <SoftwareSerial.h>
#include <string.h>

#define TIMEOUT 5000 // mS
#define LED 5



SoftwareSerial mySerial(0, 1); // RX, TX
int ind1, ind2;
int mode = 0;
int lastInput = 0;
void setup()
{
 pinMode(0, INPUT); //RX
 pinMode(1, OUTPUT); //TX
 pinMode(12 , OUTPUT); //Mot1
 pinMode(13, OUTPUT); //Mot2
 
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
    lastInput = output.toInt();
   }
 }


//MANUAL MODE1

  switch (lastInput) {
    case -1:
      forward();
      break;
    case 1:
      backward();
      break;
    default:
      stop();
  }
 
 if (Serial.available()){
    //SendCommand(Serial.readString(), "ok");
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

void forward (){
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}
void backward (){
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
}
void stop(){
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
}


