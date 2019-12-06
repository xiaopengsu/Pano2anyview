#include "pano2frontview.h"

Pano2FrontView::Pano2FrontView()
{
    m_alpha = 90;
    m_beta = 90;
    m_z = 1;
    m_res = 0.03;
}

Pano2FrontView::Pano2FrontView(double res):m_res(res), m_beta(90), m_alpha(90), m_z(1)
{

}

Pano2FrontView::~Pano2FrontView()
{

}


bool Pano2FrontView::pano_to_frontview(const cv::Mat& matpano, cv::Mat& matfrontview)
{
    int rows = matpano.rows;
    int cols = matpano.cols;
    double dtheta = PI * 2 / cols;
    double dphi = PI / rows;

    int cols_f = static_cast<int>(round(m_alpha / m_res));
    int rows_f = static_cast<int>(round(m_beta / m_res));
    (cols_f % 2 == 0) ? cols_f : (cols_f++);
    (rows_f % 2 == 0) ? rows_f : (rows_f++);
    double y = (0.5 * cols_f) / tan(m_alpha * 0.5 / 180.0 * PI);

    cv::Mat matfront(rows_f, cols_f, CV_8UC3, cv::Scalar(0, 0, 0));
    for(int u=0;u<cols_f;++u)
    {
        double x = u - cols_f / 2.0;
        for(int v=0;v<rows_f;++v)
        {
            double z = rows_f * 0.5 -v;
            double theta = asin(x / sqrt(x * x + y * y)) + PI;
            double phi = PI / 2 - atan(z / sqrt(x * x + y * y));

            double row = phi / dphi;
            double col = theta / dtheta;

            matfront.at<cv::Vec3b>(v, u) = matpano.at<cv::Vec3b>(row, col);
        }
    }
    matfrontview = matfront.clone();

    return true;
}


bool Pano2FrontView::pano_to_leftview(const cv::Mat& matpano, cv::Mat& matleftview)
{
    int rows = matpano.rows;
    int cols = matpano.cols;
    double dtheta = PI * 2 / cols;
    double dphi = PI / rows;

    int cols_f = static_cast<int>(round(m_alpha / m_res));
    int rows_f = static_cast<int>(round(m_beta / m_res));
    (cols_f % 2 == 0) ? cols_f : (cols_f++);
    (rows_f % 2 == 0) ? rows_f : (rows_f++);
    double y = (0.5 * cols_f) / tan(m_alpha * 0.5 / 180.0 * PI);

    cv::Mat matleft(rows_f, cols_f, CV_8UC3, cv::Scalar(0, 0, 0));
    for(int u=0;u<cols_f;++u)
    {
        double x = u - cols_f / 2.0;
        for(int v=0;v<rows_f;++v)
        {
            double z = rows_f * 0.5 -v;
            double theta = asin(x / sqrt(x * x + y * y)) + PI / 2;
            double phi = PI / 2 - atan(z / sqrt(x * x + y * y));

            double row = phi / dphi;
            double col = theta / dtheta;

            matleft.at<cv::Vec3b>(v, u) = matpano.at<cv::Vec3b>(row, col);
        }
    }
    matleftview = matleft.clone();

    return true;
}


bool Pano2FrontView::pano_to_rightview(const cv::Mat& matpano, cv::Mat& matrightview)
{
    int rows = matpano.rows;
    int cols = matpano.cols;
    double dtheta = PI * 2 / cols;
    double dphi = PI / rows;

    int cols_f = static_cast<int>(round(m_alpha / m_res));
    int rows_f = static_cast<int>(round(m_beta / m_res));
    (cols_f % 2 == 0) ? cols_f : (cols_f++);
    (rows_f % 2 == 0) ? rows_f : (rows_f++);
    double y = (0.5 * cols_f) / tan(m_alpha * 0.5 / 180.0 * PI);

    cv::Mat matright(rows_f, cols_f, CV_8UC3, cv::Scalar(0, 0, 0));
    for(int u=0;u<cols_f;++u)
    {
        double x = u - cols_f / 2.0;
        for(int v=0;v<rows_f;++v)
        {
            double z = rows_f * 0.5 -v;
            double theta = PI * 3 / 2 - asin(x / sqrt(x * x + y * y));
            double phi = PI / 2 - atan(z / sqrt(x * x + y * y));

            double row = phi / dphi;
            double col = theta / dtheta;

            matright.at<cv::Vec3b>(v, u) = matpano.at<cv::Vec3b>(row, col);
        }
    }
    matrightview = matright.clone();

    return true;
}


bool Pano2FrontView::pano_to_threeview(const cv::Mat& matpano, cv::Mat& matthreeview)
{
    cv::Mat matfrontview;
    cv::Mat matleftview;
    cv::Mat matrightview;

    pano_to_frontview(matpano, matfrontview);
    pano_to_leftview(matpano, matleftview);
    pano_to_rightview(matpano, matrightview);

    cv::Mat matLeftFront;
    cv::hconcat(matleftview, matfrontview, matLeftFront);
    cv::hconcat(matLeftFront, matrightview, matthreeview);

    return true;
}
