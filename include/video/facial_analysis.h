#ifndef FACIAL_ANALYSIS_H
#define FACIAL_ANALYSIS_H

#include <opencv2/opencv.hpp>
#include <vector>

namespace video {
    
struct FacialFeatures {
    int face_area;
    cv::Point face_center;
    std::vector<cv::Point> landmarks;
    // Additional facial feature data would go here
};

class FacialAnalysis {
private:
    bool initialized;
    
public:
    FacialAnalysis();
    ~FacialAnalysis();
    
    void initialize();
    void analyzeFrame(const cv::Mat& frame, FacialFeatures& features);
    void release();
    
    bool isInitialized() const { return initialized; }
};

} // namespace video

#endif // FACIAL_ANALYSIS_H