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
        int frame;
        std::vector<Carte*> cartes;
        std::vector<int> sortedIds;
        cv::VideoCapture inputVideo;
        cv::Ptr<cv::aruco::Dictionary> dictionary;
        std::vector<bool> manyGoalChecked, manyGoalChecked2;
        std::vector<std::vector<int>> manyIds;
        std::vector<std::vector<std::vector<cv::Point2f>>> manyCorners;

        std::vector<int> affinageIds(std::vector<int> const &input);
        std::vector<int> sortTrackers(std::vector<std::vector<cv::Point2f>> const &affinedCorners, std::vector<int> const &affinedIds);
        std::vector<std::vector<cv::Point2f>> affinageCorners(std::vector<std::vector<cv::Point2f>> const &input);
        std::vector<std::vector<cv::Point2f>> sortCorners(std::vector<std::vector<cv::Point2f>> const &input);
        cv::Point2f getCenter(std::vector<cv::Point2f> const &input);
        bool affinageStartGoal();
        bool checkStartGoal();
        void detectOptions();
        cv::Mat rotateImage(cv::Mat image, double angle);

    public:
        Detection();
        ~Detection();
        std::vector<Carte*> launch();


    public slots:




};

#endif // DETECTION_H
