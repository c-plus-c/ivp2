// �C���N���[�h�t�@�C��

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cctype>
#include <opencv2/opencv.hpp>
#ifdef _WIN32
#include <opencv2/opencv_lib.hpp>
#endif
using namespace cv; // ���O��Ԃ̐ݒ�

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
  img = imread(argv[1], CV_LOAD_IMAGE_COLOR); // �摜�t�@�C���̓ǂݍ���

  if(img.empty()){
    printf("Unable to load the image");
    return 1;
  }
  
  namedWindow("Display Image", CV_WINDOW_AUTOSIZE);  // �E�B���h�E����
  imshow("Display Image", img);  // �摜�\��

  Mat converted=img;
  Mat final;
  // �L�[�҂���ԂɈڍs
  while(1) {
    int ksize=3;
    double thread1,thread2;
    char filename[40];
    int c = waitKey(10);	// ������delay
    switch((char)c) {
    case 'q':		// q�L�[�Ńv���O�����I��
      return 0;
    case 's': //�\�x���t�B���^
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
