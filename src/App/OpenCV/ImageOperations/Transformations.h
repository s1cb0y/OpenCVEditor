#pragma once

#include "App/OpenCV/OpenCVImage.h"
#include "App/OpenCV/ImageOperations/ImageOperation.h"


class FlipTransformation : public ImageOperation{
public:

   enum FLIP_MODE {
      X_AXIS = 0,
      Y_AXIS,
      XY_AXIS
   };

   FlipTransformation( FlipTransformation::FLIP_MODE flipMode) 
   : m_FlipMode(flipMode){}

   ~FlipTransformation(){}

   virtual OperationType GetOperationType() const override {
      return OperationType::Transformation;
   }
   
   virtual const char* GetName() const override {
      return "FlipTransformation";
   }
   virtual OperationCategory GetOperationCategory() const override {
      return OperationCategory::OperationCategoryReversible;
   }
   virtual std::string ToString() const override { 
      std::stringstream ss;
      ss << "FlipTransformation" << ", Mode: " << m_FlipMode;
      return ss.str();
   }

   virtual bool Process(CVImage* image) override {
      if (image)
            cv::flip(image->GetProcessedData(), image->GetProcessedData(), m_FlipMode);
      return true;  
   }

private:
   FlipTransformation::FLIP_MODE m_FlipMode;
};

