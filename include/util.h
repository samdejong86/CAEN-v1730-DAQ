#include <sys/time.h>
#include <pthread.h>
#include <vector>
#include <string>

using namespace std;

#ifndef UTIL_h
#define UTIL_h

class util{

 public:
  
  static long get_time(){
    long time_ms;
    struct timeval t1;
    gettimeofday(&t1, NULL);
    time_ms = (t1.tv_sec) * 1000 + t1.tv_usec / 1000;
    return time_ms;
  }
  
  static double markTime() {
    struct timeval timeMark;
    gettimeofday(&timeMark,NULL);
    return (double)timeMark.tv_sec + (double)timeMark.tv_usec/1000000.; 
  }
  
  
  static vector<string> split(const char *str, char c = ' ')
    {
      vector<string> result;
      
      do
	{
	  const char *begin = str;
	  
	  while(*str != c && *str)
            str++;
	  
	  result.push_back(string(begin, str));
	} while (0 != *str++);
      
      return result;
    }

};

#endif
