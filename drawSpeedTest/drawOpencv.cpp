#include"lib.h"
#include"myUtils.h"
#include<Windows.h>
#include<opencv2\opencv.hpp>
#include"RealsenseAPI.h"

int main()
{
	int width = 320;
	int height = 240;
	int fps = 60;

	RealsenseAPI realsense = RealsenseAPI(width, height, fps);

	cv::Mat mat;
	char key = 0;
	mat = cv::imread("test.jpg");
	while (key != 'q')
	{
		
		realsense.getColorImage(mat);
		cv::imshow("colorImg", mat);
		//long timeStamp = timeGetTime();
		key = cv::waitKey(1);
		//std::cout << "Lag" << timeGetTime() - timeStamp << std::endl;
		printFPS();
	}

	return 0;
}
