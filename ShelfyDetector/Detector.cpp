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


int Detector::loadImage(string filepath, string outputDir) {
    Mat img = imread(filepath, IMREAD_COLOR);
    if(img.empty())
    {
        return -1;
    }
    //![load]
    Mat grayImg;
    cannyThreshold(img, grayImg);

    vector<Vec3f> circles = detectCircles(grayImg);

    showImageWithCircles(grayWindowName, grayImg, circles);
    showImageWithCircles(colorWindowName, img, circles);

    //extract logo potential from each circle detected
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point topLeft(max(c[0] - c[2] - cushion, 0), max(c[1] - c[2] - cushion, 0));
        Point bottomRight(min(topLeft.x + 700, img.cols), min(topLeft.y + 700, img.rows));
//        Point bottomRight(min(c[0] + c[2] + cushion, img.cols), min(c[1] + c[2] + cushion, img.rows));

        Rect R(topLeft, bottomRight); //Create a rect
        Mat ROI = img(R); //Crop the region of interest using above rect
        resize(ROI, ROI, Size(400, 400));
        writeImage(outputDir + "/image_" + to_string(c[0]) + "_" + to_string(c[1]) + ".jpg", ROI);
    }

    if (waitAfter){
        waitKey();
    }

    return circles.size() > 0 ? 2 : 0;
}

vector<Vec3f> Detector::detectCircles(Mat gray) {
    //![houghcircles]
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.cols/6, // change this value to detect circles with different distances to each other
                 100, 40, 100, 300 // change the last two parameters
            // (min_radius & max_radius) to detect larger circles
    );
    //![houghcircles]
    return circles;
}

void Detector::showImageWithCircles(string windowName, Mat img, vector <Vec3f> circles) {

    Mat dest;
    img.copyTo(dest);
    //![draw]
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        circle( dest, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, LINE_AA);
        circle( dest, Point(c[0], c[1]), 2, Scalar(0,255,255), 3, LINE_AA);
    }
    //![draw]
    imshow(windowName, dest );                // Show our image inside it.

}

void Detector::writeImage(string filename, Mat img) {
//    try {
        imwrite(filename, img);
//    }
//    catch (runtime_error& ex) {
//        fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
//    }
}

void Detector::cannyThreshold(Mat& img, Mat& grayImg) {
    /// Reduce noise with a kernel 3x3
    Mat dst, detected_edges;
    int edgeThresh = 1;
    int lowThreshold = 10;
    int const max_lowThreshold = 100;
    int ratio = 3;
    int kernel_size = 3;
    /// Convert the image to grayscale
    cvtColor( img, grayImg, CV_BGR2GRAY );

    blur( grayImg, grayImg, Size(6, 6));

    /// Canny detector
    Canny( grayImg, grayImg, lowThreshold, lowThreshold*ratio, kernel_size );
}
