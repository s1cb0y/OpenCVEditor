#pragma once
#include "AppEngine/Core.h"
#include <mutex>

// callback based observer pattern implementation
template <class T>
class Observable{
public:
   Observable(T v) : m_Var(v){}

   typedef std::function<void (T& value)> Tcallback;

   void Set(T v){
      m_mutex.lock();
      m_Var = v;
      notify();
      m_mutex.unlock();
   }
   
   void Subscribe(Tcallback func){
      m_subscribers.push_back(func);
   }
private:
   void notify(){
      for (auto f : m_subscribers){
         f(m_Var);
      }
   }   
private:
   T m_Var;
   std::vector<Tcallback> m_subscribers;
   std::mutex m_mutex;
};