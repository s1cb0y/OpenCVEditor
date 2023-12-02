#pragma once
#include "App/OpenCV/OpenCVImage.h"
#include "App/OpenCV/ImageOperation.h"

class OpenCVFilters{
public:

   static void GaussianBlur(CVImage *image, int size){
      if (image)         
         cv::GaussianBlur(image->GetSrcData(), image->GetDestData(), cv::Size(size, size), 0);
   }
};

class GaussianBlurFilter : public ImageOperation{
public:
   GaussianBlurFilter( uint8_t size, double sigmaX, double sigmaY = 0, cv::BorderTypes borderType = cv::BORDER_DEFAULT) 
   : m_Size(size), m_SigmaX(sigmaX), m_SigmaY(sigmaY), m_BorderType(borderType){
   }

private:
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

   virtual void Process(CVImage* image) override {
      if (image)
         cv::GaussianBlur(image->GetSrcData(), image->GetDestData(), cv::Size(m_Size, m_Size), m_SigmaX, m_SigmaY, m_BorderType);
   }

private:
   uint8_t m_Size;
   double m_SigmaX;
   double m_SigmaY;
   cv::BorderTypes m_BorderType;
};

