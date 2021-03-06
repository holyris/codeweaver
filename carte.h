#ifndef CARTE_H
#define CARTE_H
#include <QString>
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
    QString name, argument_name;
    void setName(int const id);
    void setArgumentName(int const id);

public:

    Carte(int id, cv::Point2f xy);
    Carte(int id, cv::Point2f coord, std::string type);
    Carte(int id, std::string type);
    ~Carte();
    void setArgumentId(int const argument_id);
    int getId() const;
    int getX() const;
    int getY() const;

    QString getName() const;
    QString getArgumentName() const;
    std::string getType() const;
    int getArgumentId() const;
};

#endif // CARTE_H
