#ifndef CARTE_H
#define CARTE_H
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <ctime>
#include <ctype.h>


class Carte
{

private:
    std::string type;
    int id,x,y, argument_id;


public:

    Carte(int id, cv::Point2f xy);
    Carte(int id, cv::Point2f coord, std::string type);
    void setArgumentId(int argument_id);
    int getId();
    int getX();
    int getY();
    std::string getType();
    int getArgumentId();



};

#endif // CARTE_H
