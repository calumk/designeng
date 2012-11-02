/*
 * RFM12B wireless demo - struct sender - no ack
 */

#include <RF12.h> //from jeelabs.org
#include <Ports.h> 

// RF12B constants:
const byte network  = 100;   //network group (can be in the range 1-255).
const byte myNodeID = 1;     //unique node ID of receiver (1 through 30)

//Frequency of RF12B can be RF12_433MHZ, RF12_868MHZ or RF12_915MHZ.
const byte freq = RF12_868MHZ; // Match freq to module

const byte RF12_NORMAL_SENDWAIT = 0;
int count=0;

void setup()
{
  Serial.begin(9600);
  rf12_initialize(myNodeID, freq, network);   //Initialize RFM12 
}

typedef struct {  // Message data Structure, this must match Tx
  int sampleNumber;	           
  int value1;
  int value2;
  int value3;
  int value4;
  int value5;
  int  value6;
  int value7;
  int value8;
  int value9;

} 
Payload;

Payload sample;  // declare an instance of type Payload named sample


void loop()
{

  updateValues();

  while (!rf12_canSend())  // is the driver ready to send?
    rf12_recvDone();       //no so service the driver 
  Serial.print(micros()); 
  rf12_sendStart(rf12_hdr, &sample, sizeof sample); 
  rf12_sendWait(RF12_NORMAL_SENDWAIT);  // wait for send completion
  Serial.print("  ");
  Serial.print(micros());
  Serial.print("  ");
  Serial.println(micros());



  delay(1000);
}


void updateValues(){
  count=count+1;
  sample.sampleNumber=count;
  sample.value1=count;
  sample.value2=count+1;
  sample.value3=96;
  sample.value4=count+2;
  sample.value5=count+3;
  sample.value6=count+4;
  sample.value7=count+5;
  sample.value8=0;
  sample.value9=count+7;


}



