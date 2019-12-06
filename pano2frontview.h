#ifndef PANO2FRONTVIEW_H
#define PANO2FRONTVIEW_H

#ifndef PI
#define PI 3.14159265358979323846
#endif

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <eigen3/Eigen/Dense>

class Pano2FrontView
{
public:
    Pano2FrontView();
    Pano2FrontView(double res);
    ~Pano2FrontView();

    bool pano_to_frontview(const cv::Mat& matpano, cv::Mat& matfrontview);

    bool pano_to_leftview(const cv::Mat& matpano, cv::Mat& matleftview);

    bool pano_to_rightview(const cv::Mat& matpano, cv::Mat& matrightview);

    bool pano_to_threeview(const cv::Mat& matpano, cv::Mat& matthreeview);

private:

    double m_alpha;
    double m_beta;
    double m_z;
    double m_res;

};


#endif // PANO2FRONTVIEW_H
