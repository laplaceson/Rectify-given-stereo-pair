#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;
Mat  findepipole(vector<Point> p1, vector<Point> p2)
{
	//*****************************************************
	Mat m_F = findFundamentalMat(p1, p2, FM_8POINT);
	////**************************************************epiploe line
	Mat point1a = (Mat_<double>(3, 1) << p1[1].x, p1[1].y, 1);
	Mat point2a = (Mat_<double>(3, 1) << p1[2].x, p1[2].y, 1);

	Mat line1b = m_F*point1a;
	Mat line2b = m_F*point2a;
	Mat dot = line1b.cross(line2b);
	dot /= dot.ptr<double>(0)[2];
	return dot;
}
Mat findH(Mat dot,Mat T)
{
	Mat et = T*dot;
	double theta = -atan(et.ptr<double>(1)[0]/et.ptr<double>(0)[0]);
	Mat R = (Mat_<double>(3, 3) << cos(theta), -sin(theta), 0, sin(theta), cos(theta), 0, 0, 0, 1);
	Mat ret = R*et;
	Mat G = (Mat_<double>(3, 3) << 1, 0, 0, 0, 1, 0, -1 / ret.ptr<double>(0)[0], 0, 1);
	Mat H = G*R*T;
	return H;
}
int main()
{
	Mat src1 = imread("1.jpg");
	Mat src2 = imread("2.jpg");
	//*************************************************
	vector<Point> p1(10);
	vector<Point> p2(10);
	//p1[0] = Point(584, 701);   p2[0] = Point(865, 797);
	//p1[1] = Point(1734, 873); p2[1] = Point(680, 904);
	//p1[2] = Point(687, 859);   p2[2] = Point(1350, 911);
	//p1[3] = Point(569, 918);  p2[3] = Point(795, 990);
	//p1[4] = Point(1605, 436); p2[4] = Point(1670, 433);
	//p1[5] = Point(1733, 471); p2[5] = Point(1799, 447);
	//p1[6] = Point(1386, 250); p2[6] = Point(1946, 236);
	//p1[7] = Point(1545, 1853); p2[7] = Point(1364, 1820);
	//p1[8] = Point(2164, 1845); p2[8] = Point(2040, 1850);
	//p1[9] = Point(2200, 914); p2[9] = Point(2047, 861);
	/*p1[0] = Point(155, 502); p2[0] = Point(890, 639);
	p1[1] = Point(532, 570); p2[1] = Point(1224, 658);
	p1[2] = Point(1225, 62); p2[2] = Point(1769, 78);
	p1[3] = Point(1502, 356); p2[3] = Point(2083, 324);
	p1[4] = Point(2107, 577); p2[4] = Point(2888, 457);
	p1[5] = Point(600, 697); p2[5] = Point(877, 792);
	p1[6] = Point(1516, 698); p2[6] = Point(1092, 733);
	p1[7] = Point(1459, 944); p2[7] = Point(1049, 966);
	p1[8] = Point(2242, 834); p2[8] = Point(2076, 771);
	p1[9] = Point(746, 871); p2[9] = Point(1403, 918);*/
	p1[0] = Point(155, 502); p2[0] = Point(890, 639);
	p1[1] = Point(532, 571); p2[1] = Point(1224, 658);
	p1[2] = Point(529,900); p2[2] = Point(827,975);
	p1[3] = Point(1502, 356); p2[3] = Point(2083, 324);
	p1[4] = Point(2107, 577); p2[4] = Point(2888, 457);
	p1[5] = Point(600, 697); p2[5] = Point(877, 792);
	p1[6] = Point(1516, 698); p2[6] = Point(1092, 733);
	p1[7] = Point(1459, 944); p2[7] = Point(1049, 966);
	p1[8] = Point(2242, 834); p2[8] = Point(2076, 771);
	p1[9] = Point(746, 871); p2[9] = Point(1403, 918);

	Mat T1 = (Mat_<double>(3, 3) << 1, 0, -src1.cols*0.5, 0, 1, -src1.rows*0.5, 0, 0, 1);
	Mat dota=findepipole(p1, p2);
	Mat H = findH(dota, T1);
	//Mat hh = (Mat_<double>(2, 3) << H.ptr<double>(0)[0], H.ptr<double>(0)[1], H.ptr<double>(0)[2], H.ptr<double>(1)[0], H.ptr<double>(1)[1], H.ptr<double>(1)[2]);
	//	warpAffine(src1, src1, hh, src1.size());
	Mat dotb = findepipole(p2, p1);
	Mat H1 = findH(dotb,T1);
	//	Mat hh22 = (Mat_<double>(2, 3) << H1.ptr<double>(0)[0], H1.ptr<double>(0)[1], H1.ptr<double>(0)[2], H1.ptr<double>(1)[0], H1.ptr<double>(1)[1], H1.ptr<double>(1)[2]);
	//warpAffine(src2, src2, hh22, src1.size());
	//***************************************
	vector<Point2d> c(10);
	vector<Point2d> c1(10);
	for (int i = 0; i < 10; i++)
	{
		Mat ttt = (Mat_<double>(3, 1) << p1[i].x, p1[i].y, 1);
		ttt = H1*ttt;
		c[i].x = ttt.ptr<double>(0)[0] / ttt.ptr<double>(2)[0];
		c[i].y = ttt.ptr<double>(1)[0] / ttt.ptr<double>(2)[0];
		//*
		Mat ttt1 = (Mat_<double>(3, 1) << p2[i].x, p2[i].y, 1);
		ttt1 = H*ttt1;
		c1[i].x = ttt1.ptr<double>(0)[0] / ttt1.ptr<double>(2)[0];
		c1[i].y = ttt1.ptr<double>(1)[0] / ttt1.ptr<double>(2)[0];
	}
	Mat temp1(5, 5, CV_64FC1, Scalar(0));
	Mat temp2(5, 1, CV_64FC1, Scalar(0));
	for (int i = 0; i < 10; i++)
	{
		temp1.ptr<double>(0)[0] += c[i].x*c[i].x;
		temp1.ptr<double>(0)[1] += c[i].x*c[i].y;
		temp1.ptr<double>(0)[2] += c[i].x;
		temp1.ptr<double>(1)[0] += c[i].x*c[i].y;
		temp1.ptr<double>(1)[1] += c[i].y*c[i].y;
		temp1.ptr<double>(1)[2] += c[i].y;
		temp1.ptr<double>(2)[0] += c[i].x;
		temp1.ptr<double>(2)[1] += c[i].y;
		temp1.ptr<double>(2)[2] += 1;
		temp1.ptr<double>(3)[3] += c[i].y*c[i].y;
		temp1.ptr<double>(3)[4] += c[i].y;
		temp1.ptr<double>(4)[3] += c[i].y;
		temp1.ptr<double>(4)[4] += 1;

		temp2.ptr<double>(0)[0] += c[i].x*c1[i].x;
		temp2.ptr<double>(1)[0] += c[i].y*c1[i].x;
		temp2.ptr<double>(2)[0] += c1[i].x;
		temp2.ptr<double>(3)[0] += c[i].y*c1[i].y;
		temp2.ptr<double>(4)[0] += c1[i].y;
	}
	Mat ss = temp1.inv()*temp2;
	//***
	Mat T = (Mat_<double>(3, 3) << 1, 0, src1.cols*0.5, 0, 1, src1.rows*0.5, 0, 0, 1);
	Mat HA = (Mat_<double>(3, 3) << ss.ptr<double>(0)[0], ss.ptr<double>(1)[0], ss.ptr<double>(2)[0], 0, ss.ptr<double>(3)[0], ss.ptr<double>(4)[0], 0, 0, 1);
	Mat hh1 = T*HA*H1;	
	warpPerspective(src1, src1, hh1, src1.size());
	Mat hh2 = T*H;
	warpPerspective(src2, src2, hh2, src2.size());

	Mat final_image;
	hconcat(src1, src2, final_image);
	imwrite("after1.jpg", src1);
	imwrite("after2.jpg", src2);
	imwrite("aftertotal.jpg", final_image);
	waitKey(0);
}