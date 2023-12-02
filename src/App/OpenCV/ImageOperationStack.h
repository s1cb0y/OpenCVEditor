#pragma once

#include "AppEngine/Core.h"
#include "App/OpenCV/ImageOperation.h"

class ImageOperationStack {

public:
   ImageOperationStack(){}
   ~ImageOperationStack() {}

   void PushOperation(ImageOperation* operation) {
      LOG_INFO("Push image operation {} to operation stack", operation->GetName());
      m_Operations.push_back(operation);
   }

   void PopOperation(ImageOperation* operation) {
      LOG_INFO("Pop image operation {} to operation stack", operation->GetName());
      auto it = std::find(m_Operations.begin(), m_Operations.end(), operation);
      if (it != m_Operations.end()) 
         m_Operations.erase(it);
   }

   bool ProcessImage(CVImage* image) {
      bool success = true;
      for (auto operation : m_Operations){
         success &= operation->Process(image);
      }
      return success;
   }

private:
   std::vector<ImageOperation*> m_Operations;
};