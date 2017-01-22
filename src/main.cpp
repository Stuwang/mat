#include <iostream>

#include "Value.h"

std::ostream& operator << (std::ostream& os, const mat::Value& v){
  switch ( v.GetFlag() )
  {
#define V_F(flag)\
  case mat::ValueFlag::flag:\
  os << v.Get##flag(); \
  break

    V_F(Float);
    V_F(Double);

    V_F(Int8);
    V_F(Int16);
    V_F(Int32);
    V_F(Int64);
    V_F(Uint8);
    V_F(Uint16);
    V_F(Uint32);
    V_F(Uint64);

#undef V_F
  case mat::ValueFlag::String:
  os << v.GetString();
  break;
  case mat::ValueFlag::Array:
  os << "Array ";
  break;
  case mat::ValueFlag::Object:
  os << "Object ";
  break;
  default:
  assert(0);
  }
  return os;
}

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

    do{
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

void TestArray(){
  mat::Array arr;
  uint32_t i = 0;
  auto tmp = mat::Value(i);
  arr.push_back(tmp);
  arr.push_back(mat::Value("why"));
  for ( auto &it : arr ){
    //auto i = &it;
    //if ( i->IsUint32() ){
    //  std::cout << i->GetUint32() << std::endl;
    //} else if ( i->IsString() ){
    //  std::cout << i->GetString() << std::endl;
    //} else{
    //  std::cout << "other type !" << std::endl;
    //}
    std::cout << it << std::endl;
  }

  assert(arr.size() == 2);
  mat::Array arr2;
  arr2 = arr;
  assert(arr2.size() == 2);
  mat::Array arr3(arr2);
}

void TestObject(){
  mat::Object obj;
  obj["a"] = mat::Value(1);
  obj["b"] = mat::Value(1.1);
  obj["c"] = mat::Value("string");
  for ( auto &i : obj )
  {
    std::cout
      << "name " << i.first
      << " type " << mat::FlagStr(i.second.GetFlag())
      << " Value " << i.second
      << std::endl;
  }
}

int main(){
  TestArray();
  std::cout << "==============美丽的分割线=============" << std::endl;
  TestValue();
  std::cout << "==============美丽的分割线=============" << std::endl;
  TestObject();
  std::cout << "==============美丽的分割线=============" << std::endl;
  getchar();
}
