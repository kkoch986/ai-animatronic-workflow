#ifndef VIDEO_PROCESSOR_H
#define VIDEO_PROCESSOR_H

#include <opencv2/opencv.hpp>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/shape_predictor.h>
#include <dlib/opencv/cv_image.h>
#include <vector>

namespace video {
    
class VideoProcessor {
private:
    bool initialized;
    dlib::frontal_face_detector detector;
    dlib::shape_predictor sp;
    
public:
    VideoProcessor();
    ~VideoProcessor();
    
    void initialize();
    void processFrame(cv::Mat& frame);
    void release();
};

} // namespace video

#endif // VIDEO_PROCESSOR_H