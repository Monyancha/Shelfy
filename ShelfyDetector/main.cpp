#include <iostream>
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
            "./houghcircles <image_name>, Default is ../data/board2.jpg\n" << endl;
}

int main(int argc, char** argv) {
    cv::CommandLineParser parser(argc, argv,
                                 "{help h ||}{@image|../data/board2.jpg|}"
    );
    if (parser.has("help"))
    {
        help();
        return 0;
    }
    //![load]
    string filename = parser.get<string>("@image");

    Detector detector;

    string filenames[] = {
            "../data/board.jpg",
            "../data/board3.jpg"
    };

    int count = 0;
    while (true) {
        switch(detector.loadImage(filenames[1])){
            case -1:
                help();
                cout << "can not open " << filename << endl;
                return -1;
            case 1:
                return 0;
            default:
                if (27 == waitKey(1000))
                    break;
        }
        count++;
    }
    return 0;
}