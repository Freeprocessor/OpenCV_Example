#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp> // for cvtColor

#include <iostream>


using namespace cv;
using namespace std;


int main()
{

	Mat frame;

	VideoCapture cap(0);
	if (!cap.isOpened()) // 카메라 이상 유무 확인
	{
		cerr << "카메라를 열 수 없습니다." << endl;
		return -1;
	}

	while (1) // 영상으로 보기 위함
	{
		cap.read(frame);
		if (frame.empty()) // 대부분의 카메라에서는 문제가 없지만 일부 카메라에서 처음 이미지름 가져올때 문제가 있을 수 있다. 해당 에러를 거르기 위한 구문
		{
			cerr << "캡쳐 실패" << endl;
			break;
		}

		//cvtColor(frame, frame, COLOR_BGR2GRAY);

		imshow("Live", frame);

		if (waitKey(1) >= 0) // 키 입력시 Break
			break;
	}


	return 0;
}