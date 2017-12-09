#include<RealSense\SenseManager.h>
#include<opencv2\opencv.hpp>

class RealsenseAPI
{
public:
	RealsenseAPI() {}
	RealsenseAPI(int width, int height, int fps);
	~RealsenseAPI();
	void getColorImage(cv::Mat& inputMat);
	int getWidth();
	int getHeight();
	int getFPS();
private:

	int width, height, fps;
	Intel::RealSense::SenseManager* senseManager;

};

