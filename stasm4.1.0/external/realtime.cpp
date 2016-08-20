#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.hpp>
#include "stasm_lib.h"

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
        
    Mat_<unsigned char> img;
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        
        cvtColor(frame,img, CV_BGR2GRAY);
    
        int foundface;
        float landmarks[2 * stasm_NLANDMARKS]; // x,y coords (note the 2)

        if (!stasm_search_single(&foundface, landmarks,
                                 (const char*)img.data, img.cols, img.rows, "../data", "../data"))
        {
            printf("Error in stasm_search_single: %s\n", stasm_lasterr());
            exit(1);
        }

        if (!foundface)
             printf("No face found!");
        else
        {
            // draw the landmarks on the image as white dots (image is monochrome)
            stasm_force_points_into_image(landmarks, img.cols, img.rows);
            for (int i = 0; i < stasm_NLANDMARKS; i++)
                img(cvRound(landmarks[i*2+1]), cvRound(landmarks[i*2])) = 255;
        }
        
        imshow("Real Time STASM", img);
        if(waitKey(30) >= 0) break;
    }

    return 0;
}
