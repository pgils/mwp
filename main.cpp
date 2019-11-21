#include "mwpimage.h"
#include <iostream>
#include <stdexcept>
#include <unistd.h>

using namespace std;
using namespace cv;

auto printUsage(string path) -> void {
    size_t pos;
    string name = "mwp";

    // try to get the binary name from `path`
    pos = path.rfind('/');
    if(string::npos != pos)
        name = path.substr(pos+1, path.length() - pos);

    cerr << "Usage: " << name << " -i <input> -o <output> -r <rows> -c <cols>" << endl
         << endl
         << "-i     input video file name"      << endl
         << "-o     output image file name"     << endl
         << "-r     row count (image height)"   << endl
         << "-c     column count (image width)" << endl
         << "-h     print this help and exit"   << endl
         << endl;
}

auto getNumericArg(char* optarg, int *dest) -> bool {
    if(nullptr == optarg) {
        cerr << "empty numeric argument given" << endl;
        return false;
    }

    try {
        *dest = stoi(optarg);
    }  catch (const invalid_argument& e) {
        cerr << "Failed to convert argument: " << e.what() << endl;
        return false;
    }
    return true;
}

auto main(int argc, char** argv) -> int
{
    string input;
    string output;
    int width = 0;
    int height = 0;

    int c;
    while(-1 != (c=getopt(argc, argv, "i:o:r:c:h"))) {
        switch (c) {
        case 'i':
            if (nullptr != optarg)
                input = optarg;
            break;
        case 'o':
            if (nullptr != optarg)
                output = optarg;
            break;
        case 'r':
            if(!getNumericArg(optarg, &height))
                return 1;
            break;
        case 'c':
            if(!getNumericArg(optarg, &width))
                return 1;
            break;
        case 'h':
            printUsage(argv[0]);
            return 1;
        }
    }

    if(1 > input.length() || 1 > output.length()
        || 1 > width || 1 > height) {
        printUsage(argv[0]);
        return 1;
    }


    MwpImage image(input);
    cout << "generating image" << endl;
    image.generate(height, width);
    cout << "write out file" << endl;
    image.write(output);
    cout << "finished" << endl;

    return 0;
}
