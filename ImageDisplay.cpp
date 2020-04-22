#include "ImageDisplay.h"

#include <iostream>

ImageDisplay::ImageDisplay(const std::string& windowName, unsigned int width, unsigned int height) :
#if DISPLAY_IMAGE
	image_(width, height, 1, 3, 0), display_(width, height, windowName.c_str())
#else 
	image_(width, height, 1, 3, 0)
#endif
{

}

ImageDisplay::~ImageDisplay() {
#if DISPLAY_IMAGE
	if (!display_.is_closed()) {
		display_.close();
	}
#endif
}

void ImageDisplay::set(int x, int y, const Colour& colour) {
	image_(x, y, 0, 0) = int(255 * colour.red);
	image_(x, y, 0, 1) = int(255 * colour.green);
	image_(x, y, 0, 2) = int(255 * colour.blue);
}

void ImageDisplay::refresh() {
#if DISPLAY_IMAGE
	display_.display(image_);
	display_.wait(5);
#endif
}

void ImageDisplay::save(const std::string& filename) const {
	image_.save(filename.c_str());
}

void ImageDisplay::pause(double seconds) {
#if DISPLAY_IMAGE
	display_.wait(int(seconds*1000));
#endif
}
