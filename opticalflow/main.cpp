// インクルードファイル

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <opencv2/opencv.hpp>
#ifdef _WIN32
#include <opencv2/opencv_lib.hpp>
#endif
using namespace std;
using namespace cv; // 名前空間の設定

void show_result(vector<Point2f> points, Mat img, Mat flow)
{
	
	for (vector<Point2f>::iterator ite = points.begin(); ite != points.end(); ite++)
	{
		Point2f v = flow.at<Point2f>(ite->y, ite->x);

		line(img, *ite, (*ite)+v, Scalar(150, 0, 0), 2);
	}
	
	imshow("Display Image", img);
}

int main(int argc, char *argv[])
{
	Mat flow;
	Mat img1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE); // 画像ファイルの読み込み
	Mat img2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);
	if (img1.empty() || img2.empty()){
		printf("Unable to load the image");
		return 1;
	}

	int xresol, yresol;
	xresol = atoi(argv[3]);
	yresol = atoi(argv[4]);

	vector<Point2f> points;

	for (int i = 0; i<img1.cols / xresol; i++){
		for (int j = 0; j<img1.rows / yresol; j++){
			points.push_back(Point2f(i*xresol+xresol/2, j*yresol+yresol/2));
		}
	}


	double pyr_scale = 0.5, poly_sigma = 1.1;
	int levels = 5, winsize = 15, iterations=3, poly_n = 5, flags;

	flags = OPTFLOW_FARNEBACK_GAUSSIAN;

	calcOpticalFlowFarneback(img1, img2, flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);

	namedWindow("Display Image", CV_WINDOW_AUTOSIZE);  // ウィンドウ生成
	show_result(points, img1, flow);
	// キー待ち状態に移行
	while (1) {
		int c = waitKey(10);	// 引数はdelay
		char filename[50];
		switch ((char) c) {
		case 'q':		// qキーでプログラム終了
			return 0;
		case 'p':
			scanf("%lf", &pyr_scale);
			calcOpticalFlowFarneback(img1, img2, flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
			show_result(points, img1, flow);
			break;
		case 'l':
			scanf("%d", &levels);
			calcOpticalFlowFarneback(img1, img2, flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
			show_result(points, img1, flow);
			break;
		case 'w':
			scanf("%d", &winsize);
			calcOpticalFlowFarneback(img1, img2, flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
			show_result(points, img1, flow);
			break;
		case 'i':
			scanf("%d", &iterations);
			calcOpticalFlowFarneback(img1, img2, flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
			show_result(points, img1, flow);
			break;
		case 'n':
			scanf("%d", &poly_n);
			calcOpticalFlowFarneback(img1, img2, flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
			show_result(points, img1, flow);
			break;
		case 's':
			scanf("%lf", &poly_sigma);
			calcOpticalFlowFarneback(img1, img2, flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
			show_result(points, img1, flow);
			break;
		case 'f':
			if (levels == OPTFLOW_USE_INITIAL_FLOW)
				levels = OPTFLOW_FARNEBACK_GAUSSIAN;
			else
				levels = OPTFLOW_USE_INITIAL_FLOW;
			calcOpticalFlowFarneback(img1, img2, flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
			show_result(points, img1, flow);
			break;
		case 'o': //output
			scanf("%s", filename);
			imwrite(filename, flow);
			break;
		}
	}

	return 0;
}
