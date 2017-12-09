#include"RealsenseAPI.h"
#include<RealSense\Session.h>
#include<RealSense\SampleReader.h>
#include<opencv2\opencv.hpp>

using namespace Intel::RealSense;

RealsenseAPI::RealsenseAPI(int width, int height, int fps)
{
	this->width = width;
	this->height = height;
	this->fps = fps;
	this->senseManager = SenseManager::CreateInstance();
	this->senseManager->EnableStream(Capture::STREAM_TYPE_COLOR, width, height, fps);
	this->senseManager->Init();
	Capture::Device* device = this->senseManager->QueryCaptureManager()->QueryDevice();
	device->ResetProperties(Capture::STREAM_TYPE_ANY);
	device->SetMirrorMode(Capture::Device::MirrorMode::MIRROR_MODE_DISABLED);
}

RealsenseAPI::~RealsenseAPI()
{
	if (this->senseManager != nullptr)
	{
		this->senseManager->Release();
		this->senseManager = nullptr;
	}
}

int RealsenseAPI::getFPS()
{
	return this->fps;
}

int RealsenseAPI::getHeight()
{
	return this->height;
}

int RealsenseAPI::getWidth()
{
	return this->width;
}

void RealsenseAPI::getColorImage(cv::Mat& inputMat)
{
	if (inputMat.rows != this ->height || inputMat.cols != this ->width || inputMat.type() != CV_8UC3)
	{
		inputMat = cv::Mat(this->height, this->width, CV_8UC3);
	}


	Status status = senseManager->AcquireFrame(true);
	if (status < Status::STATUS_NO_ERROR)
	{
		std::cout << "err" << std::endl;;
		return;
	}

	const Capture::Sample *sample = senseManager->QuerySample();

	if (sample->color)
	{
		Image::ImageData data = {}; //={}\‘¢‘Ì‚Ì‰Šú‰»•û–@;
		Image::Rotation rotation = sample->color->QueryRotation();
		status = sample->color->AcquireAccess(Image::ACCESS_READ, Image::PIXEL_FORMAT_RGB24, rotation, Image::OPTION_ANY, &data);
		if (status >= Status::STATUS_NO_ERROR)
		{
			memcpy(inputMat.data, data.planes[0], data.pitches[0] * this ->height);
			sample->color->ReleaseAccess(&data);
			senseManager->ReleaseFrame();
		}
	}

}