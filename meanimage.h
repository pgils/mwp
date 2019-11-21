#ifndef MEANIMAGE_H
#define MEANIMAGE_H

#include <opencv2/videoio.hpp>
#include <opencv2/core/mat.hpp>
#include <string>

class MeanImage
{
public:
    MeanImage(const std::string& inputFile);
    // delete copy constructor and assignment operator
    MeanImage(const MeanImage&) = delete;
    auto operator=(const MeanImage&) -> MeanImage& = delete;
    // delete move constructor and assignment operator
    MeanImage(MeanImage&&) = delete;
    auto operator=(MeanImage&&) -> MeanImage& = delete;
    virtual ~MeanImage();

private:
    cv::VideoCapture *capture;
    cv::Mat *output;

public:
    auto generate(int height, int width) -> bool;
    auto write(const std::string& filename) -> bool;
};

#endif // MEANIMAGE_H
