#include <iostream>
#include <dirent.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "Detector.h"

using namespace cv;
using namespace std;


static void help()
{
    cout << "\nThis program demonstrates circle finding with the Hough transform.\n"
            "Usage:\n"
            "./houghcircles <image_name>, Default is ../dataset\n" << endl;
}


int main(int argc, char** argv) {
    cv::CommandLineParser parser(argc, argv,
                                 "{help h ||}{@image|./image.jpg|}{@output|./result|}"
    );
    if (parser.has("help"))
    {
        help();
        return 0;
    }
    Detector detector;

    //![load]
    string filename = parser.get<string>("@image");
    string output = parser.get<string>("@output");
    return detector.loadImage(filename, output);
}