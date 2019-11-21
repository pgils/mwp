#ifndef MEANIMAGE_H
#define MEANIMAGE_H

#include <opencv2/videoio.hpp>
#include <opencv2/core/mat.hpp>
#include <string>

class MwpImage
{
public:
    MwpImage(const std::string& inputFile);
    // delete copy constructor and assignment operator
    MwpImage(const MwpImage&) = delete;
    auto operator=(const MwpImage&) -> MwpImage& = delete;
    // delete move constructor and assignment operator
    MwpImage(MwpImage&&) = delete;
    auto operator=(MwpImage&&) -> MwpImage& = delete;
    virtual ~MwpImage();

private:
    cv::VideoCapture *capture;
    cv::Mat *output;

public:
    auto generate(int height, int width) -> bool;
    auto write(const std::string& filename) -> bool;
};

#endif // MEANIMAGE_H
