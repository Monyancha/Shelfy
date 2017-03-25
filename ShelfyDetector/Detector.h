//
// Created by sajarora on 3/25/17.
//

#ifndef SHELFYDETECTOR_DETECTOR_H
#define SHELFYDETECTOR_DETECTOR_H

#include <iostream>
#include <string>
#include <vector>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

class Detector {

public:
    Detector();

    int loadImage(string filename);

    std::vector<Vec3f> detectCircles(Mat image);

    Mat getGrayImage(Mat mat);

    void showImageWithCircles(string mat, Mat vector, std::vector <Vec3f> vector1);

private:
    string grayWindowName = "Gray Window";
    string colorWindowName = "Color Window";
    string featureWindowName = "Feature Window";

    int cushion = 80;
};


#endif //SHELFYDETECTOR_DETECTOR_H
