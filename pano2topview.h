#ifndef PANO2TOPVIEW_H
#define PANO2TOPVIEW_H

#ifndef PI
#define PI 3.14159265358979323846
#endif

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <eigen3/Eigen/Dense>

class Pano2TopView
{
public:
    Pano2TopView();
    Pano2TopView(double resolution, double height);
    ~Pano2TopView();

    bool pano_to_topview(const cv::Mat& matpano, cv::Mat& mattopview);

    bool topview_to_pano(const cv::Mat& mattopview, cv::Mat& matpano);


private:

    double m_dresolution;
    double m_dwidth;
    double m_dlength;

    double m_iRow;
    double m_icol;

    double m_dheight;

};


#endif // PANO2TOPVIEW_H
