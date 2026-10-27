#ifndef VIDEO_PROCESSOR_H
#define VIDEO_PROCESSOR_H

#include <opencv2/opencv.hpp>
#include "facial_analysis.h"
#include <memory>

namespace video {
    
class VideoProcessor {
private:
    cv::VideoCapture cap;
    bool initialized;
    FacialAnalysis facialAnalyzer;
    
public:
    VideoProcessor();
    ~VideoProcessor();
    
    bool initialize(int deviceId = 0);
    bool processFrame(cv::Mat& frame);
    void release();
    
    // Feature extraction methods
    FacialFeatures extractFacialFeatures(const cv::Mat& frame);
    void drawFacialFeatures(cv::Mat& frame, const FacialFeatures& features);
    
    // Utility methods
    bool isInitialized() const { return initialized; }
};

} // namespace video

#endif // VIDEO_PROCESSOR_H