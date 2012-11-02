/**
 * Simple Read
 * 
 * Read data from the serial port and change the color of a rectangle
 * when a switch connected to a Wiring or Arduino board is pressed and released.
 * This example works with the Wiring / Arduino program that follows below.
 */

import processing.serial.*;
Serial myPort;  // Create object from Serial class
int[] currentValues= {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
boolean newValues=false;

void setup() 
{
  size(200, 200);
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');
}

void draw()
{
  if (newValues){
   println(currentValues);
  newValues=false; 
  }
}


void serialEvent(Serial myPort) { 
  String inString = myPort.readStringUntil('\n');
  if (inString != null) {
    inString = trim(inString);
    int[] extractedValues = int(split(inString, ","));
    if (extractedValues.length ==10) {
      arrayCopy(extractedValues, currentValues);
      newValues=true;
    }
  }
}


