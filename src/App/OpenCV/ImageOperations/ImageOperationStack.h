#pragma once

#include "AppEngine/Core.h"
#include "App/OpenCV/ImageOperations/ImageOperation.h"
#include "App/OpenCV/OpenCVImage.h"

class ImageOperationStack {

public:
   ImageOperationStack() : m_OpCount(0), m_Image(nullptr){}
   ~ImageOperationStack() {}

   void SetImage(CVImage* image){
      m_Image = image;
   }

   int PushOperation(ImageOperation* operation) {
      LOG_INFO("Push image operation {} to operation stack", operation->GetName());
      m_Operations.push_back(operation);
      ProcessImage();
      return ++m_OpCount;
   }

   void PopOperation(u_int32_t opId) {
      if (m_OpCount > 0){
         LOG_INFO("Pop image operation {} from operation stack", m_Operations[opId - 1]->GetName());      
         m_Operations.erase(m_Operations.begin() + opId - 1);
         if (m_Image)
            m_Image->Reset();
         ProcessImage();
         m_OpCount--;
      }
      
   }


private:
   bool ProcessImage() {
      bool success = true;      
      if (m_Image){
         for (auto operation : m_Operations){            
            if (false == operation->Process(m_Image)){
               LOG_ERROR("Could not execute image processing operation: {}", operation->GetName());
            }
         }
      } else {
         LOG_WARNING("Try to process image although image is NULL");
      }
      if (success == false)
         LOG_ERROR("Could not process image successfully!");
      return success;
   }

   std::vector<ImageOperation*> m_Operations;
   u_int32_t m_OpCount;
   CVImage* m_Image;
};