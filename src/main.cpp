#include <iostream>
#include <opencv2/opencv.hpp>
#include "video/video_processor.h"
#include "control/control_system.h"
#include "audio/audio_processor.h"
#include "audio/speech_processor.h"
#include "video/facial_analysis.h"

int main() {
    std::cout << "AI Animatronic System - Phase 5 & 6 Implementation" << std::endl;
    std::cout << "==================================================" << std::endl;
    
    // Initialize components
    video::VideoProcessor videoProcessor;
    control::ControlSystem controlSystem;
    audio::AudioProcessor audioProcessor;
    audio::SpeechProcessor speechProcessor;
    video::FacialAnalysis facialAnalyzer;
    
    try {
        // Initialize video processor
        std::cout << "Initializing video processor..." << std::endl;
        if (!videoProcessor.initialize()) {
            std::cerr << "Failed to initialize video processor" << std::endl;
            return 1;
        }
        
        // Load facial analysis models
        std::cout << "Loading facial analysis models..." << std::endl;
        // Note: In a real system, you would specify the correct paths for your models
        if (!facialAnalyzer.loadModels("", "")) {
            std::cerr << "Failed to load facial analysis models" << std::endl;
            return 1;
        }
        
        // Initialize control system
        std::cout << "Initializing control system..." << std::endl;
        controlSystem.initialize("127.0.0.1", 8000);
        
        // Initialize audio processor
        std::cout << "Initializing audio processor..." << std::endl;
        audioProcessor.initialize(44100, 512);
        
        // Initialize speech processor
        std::cout << "Initializing speech processor..." << std::endl;
        speechProcessor.initialize(44100, 512);
        
        // Start audio capture
        std::cout << "Starting audio capture..." << std::endl;
        audioProcessor.startCapture();
        speechProcessor.startCapture();
        
        // Main processing loop
        std::cout << "System initialized successfully. Starting main processing loop..." << std::endl;
        
        cv::Mat frame;
        cv::namedWindow("AI Animatronic System", cv::WINDOW_AUTOSIZE);
        
        while (true) {
            // Capture video frame
            if (!videoProcessor.processFrame(frame)) {
                std::cerr << "Failed to capture video frame" << std::endl;
                break;
            }
            
            // Extract facial features
            auto features = videoProcessor.extractFacialFeatures(frame);
            
            // Draw facial features on the frame
            videoProcessor.drawFacialFeatures(frame, features);
            
            // Send data to control system (OSC communication)
            if (features.landmarks.size() >= 68) {
                // Map facial features to OSC messages
                controlSystem.sendFaceData(features);
                
                // Send audio data to control system for audio-reactive responses
                // This would typically involve capturing audio samples and sending them through OSC
                std::vector<float> audioSamples = {0.1f, 0.2f, 0.3f}; // Mock audio data
                controlSystem.sendAudioData(audioSamples);
            }
            
            // Process speech if available (in a real system, this would be continuous)
            // This is just an example of how speech processing would integrate
            std::vector<float> mockAudioData(1024, 0.5f); // Mock audio data for demonstration
            std::string transcribedText = speechProcessor.transcribeAudio(mockAudioData);
            std::string emotion = speechProcessor.analyzeSpeechEmotion(mockAudioData);
            
            // Display transcribed text and emotion on frame
            if (!transcribedText.empty()) {
                cv::putText(frame, "Transcribed: " + transcribedText, 
                           cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.6, 
                           cv::Scalar(255, 255, 255), 2);
            }
            
            if (!emotion.empty()) {
                cv::putText(frame, "Emotion: " + emotion, 
                           cv::Point(10, 60), cv::FONT_HERSHEY_SIMPLEX, 0.6, 
                           cv::Scalar(255, 255, 255), 2);
            }
            
            // Display the frame
            cv::imshow("AI Animatronic System", frame);
            
            // Break on ESC key press
            if (cv::waitKey(1) == 27) {
                break;
            }
        }
        
        std::cout << "AI Animatronic System is running..." << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error in main: " << e.what() << std::endl;
        return 1;
    }
    
    // Cleanup
    std::cout << "Cleaning up..." << std::endl;
    audioProcessor.stopCapture();
    audioProcessor.release();
    speechProcessor.release();
    videoProcessor.release();
    
    std::cout << "AI Animatronic System shutdown complete." << std::endl;
    return 0;
}