/*
 * RFM12B wireless demo - struct receiver - no ack
 *
 */


#include <RF12.h>  //from jeelabs.org
#include <Ports.h> 

// RF12B constants:
const byte network  = 100;   //network group (can be in the range 1-255).
const byte myNodeID = 2;     //unique node ID of receiver (1 through 30)

//Frequency of RF12B can be RF12_433MHZ, RF12_868MHZ or RF12_915MHZ.
const byte freq = RF12_868MHZ; // Match freq to module

void setup()
{
  rf12_initialize(myNodeID,freq,network);   //Initialize RFM12 with settings defined above  
  Serial.begin(9600); 
}

typedef struct {  // Message data Structure, this must match Tx
   int   sampleNumber;	           
  int value1;
  int value2;
  int value3;
  int value4;
  int value5;
  int value6;
  int value7;
  int value8;
  int value9;
} 
Payload;

Payload sample;         // declare an instance of type Payload named sample

void loop() {

  if (rf12_recvDone() && rf12_crc == 0 && (rf12_hdr & RF12_HDR_CTL) == 0) 
  {
    sample = *(Payload*)rf12_data;            // Access the payload  
   printOutValues();
  }
}



void printOutValues(){

   Serial.print(sample.sampleNumber);
   Serial.print(",");
   Serial.print(sample.value1);
   Serial.print(","); 
   Serial.print(sample.value2);
   Serial.print(",");
  Serial.print(sample.value3);
   Serial.print(",");  
   Serial.print(sample.value4);
   Serial.print(","); 
  Serial.print(sample.value5);
   Serial.print(","); 
   Serial.print(sample.value6);
   Serial.print(","); 
   Serial.print(sample.value7);
   Serial.print(","); 
   Serial.print(sample.value8);
   Serial.print(","); 
   Serial.print(sample.value9);
   Serial.println(); 
}
