#include <iostream>

#include "Value.h"

int main(){
  mat::Value value;
  value.SetInt32(12);
  std::cout << value.GetInt32() << std::endl;
/*
  mat::Array arr;
  arr.push_back(mat::Value(1));
  arr.push_back(mat::Value("111111111111111"));*/
}
