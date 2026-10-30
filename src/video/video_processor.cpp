#include "video/video_processor.h"
#include <iostream>

namespace video {
    
VideoProcessor::VideoProcessor() : initialized(false) {
    // Constructor implementation
}

VideoProcessor::~VideoProcessor() {
    // Destructor implementation
    if (initialized) {
        release();
    }
}

bool VideoProcessor::initialize(int deviceId) {
    try {
        // Open video capture device
        cap.open(deviceId);
        
        if (!cap.isOpened()) {
            std::cerr << "Error: Could not open video device " << deviceId << std::endl;
            return false;
        }
        
        // Set video properties (optional)
        cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
        cap.set(cv::CAP_PROP_FPS, 30);
        
        initialized = true;
        std::cout << "Video processor initialized successfully" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error initializing video processor: " << e.what() << std::endl;
        initialized = false;
        return false;
    }
}

bool VideoProcessor::processFrame(cv::Mat& frame) {
    if (!initialized || !cap.isOpened()) {
        return false;
    }
    
    try {
        // Capture a frame
        if (!cap.read(frame)) {
            std::cerr << "Error: Could not read frame from video device" << std::endl;
            return false;
        }
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error processing video frame: " << e.what() << std::endl;
        return false;
    }
}

void VideoProcessor::release() {
    if (cap.isOpened()) {
        cap.release();
    }
    initialized = false;
    std::cout << "Video processor released" << std::endl;
}

FacialFeatures VideoProcessor::extractFacialFeatures(const cv::Mat& frame) {
    return facialAnalyzer.analyzeFrame(frame);
}

void VideoProcessor::drawFacialFeatures(cv::Mat& frame, const FacialFeatures& features) {
    facialAnalyzer.drawFeatures(frame, features);
}

} // namespace video