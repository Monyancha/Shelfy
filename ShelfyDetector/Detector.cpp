//
// Created by sajarora on 3/25/17.
//

#include "Detector.h"

Detector::Detector() {
    //![display]
    namedWindow(grayWindowName, WINDOW_NORMAL ); // Create a window for display.
    namedWindow(colorWindowName, WINDOW_NORMAL ); // Create a window for display.
    namedWindow(featureWindowName, WINDOW_NORMAL);
}


int Detector::loadImage(std::string filename) {
    Mat img = imread(filename, IMREAD_COLOR);
    if(img.empty())
    {
        return -1;
    }
    //![load]
    Mat grayImg = getGrayImage(img);
    vector<Vec3f> circles = detectCircles(grayImg);


    //extract logo potential from each circle detected
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
//        int fontFace = FONT_HERSHEY_PLAIN;
//        double fontScale = 2;
//        int thickness = 3;
        Point topLeft(c[0] - c[2] - cushion, c[1] - c[2]);
        Point bottomRight(c[0] + c[2], c[1] + c[2] + cushion);


        if (topLeft.x > 0 && topLeft.y > 0) {
          string text = "Top Left";
//        cv::putText(img, text, topLeft, fontFace, fontScale, Scalar::all(255), thickness,8);
//        text = "Bottom Right";
//        cv::putText(img, text, bottomRight, fontFace, fontScale, Scalar::all(255), thickness,8);
            Rect R(topLeft, bottomRight); //Create a rect
            Mat ROI = img(R); //Crop the region of interest using above rect
            resize(ROI, ROI, Size(400, 400));
            imshow(featureWindowName, ROI);
            int keyCode = waitKey();

            switch(keyCode){
                case 'z':
                    cout << "Save";
                    break;
                case 'x':
                    cout << "No save";
                    break;
                case 27:
                    return 1;
                default:
                    continue;
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
                 gray.rows/16, // change this value to detect circles with different distances to each other
                 100, 30, 130, 150 // change the last two parameters
            // (min_radius & max_radius) to detect larger circles
    );
    //![houghcircles]
    return circles;
}

Mat Detector::getGrayImage(Mat img) {
    //![convert_to_gray]
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    //![convert_to_gray]

    //![reduce_noise]
    medianBlur(gray, gray, 5);
    //![reduce_noise]
    return gray;
}

void Detector::showImageWithCircles(string windowName, Mat img, vector <Vec3f> circles) {

    //![draw]
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        circle( img, Point(c[0], c[1]), c[2], Scalar(0,255,255), 3, LINE_AA);
        circle( img, Point(c[0], c[1]), 2, Scalar(0,255,255), 3, LINE_AA);
    }
    //![draw]
    imshow(windowName, img );                // Show our image inside it.

}
