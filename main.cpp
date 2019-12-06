#include <iostream>
#include <fstream>
#include "pano2frontview.h"
#include "pano2topview.h"

using namespace std;

const char* usage =
        "\n"
        "\n .input 4 address: ./build/myPano2anyview ../data/image/ ../data/front_image/ ../data/top_image/"
        "\n";
static void help()
{
    cout<<usage;
}

int main(int argc, char **argv)
{

    if(argc != 4)
    {
        help();
        return 0;
    }
    string Panpic = argv[1];
    string Frontpic = argv[2];
    string toppic = argv[3];

    string Panoname;
    vector<string> Panonames;
    ifstream Panpicname;
    Panpicname.open(Panpic+".txt");
    cout<<Panpic+".txt"<<endl;
    if(!Panpicname.is_open())
    {
        std::cerr<<"error, Panoname data not exist"<<std::endl;
        return false;
    }
    while(Panpicname>>Panoname)  //    while(Panpicname.is_open() && Panpicname>>Panoname)
    {
        Panonames.push_back(Panoname);
        cout<<Panoname<<endl;
    }
    Panpicname.close();




    Pano2FrontView Panos;
    Pano2TopView Tops;
    cv::Mat Pano;
    cv::Mat matthreeview;
    cv::Mat mattopview;
    cv::Mat mattopview2;
    for(int i=0;i<Panonames.size();++i)
    {
        //        Pano = cv::imread(Panpic + Panonames[i] + ".jpg");
        //           Pano = cv::imread("../data/image/" + Panonames[i]);
          Pano = cv::imread(Panpic +"/" + Panonames[i]);//
          if(Pano.empty())
          {
              cout<<"path= "<<Panpic<<endl;
              std::cerr<<"error, Panoimage load fail"<<std::endl;
          }
//        Panos.pano_to_leftview(Pano, matthreeview);
//        Panos.pano_to_rightview(Pano, mattopview);
//        Panos.pano_to_threeview(Pano, mattopview2);
        Panos.pano_to_frontview(Pano, matthreeview);
        Tops.pano_to_topview(Pano, mattopview);


        cv::Mat img;cv::Mat imgshow; img=mattopview.clone();
        cv::resize(img,imgshow,cv::Size(img.cols/4,img.rows/4),0,0);
        cv::imshow("top", imgshow);
        cv::waitKey(10);

        cv::imwrite(Frontpic +"/" +Panonames[i], matthreeview);
        cv::imwrite(toppic +"/"+ Panonames[i], mattopview);
//        cv::imwrite(Frontpic +"/" + to_string(i) + ".jpg", matthreeview);
//        cv::imwrite(toppic +"/"+ to_string(i) + ".jpg", mattopview);
    }

    return 0;
}
