#ifndef _MAT_DEFINE_H_
#define _MAT_DEFINE_H_

template<class T, int N>
inline char(&_ArraySizeHelper(T(&data)[N]))[N]{
  return static_cast<char(&)[N]>(0x80);
};

#define ARRAY_SIZE(arr)\
  sizeof(_ArraySizeHelper(arr))

template<class T>
void DoZero(T* const data){
  memset(data, sizeof(T), 0);
}

template<class T, int N>
void DoZero(T(&arr)[N]){
  memset(&arr, N*sizeof(T), 0);
}

template<class T,int dst_size, int src_size>
void DoCopy(T(&dst)[dst_size], const T(&src)[src_size]){
  static_assert(dst_size >= src_size, "dst_size must large or equal than src_size");
  memcpy(static_cast<void*>(&dst), 
    static_cast<const void*>(&src), sizeof(T)*src_size);
}

#endif
