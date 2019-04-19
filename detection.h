#ifndef DETECTION_H
#define DETECTION_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <ctype.h>

#include "carte.h"
class Detection
{

    private:
        std::vector<Carte*> cartes;
        std::vector<int> ids, affinedIds, sortedIds, vector_argument, vector_function;
        std::vector<std::vector<cv::Point2f>> corners, affinedCorners;
        cv::VideoCapture inputVideo;
        cv::Ptr<cv::aruco::Dictionary> dictionary;
        std::vector<bool> manyGoalChecked, manyGoalChecked2;
        std::vector<std::vector<int>> manyIds;
        std::vector<std::vector<std::vector<cv::Point2f>>> manyCorners;


        cv::Point2f getXY(int const id);
        std::vector<int> affinageIds();
        bool affinageStartGoal();
        bool checkStartGoal();
        std::vector<std::vector<cv::Point2f>> affinageCorners();
        cv::Point2f getCenter(std::vector<cv::Point2f> const &input);
        std::vector<int> sortTrackers();
        void detectOptions();
        cv::Mat rotateImage(cv::Mat image, double angle);

    public:
        Detection();
        ~Detection();
        void launch();
        std::vector<Carte*> getCartes();


    public slots:




};

#endif // DETECTION_H
