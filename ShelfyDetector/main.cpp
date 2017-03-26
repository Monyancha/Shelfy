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
            "./houghcircles <image_name>, Default is ../data/dataset\n" << endl;
}

vector<string> getFilesInDir(string dirname){
    DIR *dir;
    struct dirent *ent;
    vector<string> filenames;

    if ((dir = opendir(dirname.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            string filename(ent->d_name);
            if (filename != "." && filename != "..")
                filenames.push_back(dirname + "/" + filename);
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
    }
    return filenames;
}

int main(int argc, char** argv) {
    cv::CommandLineParser parser(argc, argv,
                                 "{help h ||}{@image|../data/dataset|}"
    );
    if (parser.has("help"))
    {
        help();
        return 0;
    }
    Detector detector;

    int count = 0;
    //![load]
    vector<string> files = getFilesInDir(parser.get<string>("@image"));
    for (size_t i = 0; i < files.size(); i++){
        cout << files[i];
        switch(detector.loadImage(count, files[i])){
            case -1:
                cout << "can not open " << files[i] << endl;
                return -1;
            case 1:
                return 0;
            default:
                break;
        }
        count++;
        if (27 == waitKey())
            break;
    }

//
//    Detector detector;
//
//    string filenames[] = {
//            "../data/board.jpg",
//            "../data/board3.jpg"
//    };
//
//    int count = 0;
//    while (true) {
//        switch(detector.loadImage(count, filenames[1])){
//            case -1:
//                help();
//                cout << "can not open " << filename << endl;
//                return -1;
//            case 1:
//                return 0;
//            default:
//                break;
//        }
//        count++;
//        if (27 == waitKey(30))
//            break;
//    }
    return 0;
}