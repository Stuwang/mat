#include <iostream>

#include "Value.h"

int main(){
  {
	  mat::Value value;
	  value.SetInt32(12);
	  std::cout << value.GetInt32() << std::endl;

	  value.SetString("hahahhah");
	  mat::Value b = value;
      std::cout << "fuck!!" << std::endl;
	  std::cout << value.GetString() << std::endl; 
  }
  std::cout << "fuck!!" << std::endl;
  
  mat::Array arr;
  arr.push_back(mat::Value(1));
  arr.push_back(mat::Value("111111111111111"));
  for(auto it: arr){
	auto i = &it;
	if(i->IsInt32()){
		std::cout << i->GetInt32() << std::endl;
	}else if(i->IsString()){
		std::cout << i->GetString() << std::endl;
	}else{
		std::cout << "other type !" << std::endl;
	}
  }
}
