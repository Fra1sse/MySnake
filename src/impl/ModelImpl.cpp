// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "impl/ModelImpl.h"
/*
namespace
{
constexpr unsigned short VENDOR_ID = 0x048d;
constexpr unsigned short PRODUCT_ID = 0x6006;

constexpr unsigned char GET_EFFECT_BYTE = static_cast<unsigned char>(0x88);

constexpr unsigned REPORT_LENGTH = 9;
}

namespace ErrorMsg
{
constexpr const char* ChipError = "ErrorMsg: something is wrong with the chip";
}

static inline void logAndThrowRuntimeErr(hid_device* dev)
{
	std::wcerr << hid_error(dev) << '\n'; // todo: make error/log file
	throw std::runtime_error(ErrorMsg::ChipError);
}

static inline void checkReportError(int res, hid_device* dev)
{
	if (res == -1)
	{
		logAndThrowRuntimeErr(dev);
	}
}

static inline void init()
{
	const int res = hid_init();
	checkReportError(res, nullptr);
}

static inline void getSettings(hid_device* dev, unsigned char* buf)
{
	assert(dev);
	buf[0] = GET_EFFECT_BYTE;
	int res = hid_send_feature_report(dev, buf, REPORT_LENGTH);
	checkReportError(res, dev);

	buf[0] = 0;
	res = hid_get_feature_report(dev, buf, REPORT_LENGTH);
	checkReportError(res, dev);
}

static hid_device* openDevice()
{
	auto dev = hid_open(VENDOR_ID, PRODUCT_ID, nullptr);
	if (!dev)
	{
		logAndThrowRuntimeErr(nullptr);
	}
	return dev;
}
*/
ModelImpl::ModelImpl()
{
    tailX = static_cast<int*>(calloc(441, sizeof(int)));
    tailY = static_cast<int*>(calloc(441, sizeof(int)));

}
/*
hid_device* ModelImpl::getChipHandler()
{
	return ModelImpl::_dev;
}

int ModelImpl::getBrightness()
{
	return ModelImpl::_brightness;
}*/

ModelImpl::~ModelImpl()
{
    free(tailX);
    free(tailY);
}

void ModelImpl::SetInputDirection(sides direction) {
    dir = direction;
}
