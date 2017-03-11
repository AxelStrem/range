# range container emulator for c++

      for(int i : range<int>(10, 45))  
      {
         //...
      }

      auto v = range<int>(-20,20).convert<std::vector<int>>();
      
Hopefully c++17 would allow skipping the `<int>` part in `range<int>`.    
