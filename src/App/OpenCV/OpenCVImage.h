#pragma once

#include "AppEngine/Core.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

class CVImage{
   bool scale = false;
public:
   CVImage(const std::string& path) : m_Window_width(0), m_Window_height(0), m_FilePath(path){      
      Load(path);
   }
   
   std::string& GetFilePath() {
      return m_FilePath;
   }
   
   void Render() {
      if (!m_ImageDataProcessed.empty()) {
         //Clear color and depth buffers
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         glMatrixMode(GL_MODELVIEW);     // Operate on model-view matrix
         if (scale)
            glScalef(1.0 / 2.0, 1.0 / 2.0, 1.0); 
         glEnable(GL_TEXTURE_2D);
         // combine original and processed image
         cv::Mat imgCombined;
         cv::hconcat( m_ImageData, m_ImageDataProcessed, imgCombined);
         GLuint image_tex = MatToTexture(imgCombined, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP);

         /* Draw a quad */
         glBegin(GL_QUADS);
         glTexCoord2d(0.0, 0.0); glVertex2d(-1.0, -1.0);
         glTexCoord2d(1.0, 0.0); glVertex2d(+1.0, -1.0);
         glTexCoord2d(1.0, 1.0); glVertex2d(+1.0, +1.0);
         glTexCoord2d(0.0, 1.0); glVertex2d(-1.0, +1.0);
         glEnd();

         glDeleteTextures(1, &image_tex);
         glDisable(GL_TEXTURE_2D);
         // cv::imshow("Picure", m_ImageData);
         // cv::waitKey(1);
      }
   }

   // reset to image data to the original 
   void Reset(){
      m_ImageDataProcessed = m_ImageData.clone();
   }

   // Gets the current (processed) image data
   cv::Mat& GetProcessedData() { return m_ImageDataProcessed;}

   // Gets the reference to the original image data
   cv::Mat& GetOriginalData() { return m_ImageData;}

   uint32_t GetWindowHeight() { return m_Window_height;}
   uint32_t GetWindowWidth() { return m_Window_width;}

private:
   // Load the images and stores it as cv::Mat
   bool Load(const std::string& path) {
      m_ImageData = cv::imread(path);
      if (!m_ImageData.empty()) {         
         m_ImageDataProcessed = m_ImageData.clone();
         m_Window_width = m_ImageData.cols * 2; // show original and processed
         m_Window_height = m_ImageData.rows;
         LOG_INFO(printf("Loading image (size %d : %d) succesful!\n", m_ImageData.cols , m_ImageData.rows));
         return true;
      }
      LOG_ERROR("Loading image failed!");
      return false;
   }

   // Function turn a cv::Mat into a texture, and return the texture ID as a GLuint for use
   GLuint MatToTexture(const cv::Mat &mat, GLenum minFilter, GLenum magFilter, GLenum wrapFilter) {
      // Generate a number for our textureID's unique handle
      GLuint textureID;
      glGenTextures(1, &textureID);

      // Bind to our texture handle
      glBindTexture(GL_TEXTURE_2D, textureID);

      // Catch silly-mistake texture interpolation method for magnification
      if (magFilter == GL_LINEAR_MIPMAP_LINEAR ||
         magFilter == GL_LINEAR_MIPMAP_NEAREST ||
         magFilter == GL_NEAREST_MIPMAP_LINEAR ||
         magFilter == GL_NEAREST_MIPMAP_NEAREST)
      {
         LOG_INFO("You can't use MIPMAPs for magnification - setting filter to GL_LINEAR");
         magFilter = GL_LINEAR;
      }

      // Set texture interpolation methods for minification and magnification
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

      // Set texture clamping method
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapFilter);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapFilter);

      // Set incoming texture format to:
      // GL_BGR       for CV_CAP_OPENNI_BGR_IMAGE,
      // GL_LUMINANCE for CV_CAP_OPENNI_DISPARITY_MAP,
      // Work out other mappings as required ( there's a list in comments in main() )
      GLenum inputColourFormat = GL_BGR;
      if (mat.channels() == 1)
      {
         inputColourFormat = GL_LUMINANCE;
      }

      // Create the texture
      glTexImage2D(GL_TEXTURE_2D,     // Type of texture
         0,                 // Pyramid level (for mip-mapping) - 0 is the top level
         GL_RGB,            // Internal colour format to convert to
         mat.cols,          // Image width  i.e. 640 for Kinect in standard mode
         mat.rows,          // Image height i.e. 480 for Kinect in standard mode
         0,                 // Border width in pixels (can either be 1 or 0)
         inputColourFormat, // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
         GL_UNSIGNED_BYTE,  // Image data type
         mat.ptr());        // The actual image data itself

      // If we're using mipmaps then generate them. Note: This requires OpenGL 3.0 or higher
      if (minFilter == GL_LINEAR_MIPMAP_LINEAR ||
         minFilter == GL_LINEAR_MIPMAP_NEAREST ||
         minFilter == GL_NEAREST_MIPMAP_LINEAR ||
         minFilter == GL_NEAREST_MIPMAP_NEAREST)
      {
         glGenerateMipmap(GL_TEXTURE_2D);
      }

      return textureID;
   }
   
private:
   cv::Mat m_ImageData;
   cv::Mat m_ImageDataProcessed;
   uint32_t m_Window_width;
   uint32_t m_Window_height;
   std::string m_FilePath;
};
