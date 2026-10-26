#ifndef VIDEO_PROCESSOR_H
#define VIDEO_PROCESSOR_H

namespace video {
    
class VideoProcessor {
public:
    VideoProcessor();
    ~VideoProcessor();
    
    void initialize();
    void processFrame(cv::Mat& frame);
    void release();
    
private:
    // Video processing members
    cv::VideoCapture capture;
    bool initialized;
};

} // namespace video

#endif // VIDEO_PROCESSOR_H