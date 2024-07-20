#ifndef SOUND_HPP
#define SOUND_HPP

#include <portaudio.h>

#define SAMPLE_RATE 44100
#define AMPLITUDE 0.1

struct PaData {
    double phase;
    float frequency;
};

static int paCallback(const void *inputBuffer, void *outputBuffer,
                      unsigned long framesPerBuffer,
                      const PaStreamCallbackTimeInfo* timeInfo,
                      PaStreamCallbackFlags statusFlags,
                      void *userData) {
    PaData *data = (PaData*)userData;
    float *out = (float*)outputBuffer;
    (void)inputBuffer;

    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        out[i] = (data->phase < 0.5 ? 1 : -1) * AMPLITUDE;
        data->phase += data->frequency / SAMPLE_RATE;
        if (data->phase >= 1.0) data->phase -= 1.0;
    }

    return paContinue;
}

inline void make_sound(float frequency, float duration) {
    PaStream *stream;
    PaData data = { 0.0, frequency };

    Pa_Initialize();
    Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE, 256, paCallback, &data);
    Pa_StartStream(stream);

    Pa_Sleep(duration * 1000);
   
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
}   

class Voice {
public: 
    void make_sound(float frequency, float duration) {
        PaStream *stream;
        PaData data = { 0.0, frequency };

        Pa_Initialize();
        Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE, 256, paCallback, &data);
        Pa_StartStream(stream);

        Pa_Sleep(duration * 1000);
       
        Pa_StopStream(stream);
        Pa_CloseStream(stream);
        Pa_Terminate();
    }   
};

#endif
