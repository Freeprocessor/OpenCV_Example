#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp> // 이미지파일 저장, 불러오기
#include <opencv2/highgui.hpp> // Interface 구현 모듈
#include <opencv2/imgproc.hpp> // 캐니 앳지 검출 함수 모듈
//#include <opencv2/opencv.hpp> // OpenCV 헤더를 모두 불러옴

#include <iostream> // 입출력을 위한 모듈


// OpenCV와 C++ 표준 라이브러리는 충돌나는 함수가 없기 때문에 
// using namespace를 사용해도 상관이 없다. 하지만 대형 프로젝트의 경우 주의해야함
using namespace cv;
using namespace std;


int main() // 메인함수 아규먼트 생략
{
	Mat image; // Mat 객체 선언
	image = imread("unnamed.jpg", IMREAD_GRAYSCALE);	// 이미지를 읽어서 리턴되는 Mat 객체를 대입
														// 두번째 아규먼트로는 IMREAD_UNCHANGED(알파채널을 포함시킨 컬러 이미지를 리턴함), 
														// IMREAD_COLOR(알파채널이 없는 컬러 이미지를 리턴함), IMREAD_GRAYSCALE(그레이스케일 이미지로 변환하여 리턴함)등을 사용함
	if (image.empty()) // 이미지가 비어있다면 에러메세지 출력 후 종료
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	//namedWindow("Original", WINDOW_AUTOSIZE);	// 창 생성 첫번째 아규먼트는 윈도우 타이틀에 보여질 메세지, 두번째 아규먼트는 WINDOW_AUTOSIZE의 경우 이미지 크기에 맞춰짐(창 크기 변경 불가)
											// WINDOW_NORMAL의 경우 창 크기 조절 가능 또한 윈도우 해상도에 따라서 윈도우 크기가 맞춰짐 
											// 또한 생략가능 imshow만을 사용하여 위의 구문을 생략 가능하나, 트랙바를 붙이는 등 작업을 하기 위해선 필요함
	//setWindowProperty("Original", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
	imshow("Original", image);
	Canny(image, image, 50, 150);
	imshow("Canny", image);	// imshow 함수는 첫번째 아규먼트로 생성한 창에, 두번째 아규먼트로 Mat 객체에 저장된 이미지를 보여줌

	waitKey(0); // 키 입력을 일정시간 동안 대기. 0을 아규먼트로 사용시 무한정 대기 함
}