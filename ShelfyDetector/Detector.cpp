//
// Created by sajarora on 3/25/17.
//

#include "Detector.h"

Detector::Detector() {
    //![display]
    namedWindow(grayWindowName, WINDOW_NORMAL ); // Create a window for display.
    namedWindow(colorWindowName, WINDOW_NORMAL ); // Create a window for display.
//    namedWindow(featureWindowName, WINDOW_NORMAL);
}


int Detector::loadImage(int count, std::string filename) {
    Mat img = imread(filename, IMREAD_COLOR);
    if(img.empty())
    {
        return -1;
    }
    //![load]
//    Mat grayImg = getGrayImage(img);
    Mat grayImg;
    cannyThreshold(img, grayImg);

    vector<Vec3f> circles = detectCircles(grayImg);

    //extract logo potential from each circle detected
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point topLeft(c[0] - c[2] - cushion, c[1] - c[2]);
        Point bottomRight(c[0] + c[2], c[1] + c[2] + cushion);


        if (topLeft.x > 0 && topLeft.y > 0 && bottomRight.x < img.size().width && bottomRight.y < img.size().height) {
            Rect R(topLeft, bottomRight); //Create a rect
            Mat ROI = img(R); //Crop the region of interest using above rect
            resize(ROI, ROI, Size(400, 400));
            imshow(featureWindowName, ROI);

            if (createDatasetMode){
                if (supervisedDatasetCreation(count, int(i), ROI) == 1){ //quit the app
                    return 1;
                }
            } else {

            }

        }
    }

    showImageWithCircles(grayWindowName, grayImg, circles);
    showImageWithCircles(colorWindowName, img, circles);

    return 0;
}

vector<Vec3f> Detector::detectCircles(Mat gray) {
    //![houghcircles]
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows/8, // change this value to detect circles with different distances to each other
                 100, 60, 120, 300 // change the last two parameters
            // (min_radius & max_radius) to detect larger circles
    );
    //![houghcircles]
    return circles;
}


Mat Detector::getGrayImage(Mat img) {
    //![convert_to_gray]
    Mat gray;
    /// Convert the image to grayscale
    cvtColor( img, img, CV_BGR2GRAY );

    blur( img, gray, Size(4, 4) );

    //![reduce_noise]
    return gray;
}

void Detector::showImageWithCircles(string windowName, Mat img, vector <Vec3f> circles) {

    //![draw]
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        circle( img, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, LINE_AA);
        circle( img, Point(c[0], c[1]), 2, Scalar(0,255,255), 3, LINE_AA);
    }
    //![draw]
    imshow(windowName, img );                // Show our image inside it.

}

void Detector::writeImage(string filename, Mat img) {
//    try {
        imwrite(filename, img);
//    }
//    catch (runtime_error& ex) {
//        fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
//    }
}

int Detector::supervisedDatasetCreation(int frameCount, int featureCount, Mat img) {
    int keyCode = waitKey();
    string directory = "neg";
    switch(keyCode){
        case 'a':
            directory = "stella";
            break;
        case 's':
            directory = "shock";
            break;
        case 27:
            return 1;
        default:
            break;
    }
    writeImage("../data/" + directory + "/img_" + to_string(frameCount) + "_" + to_string(featureCount) + ".jpg", img);
    return 0;
}

void Detector::cannyThreshold(Mat& img, Mat& grayImg) {
    /// Reduce noise with a kernel 3x3
    Mat dst, detected_edges;
    int edgeThresh = 1;
    int lowThreshold = 9;
    int const max_lowThreshold = 100;
    int ratio = 3;
    int kernel_size = 3;
    /// Convert the image to grayscale
    cvtColor( img, grayImg, CV_BGR2GRAY );

    blur( grayImg, grayImg, Size(4, 4) );

    /// Canny detector
    Canny( grayImg, grayImg, lowThreshold, lowThreshold*ratio, kernel_size );
}
