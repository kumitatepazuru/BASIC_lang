#pragma once

inline auto get_file_name(const char* s)
{
  auto i = strlen(s) - 1;
  while( s[i] != '\\' && s[i] != '/' ) i--;
  return s + i + 1;
}

template <class T, class F, class... Args>
int find_vector(std::vector<T>& vec, F compare, Args ...args)
{
  for( int i = 0; i < vec.size(); i++ )
    if( compare(vec[i], args...) )
      return i;

  return -1;
}

template <class... Args>
std::string format(std::string const& fmt, Args... args)
{
  char buf[1000];
  sprintf(buf, fmt.c_str(), args...);
  return buf;
}

#if _DEBUG_BUILD_
  #define  alart  fprintf(stderr,"\t%s:%d\n",get_file_name(__FILE__),__LINE__)
#else
  #define alart
#endif

