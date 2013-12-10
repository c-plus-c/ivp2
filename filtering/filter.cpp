// インクルードファイル

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cctype>
#include <opencv2/opencv.hpp>
#ifdef _WIN32
#include <opencv2/opencv_lib.hpp>
#endif
using namespace cv; // 名前空間の設定

using namespace std;

int input_ksize()
{
  int ksize=1;
  do{
    printf("input ksize :");
    scanf("%d",&ksize);
  }while(ksize%2==0);

  return ksize;
}

int main(int argc,char *argv[])
{
  Mat img;
  img = imread(argv[1], CV_LOAD_IMAGE_COLOR); // 画像ファイルの読み込み

  if(img.empty()){
    printf("Unable to load the image");
    return 1;
  }
  
  namedWindow("Display Image", CV_WINDOW_AUTOSIZE);  // ウィンドウ生成
  imshow("Display Image", img);  // 画像表示

  Mat converted=img;
  Mat final;
  // キー待ち状態に移行
  while(1) {
    int ksize=3;
    double thread1,thread2;
    char filename[40];
    int c = waitKey(10);	// 引数はdelay
    switch((char)c) {
    case 'q':		// qキーでプログラム終了
      return 0;
    case 's': //ソベルフィルタ
      printf("Sobel Filter\n");
      ksize=input_ksize();
      Sobel(img,converted,CV_32F,1,1,ksize);
      convertScaleAbs(converted,final);
      imshow("Display Image",final);
      break;
    case 'l':
      printf("Laplacian Filter\n");
      ksize=input_ksize();
      Laplacian(img,converted,CV_32F,ksize);
      convertScaleAbs(converted,final);
      imshow("Display Image",final);
      break;
    case 'c':
      printf("Canny Filter\n");
      printf("input threshold1 threshold2  :");
      scanf("%lf",&thread1);
      scanf("%lf",&thread2);

      Canny(img,converted,thread1,thread2);
      convertScaleAbs(converted,final);
      imshow("Display Image",final);
      break;
    case 'w':
      printf("Save\n");
      printf("input filename:");
      scanf("%s",filename);
      imwrite(filename,final);
      break;
    }
  }
  
  return 0;
}
