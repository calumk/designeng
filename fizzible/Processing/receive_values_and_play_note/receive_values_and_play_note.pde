// added code to play and pan sine note based on the first two elements
// in the current values array
// set the variable maxValue to scale the pitch well


import ddf.minim.*;
import ddf.minim.signals.*;
import processing.serial.*;

Minim minim;
AudioOutput out;
SineWave sine;

Serial myPort;  // Create object from Serial class
int[] currentValues= {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

//change these to reflect the maximum values you will get
int maxValue1=255;
int maxValue2=255;

boolean newValues=false;

void setup() 
{
  size(512, 200, P2D);
  minim = new Minim(this);
  // get a line out from Minim, default bufferSize is 1024, default sample rate is 44100, bit depth is 16
  out = minim.getLineOut(Minim.STEREO);
  // create a sine wave Oscillator, set to 440 Hz, at 0.5 amplitude, sample rate from line out
  sine = new SineWave(440, 0.5, out.sampleRate());
  // set the portamento speed on the oscillator to 200 milliseconds
  sine.portamento(200);
  // add the oscillator to the line out
  out.addSignal(sine);

  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');
}

void draw()
{
  background(0);
  stroke(255);
  // draw the waveforms
  for (int i = 0; i < out.bufferSize() - 1; i++)
  {
    float x1 = map(i, 0, out.bufferSize(), 0, width);
    float x2 = map(i+1, 0, out.bufferSize(), 0, width);
    line(x1, 50 + out.left.get(i)*50, x2, 50 + out.left.get(i+1)*50);
    line(x1, 150 + out.right.get(i)*50, x2, 150 + out.right.get(i+1)*50);
  }


  if (newValues) {
    println(currentValues);
    // with portamento on the frequency will change smoothly
    float freq = map(abs(currentValues[0]), 0, maxValue1, 60, 1500);
    sine.setFreq(freq);
    //we can also pan the sound
    float pan = map(abs(currentValues[1]), 0, maxValue2, -1, 1);
    sine.setPan(pan);

    newValues=false;
  }
}

void stop()
{
  out.close();
  minim.stop();

  super.stop();
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

