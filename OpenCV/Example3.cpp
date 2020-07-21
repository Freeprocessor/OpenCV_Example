#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 트랙바 생성시 요구하는 콜백 함수 정의
void dummy(int, void*)
{

}

int threshold1 = 30;// saturation, value 값은 30
// RGB 색 공간으로는 색의 범위에 따라서 구분을 하기가 힘듬. HVS는 원하는 색을 검출하기 위해 많이 사용되는 색 공간 중 하나
// 채도는 색상의 진함(H, 0~255), 명도는 색상이 밝은 정도를 의미(V)하고 값이 작아질수록 어두위짐, 
Vec3b lower_blue1, upper_blue1, lower_blue2, upper_blue2, lower_blue3, upper_blue3;
Mat img_color;


// 마우스 클릭시 호출되는 콜백 함수
// 클릭한 P3 좌표를 받아서 셀값을 받아옴
void mouse_callback(int event, int x, int y, int flags, void* param) 
{
	// 마우스 좌클릭을 하는 것으로 이벤트를 정함
	if (event == EVENT_LBUTTONDOWN)
	{
		// 클릭한 위치에 있는 픽셀의 값을 읽어옴
		Vec3b color_pixel = img_color.at<Vec3b>(y, x);

		// 한 픽셀로 구성된 이미지로 변경함
		Mat bgr_color = Mat(1, 1, CV_8UC3, color_pixel);


		//cvt 컬러 함수를 이용하여 이미지를 비주얼 색 공간에서 HVS 색공간으로 변환함
		Mat hsv_color;
		cvtColor(bgr_color, hsv_color, COLOR_BGR2HSV);

		// hue 값을 정수 변수에 대입
		int hue = hsv_color.at<Vec3b>(0, 0)[0];
		int saturation = hsv_color.at<Vec3b>(0, 0)[1];
		int value = hsv_color.at<Vec3b>(0, 0)[2];

		cout << "hue = " << hue << endl;
		cout << "saturation = " << saturation << endl;
		cout << "value = " << value << endl;

		// 마우스 클릭한 위치에 픽셀에서 얻은 값과 유사한 색상을 추출하기 위해 범위를 정해야 함
		if (hue < 10)
		{
			// 앞에서 구한 6개의 값에 +-10 하여 범위를 조정함
			cout << "case 1" << endl;
			lower_blue1 = Vec3b(hue - 10 + 180, threshold1, threshold1);
			upper_blue1 = Vec3b(180, 255, 255);
			lower_blue2 = Vec3b(0, threshold1, threshold1);
			upper_blue2 = Vec3b(hue, 255, 255);
			lower_blue3 = Vec3b(hue, threshold1, threshold1);
			upper_blue3 = Vec3b(hue + 10, 255, 255);
		}
		else if (hue > 170)
		{
			cout << "case 2" << endl;
			lower_blue1 = Vec3b(hue, threshold1, threshold1);
			upper_blue1 = Vec3b(180, 255, 255);
			lower_blue2 = Vec3b(0, threshold1, threshold1);
			upper_blue2 = Vec3b(hue + 10 - 180, 255, 255);
			lower_blue3 = Vec3b(hue - 10, threshold1, threshold1);
			upper_blue3 = Vec3b(hue, 255, 255);
		}
		else
		{
			cout << "case 3" << endl;
			lower_blue1 = Vec3b(hue, threshold1, threshold1);
			upper_blue1 = Vec3b(hue + 10, 255, 255);
			lower_blue2 = Vec3b(hue - 10, threshold1, threshold1);
			upper_blue2 = Vec3b(hue, 255, 255);
			lower_blue3 = Vec3b(hue - 10, threshold1, threshold1);
			upper_blue3 = Vec3b(hue, 255, 255);
		}

		cout << "hue = " << hue << endl;
		cout << "#1 = " << lower_blue1 << "~" << upper_blue1 << endl;
		cout << "#2 = " << lower_blue2 << "~" << upper_blue2 << endl;
		cout << "#3 = " << lower_blue3 << "~" << upper_blue3 << endl;
	}
}



int main()
{
	// 윈도우 등록
	namedWindow("img_color");
	// 윈도우에 마우스 콜백 함수를 등록
	setMouseCallback("img_color", mouse_callback);
	// 트렉바를 변수 threshold1에 연결하여 생성(최대 255), 초기값은 30
	createTrackbar("threshold", "img_color", &threshold1, 255, dummy);
	setTrackbarPos("threshold", "img_color", 30);


	Mat img_hsv;

	// 카메라에서 이미지를 가져올 수 있도록 비디오 캡쳐 색 개체 생성
	VideoCapture cap(0);
	if (!cap.isOpened()) {

		cout << "카메라를 열 수 없습니다." << endl;
		return -1;
	}


	while (1)
	{
		// 비디오 캡쳐 객체 리드 함수를 사용하여 카메라로부터 이미지를 가져옴
		cap.read(img_color);

		// 트랙바 이동 시 파킹 값을 가져옴, 마우스 클릭 시 콜백 함수에서 범위가 업데이트 되어 사용됨
		threshold1 = getTrackbarPos("threshold", "img_color");

		// 이미지를 비주얼 색 공간에서 HVS 색 공간으로 변환
		cvtColor(img_color, img_hsv, COLOR_BGR2HSV);


		// 마우스 클릭 시 생성되는 범위를 가지고 HVS 이미지에서 마스크 이미지 생성
		Mat img_mask1, img_mask2, img_mask3, img_mask;
		// inRange 함수는 이미지 내에 있는 픽셀을 흰색으로 그 외의 픽셀을 검정색으로 만듬(=바이너리 이미지)
		inRange(img_hsv, lower_blue1, upper_blue1, img_mask1);
		inRange(img_hsv, lower_blue2, upper_blue2, img_mask2);
		inRange(img_hsv, lower_blue3, upper_blue3, img_mask3);
		img_mask = img_mask1 | img_mask2 | img_mask3;


		Mat img_result;
		// 마스크 이미지와 원본 이미지를 &연산하여 마스크 이미지에서 흰색으로 표현되는 부분만 원본이미지에서 당겨줌
		bitwise_and(img_color, img_color, img_result, img_mask);

		imshow("img_color", img_color);
		imshow("img_mask", img_mask);
		imshow("img_result", img_result);

		if (waitKey(1) > 0)
			break;
	}


	return 0;
}