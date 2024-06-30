// Copyright (C) 2024 twyleg
#include "gnuplot.h"

GnuPlot::GnuPlot(){

    gnuplot = 0;

    title = "";

    open();

}

void GnuPlot::open(){

    gnuplot = popen("gnuplot -p","w");

	fprintf(gnuplot, "set grid\n");
	fprintf(gnuplot, "set terminal pngcairo size 640,480 enhanced font 'Verdana,10'\n");
	fprintf(gnuplot, "set output '/tmp/gnuplot.png'\n");
	fflush(gnuplot);
}

void GnuPlot::close(){

    pclose(gnuplot);
}

void GnuPlot::reset(){
    close();
    open();
}

void GnuPlot::startMultiplot(){
	fprintf(gnuplot, "set output '/tmp/gnuplot.png'\n");
	fprintf(gnuplot, "set multiplot\n");
	fflush(gnuplot);
}

void GnuPlot::stopMultiplot(){
	fprintf(gnuplot, "unset multiplot\n");
	//fprintf(gnuplot, "set output\n");
	fflush(gnuplot);
}

void GnuPlot::drawPoint(double x, double y, double z, char *color){
	fprintf(gnuplot, "set style line 1 lc rgb \"%s\" lt 1 lw 2 pt 7 ps 1\n",color);
	fprintf(gnuplot, "splot '-' w p ls 1\n");
	fprintf(gnuplot, "%f %f %f\n",x,y,z);
	fprintf(gnuplot, "e\n");
	fflush(gnuplot);
}

void GnuPlot::drawPoint(cv::Mat &point, char *color){

	drawPoint(point.at<double>(0),point.at<double>(1),point.at<double>(2),color);

}

void GnuPlot::drawCoordinateSystem(cv::Mat &O_T_D, double length){

	/*
	 * O_T_D - Destination realtiv zu Origin
	 */

	double D_originPointData[4] = {0, 0, 0, 1};

	cv::Mat D_originPoint(4,1,CV_64F,D_originPointData);

	double D_axisPointXData[4] = {length, 0, 0, 1};
	double D_axisPointYData[4] = {0, length, 0, 1};
	double D_axisPointZData[4] = {0, 0, length, 1};

	cv::Mat D_axisPointX(4,1,CV_64F,D_axisPointXData);
	cv::Mat D_axisPointY(4,1,CV_64F,D_axisPointYData);
	cv::Mat D_axisPointZ(4,1,CV_64F,D_axisPointZData);

	cv::Mat O_originPoint = O_T_D * D_originPoint;
    cv::Mat O_axisPointX = O_T_D * D_axisPointX;
    cv::Mat O_axisPointY = O_T_D * D_axisPointY;
    cv::Mat O_axisPointZ = O_T_D * D_axisPointZ;

    drawLine(O_originPoint,O_axisPointX,"red");
    drawLine(O_originPoint,O_axisPointY,"green");
    drawLine(O_originPoint,O_axisPointZ,"blue");

}

void GnuPlot::drawLine(double x1, double y1, double z1, double x2, double y2, double z2,char *color){
	fprintf(gnuplot, "set style line 2 lc rgb \"%s\" lt 1 lw 2 pt 7 ps 0\n",color);
	fprintf(gnuplot, "splot '-' w l ls 2\n");

	fprintf(gnuplot, "%f %f %f\n",x1,y1,z1);
	fprintf(gnuplot, "%f %f %f\n",x2,y2,z2);

	fprintf(gnuplot, "e\n");
	fflush(gnuplot);
}

void GnuPlot::drawLine(cv::Mat &pointOne, cv::Mat &pointTwo, char *color){

	drawLine(pointOne.at<double>(0),pointOne.at<double>(1),pointOne.at<double>(2),pointTwo.at<double>(0),pointTwo.at<double>(1),pointTwo.at<double>(2),color);

}

void GnuPlot::setRangeX(double min, double max){
	fprintf(gnuplot, "set xrange [%f:%f]\n",min,max);
	fflush(gnuplot);
}

void GnuPlot::setRangeY(double min, double max){
	fprintf(gnuplot, "set yrange [%f:%f]\n",min,max);
	fflush(gnuplot);
}

void GnuPlot::setRangeZ(double min, double max){
	fprintf(gnuplot, "set zrange [%f:%f]\n",min,max);
	fflush(gnuplot);
}


void GnuPlot::setTitle(std::string &title){
    this->title = title;
    fprintf(gnuplot, "set terminal qt title \"%s\"\n",title.c_str());
    fflush(gnuplot);
}
