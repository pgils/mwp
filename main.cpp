#include <iostream>
#include <opencv2/opencv.hpp>
#include "meanimage.h"

using namespace std;
using namespace cv;

auto main(int, char** argv) -> int
{
    cout << "create MeanImage obj" << endl;
    MeanImage image(argv[1]);
    cout << "generate image" << endl;
    image.generate(1080, 1920);
    cout << "write out file" << endl;
    image.write(argv[2]);

    return 0;
}
