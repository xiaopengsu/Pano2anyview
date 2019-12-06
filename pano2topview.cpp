#include "pano2topview.h"


Pano2TopView::Pano2TopView()
{
    m_dresolution = 0.02;
    m_dwidth = 30;
    m_dlength = 30;

    m_iRow = 4096;
    m_icol = 8192;

    m_dheight = 2.4;
}


Pano2TopView::Pano2TopView(double resolution, double height)
{
    m_dresolution = resolution;
    m_dwidth = 30;
    m_dlength = 30;

    m_iRow = 4096;
    m_icol = 8192;

    m_dheight = height;
}


Pano2TopView::~Pano2TopView()
{

}


bool Pano2TopView::pano_to_topview(const cv::Mat& matpano, cv::Mat& mattopview)
{
    int rows = matpano.rows;
    int cols = matpano.cols;
    double dtheta = PI * 2 / cols;
    double dphi = PI / rows;

    int cols_f = (static_cast<int>(ceil(m_dwidth / m_dresolution))) * 2;
    int rows_f = (static_cast<int>(ceil(m_dlength / m_dresolution))) * 2;
    cv::Mat mattop(rows_f, cols_f, CV_8UC3, cv::Scalar(0, 0, 0));

#pragma omp parallel for
    for(int i=0;i<cols_f;++i)
    {
        double x = (i - cols_f / 2.0) * m_dresolution;
        x += 0.5 * m_dresolution;
        for(int j=0;j<rows_f;++j)
        {
            double y = -(j - rows_f * 0.5) * m_dresolution;
            y -= 0.5 * m_dresolution;
            double xy = sqrt(x * x + y * y);

            double phi = PI - atan(xy / m_dheight) - 0.000001;
            double row = phi / dphi;
            double theta = PI * 1.5 - atan2(y, x);
            theta = theta < 0 ? (theta + PI * 2) : theta;
            double col = theta / dtheta;

            mattop.at<cv::Vec3b>(j, i) = matpano.at<cv::Vec3b>(row, col);
        }
    }

    mattopview = mattop.clone();

    return true;
}

bool Pano2TopView::topview_to_pano(const cv::Mat& mattopview, cv::Mat& matpano)
{
    if(mattopview.rows != 3000 || mattopview.cols != 3000)
    {
        return false;
    }

    double dtheta = PI * 2 / m_icol;
    double dphi = PI / m_iRow;
    cv::Mat matPa(m_iRow, m_icol, CV_8UC3, cv::Scalar(0, 0, 0));
    int row_cut = m_iRow / 2 +10;

#pragma omp parallel for
    for(int i=0;i<m_icol;++i)
    {
        double theta = PI * 1.5 - i * dtheta;
        double sin_theta = sin(theta);
        double cos_theta = cos(theta);

        for(int j=row_cut;j<m_iRow;++j)
        {
            double phi = PI / 2 - j * dphi;
            double sin_phi = sin(phi);
            double cos_phi = cos(phi);

            cv::Point2f pt;
            pt.x = -m_dheight / sin_phi * cos_phi * cos_theta;
            pt.y = -m_dheight / sin_phi * cos_phi * sin_theta;
            if(fabs(pt.x) > 30 - 0.001 || fabs(pt.y) > 30 - 0.001)
            {
                continue;
            }
            double col = (pt.x + m_dwidth) / m_dresolution;
            double row = (m_dlength - pt.x) / m_dresolution;

            matPa.at<cv::Vec3b>(j, i) = mattopview.at<cv::Vec3b>(row, col);
        }
    }

    matpano = matPa.clone();

    return true;
}
