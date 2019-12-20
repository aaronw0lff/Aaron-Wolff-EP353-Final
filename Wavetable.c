#include "Wavetable.h"
#include <sndfile.h>

void createWavetable(Wavetable *wavetable){
  //Square wave approximation
  for(int i = 1; i <= 15; i+=2){ //Up to 15th harmonics, but only odd harmonics
    double delta = (2.0 * M_PI) / (wavetable->size - 1) * i;
    double angle = 0.0;
    for (int n = 0; n < wavetable->size; n++){
      wavetable->table[n] += (1.0f / i) * sin(angle);
      angle += delta;
    }
  }
}



void initWavetable(Wavetable *wavetable, unsigned long length){
  wavetable->size = length;
  // wavetable->table = (float *) calloc(length, sizeof(float));
  wavetable->table = (float *) malloc(length * sizeof(float));
  wavetable->delta = 0.0f; // kDefaultFrequency * (kTableSize / kSamplingRate);//set frequecy
  wavetable->curIndex = 0.0f;
  wavetable->isPlaying = true;
  wavetable->amplitude = 1.0f;
  printf("b\n");
}

void writeToWavetable(Wavetable *wavetable, float* buffer, unsigned long length){
  memcpy(wavetable->table, buffer, (size_t) length);
}

float next(Wavetable *wavetable){
  unsigned long index0 = (unsigned long) wavetable->curIndex;
  unsigned long index1 = index0 + 1;
  
  //Calculate the interpolation value
  float fraction = wavetable->curIndex - (float)index0;
  
  //get values from the wavetable
  float value0 = wavetable->table[index0];
  float value1 = wavetable->table[index1];
  
  //Calculate the interpolated value
  float sample = value0 + fraction * (value1 - value0);
  
  //increment the angle delta of the table and wrap
  wavetable->curIndex += wavetable->delta;
  
  if(wavetable->curIndex >= (float) wavetable->size){
      wavetable->curIndex -= (float) wavetable->size;
  }
  
  return sample;
}

void setFrequency(Wavetable *wavetable, char *midi){
  static char m = 0;
  if(m != *midi){
    // calculates frequency in Hz from midi note
    float frequency = (440.0f * pow(2, (*midi - 69.0f)/12.0f));

    // calculates timestep from frequency
    wavetable->delta = frequency * (kTableSize / kSamplingRate);

    m = *midi;
  }
}

void setFrequencyHz(Wavetable *wavetable, float freq_Hz){

  wavetable->delta = freq_Hz * (kTableSize / kSamplingRate);
  // printf("\tfreq_hz: %f\n", freq_Hz);
  // printf("\tdelta: %f\n", wavetable->delta);
}

void setAmplitude(Wavetable *wavetable, float amplitude){
  wavetable->amplitude = amplitude;
}


void loadwavetable(Wavetable *wavetable){
    SNDFILE *table;
    SF_INFO tableinfo; 
    memset(&tableinfo, 0, sizeof(SF_INFO));

    // float *test_buffer = malloc(1920000 * sizeof(float));

    // printf("a\n");
    table = sf_open("192sinetable.wav", SFM_READ, &tableinfo);
    //printf("begin loading wavetable\n");
    initWavetable(wavetable, (unsigned long) tableinfo.frames);

    // wavetable->table = malloc(tableinfo.frames * sizeof(float));

    // int count = 0;
    // count = 
    sf_read_float(table, wavetable->table, tableinfo.frames);

    //writeToWavetable(wavetable, test_buffer, tableinfo.frames);

    //free(test_buffer);

    //printf("%lld %d\n", tableinfo.frames, tableinfo.channels);


    sf_close(table);
    printf("d\n");

}