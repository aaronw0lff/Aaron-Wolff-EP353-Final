#include "Envelope.h"
#include <stdio.h>

void initEnvelopeFreq(Envelope *envelope, float duration, int initfreq, int attacktime, int primfreq, char yndescend, int resttime, int fadetime, float sampleRate){
  envelope->duration = duration;
  envelope->sampleRate = sampleRate;
  envelope->totalFrames = sampleRate * duration;
  envelope->max = kMaxAmp;
  envelope->gate = false;
  envelope->curIndex = 0;
  envelope->curFrame = 0;

  int xUnit = envelope->totalFrames / (kNumPoints - 1);
  float yUnit = kMaxAmp / (kNumPoints - 1);
  
  // extern int samplerate;
  // extern int initfreq;
  // extern int attacktime;
  // extern float ampdecay;
  // extern int primfreq; 
  // extern char yndescend;
  // extern int resttime;
  // extern int fadetime;


  envelope->points[0].x = 0;
  envelope->points[0].y = initfreq;
  envelope->points[1].x = (attacktime/1000.0)*192000.0;
  envelope->points[1].y = primfreq;
  envelope->points[2].x = ((attacktime+resttime)/1000.0)*192000.0;
  envelope->points[2].y = primfreq;
  envelope->points[3].x = ((attacktime+resttime+fadetime)/1000.0)*192000.0;
  if(yndescend == 'y'){
    envelope->points[3].y = 20;
  }else if(yndescend == 'n'){
    envelope->points[3].y = primfreq;
  }



  //Initialize points in the envelope
  for(int i=0; i<kNumPoints; i++){
    
    //envelope->points[i].x = xUnit * i;
    //Change y points to have different envelope shapes
   // envelope->points[i].y = kMaxAmp - yUnit * i;
    printf("pitchenvelope->points[%d].x: %f\n", i, (float)envelope->points[i].x);
    printf("pitchenvelope->points[%d].y: %f\n", i, (float)envelope->points[i].y);
  }

  envelope->points[kNumPoints-1].x = envelope->totalFrames;
  envelope->points[kNumPoints-1].y = 0.0f;
}

void resetFreq(Envelope *envelope){
  envelope->curFrame = 0;
  envelope->curIndex = 0;
  envelope->gate = false;
}

float getCurrentFreq(Envelope *envelope){
  static Point a, b;
  static float m, y; //slope and amp
  //Check to make sure the gate is on
  if(!envelope->gate) return 0;

  //End of envelope. Reset to the beginning
  if(envelope->curFrame >= envelope->points[kNumPoints-1].x){
    resetFreq(envelope);
    return 0;
  }
  
  // If the frame is on or over next point, increment the curIndex
  if(envelope->curFrame >= envelope->points[envelope->curIndex + 1].x){
    envelope->curIndex++;
  }

  a = envelope->points[envelope->curIndex];
  b = envelope->points[envelope->curIndex + 1];

  // Calculate slope of the two points
  m = (b.y - a.y) / (b.x - a.x);
  // Calculate the amp from the slope
  y = (m * envelope->curFrame - m * a.x) + a.y;

  //Increment frame
  envelope->curFrame++;

  // printf("y: %f\n", y);
  // printf("%d %f %f %f %f\n", envelope->curFrame, a.x, a.y, b.x, b.y);

  return y;
}

void setDurationFreq(Envelope *envelope, float duration){
  static int totalFrames;
  static float unit;

  if(duration < 0.05){
    duration = 0.05;
  }

  totalFrames = envelope->totalFrames;
  envelope->totalFrames = envelope->totalFrames * duration;
  unit = (float) envelope->totalFrames / totalFrames;
  
  //Recompute the duration values
  for(int i=0; i<kNumPoints; i++){
    envelope->points[i].x = (int)(envelope->points[i].x * unit);
  }
}

