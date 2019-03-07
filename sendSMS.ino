/* 
 * File : sendSMS.ino
 * Author : Léo Bonnaire
 * Date : Fri, March 1 2019
 * 
 * Function : Send a SMS using GSM librairy
 * 
 * How2Use : define the PIN code of the SIM card you put
 *           setup the connection using setupMsg() in the setup loop
 *           send your SMS with sendMsg()
 *           This function takes 2 arguments :
 *            * The number you want to send your message (char)
 *            * The text you want to send (char)
 * 
 * Source used here : www.arduino.cc/en/Tutorial/GSMExamplesSendSMS
 * 
 */

#include <GSM.h>
#define PINNUMBER ""

GSM gsmAccess;
GSM_SMS sms;

void setup() {
  Serial.begin(9600);
  setupMsg();
}

void loop() {
  Serial.print("Enter a mobile phone : ");
  char cNumber[20];
  readSerial(cNumber);
  Serial.println();
  Serial.print("Now, enter the content : ");
  char txtMsg[200];
  readSerial(txtMsg);
  sendMsg (cNumber, txtMsg);
}

/*** FUNCTIONS SECTION BELOW ***/

// Use this function in the setup loop to connect
void setupMsg () {
  boolean bConnected = false;
  while(!bConnected){
    if(gsmAccess.begin(PINNUMBER)==GSM_READY)
      bConnected = true;
    else {
      Serial.println("Still not connected ...");
      delay(1000);
    }
  }
  Serial.println("Ready to go !");
}

// Send a SMS
void sendMsg (char cNumber[], char txtMsg[]) {
  Serial.println("\nSending message ...");
  sms.beginSMS(cNumber);
  sms.print(txtMsg);
  sms.endSMS();
  Serial.print("\nMessage succesfully sent to : \n");
  Serial.println(cNumber);
}

// Read the user inputs
int readSerial(char result[]) {
  int i = 0;
  while(1) {
    while (Serial.available() > 0) {
       char inChar = Serial.read();
       if (inChar == '\n') {
        result[i] = '\0';
        Serial.flush();
        return 0;
       }
       if (inChar != '\r') {
         result[i] = inChar;
         i++;
       }
    }
  }
}
