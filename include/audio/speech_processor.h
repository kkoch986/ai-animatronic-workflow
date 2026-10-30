#ifndef SPEECH_PROCESSOR_H
#define SPEECH_PROCESSOR_H

#include <vector>

namespace audio {
    
class SpeechProcessor {
private:
    bool initialized;
    int sample_rate;
    int buffer_size;
    
public:
    SpeechProcessor();
    ~SpeechProcessor();
    
    void initialize(int sample_rate, int buffer_size);
    void processAudio(const std::vector<float>& audio_data);
    void release();
    
    bool isInitialized() const { return initialized; }
};

} // namespace audio

#endif // SPEECH_PROCESSOR_H