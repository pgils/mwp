#include "mwpimage.h"
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace std;
using namespace cv;

MwpImage::MwpImage(const string& inputFile)
{
    this->output = nullptr;
    this->capture = new VideoCapture;
    this->capture->setExceptionMode(true);
    try {
        this->capture->open(inputFile);
    }  catch (...) {
        throw;
    }
    // we no longer need exceptions for capture device
    this->capture->setExceptionMode(false);
}

MwpImage::~MwpImage() {
    this->capture->release();
    delete this->capture;
    delete this->output;
}

auto MwpImage::generate(int height, int width) -> bool {
    double totalFrames;
    double framesPerCol;
    double currentFrame;
    int colIndex;
    Mat frame;
    Mat column;
    Mat meanColumn;

    if(height < 1 || width < 1) {
        cerr << "invalid dimensions" << endl;
        return false;
    }

    totalFrames = this->capture->get(CAP_PROP_FRAME_COUNT);
    framesPerCol = totalFrames / width;
    colIndex = 0;
    this->output = new Mat(height, width, CV_32FC3, Scalar(0));

    for(;;) {
        if(!this->capture->grab())
            break;

        currentFrame = this->capture->get(CAP_PROP_POS_FRAMES);

        if(currentFrame >= (framesPerCol * colIndex)) {

            this->capture->retrieve(frame);

            // reduce the frame down to a 1-pixel column
            reduce(frame, column, 1, REDUCE_AVG);
            // create a column with a single color (average)
            meanColumn = Mat(height, 1, CV_32FC3, mean(column));
            // copy the column to `output`
            meanColumn.col(0).copyTo(this->output->col(colIndex++));

            if(colIndex >= width)
                break;
        }
    }
    return true;
}

auto MwpImage::write(const std::string& filename) -> bool {
    bool result;

    try {
        result = imwrite(filename, *this->output);
    }  catch (const Exception& e) {
        cerr << "Exception saving output file: " << e.what() << endl;
    }
    return result;
}
