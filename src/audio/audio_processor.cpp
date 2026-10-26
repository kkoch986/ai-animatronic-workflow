#include "audio/audio_processor.h"
#include <iostream>
#include <vector>
#include <cmath>

namespace audio {
    
AudioProcessor::AudioProcessor() : initialized(false), stream(nullptr), sampleRate(44100), framesPerBuffer(512) {
    // Constructor implementation
}

AudioProcessor::~AudioProcessor() {
    // Destructor implementation
    if (initialized) {
        release();
    }
}

void AudioProcessor::initialize(int rate, int frames) {
    try {
        sampleRate = rate;
        framesPerBuffer = frames;
        
        // Initialize PortAudio
        Pa_Initialize();
        
        // Open audio stream
        Pa_OpenDefaultStream(&stream, 1, 0, paFloat32, sampleRate, framesPerBuffer, nullptr, nullptr);
        
        initialized = true;
        std::cout << "Audio processor initialized successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error initializing audio processor: " << e.what() << std::endl;
        initialized = false;
    }
}

void AudioProcessor::processAudio() {
    // This method will be implemented in later phases
    if (!initialized) {
        return;
    }
    
    // In a real implementation, this would:
    // 1. Capture audio samples
    // 2. Process them with FFT
    // 3. Extract meaningful features
    // 4. Map to control parameters
    
    std::cout << "Processing audio data" << std::endl;
}

void AudioProcessor::release() {
    if (stream) {
        Pa_CloseStream(stream);
        stream = nullptr;
    }
    
    Pa_Terminate();
    initialized = false;
    std::cout << "Audio processor released" << std::endl;
}

void AudioProcessor::startCapture() {
    if (!initialized || !stream) {
        return;
    }
    
    Pa_StartStream(stream);
    std::cout << "Audio capture started" << std::endl;
}

void AudioProcessor::stopCapture() {
    if (!initialized || !stream) {
        return;
    }
    
    Pa_StopStream(stream);
    std::cout << "Audio capture stopped" << std::endl;
}

std::vector<double> AudioProcessor::performFFT(const std::vector<float>& input) {
    if (input.empty()) {
        return {};
    }
    
    int n = input.size();
    std::vector<double> output(n);
    
    // Create FFTW plan
    fftw_plan plan = fftw_plan_dft_r2c_1d(n, const_cast<float*>(input.data()), 
                                         reinterpret_cast<fftw_complex*>(output.data()), 
                                         FFTW_MEASURE);
    
    // Execute FFT
    fftw_execute(plan);
    
    // Clean up
    fftw_destroy_plan(plan);
    
    return output;
}

std::vector<double> AudioProcessor::getFrequencyBands(const std::vector<double>& fftResult, int numBands) {
    if (fftResult.empty() || numBands <= 0) {
        return {};
    }
    
    std::vector<double> bands(numBands, 0.0);
    int n = fftResult.size();
    
    // Simple banding - distribute FFT bins across frequency bands
    for (int i = 0; i < n && i < numBands; ++i) {
        bands[i] = fftResult[i];
    }
    
    return bands;
}

} // namespace audio