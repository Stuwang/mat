#include <iostream>

#include "Value.h"

void TestValue(){

#define TEST_M(type,flag)\
  do{\
    type i = __LINE__; \
    mat::Value v(i); \
    assert(v.Is##flag()); \
    v.Set##flag(i + 1); \
    assert(v.Get##flag() == i + 1); \
    mat::Value v2 = v; \
    assert(v2.Is##flag()); \
    assert(v2.Get##flag() == i+1); \
    mat::Value v3; \
    v3 = v2;\
    assert(v3.Is##flag()); \
    assert(v3.Get##flag() == i+1); \
  } while ( 0 );

  try{
    TEST_M(float, Float);
    TEST_M(double, Double);

    TEST_M(int8_t, Int8);
    TEST_M(int16_t, Int16);
    TEST_M(int32_t, Int32);
    TEST_M(int64_t, Int64);
    TEST_M(uint8_t, Uint8);
    TEST_M(uint16_t, Uint16);
    TEST_M(uint32_t, Uint32);
    TEST_M(uint64_t, Uint64);

    do
    {
      mat::Value v("bbb");
      assert(v.GetString() == "bbb");
      v.SetString("aaa");
      assert(v.GetString() == "aaa");
      assert(v.IsString());
    } while ( 0 );

    std::cout << "ok , " << std::endl;
  } catch ( mat::TypeExecption e ){
    std::cout << e.Message() << std::endl;
  }

#undef TEST_M

}

int main(){
  {
    
  }
  std::cout << "fuck!!" << std::endl;

  mat::Array arr;
  uint32_t i = 0;
  auto tmp = mat::Value(i);
  arr.push_back(tmp);
  arr.push_back(mat::Value("why"));
  for ( auto it : arr ){
    auto i = &it;
    if ( i->IsUint32() ){
      std::cout << i->GetUint32() << std::endl;
    } else if ( i->IsString() ){
      std::cout << i->GetString() << std::endl;
    } else{
      std::cout << "other type !" << std::endl;
    }
  }

  TestValue();
  getchar();
}
