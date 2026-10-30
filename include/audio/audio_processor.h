#ifndef AUDIO_PROCESSOR_H
#define AUDIO_PROCESSOR_H

#include <portaudio.h>
#include <fftw3.h>
#include <vector>
#include <string>

namespace audio {
    
class AudioProcessor {
private:
    bool initialized;
    PaStream* stream;
    int sampleRate;
    int framesPerBuffer;
    
public:
    AudioProcessor();
    ~AudioProcessor();
    
    void initialize(int rate, int frames);
    void processAudio();
    void release();
    void startCapture();
    void stopCapture();
    
    // FFT processing methods
    std::vector<double> performFFT(const std::vector<float>& input);
    std::vector<double> getFrequencyBands(const std::vector<double>& fftResult, int numBands);
};

} // namespace audio

#endif // AUDIO_PROCESSOR_H