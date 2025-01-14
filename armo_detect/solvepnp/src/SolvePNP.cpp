#include "SolvePNP.h"

/**
 * @brief 
 * 
 * @param inputPtr 
 */

void SolvePNP::solution(Point2f inputPtr[]){
    vector<Point2f> imgPoints = vector<Point2f>{
        inputPtr[0],inputPtr[1],inputPtr[2],inputPtr[3]
    };
    solvePnP(_worldPoints,imgPoints,_camera_matrix,_distortion_coefficients,_rVec,_tVec,false,SOLVEPNP_ITERATIVE);
    x = _tVec.at<double>(0,0);
    y = _tVec.at<double>(0,1);
    z = _tVec.at<double>(0,2);
    
    yaw = atanf(x/z)*180/3.1415926;
    pitch = atanf(y/z)*180/3.1415926;

    cout<<"yaw:" << yaw<<endl;
    cout<<"pitch:"<< pitch<<endl;
    cout<<"distance:"<<0.1*sqrtf(powf(_tVec.at<double>(0,0),2)+powf(_tVec.at<double>(0,1),2)+powf(_tVec.at<double>(0,2),2))<<"cm"<<endl;
    cv::Mat rotM;
	cv::Rodrigues(_rVec, rotM);
    
    double r11 = rotM.ptr<double>(0)[0];
	double r21 = rotM.ptr<double>(1)[0];
	double r31 = rotM.ptr<double>(2)[0];
	double r32 = rotM.ptr<double>(2)[1];
	double r33 = rotM.ptr<double>(2)[2];
/*************************************此处计算出相机的旋转角**********************************************/
	//计算出相机坐标系的三轴旋转欧拉角，旋转后可以转出世界坐标系。
	//旋转顺序为z、y、x
	thetaz = atan2(r21, r11) / CV_PI * 180;
	thetay = atan2(-1 * r31, sqrt(r32*r32 + r33*r33)) / CV_PI * 180;
	thetax = atan2(r32, r33) / CV_PI * 180;
}