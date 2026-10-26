#include "video/video_processor.h"
#include <opencv2/opencv.hpp>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing/shape_predictor.h>
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

void VideoProcessor::initialize() {
    try {
        // Initialize face detector
        detector = dlib::get_frontal_face_detector();
        
        // Load shape predictor model (this would be a path to your .dat file)
        // For now, we'll just initialize the detector
        std::cout << "Video processor initialized successfully" << std::endl;
        initialized = true;
    } catch (const std::exception& e) {
        std::cerr << "Error initializing video processor: " << e.what() << std::endl;
        initialized = false;
    }
}

void VideoProcessor::processFrame(cv::Mat& frame) {
    // Process individual frame
    if (!initialized || frame.empty()) {
        return;
    }
    
    try {
        // Convert OpenCV Mat to dlib image format
        dlib::cv_image<dlib::bgr_pixel> cimg(frame);
        
        // Detect faces
        std::vector<dlib::rectangle> faces = detector(cimg);
        
        // Process each detected face
        for (const auto& face : faces) {
            // This is where we'd extract facial landmarks if we had a model loaded
            // For now, just display face detection results
            
            // Draw rectangle around face
            cv::Point pt1(face.left(), face.top());
            cv::Point pt2(face.right(), face.bottom());
            cv::rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0), 2);
            
            std::cout << "Detected face at: (" << face.left() << ", " << face.top() 
                      << ") - (" << face.right() << ", " << face.bottom() << ")" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error processing frame: " << e.what() << std::endl;
    }
}

void VideoProcessor::release() {
    // Release resources
    initialized = false;
    std::cout << "Video processor released" << std::endl;
}

} // namespace video