#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Audio.h"

#define kDefaultFrequency 440.0
#define kTableSize 192000 //(1<<7) //128

typedef struct Wavetable {
  float *table;
  unsigned long size;
  float curIndex;
  float delta;
  bool isPlaying;
  float amplitude;
} Wavetable;

// Function Prototypes
void createWavetable(Wavetable *wavetable);
void initWavetable(Wavetable *wavetable, unsigned long length);
void writeToWavetable(Wavetable *wavetable, float* buffer, unsigned long length);
float next(Wavetable *wavetable);
void setFrequency(Wavetable *wavetable, char *midi);
void setAmplitude(Wavetable *wavetable, float amplitude);
void setFrequencyHz(Wavetable *wavetable, float freq_Hz);
void loadwavetable(Wavetable *wavetable);