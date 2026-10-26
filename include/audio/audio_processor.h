#ifndef AUDIO_PROCESSOR_H
#define AUDIO_PROCESSOR_H

#include <portaudio.h>
#include <string>

namespace audio {
    
class AudioProcessor {
private:
    bool initialized;
    PaStream* audio_stream;
    PaStreamParameters input_params;
    unsigned int sample_rate;
    unsigned int buffer_size;
    
public:
    AudioProcessor();
    ~AudioProcessor();
    
    void initialize();
    void processAudio();
    void release();
    
    // Callback function for PortAudio
    static int audioCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData);
};

} // namespace audio

#endif // AUDIO_PROCESSOR_H