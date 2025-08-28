// CameraManager.hpp (very short)
#pragma once
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <functional>
#include <thread>
#include <atomic>

class CameraManager
{
public:
    using FrameCallback = std::function<void(const cv::Mat &rgb, const cv::Mat &depth)>;
    CameraManager();
    ~CameraManager();
    void start(FrameCallback cb);
    void stop();

private:
    rs2::pipeline pipe;
    std::thread capture_thread;
    std::atomic<bool> running{false};
};
