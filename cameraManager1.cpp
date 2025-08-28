// CameraManager.cpp (core loop)
#include "CameraManager.hpp"
CameraManager::CameraManager()
{
    rs2::config cfg;
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
    cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);
    pipe.start(cfg);
}
void CameraManager::start(FrameCallback cb)
{
    running = true;
    capture_thread = std::thread([this, cb]()
                                 {
        while(running) {
            auto frames = pipe.wait_for_frames();
            rs2::frame color = frames.get_color_frame();
            rs2::frame depth = frames.get_depth_frame();
            cv::Mat rgb(cv::Size(640,480), CV_8UC3, (void*)color.get_data(), cv::Mat::AUTO_STEP);
            cv::Mat depth16(cv::Size(640,480), CV_16U, (void*)depth.get_data(), cv::Mat::AUTO_STEP);
            cv::Mat depth_m; depth16.convertTo(depth_m, CV_32F, 0.001f); // meters
            cb(rgb, depth_m);
        } });
}
void CameraManager::stop()
{
    running = false;
    if (capture_thread.joinable())
        capture_thread.join();
    pipe.stop();
}
CameraManager::~CameraManager() { stop(); }
