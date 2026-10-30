#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

namespace control {
    
class ControlSystem {
private:
    bool initialized;
    std::string osc_address;
    int osc_port;
    
public:
    ControlSystem();
    ~ControlSystem();
    
    void initialize(const std::string& address, int port);
    void sendOSCMessage(const std::string& path, const std::vector<float>& values);
    void processVideoFrame(const cv::Mat& frame);
    void release();
};

} // namespace control

#endif // CONTROL_SYSTEM_H