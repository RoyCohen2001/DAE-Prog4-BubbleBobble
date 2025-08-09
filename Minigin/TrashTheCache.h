#pragma once  
#include <chrono>  
#include <vector>  

namespace ttc {  
   struct Transform  
   {  
       float matrix[16] = {  
           1,0,0,0,  
           0,1,0,0,  
           0,0,1,0,  
           0,0,0,1 };  
   };  

   class GameObject {  
   public:
       Transform local;  
       int id;  
   };  

   class GameObjectAlt {
   public:
	   Transform* local;
	   int id;
   };

   class TrashTheCache  
   {  
   public:  
       void RunIntegerBenchmark();  
       void RunGameObjectBenchmark();  
       void RunGameObjectAltBenchmark();  

       const std::vector<float>& GetIntegerTimes() const { return integerTimes; }  
       const std::vector<float>& GetGameObjectTimes() const { return gameObjectTimes; }  
       const std::vector<float>& GetGameObjectAltTimes() const { return gameObjectAltTimes; }  
   private:  
       std::vector<float> stepSizes;  
       std::vector<float> integerTimes;  
       std::vector<float> gameObjectTimes;  
       std::vector<float> gameObjectAltTimes;  

       const size_t m_BufferSize{ 1 << 26 }; // 2^26 = 67,108,864 integers  
   };  
}
