#pragma once

#include "AppEngine/Core.h"
#include "App/OpenCV/ImageOperation.h"

class ImageOperationStack {
public:
   ImageOperationStack(CVImage* image) : m_Image(image){}
   ~ImageOperationStack() {}

   void PushOperation(ImageOperation* operation) {
      m_Operations.push_back(operation);
      this->ProcessImage();
   }

   void PopOperation(ImageOperation* operation) {
      auto it = std::find(m_Operations.begin(), m_Operations.end(), operation);
      if (it != m_Operations.end()) 
         m_Operations.erase(operation);
      this->ProcessImage();
   }

private:
   
   void ProcessImage() {
      for (auto operation : m_Operations){
         operation->Process(m_Image);
      }
   }

private:
   CVImage* m_Image;
   std::vector<ImageOperation*> m_Operations;
};