#pragma once

#include "AppEngine/Core.h"
#include "App/OpenCV/ImageOperation.h"

class ImageOperationStack {

public:
   ImageOperationStack() : m_OpCount(0){}
   ~ImageOperationStack() {}

   int PushOperation(ImageOperation* operation) {
      LOG_INFO("Push image operation {} to operation stack", operation->GetName());
      m_Operations.push_back(operation);
      return ++m_OpCount;
   }

   void PopOperation(u_int32_t opId) {
      auto it = std::find(m_Operations.begin(), m_Operations.end(), operation);
      if (it != m_Operations.end()){
         LOG_INFO("Pop image operation {} from operation stack", operation->GetName());
         m_Operations.erase(it);
         --m_OpCount;
      }
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
   u_int32_t m_OpCount;
};