#ifndef FACIAL_ANALYSIS_H
#define FACIAL_ANALYSIS_H

#include <opencv2/opencv.hpp>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <vector>
#include <memory>

namespace video {
    
struct FacialFeatures {
    cv::Point leftEyeCenter;
    cv::Point rightEyeCenter;
    cv::Point noseTip;
    cv::Point mouthCenter;
    std::vector<cv::Point> landmarks;
    double smileIntensity;
    double eyeOpenness;
    double gazeDirectionX;
    double gazeDirectionY;
    bool isBlinking;
};

class FacialAnalysis {
private:
    dlib::shape_predictor predictor;
    dlib::frontal_face_detector detector;
    bool modelLoaded;
    
public:
    FacialAnalysis();
    ~FacialAnalysis();
    
    bool loadModels(const std::string& faceDetectorPath, const std::string& shapePredictorPath);
    FacialFeatures analyzeFrame(const cv::Mat& frame);
    void drawFeatures(cv::Mat& frame, const FacialFeatures& features);
    std::vector<cv::Point> getFaceLandmarks(const dlib::full_object_detection& dets);
    
    // Expression analysis
    double calculateSmileIntensity(const std::vector<cv::Point>& landmarks);
    double calculateEyeOpenness(const std::vector<cv::Point>& landmarks);
    bool detectBlinking(const std::vector<cv::Point>& landmarks);
    cv::Point calculateGazeDirection(const std::vector<cv::Point>& landmarks);
};

} // namespace video

#endif // FACIAL_ANALYSIS_H