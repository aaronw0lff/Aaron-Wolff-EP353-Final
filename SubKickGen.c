
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sndfile.h>
#include "Wavetable.h"

#include "Envelope.h"

#define kSampleRate 192000
#define kBufferSize 192000

int samplerate = 192000;
int initfreq;
int attacktime;
float ampdecay;
int primfreq;
char yndescend;
int resttime;
int fadetime;

Wavetable* sine1hz;

// reading the wavetable audio file into wavetable struct
// void loadwavetable(Wavetable *wavetable){
//     SNDFILE *table;
//     SF_INFO tableinfo; 

//     float *test_buffer = malloc(1920000 * sizeof(float));

//     printf("a\n");
//     table = sf_open("192sinetable.wav", SFM_READ, &tableinfo);
//     printf("begin loading wavetable\n");
//     initWavetable(wavetable, (unsigned long) tableinfo.frames);

//     wavetable->table = malloc(tableinfo.frames * sizeof(float));

//     sf_read_float(table, test_buffer, tableinfo.frames);

//     writeToWavetable(wavetable, test_buffer, tableinfo.frames);


//     sf_close(table);
//     printf("d\n");
// }


void kickgen(float* buffer, Envelope *FreqEnvelope, Envelope *AmpEnvelope){
    float current_amp = 0;
    
    Wavetable* wavetable = (Wavetable *) malloc(sizeof(Wavetable));
    loadwavetable(wavetable);
    
    int i=0;
    FreqEnvelope->gate = 1;
    AmpEnvelope->gate = 1;
    for(i = 0; i < AmpEnvelope->totalFrames; i++){
        float freq = getCurrentFreq(FreqEnvelope);
        // printf("\t current freq: %f\n", xfreq);
        setFrequencyHz(wavetable, freq);
        current_amp = getCurrentAmp(AmpEnvelope);
        // printf("\tcurrent_amp: %f\n", current_amp);
        buffer[i] = current_amp * next(wavetable);
        // * next(wavetable);
    }
}


void writekick(float* buffer, sf_count_t  num_samples){
    SNDFILE *kickfile;
    SF_INFO kickinfo; 
    memset(&kickinfo, 0, sizeof(SF_INFO));
    
    kickinfo.channels = 1;
    kickinfo.frames = num_samples;
    kickinfo.samplerate = 192000;
    kickinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_32;

    printf("size: %lld %lld %d\n", num_samples, kickinfo.frames, kickinfo.channels);
    kickfile = sf_open("K_I_C_C.wav", SFM_WRITE, &kickinfo);

    printf("size: %lld %lld %d\n", num_samples, kickinfo.frames, kickinfo.channels);

    // for(int i=0;i<num_samples;i++){
    //     printf("%d %f\n", i, buffer[i]);
    // }

    int count = sf_write_float(kickfile, buffer, num_samples);
    printf("Wrote: %d %lld\n", count, kickinfo.frames);

    sf_close(kickfile);
}



int main(int argc, char const *argv[])
{
    // initfreq = 200;
    // attacktime = 10;
    // ampdecay = 10;
    // primfreq = 100;
    // yndescend = 'y';
    // resttime = 200;
    // fadetime = 100;
    
//asking and scanning for user-defined parameters
    printf("\n\n\n\n-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-\nW E L C O M E      T O     T H E     F A T    K I C C     G E N E R A T O R  \n-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-\n\nStarting Frequency (Hz): ");
    scanf("%d", &initfreq);

    printf("\nAttack Time (ms): ");
    scanf("%d", &attacktime);

    ampdecay = attacktime/1000.0;

    printf("\nResting Frequency (Hz): ");
    scanf("%d", &primfreq);

    printf("\nDescend? (y/n): ");
    scanf("%s", &yndescend);




        if(yndescend == 'y'){
          printf("\nOk, How long to rest before going down? (ms): ");
          scanf("%d", &resttime);
          printf("\nHow long should it take to go down? (ms): ");
          scanf("%d", &fadetime);
      }else if(yndescend == 'n'){
        printf("\nOk, How long before fade out? (ms): ");
        scanf("%d", &fadetime);

         }else printf("\nE R R O R :   I N V A L I D    I N P U T \n");
    printf("\n");

    // printf("buffer allocated");
    Envelope* AmpEnvelope = (Envelope *) malloc(sizeof(Envelope));
    Envelope* FreqEnvelope = (Envelope *) malloc(sizeof(Envelope));
    
    //trying to initialize the lengths of both envelopes (getCurrentAmp and getCurrentPitch)
    //I made get current pitch so that I could have two separate envelopes for pitch and amplitude
    initEnvelopeFreq(FreqEnvelope, (float)(attacktime+resttime+fadetime), initfreq, attacktime, primfreq, yndescend, resttime, fadetime, 192000);
    initEnvelopeAmp(AmpEnvelope, (float)(attacktime+resttime+fadetime), initfreq, attacktime, primfreq, yndescend, resttime, fadetime, 192000);
    float* buffer = (float *) malloc(AmpEnvelope->totalFrames*sizeof(float));

    kickgen(buffer, FreqEnvelope, AmpEnvelope);

    printf("first %d\n", AmpEnvelope->totalFrames);
    writekick(buffer, (sf_count_t) AmpEnvelope->totalFrames);


  // testing whether values were saved:    printf("\n%d %d %d %c %d %d\n", initfreq, attacktime, primfreq, yndescend, resttime, fadetime);
    free(buffer);
    
    free(AmpEnvelope);
    free(FreqEnvelope);

    return 0;
}
