/*
*author:Li Yihong
*本设计要实现的内容是对人脸的表情（高兴、生气（愤怒）、悲伤）等进行识别，该功能的应用有人机交互应用、通信系统应用、娱乐游戏应用、智能医疗应用等等。计算机在我们的日常生活中运用广泛，当前人机交互的发展的方向是更加智能和友好，比如可以根据人脸的表情做出相对应的反应；通信领域的应用则主要是在传输过程中通过计算机对人脸的表情进行分类，提取出有用的信息，然后在接收端进行重新组合，节省宽带的占用和在网络环境较差时，能够进行传输；在娱乐游戏中的运用则主要是根据人脸的表情变化，做出相对应的反应，从而达到更好的娱乐效果；智能医疗的应用是在治疗的过程中，对严重患者的表情进行判断，从而达到了解病人的痛苦程度，进行相对应的治疗，以减轻患者的病痛情况。 
*/
#include "opencv2/objdetect/objdetect.hpp"
    #include "opencv2/highgui/highgui.hpp"
    #include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
    #include <stdio.h>
using namespace std;
    using namespace cv;
    /** Function Headers */
    void detectAndDisplay( Mat frame );
/** Global variables */
    String face_cascade_name=
"data/haarcascade_frontalface_alt.xml";
    String eyes_cascade_name =
"data/haarcascade_eye_tree_eyeglasses.xml";
String mouths_cascade_name = "data/haarcascade_mcs_mouth.xml";
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    CascadeClassifier mouths_cascade;
    string window_name = "Capture - Face detection";
    RNG rng(12345);
int eyedx,mouthdx;
    /** @function main */
    int main( int argc, const char** argv )
    {
        CvCapture* capture;
        Mat frame;
        cout<<"in main"<<endl;
//-- 1. Load the cascades
if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
if( !mouths_cascade.load( mouths_cascade_name ) ){ printf
("—(!)Error loading\n"); return -1; };
        //-- 2. Read the video stream
        capture = cvCaptureFromCAM( 0);////-1
        if( capture )
        {
            cout<<"capture is ok."<<endl;
            while( true )
            {
                frame = cvQueryFrame( capture );
                //-- 3. Apply the classifier to the frame
                if( !frame.empty() )
                { 
cout<<"frame is ok."<<endl; 
detectAndDisplay( frame );
                }
                else
                {   
printf(" --(!) No captured frame -- Break!"); break;
}
                int c = waitKey(10);
                if( (char)c == 'c' )
                {   
break;
}
            }
        }
        return 0;
    }
/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
        std::vector<Rect> faces;
        Mat frame_gray,frame2;
        normalize(frame,frame2 , 0,255, NORM_MINMAX, CV_8UC3);
        cvtColor( frame2, frame_gray, CV_BGR2GRAY );
        equalizeHist( frame_gray, frame_gray );
//normalize(frame_gray,Image, 0,255, NORM_MINMAX,
//CV_8UC3);
        //-- Detect faces
face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
        for( size_t i = 0; i < faces.size(); i++ )
        {
            Point center( faces[i].x + faces[i].width*0.5,
faces[i].y + faces[i].height*0.5 );
ellipse( frame_gray, center, Size( faces[i].width*0.6, faces[i].height*0.6), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
            Mat faceROI = frame_gray( faces[i] );
            std::vector<Rect> eyes;
            std::vector<Rect> mouths;
            eyedx=-1;
            //-- In each face, detect eyes
eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2,
0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
mouths_cascade.detectMultiScale( faceROI, mouths , 1.1,
2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
            for(size_t  j = 0; j < eyes.size(); j++ )
            {
Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5,faces[i].y + eyes[j].y + eyes[j].height*0.5 );
int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
circle( frame_gray, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
//cout<<eyes[j].width<<" "<<eyes[j].height<<endl;
if(eyes[j].height>=80)
eyedx=1;
else
                    eyedx=0;
//if(eyes[j].height<40&&eyes[j].width>60)eyedx=-1;
//else if(radius>=40&&radius<=45)eyedx=0;
//else eyedx=1;
            }
            for( size_t z = 0; z < mouths.size(); z++ )
            {
Point center(faces[i].x+mouths[z].x + mouths[z].width*0.5,faces[i].y + mouths[z].y + mouths[z].height*0.5 );
if(mouths[z].y + mouths[z].height*0.5
>faces[i].height/2)
                {
                    ellipse( frame_gray,center, 
Size(mouths[z].width*0.5,mouths[z].height*0.5)
, 0, 0, 360, Scalar( 255, 255, 255 ), 4, 8, 0 );
if(mouths[z].width>110) mouthdx=1;
else mouthdx=0;
//cout<<mouths[z].width<<" //"<<mouths[z].height<< endl;
//else //if(mouths[z].width<=80&&mouths[z].height>80) //mouthdx=-1;
//else mouthdx=0;
                } 
}
            if(mouthdx==1) cout<<"happy"<<endl;
else if(eyedx==1&&mouthdx==0) cout<<"angry"<<endl;
else cout<<"sad"<<endl;
        }
        //-- Show what you got
        imshow( window_name, frame_gray );
    }
