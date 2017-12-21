/**
*author:Li Yihong
*通过kinent识别人体动作，并与Arduino的单片机进行通信，从而控制机器人做出各种各样的动作。
*1、这里需要引入Kinect的SDK的
*2、上位机采用C ++语言开发，通过TCP与Arduino的单片机通信，从而控制机器人
*/
#include <Kinect.h>
#pragma comment ( lib, "kinect20.lib" )
#include <iostream>
Joint joints[JointType_Count];
using namespace std;
class walk
{

public:
    int state;
    walk()
    {
        state = 0;
    }
    void update()
    {
        if ((abs(joints[JointType_KneeLeft].Position.Z - joints[JointType_HipLeft].Position.Z) > 0.15 ||
            abs(joints[JointType_KneeRight].Position.Z - joints[JointType_HipRight].Position.Z) > 0.15)

            )
        {
            cout << "走路" << endl;
            state = 1;
        }
        else
        {
            state = 0;
        }
    }
};
class turnleft
{
public:
    turnleft()
    {

    }
    void update(int x)
    {
        if (x == 1&&joints[JointType_HandLeft].Position.Y>joints[JointType_Head].Position.Y
            &&joints[JointType_HandRight].Position.Y<joints[JointType_Head].Position.Y)
        {
            cout << "转左" << endl;
        }
    }

};
class turnright
{
public:
    turnright()
    {

    }
    void update(int x)
    {
        if (x == 1 && joints[JointType_HandRight].Position.Y>joints[JointType_Head].Position.Y
            &&joints[JointType_HandLeft].Position.Y<joints[JointType_Head].Position.Y)
        {
            cout << "转右" << endl;
        }
    }

};
class yougouquan
{
public:
    yougouquan()
    {
    }
    void update(int a,int k)
    {
        if (
            //joints[JointType_HandRight].Position.Y>joints[JointType_ElbowRight].Position.Y
            joints[JointType_HandRight].Position.Y>joints[JointType_SpineMid].Position.Y
            &&joints[JointType_HandRight].Position.X<joints[JointType_ShoulderLeft].Position.X
            &&a == 1&&k!=1
            //&&joints[JointType_HandLeft].Position.Y>joints[JointType_ElbowLeft].Position.Y
            //&&joints[JointType_HandLeft].Position.Y>joints[JointType_SpineMid].Position.Y
            )
        {
            cout << "右勾拳" << endl;
            Sleep(1000);
        }
    }
};
class yougouquan2
{
public:
    yougouquan2()
    {
    }
    void update(int a,int k)
    {
        if (
            //joints[JointType_HandRight].Position.Y>joints[JointType_ElbowRight].Position.Y
        //  joints[JointType_HandRight].Position.Y>joints[JointType_SpineMid].Position.Y
            joints[JointType_HandLeft].Position.X > joints[JointType_ShoulderRight].Position.X
            &&a == 1 && k != 1
            //&&joints[JointType_HandLeft].Position.Y > joints[JointType_ElbowLeft].Position.Y
            &&joints[JointType_HandLeft].Position.Y>joints[JointType_SpineMid].Position.Y)
        {
            cout << "左勾拳" << endl;
            Sleep(1000);
        }

    }

};
class shanggouquan2
{
    int state;
    int timestamp;
    int lasttimes;
public:
    shanggouquan2()
    {
        state = 0;
    }
    void update(int a,int z,int k)
    {
        if (joints[JointType_HandRight].Position.Y<joints[JointType_Head].Position.Y
            &&joints[JointType_HandLeft].Position.Y>joints[JointType_Head].Position.Y
            &&joints[JointType_ShoulderLeft].Position.Z>joints[JointType_ElbowLeft].Position.Z+0.1
            &&z!=1&&k!=1 && a == 1
            )
        {
            cout << "上钩拳" << endl;
            Sleep(1000);
        }
    }
};
class shanggouquan
{
    int state;
    int timestamp;
    int lasttime;
public:
    shanggouquan()
    {
        state = 0;
        timestamp = 0;
        lasttime = 1;
    }
    void update(int a,int z,int k)
    {
        if (joints[JointType_HandRight].Position.Y > joints[JointType_Head].Position.Y
            && joints[JointType_HandLeft].Position.Y < joints[JointType_Head].Position.Y
            && joints[JointType_ShoulderRight].Position.Z>joints[JointType_ElbowRight].Position.Z + 0.1
            &&k!=1 && z != 1 && a == 1
            )
        {
            cout << "上钩拳" << endl;
            Sleep(1000);
        }
    }
};
class juezhao
{
public:
    int timestamps;
    int lasttimes;
    int state;
public:
    juezhao()
    {
        timestamps = 0;
        state = 0;
        lasttimes = 50;
    }
    void update(int a,int k)
    {
        if (a!=1)
        {
            state = 0;
            timestamps = 0;
        }
        if (
            joints[JointType_ElbowLeft].Position.Y>joints[JointType_HipLeft].Position.Y
            &&joints[JointType_ElbowRight].Position.Y>joints[JointType_HipRight].Position.Y
            &&abs(joints[JointType_HandRight].Position.Y - joints[JointType_HandLeft].Position.Y)<0.1
            &&abs(joints[JointType_HandRight].Position.X - joints[JointType_HandLeft].Position.X)<0.1
            &&a==1&&k!=1
            )
        {
            cout << "一" << endl;
            state = 1;
        }
        if (state == 1)
        {
            timestamps++;
            if (timestamps<lasttimes)
            {
                if ((joints[JointType_HandRight].Position.Y>joints[JointType_Head].Position.Y
                    ||joints[JointType_HandLeft].Position.Y>joints[JointType_Head].Position.Y)
                    &&a==1&&k!=1)
                {
                    cout << "绝招" << endl;
                    state = 0;
                    timestamps = 0;
                    Sleep(1000);
                }
            }
            else
            {
                state = 0;
                timestamps = 0;
            }
        }
    }

};
/*class archery
{
private:
    int lasttime;
    int timestamp;
    int state;
public:
    archery()
    {
        lasttime = 50;
        state = 0;
        timestamp = 0;
    }
    void update(Joint a[])
    {
        if(a[7].Position.X*100>=a[11].Position.X*100-5&&a[7].Position.X*100<=a[11].Position.X*100+5
            && a[7].Position.Y * 100 >= a[11].Position.Y*100 - 5 && a[7].Position.Y * 100 <= a[11].Position.Y*100 + 5
            && a[7].Position.Z * 100 >= a[11].Position.Z * 100 - 5 && a[7].Position.Z * 100 <= a[11].Position.Z * 100 + 5
            )
        {
            state = 1;
            cout << "拍手" << endl;
        }
        if (state==1)
        {
            timestamp++;
            if (timestamp < lasttime)
            {
                if (joints[11].Position.Y*100>joints[0].Position.Y*100
                    && joints[11].Position.Y * 100 <= joints[9].Position.Y * 100 + 20
                    && joints[11].Position.Y * 100 >= joints[9].Position.Y * 100 - 20
                    && joints[9].Position.Y * 100 <= joints[8].Position.Y * 100 + 20
                    && joints[9].Position.Y * 100 >= joints[8].Position.Y * 100 - 20
                    &&joints[5].Position.Y * 100>joints[0].Position.Y * 100
                    &&joints[7].Position.Y>joints[5].Position.Y
                    && joints[4].Position.Y * 100 <= joints[5].Position.Y * 100 + 20
                    && joints[4].Position.Y * 100 >= joints[5].Position.Y * 100 - 20
                    && joints[5].Position.Y * 100 <= joints[7].Position.Y * 100 + 20
                    && joints[5].Position.Y * 100 >= joints[7].Position.Y * 100 - 20
                    &&joints[11].Position.Z<joints[9].Position.Z&&joints[9].Position.Z<joints[8].Position.Z
                    &&joints[8].Position.Z<joints[4].Position.Z
)   
                {
                    cout << "射箭" << endl;
                    Sleep(1000); 
                    state = 0;
                }
            }
            else
            {
                state = 0;
                timestamp = 0;
            }
        }
    }
};*/
/*class pneumatic
{
    int state;
    int timestamps;
    int lasttimes;
    pneumatic()
    {
        state = 0;
        timestamps = 0;
        lasttimes = 50;
    }
    void update()
    {
        if (joints[JointType_HandRight].Position.Y < joints[JointType_SpineMid].Position.Y
            &&joints[JointType_HandLeft].Position.Y < joints[JointType_SpineBase].Position.Y
            &&abs(joints[JointType_HandLeft].Position.X - joints[JointType_HandRight].Position.X) < 0.08
            &&abs(joints[JointType_HandRight].Position.Y - joints[JointType_HandLeft].Position.Y) < 0.08
            )
        {
            state = 1;
            if (state == 1)
            {
                timestamps++;
                if (timestamps > lasttimes)
                {
                    state = 2;
                }
            }
        }
        if (state == 2)
        {
            if (joints[JointType_HandLeft].Position.Y>joints[JointType_SpineMid].Position.Y
                &&joints[JointType_HandRight].Position.Y>joints[JointType_SpineMid].Position.Y
                &&abs(joints[JointType_HandLeft].Position.X - joints[JointType_HandRight].Position.X) < 0.08
                &&abs(joints[JointType_HandRight].Position.Y - joints[JointType_HandLeft].Position.Y) < 0.08
                )
            {
                state = 3;
                Sleep(200);
                cout << "龟派气功" << endl;
                state = 0;
                timestamps = 0;
                Sleep(2000);
            }
        }
        state = 0;
    }

};*/
int main()
{
    int temp;
    int hand=0;
    yougouquan y;
    shanggouquan s;
    juezhao z;
    yougouquan2 y2;
    shanggouquan2 s2;
    turnleft l;
    turnright r;
    //archery a;
    IKinectSensor* sensor;  
    walk w;
    HRESULT hr = GetDefaultKinectSensor(&sensor);  
    if (FAILED(hr))
    {
        cout << "获取Kinect失败" << endl;
        return 0;
    }
    BOOLEAN bIsOpen = 0;
    sensor->get_IsOpen(&bIsOpen); 
    if (!bIsOpen) 
    {
        hr = sensor->Open();
        if (FAILED(hr))
        {
            cout << "开启Kinect失败" << endl;
            return -1;
        }
        cout << "正在开启Kinect，请等待" << endl;
        Sleep(3000);
    }
    bIsOpen = 0;
    sensor->get_IsOpen(&bIsOpen); 
    if (bIsOpen == true)
    {
        cout << "开启成功" << endl;
    }
    BOOLEAN bAvaliable = 0;
    sensor->get_IsAvailable(&bAvaliable); 
    DWORD dwCapability = 0;
    sensor->get_KinectCapabilities(&dwCapability);
    cout << "容量为：" << endl;
    TCHAR bbuid[256] = { 0 };
    sensor->get_UniqueKinectId(256, bbuid); 
    cout << "玩家ID为" << bbuid << endl;
    IBodyFrameSource* BodyFrameSource = nullptr;
    sensor->get_BodyFrameSource(&BodyFrameSource); 
    INT32 nBodyNum = 0;
    BodyFrameSource->get_BodyCount(&nBodyNum);
    cout << "BODY个数" << nBodyNum << endl;
    IBodyFrameReader* BodyFrameReader = nullptr;
    BodyFrameSource->OpenReader(&BodyFrameReader); 

    while (true)
    {
        IBodyFrame* BodyFrame = nullptr;
        BodyFrameReader->AcquireLatestFrame(&BodyFrame); 
        if (!BodyFrame)
        {
            Sleep(100);
            continue;
        }
        IBody* iBody[BODY_COUNT] = { 0 };
        BodyFrame->GetAndRefreshBodyData(BODY_COUNT, iBody); // 更新所有人身体数据  
        for (int i = 0; i < BODY_COUNT; ++i)
        {
            IBody* pBody = iBody[i]; // 轮询每个人的信息  
            if (pBody)
            {
                BOOLEAN bTracked = false;
                hr = pBody->get_IsTracked(&bTracked); // 检测是否被跟踪，即是否有这个人  
                if (bTracked)
                {
                    HandState leftHandState = HandState_Unknown;
                    HandState rightHandState = HandState_Unknown;
                    pBody->get_HandLeftState(&leftHandState); // 获取左手的状态  
                    pBody->get_HandRightState(&rightHandState); // 获取右手的状态  
                    if (leftHandState == HandState_Open||rightHandState == HandState_Open)
                    {
                        hand = 0;
                    }
                    else
                    {
                        hand = 1;
                    }
                    hr = pBody->GetJoints(_countof(joints), joints); // 获取身体的骨骼信息，25点
                    z.update(hand,w.state);
                    s.update(hand,z.state,w.state);
                    y.update(hand,w.state);
                    s2.update(hand,z.state,w.state);
                    y2.update(hand,w.state);
                    w.update();
                    l.update(w.state);
                    r.update(w.state);
                    if (w.state!=1&&abs(joints[11].Position.X - joints[JointType_ElbowRight].Position.X) <= 0.1&&abs(joints[JointType_ShoulderRight].Position.X - joints[JointType_ElbowRight].Position.X) <= 0.1&&abs(joints[JointType_ShoulderRight].Position.Y - joints[JointType_ElbowRight].Position.Y) <= 0.1&&abs(joints[JointType_HandRight].Position.Y - joints[JointType_ElbowRight].Position.Y) <= 0.1)
                    {
                        cout << "右直拳" << endl;
                        Sleep(1000);
                    }
                    if (w.state!=1&&abs(joints[JointType_HandLeft].Position.X - joints[JointType_ElbowLeft].Position.X) <= 0.1&&abs(joints[JointType_ElbowLeft].Position.X - joints[JointType_ShoulderLeft].Position.X) <= 0.1&&abs(joints[JointType_ShoulderLeft].Position.Y - joints[JointType_ElbowLeft].Position.Y) <= 0.1&&abs(joints[JointType_ElbowLeft].Position.Y - joints[JointType_HandLeft].Position.Y) <= 0.1)
                    {
                        cout << "左直拳" << endl;
                        Sleep(1000);
                    }
                //  cout << "左手X" << joints[JointType_HandLeft].Position.X << endl;
                //  cout << "右肩X" << joints[JointType_HandRight].Position.X << endl;
                    //Sleep(2000);
                    /*cout << hand << endl;
                    cout << "脊椎Y" << joints[JointType_SpineMid].Position.Y << endl;
                    cout << "左手Y" << joints[JointType_HandLeft].Position.Y << endl;
                    cout << "右手Y" << joints[JointType_HandRight].Position.Y << endl;
                    cout << "头Y" << joints[JointType_Head].Position.Y << endl;
                    /*cout << hand << endl;
                    cout << "左手X" << joints[JointType_HandLeft].Position.X << endl;
                    cout << "左肘X" << joints[JointType_ElbowLeft].Position.X << endl;
                    cout << "左手Y" << joints[JointType_HandRight].Position.Y << endl;
                    cout << "左肘Y" << joints[JointType_ElbowLeft].Position.Y << endl;
                    cout << "右手X" << joints[JointType_HandRight].Position.X << endl;
                    cout << "右肘X" << joints[JointType_ElbowRight].Position.X << endl;
                    cout << "右手Y" << joints[JointType_HandRight].Position.Y << endl;
                    cout << "右肘Y" << joints[JointType_ElbowRight].Position.Y << endl;*/
                    //cout << "右肩X" << joints[JointType_ShoulderRight].Position.X << endl;
                    //cout << "左手Y" << joints[JointType_HandLeft].Position.Y << endl;
                    //cout << "头Y" << joints[JointType_Head].Position.Y << endl;
                    //Sleep(8000);
                    /*if (rightHandState == HandState_Closed || leftHandState == HandState_Closed)
                    {
                    cout << "拳头" << endl;
                    Sleep(1000);
                    }*/

                }
            }
        }
        for (int i = 0; i < BODY_COUNT; ++i)
        {
            iBody[i]->Release();
        }
        BodyFrame->Release();
    }
    sensor->Close();
}
