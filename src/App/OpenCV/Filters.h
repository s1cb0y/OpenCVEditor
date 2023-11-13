#pragma once
#include "App/OpenCV/OpenCVImage.h"

class OpenCVFilters{
public:

   static void GaussianBlur(CVImage *image, int size){
      if (image)
         cv::GaussianBlur(image->GetSrcData(), image->GetDestData(), cv::Size(size, size), 0);
   }
};