#ifndef SPEECH_PROCESSOR_H
#define SPEECH_PROCESSOR_H

#include <portaudio.h>
#include <string>
#include <vector>
#include <memory>

namespace audio {
    
class SpeechProcessor {
private:
    bool initialized;
    PaStream* stream;
    int sampleRate;
    int framesPerBuffer;
    
public:
    SpeechProcessor();
    ~SpeechProcessor();
    
    void initialize(int rate, int frames);
    void startCapture();
    void stopCapture();
    void release();
    
    // Speech processing methods
    std::string transcribeAudio(const std::vector<float>& audioData);
    std::string analyzeSpeechEmotion(const std::vector<float>& audioData);
    bool isCommand(const std::string& text, const std::vector<std::string>& commands);
    std::vector<std::string> extractKeywords(const std::string& text);
    
    // Audio feature extraction
    double calculateLoudness(const std::vector<float>& audioData);
    double calculatePitch(const std::vector<float>& audioData);
    bool isSpeechPresent(const std::vector<float>& audioData);
};

} // namespace audio

#endif // SPEECH_PROCESSOR_H