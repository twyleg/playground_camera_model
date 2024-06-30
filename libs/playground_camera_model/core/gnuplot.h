// Copyright (C) 2024 twyleg
// Copyright (C) 2024 twyleg
#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <string>

#include <opencv2/opencv.hpp>

class GnuPlot{

private:

    FILE *gnuplot;

    std::string title;

public:

    GnuPlot();

    void open();
    void close();
    void reset();

    void startMultiplot();
    void stopMultiplot();

    void drawPoint(double x, double y, double z, char *color);
    void drawPoint(cv::Mat &point, char *color);

    void drawLine(double x1, double y1, double z1, double x2, double y2, double z2,char *color);
    void drawLine(cv::Mat &pointOne, cv::Mat &pointTwo, char *color);

    void drawCoordinateSystem(cv::Mat &O_T_D, double length);

    void setRangeX(double min, double max);
    void setRangeY(double min, double max);
    void setRangeZ(double min, double max);

    void setTitle(std::string &title);

};
