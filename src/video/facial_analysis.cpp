#include "video/facial_analysis.h"
#include <dlib/image_processing.h>
#include <dlib/opencv.h>
#include <iostream>
#include <cmath>

namespace video {
    
FacialAnalysis::FacialAnalysis() : modelLoaded(false) {
    // Constructor implementation
}

FacialAnalysis::~FacialAnalysis() {
    // Destructor implementation
}

bool FacialAnalysis::loadModels(const std::string& faceDetectorPath, const std::string& shapePredictorPath) {
    try {
        // Load the face detector
        detector = dlib::get_frontal_face_detector();
        
        // Load the shape predictor
        dlib::deserialize(shapePredictorPath) >> predictor;
        
        modelLoaded = true;
        std::cout << "Facial analysis models loaded successfully" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error loading facial analysis models: " << e.what() << std::endl;
        modelLoaded = false;
        return false;
    }
}

FacialFeatures FacialAnalysis::analyzeFrame(const cv::Mat& frame) {
    FacialFeatures features;
    
    if (!modelLoaded || frame.empty()) {
        return features;
    }
    
    try {
        // Convert OpenCV Mat to dlib format
        dlib::cv_image<dlib::bgr_pixel> cimg(frame);
        
        // Detect faces
        std::vector<dlib::rectangle> faces = detector(cimg);
        
        if (faces.empty()) {
            return features;
        }
        
        // Get the first detected face
        dlib::full_object_detection shape = predictor(cimg, faces[0]);
        
        // Extract landmarks
        features.landmarks = getFaceLandmarks(shape);
        
        // Calculate facial features
        features.smileIntensity = calculateSmileIntensity(features.landmarks);
        features.eyeOpenness = calculateEyeOpenness(features.landmarks);
        features.isBlinking = detectBlinking(features.landmarks);
        features.gazeDirectionX = 0.0;
        features.gazeDirectionY = 0.0;
        
        // Calculate specific points
        if (features.landmarks.size() >= 68) {
            features.leftEyeCenter = features.landmarks[36];
            features.rightEyeCenter = features.landmarks[45];
            features.noseTip = features.landmarks[30];
            features.mouthCenter = features.landmarks[51];
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error analyzing facial frame: " << e.what() << std::endl;
    }
    
    return features;
}

void FacialAnalysis::drawFeatures(cv::Mat& frame, const FacialFeatures& features) {
    if (frame.empty()) {
        return;
    }
    
    // Draw landmarks
    for (size_t i = 0; i < features.landmarks.size(); ++i) {
        cv::circle(frame, features.landmarks[i], 2, cv::Scalar(0, 255, 0), -1);
    }
    
    // Draw face bounding box if available
    // This would be implemented in a more complete system
    
    // Draw facial feature indicators
    if (!features.landmarks.empty()) {
        // Draw eye centers
        if (features.landmarks.size() >= 46) {
            cv::circle(frame, features.leftEyeCenter, 5, cv::Scalar(255, 0, 0), 2);
            cv::circle(frame, features.rightEyeCenter, 5, cv::Scalar(255, 0, 0), 2);
        }
        
        // Draw mouth center
        if (features.landmarks.size() >= 52) {
            cv::circle(frame, features.mouthCenter, 5, cv::Scalar(0, 0, 255), 2);
        }
    }
}

std::vector<cv::Point> FacialAnalysis::getFaceLandmarks(const dlib::full_object_detection& dets) {
    std::vector<cv::Point> landmarks;
    
    for (int i = 0; i < dets.num_parts(); ++i) {
        landmarks.push_back(cv::Point(dets.part(i).x(), dets.part(i).y()));
    }
    
    return landmarks;
}

double FacialAnalysis::calculateSmileIntensity(const std::vector<cv::Point>& landmarks) {
    if (landmarks.size() < 68) {
        return 0.0;
    }
    
    // Calculate smile intensity based on mouth shape
    // Points 48-54 represent the mouth contour
    cv::Point leftCorner = landmarks[48];
    cv::Point rightCorner = landmarks[54];
    cv::Point topLip = landmarks[51];
    cv::Point bottomLip = landmarks[57];
    
    // Calculate vertical distance of lip
    double lipHeight = abs(bottomLip.y - topLip.y);
    
    // Calculate horizontal distance of mouth
    double mouthWidth = abs(rightCorner.x - leftCorner.x);
    
    // Smile intensity is a ratio of height to width (0-1 scale)
    if (mouthWidth > 0) {
        return std::min(1.0, lipHeight / mouthWidth);
    }
    
    return 0.0;
}

double FacialAnalysis::calculateEyeOpenness(const std::vector<cv::Point>& landmarks) {
    if (landmarks.size() < 68) {
        return 0.0;
    }
    
    // Calculate eye openness using eye landmarks
    // Left eye: points 36-41 (6 points)
    // Right eye: points 42-47 (6 points)
    
    // For simplicity, we'll calculate based on vertical distance
    cv::Point leftEyeTop = landmarks[37];
    cv::Point leftEyeBottom = landmarks[41];
    cv::Point rightEyeTop = landmarks[43];
    cv::Point rightEyeBottom = landmarks[47];
    
    double leftEyeHeight = abs(leftEyeBottom.y - leftEyeTop.y);
    double rightEyeHeight = abs(rightEyeBottom.y - rightEyeTop.y);
    
    // Average eye openness
    double avgEyeHeight = (leftEyeHeight + rightEyeHeight) / 2.0;
    
    // This would need to be normalized based on face size for accurate results
    return std::min(1.0, avgEyeHeight / 20.0); // Assuming max eye height of 20 pixels
}

bool FacialAnalysis::detectBlinking(const std::vector<cv::Point>& landmarks) {
    if (landmarks.size() < 68) {
        return false;
    }
    
    // Simple blinking detection based on eye openness
    double openness = calculateEyeOpenness(landmarks);
    
    // If eye openness is very low, it's likely a blink
    return openness < 0.1;
}

cv::Point FacialAnalysis::calculateGazeDirection(const std::vector<cv::Point>& landmarks) {
    if (landmarks.size() < 68) {
        return cv::Point(0, 0);
    }
    
    // Calculate gaze direction based on eye positions
    // This is a simplified implementation
    
    // Average of left and right eye centers
    cv::Point leftEyeCenter = landmarks[36];
    cv::Point rightEyeCenter = landmarks[45];
    
    int centerX = (leftEyeCenter.x + rightEyeCenter.x) / 2;
    int centerY = (leftEyeCenter.y + rightEyeCenter.y) / 2;
    
    return cv::Point(centerX, centerY);
}

} // namespace video