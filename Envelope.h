#include <stdbool.h>

#define kNumPoints 4 //I changed this to 4 because my envelopes only need 4 points
#define kMaxAmp 1.0f

typedef struct Point {
  float x;
  float y;
} Point;

typedef struct Envelope {
  bool gate;
  Point points[kNumPoints];
  int curIndex;
  int curFrame;
  int totalFrames; //sampleRate * duration
  float sampleRate;
  float duration; //Duration of envelope in second
  float max; // Max y value
} Envelope;

// Function Prototypes
void initEnvelopeAmp(Envelope *envelope, float duration, int initfreq, int attacktime, int primfreq, char yndescend, int resttime, int fadetime, float sampleRate);
void initEnvelopeFreq(Envelope *envelope, float duration, int initfreq, int attacktime, int primfreq, char yndescend, int resttime, int fadetime, float sampleRate);
void reset(Envelope *envelope);
float getCurrentAmp(Envelope *envelope);
float getCurrentFreq(Envelope *envelope);
void setDuration(Envelope *envelope, float duration);