/**
*author:Li Yihong
*为了模拟小车通过接收指令，自主摆阵列的情形，本算法通过摄像头获取各个小车的位置，通过OpenCV的图像处理分析出各个小车的距离，并设置一个安全距离，当小车之间的距离小于安全距离时，小车之间就拉开距离，否则，各个小车仍按照阵列各自的位置目标前进。
*下面是算法的具体实现。
*/
#include <iostream>
#include<cstdlib>
#include<ctime>
#include "opencv2/objdetect/objdetect.hpp"
#include<fstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cv.h>    
#include <highgui.h>    
#include <stdio.h>
using namespace cv;
using namespace std;
const int SafeLong = 40;
const int SafeDistance = 20;
const int GoalDistance = 5;
const int TotalNum = 2;
class point
{
public:
    double x, y;
};
point dstlocation[16];
point dirlong[SafeLong+1];
class Car
{
public:

    point location;
    point dstlocation;
    int num;
    int dir;
    int state;
    //int bumpdir[5];
    Car()
    {
        state = 1;
        dir = 0;
        location.x = 0;
        location.y = 0;
        dstlocation.x = 0;
        dstlocation.y = 0;
    }
    double dist(const point &a)
    {
        return sqrt(pow(location.x - a.x, 2) + pow(location.y - a.y, 2));
    }
    void update()
    {}
    void check()
    {}
    void up()
    {}
    void down()
    {}
    void left()
    {}
    void right()
    {}
};

//const int CarWidth = 10;
//const int CarHeight = 10;
//int CarBumpNum = 0;
//int CarBump[16];
Car car[TotalNum];
void start()
{
    for (int i = 0; i < TotalNum; i++)
    {
        if (abs(car[i].location.x-car[i].dstlocation.x)<abs(car[i].location.y-car[i].dstlocation.y)
            && abs(car[i].location.x - car[i].dstlocation.x)>GoalDistance
            )
        {
            if (car[i].location.x < car[i].dstlocation.x)
            {
                car[i].dir = 1;
            }
            else
            {
                car[i].dir = 2;
            }
        }
        else
        {
            if (car[i].location.y < car[i].dstlocation.y)
            {
                car[i].dir = 3;
            }
            else
            {
                car[i].dir = 4;
            }
        }
    }
}
void CheckX(Car&a)
{

    if (a.location.x < a.dstlocation.x)
    {
        a.dir = 1;
    }
    else
    {
        a.dir = 2;
    }
}
void CheckY(Car&a)
{

    if (a.location.y < a.dstlocation.y)
    {
        a.dir = 3;
    }
    else
    {
        a.dir = 4;
    }

}
void move()
{
    for (int i = 0; i < TotalNum; i++)
    {
        cout << car[1].dir << endl;
        if (car[i].dist(car[i].dstlocation) <= sqrt(pow(GoalDistance,2)+pow(GoalDistance,2)))
        {
            car[i].dir = 5;
            car[i].state = 2;
            continue;
        }
        if (car[i].state!=0)
        {
            if (abs(car[i].location.x-car[i].dstlocation.x)<GoalDistance&&car[i].dir==0)
            {
                CheckY(car[i]);
            }
            if (abs(car[i].location.y - car[i].dstlocation.y)<GoalDistance)
            {
                CheckX(car[i]);
            }
            switch (car[i].dir)
            {
            case 1:car[i].location.x++; break;
            case 2:car[i].location.x--; break;
            case 3:car[i].location.y++; break;
            case 4:car[i].location.y--; break;
            default:
                break;
            }
        }
        car[i].state = 1;
        for (int j = 0; j < i; j++)
        {
            if (car[i].dist(car[j].location) < SafeDistance)
            {

                if (car[i].dir==car[j].dir)
                {
                    continue;
                }
                switch (car[i].dir)
                {
                case 1:
                    switch (car[j].dir)
                    {
                    case 2:car[i].state = 0;
                        CheckY(car[i]); break;
                    case 3:
                        if (car[i].location.x<car[j].location.x&&car[i].location.y>car[j].location.y)
                        {
                            car[i].dir = 2;
                            car[i].state = 0;
                        }break;
                    case 4:
                        if (car[i].location.x < car[j].location.x&&car[i].location.y < car[j].location.y)
                        {
                            car[i].dir = 2;
                            car[i].state = 0;
                        }break;
                    case 5:
                        if (car[i].location.x < car[j].location.x)
                        {
                            CheckY(car[i]);
                            car[i].state = 0;
                        }
                        break;
                    }break;
                case 2:
                    switch (car[j].dir)
                    {
                    case 1:car[i].state = 0;
                        CheckY(car[i]); break;
                    case 3:
                        if (car[i].location.x > car[j].location.x&&car[i].location.y > car[j].location.y)
                        {
                            car[i].state = 0;
                            car[i].dir = 1;
                        }break;
                    case 4:
                        if (car[i].location.x > car[j].location.x&&car[i].location.y < car[j].location.y)
                        {
                            car[i].state = 0;
                            car[i].dir = 1;
                        }break;
                    case 5:
                        if (car[i].location.x > car[j].location.x)
                        {
                            CheckY(car[i]);
                            cout << car[i].dir << endl;
                            cout << car[j].dir << endl;
                            car[i].state = 0;
                        }
                        break;
                    }break;
                case 3:
                    switch (car[j].dir)
                    {
                    case 1:
                        if (car[i].location.x > car[j].location.x&&car[i].location.y<car[j].location.y)
                        {
                            car[i].state = 0;
                            car[i].dir = 4;
                        }
                        break;
                    case 2:
                        if (car[i].location.x < car[j].location.x&&car[i].location.y<car[j].location.y)
                        {
                            car[i].state = 0;
                            car[i].dir = 4;
                        }
                        break;
                    case 4:
                        car[i].state = 0;
                        CheckX(car[i]);
                        break;
                    case 5:
                        if (car[i].location.y < car[j].location.y)
                        {
                            CheckX(car[i]);
                            car[i].state = 0;
                        }
                        break;
                    }break;
                case 4:
                    switch (car[j].dir)
                    {
                    case 1:
                        if (car[i].location.x > car[j].location.x&&car[i].location.y>car[j].location.y)
                        {
                            car[i].state = 0;
                            car[i].dir = 3;
                        }
                        break;
                    case 2:
                        if (car[i].location.x < car[j].location.x&&car[i].location.y>car[j].location.y)
                        {
                            car[i].state = 0;
                            car[i].dir = 3;
                        }
                        break;
                    case 3:
                        car[i].state = 0;
                        CheckX(car[i]);
                        break;
                    case 5:
                        if (car[i].location.y > car[j].location.y)
                        {
                            CheckX(car[i]);
                            car[i].state = 0;
                        }
                        break;
                    }break;
                }
            }

            if (car[i].state==0)
            {
                break;
            }
        }
        if (car[i].state==0)
        {
            continue;
        }
        for (int j = i+1; j < TotalNum; j++)
        {

            if (car[i].dist(car[j].location) < SafeDistance)
            {
                if (car[i].dir == car[j].dir)
                {
                    continue;
                }
                switch (car[i].dir)
                {
                case 1:
                    switch (car[j].dir)
                    {
                    case 2:car[i].state = 0;
                        CheckY(car[i]); break;
                    case 3:
                        if (car[i].location.x<car[j].location.x&&car[i].location.y>car[j].location.y)
                        {
                            car[i].dir = 2;
                            car[i].state = 0;
                        }break;
                    case 4:
                        if (car[i].location.x < car[j].location.x&&car[i].location.y < car[j].location.y)
                        {
                            car[i].dir = 2;
                            car[i].state = 0;
                        }break;
                    case 5:
                        if (car[i].location.x < car[j].location.x)
                        {
                            CheckY(car[i]);
                        }
                        break;
                    }break;
                case 2:
                    switch (car[j].dir)
                    {
                    case 1:car[i].state = 0;
                        CheckY(car[i]); break;
                    case 3:
                        if (car[i].location.x > car[j].location.x&&car[i].location.y > car[j].location.y)
                        {
                            car[i].state = 0;
                            car[i].dir = 1;
                        }break;
                    case 4:
                        if (car[i].location.x > car[j].location.x&&car[i].location.y < car[j].location.y)
                        {
                            car[i].state = 0;
                            car[i].dir = 1;
                        }break;
                    case 5:
                        if (car[i].location.x > car[j].location.x)
                        {
                            CheckY(car[i]);
                        }
                        break;
                    }break;
                case 3:
                    switch (car[j].dir)
                    {
                    case 1:
                        if (car[i].location.x > car[j].location.x&&car[i].location.y<car[j].location.y)
                        {
                            car[i].state = 0;
                            car[i].dir = 4;
                        }
                        break;
                    case 2:
                        if (car[i].location.x < car[j].location.x&&car[i].location.y<car[j].location.y)
                        {
                            car[i].state = 0;
                            car[i].dir = 4;
                        }
                        break;
                    case 4:
                        car[i].state = 0;
                        CheckX(car[i]);
                        break;
                    case 5:
                        if (car[i].location.y < car[j].location.y)
                        {
                            CheckX(car[i]);
                        }
                        break;
                    }break;
                case 4:
                    switch (car[j].dir)
                    {
                    case 1:
                        if (car[i].location.x > car[j].location.x&&car[i].location.y>car[j].location.y)
                        {
                            car[i].state = 0;
                            car[i].dir = 3;
                        }
                        break;
                    case 2:
                        if (car[i].location.x < car[j].location.x&&car[i].location.y>car[j].location.y)
                        {
                            car[i].state = 0;
                            car[i].dir = 3;
                        }
                        break;
                    case 3:
                        car[i].state = 0;
                        CheckX(car[i]);
                        break;
                    case 5:
                        if (car[i].location.y > car[j].location.y)
                        {
                            CheckX(car[i]);
                        }
                        break;
                    }break;
                }
            }
            if (car[i].state == 0)
            {
                break;
            }
        }
        if (car[i].state == 0)
        {
            continue;
        }
        if (car[i].location.x>car[i].dstlocation.x+20&&car[i].dir==1)
        {
            if (abs(car[i].location.y-car[i].dstlocation.y)<GoalDistance)
            {
                car[i].dir = 2;
            }
            else
            {
                CheckY(car[i]);
            }
        }
        if (car[i].location.x<car[i].dstlocation.x-20&&car[i].dir == 2)
        {
            if (abs(car[i].location.y - car[i].dstlocation.y)<GoalDistance)
            {
                car[i].dir = 2;
            }
            else
            {
                CheckY(car[i]);
            }
        }
        if (car[i].location.y>car[i].dstlocation.y + 20 && car[i].dir == 3)
        {
            if (abs(car[i].location.x - car[i].dstlocation.x)<GoalDistance)
            {
                car[i].dir = 4;
            }
            else
            {
                CheckX(car[i]);
            }
        }
        if (car[i].location.y<car[i].dstlocation.y - 20 && car[i].dir == 4)
        {
            if (abs(car[i].location.x - car[i].dstlocation.x)<GoalDistance)
            {
                car[i].dir = 3;
            }
            else
            {
                CheckX(car[i]);
            }
        }
    }
}
int main()
{
    Mat a = imread("C:\\Users\\ASUS\\Desktop\\box.jpg");
    srand((unsigned)time(0));
    for (int i = 0; i < TotalNum; i++)
    {
        car[i].location.x =50+50*i;
        car[i].location.y = 50;
        car[i].dstlocation.x = 50-25*i;
        car[i].dstlocation.y = 50;
    }
    start();
    while (true)
    {
        a = imread("C:\\Users\\ASUS\\Desktop\\box.jpg");
        move();
        for (int i = 0; i < TotalNum; i++)
        {
            CvPoint firstpoint;
            CvPoint secondpoint;
            firstpoint.x = car[i].location.x-5;
            firstpoint.y = car[i].location.y-5;
            secondpoint.x = car[i].location.x + 5;
            secondpoint.y = car[i].location.y + 5;
            rectangle(a, firstpoint, secondpoint, Scalar(166, 155, 155));
        }
        for (int i = 0; i < TotalNum; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (car[i].dist(car[j].location) < SafeDistance - 10)
                {
                    cout << "错误" << endl;
                }
            }
            for (int j = i+1; j < TotalNum; j++)
            {
                if (car[i].dist(car[j].location) < SafeDistance - 10)
                {
                    cout << "错误" << endl;
                }
            }
        }
        imshow("youxi", a);
        waitKey(10);
    }

}
