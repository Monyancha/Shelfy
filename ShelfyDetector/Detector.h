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

    int loadImage(string filepath, string outputDir);

    std::vector<Vec3f> detectCircles(Mat image);

    void showImageWithCircles(string mat, Mat vector, std::vector <Vec3f> vector1);

private:
    string grayWindowName = "Gray Window";
    string colorWindowName = "Color Window";
    string featureWindowName = "Feature Window";
    bool createDatasetMode = true;

    int cushion = 150;

    void writeImage(string string, Mat img);

    void cannyThreshold(Mat &img, Mat &grayImg);

    bool waitAfter = true;

};


#endif //SHELFYDETECTOR_DETECTOR_H
