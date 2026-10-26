#include "video/video_processor.h"
#include <opencv2/opencv.hpp>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing/shape_predictor.h>
#include <iostream>
#include <fstream>

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
        
        // Load shape predictor model for facial landmarks
        // Note: This path should be updated to point to your actual model file
        std::string shape_predictor_path = "data/shape_predictor_68_face_landmarks.dat";
        
        // Check if model file exists
        std::ifstream file(shape_predictor_path);
        if (file.good()) {
            dlib::deserialize(shape_predictor_path) >> sp;
            std::cout << "Loaded shape predictor model from: " << shape_predictor_path << std::endl;
        } else {
            std::cerr << "Warning: Shape predictor model not found at " << shape_predictor_path 
                      << ". Facial landmarks will not be available." << std::endl;
        }
        
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
            // Draw rectangle around face
            cv::Point pt1(face.left(), face.top());
            cv::Point pt2(face.right(), face.bottom());
            cv::rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0), 2);
            
            std::cout << "Detected face at: (" << face.left() << ", " << face.top() 
                      << ") - (" << face.right() << ", " << face.bottom() << ")" << std::endl;
            
            // If we have a shape predictor model, extract facial landmarks
            if (sp) {
                dlib::full_object_detection shape = sp(cimg, face);
                
                // Draw facial landmarks
                for (unsigned long i = 0; i < shape.num_parts(); ++i) {
                    cv::Point point(shape.part(i).x(), shape.part(i).y());
                    cv::circle(frame, point, 2, cv::Scalar(0, 0, 255), -1);
                }
                
                std::cout << "Extracted " << shape.num_parts() << " facial landmarks" << std::endl;
            }
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