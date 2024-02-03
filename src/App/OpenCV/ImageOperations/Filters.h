#pragma once

#include "App/OpenCV/OpenCVImage.h"
#include "App/OpenCV/ImageOperations/ImageOperation.h"


class GaussianBlurFilter : public ImageOperation{

public:
   GaussianBlurFilter( uint8_t size, double sigmaX, double sigmaY = 0, cv::BorderTypes borderType = cv::BORDER_DEFAULT) 
   : m_Size(size), m_SigmaX(sigmaX), m_SigmaY(sigmaY), m_BorderType(borderType){}

   ~GaussianBlurFilter(){}

   virtual OperationType GetOperationType() const override {
      return OperationType::Filter;
   }
   
   virtual const char* GetName() const override {
      return "GaussianBlur";
   }
   virtual OperationCategory GetOperationCategory() const override {
      return OperationCategory::OperationCategoryIrreversible;
   }
   virtual std::string ToString() const override { 
      std::stringstream ss;
      ss << "GaussianBlur" << ", Kernelsize: " << m_Size << ", sigmaX: " << m_SigmaX << ", sigmaY: " << m_SigmaY
         << "border type: "<< m_BorderType;
      return ss.str();
   }

   virtual bool Process(CVImage* image) override {
      bool success = false;
      if (image)
         if (m_Size % 2){
            cv::GaussianBlur(image->GetProcessedData(), image->GetProcessedData(), cv::Size(m_Size, m_Size), m_SigmaX, m_SigmaY, m_BorderType);
            success = true;;
         } else {
            LOG_ERROR("GaussianBlurFilter: Please select an odd kernel size for gaussian blur filter");
         }
      return success;  
   }

private:
   uint8_t m_Size;
   double m_SigmaX;
   double m_SigmaY;
   cv::BorderTypes m_BorderType;
};

