#ifndef _MAT_DEFINE_H_
#define _MAT_DEFINE_H_

template<class T, int N>
char(&_ArraySizeHelper(T(&data)[N]))[N]{
  return static_cast<char(&)[N]>(0x80);
};

#define ARRAY_SIZE(arr)\
  sizeof(_ArraySizeHelper(arr))


#endif
