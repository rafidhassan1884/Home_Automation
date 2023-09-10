#include <SoftwareSerial.h>
//#include <ESP8266WiFi.h>
// Configure software serial port
SoftwareSerial SIM900(7, 8); // Rx, Tx
#define SW1 2
#define SW2 3
#define SW3 4
#define SW4 5
#define TRIG 6
int s1 =0; 
int s2 = 0;
int s3 = 0;
int s4 = 0;
int trig = 0;
int flag =1;

void setup() {

  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  pinMode(SW4, INPUT);
  pinMode(TRIG, INPUT);
  // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  // Make sure that corresponds to the baud rate of your module
  delay(10000);
  Serial.begin(19200);
  SIM900.begin(19200);
  // Give time to your GSM shield log on to network
  delay(10000);   
  
  // Send the SMS
  //sendSMS();
}

void loop() { 
 
 s1 = digitalRead(SW1);
 s2 = digitalRead(SW2);
 s3 = digitalRead(SW3);
 s4 = digitalRead(SW4);
 trig = digitalRead(TRIG);


 if(trig ==1){
   sendSMS();

   while(trig==1)
   {

    trig = digitalRead(TRIG);
    delay(100);
   }
 }
 delay(5000);
  
}

void sendSMS() {
  // AT command to set SIM900 to SMS mode
  Serial.println("Entered!!!");
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT+CMGS=\"+8801755778923\""); 
  delay(100);
  char buffer[40];
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  sprintf(buffer, "S1=%d, S2=%d, S3=%d, S4=%d,", !s1, !s2, !s3, !s4);
  String msg = String(buffer);
  SIM900.println(msg);
  Serial.println("Msg sent");
  Serial.println(msg); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(1000); // agey 5000 silo
}
