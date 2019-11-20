#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main(int, char** argv)
{
    cout << "File name: " << argv[1] << endl;
    VideoCapture cap(argv[1]);

    if(!cap.isOpened()) {
        cout << "open capture failed." << endl;
        return 1;
    }

    double framesPerCol = cap.get(CAP_PROP_FRAME_COUNT) / SCREEN_WIDTH;
    cout << "Total frames: " << cap.get(CAP_PROP_FRAME_COUNT) << endl;
    cout << "Frames per Column: " << framesPerCol << endl;

    int colIndex = 0;
    Mat output(SCREEN_HEIGHT, SCREEN_WIDTH, CV_32FC3);

    for(;;) {
        Mat frame;
        cap >> frame;
        if(frame.empty()) {
            cout << "frame empty." << endl;
            break;
        }

        double currentFrame = cap.get(CAP_PROP_POS_FRAMES);
        if (currentFrame > (colIndex * framesPerCol)) {
            cout << "Using frame " << currentFrame << " for index " << colIndex << endl;

            Mat column;
            // reduce the frame down to a 1-pixel column
            reduce(frame, column, 1, REDUCE_AVG);
            // create a column with a single color (average)
            Mat meanColumn(SCREEN_HEIGHT, 1, CV_32FC3, mean(column));
            // copy the column to `output`
            meanColumn.col(0).copyTo(output.col(colIndex++));
        }

    }
    // close the video file
    cap.release();

    // Write the output image to file
    imwrite(argv[2], output);


    return 0;
}
