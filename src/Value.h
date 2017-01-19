#ifndef MAT_VALUE_H_
#define MAT_VALUE_H_

#include <stdint.h>

#include <cstring>
#include <string>
#include <vector>
#include <map>

#include <cassert>
#include <type_traits>

#include "define.h"

namespace mat
{

  template<int t1, int t2, int...args>
  struct MaxOf{
    static const int value = t1 > t2 ?
    MaxOf<t1, args...>::value :
    MaxOf<t2, args...>::value
    ;
  };

  template<int t1, int t2>
  struct MaxOf<t1, t2>{
    static const int value = t1 > t2 ?
  t1 : t2;
  };

  class TypeExecption{
  public:
    explicit TypeExecption(const char* data = "unknow error ")
      :msg_(data){};
    std::string Message()const {
      return msg_;
    }
    std::string msg_;
  };

  class Value;

  class Object{
  public:
    Object(){

    };

    ~Object(){};

    Value& operator[](const std::string & name) {
      return data_[name];
    };

    const Value& operator[](const std::string & name) const {
      return const_cast<Object*>(this)->data_[name];
    };

    Value& at(const std::string & name) {
      return data_.at(name);
    };

    const Value& at(const std::string & name) const {
      return data_.at(name);
    };

    void erase(const std::string & name){
      data_.erase(name);
    }

    // void AddField(const std::string &name, const Value& value){
    //   data_.insert(name,value);
    // }


  private:
    std::map<std::string, Value> data_;
  };

  class Array {
  public:
    typedef Value value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    //struct iterator{

    //};

    typedef std::vector<Value>::iterator iterator;
    typedef std::vector<Value>::const_iterator const_iterator;

    Array(){};
    Array(std::size_t size){};
    ~Array(){};
    iterator begin(){ return data_.begin(); };
    //iterator end(){ return begin() + data_.size(); };
    iterator end(){ return data_.end(); };
    const_iterator cbegin()const{ return (data_.cbegin()); };
    const_iterator cend() const{ return (data_.cend()); };

    void push_back(const Value& value){ data_.push_back(value); };
    // iterator erase(iterator i){
    //   int len = i - begin();
    //   return &*(data_.erase(data_.cbegin() + len));
    // };
  private:
    std::vector<Value> data_;
  };



  enum class ValueFlag :int {
    None = 0,
    Float,
    Double,
    Int8,
    Uint8,
    Int16,
    Uint16,
    Int32,
    Uint32,
    Int64,
    Uint64,
    String,
    Array,
    Object
  };

  static const char* FlagStr(ValueFlag f){
    int value = static_cast<int>(f);
    const char* typemsg[] = {
      "None",
      "Float",
      "Double",
      "Int8",
      "Uint8",
      "Int16",
      "Uint16",
      "Int32",
      "Uint32",
      "Int64",
      "Uint64"
    };
    assert(value < ARRAY_SIZE(typemsg));
    return typemsg[value];
  };

  class Value {
  public:
    explicit Value(std::nullptr_t = nullptr){ SetFlag(ValueFlag::None); };
    explicit Value(float value){ SetFlag(ValueFlag::Float); Set(value); };
    explicit Value(double value){ SetFlag(ValueFlag::Double); Set(value); };
    explicit Value(int32_t value){ SetFlag(ValueFlag::Int32); Set(value); };
    explicit Value(uint32_t value){ SetFlag(ValueFlag::Uint32); Set(value); };
    explicit Value(int64_t value){ SetFlag(ValueFlag::Int64); Set(value); };
    explicit Value(uint64_t value){ SetFlag(ValueFlag::Uint64); Set(value); };
    explicit Value(int16_t value){ SetFlag(ValueFlag::Int16); Set(value); };
    explicit Value(uint16_t value){ SetFlag(ValueFlag::Uint16); Set(value); };
    explicit Value(int8_t value){ SetFlag(ValueFlag::Int8); Set(value); };
    explicit Value(uint8_t value){ SetFlag(ValueFlag::Uint8); Set(value); };
    explicit Value(const std::string& value){ SetFlag(ValueFlag::None); SetString(value); };
    explicit Value(const Array& arr){ SetArray(arr); };
    explicit Value(const Object& obj){ SetObject(obj); };

    bool IsDouble() const{ return flag_ == ValueFlag::Double; };
    bool IsFloat() const{ return flag_ == ValueFlag::Float; };
    bool IsInt64() const{ return flag_ == ValueFlag::Int64; };
    bool IsUint64() const{ return flag_ == ValueFlag::Uint64; };
    bool IsInt32() const{ return flag_ == ValueFlag::Int32; };
    bool IsUint32() const{ return flag_ == ValueFlag::Uint32; };
    bool IsInt16() const{ return flag_ == ValueFlag::Int16; };
    bool IsUint16() const{ return flag_ == ValueFlag::Uint16; };
    bool IsInt8() const{ return flag_ == ValueFlag::Int8; };
    bool IsUint8() const{ return flag_ == ValueFlag::Uint8; };
    bool IsArray() const{ return flag_ == ValueFlag::Array; };
    bool IsObject() const { return flag_ == ValueFlag::Object; };
    bool IsString() const { return flag_ == ValueFlag::String; };

    bool IsNumeric() const{
      return IsFloat() || IsDouble() ||
        IsInt16() || IsUint16() ||
        IsInt8() || IsUint8() ||
        IsInt32() || IsUint32() ||
        IsInt64() || IsUint64();
    };

#ifndef DEFINE_GET
//#define DEFINE_GET(type,flag)   \
//  type Get##flag() const {\
//    if ( flag_ != ValueFlag::flag ){\
//      std::string err = std::string() + " execept "#type" but " + FlagStr(flag_); \
//      throw TypeExecption(err.c_str()); \
//    }\
//    return *reinterpret_cast<type*>(const_cast<unsigned char*>(data_)); \
//  };

#define DEFINE_GET(type,flag)   \
  type Get##flag() const {\
    if ( flag_ != ValueFlag::flag ){ \
      std::string err = std::string() + " execept "#type" but " + FlagStr(flag_); \
      throw TypeExecption(err.c_str()); \
    }\
    return Get<type>(); \
  };
#else
# error "has defined DEFINE_GET,will error"
#endif

    DEFINE_GET(float, Float);
    DEFINE_GET(double, Double);

    DEFINE_GET(int8_t, Int8);
    DEFINE_GET(int16_t, Int16);
    DEFINE_GET(int32_t, Int32);
    DEFINE_GET(int64_t, Int64);
    DEFINE_GET(uint8_t, Uint8);
    DEFINE_GET(uint16_t, Uint16);
    DEFINE_GET(uint32_t, Uint32);
    DEFINE_GET(uint64_t, Uint64);

#undef DEFINE_GET

    const std::string& GetString() const {
      if ( flag_ != ValueFlag::String ){
        throw TypeExecption("Not a String");
      }
      return static_cast<const Value*>(this)->Get<std::string>();
    }
    std::string& GetString(){
      if ( flag_ != ValueFlag::String ){
        throw TypeExecption("Not a String");
      }
      return this->Get<std::string>();
    }


    const Array& GetArray()const {
      if ( flag_ != ValueFlag::String ){
        throw TypeExecption("Not a Array");
      }
      return Get<Array>();
    }
    Array& GetArray(){
      if ( flag_ != ValueFlag::String ){
        throw TypeExecption("Not a Array");
      }
      return Get<Array>();
    }

    const Object& GetObject()const{
      if ( flag_ != ValueFlag::String ){
        throw TypeExecption("Not a Object");
      }
      return Get<Object>();
    }
    Object& GetObject(){
      if ( flag_ != ValueFlag::String ){
        throw TypeExecption("Not a Object");
      }
      return Get<Object>();
    }

#define DEFINE_SET(type,flag)\
  void Set##flag(type value){\
    Clear(); \
    SetFlag(ValueFlag::flag); \
    Set<type>(value); \
  };

    DEFINE_SET(float, Float);
    DEFINE_SET(double, Double);

    DEFINE_SET(int8_t, Int8);
    DEFINE_SET(int16_t, Int16);
    DEFINE_SET(int32_t, Int32);
    DEFINE_SET(int64_t, Int64);
    DEFINE_SET(uint8_t, Uint8);
    DEFINE_SET(uint16_t, Uint16);
    DEFINE_SET(uint32_t, Uint32);
    DEFINE_SET(uint64_t, Uint64);

#undef DEFINE_SET

    void SetString(const std::string& value){
      Clear();
      new (&Get<std::string>()) std::string();
      this->Get<std::string>() = value;
      SetFlag(ValueFlag::String);
    }

    void SetObject(const Object& obj){
      Clear();
      this->Get<Object*>() = new Object(obj);
    }

    void SetArray(const Array& arr){
      Clear();
      this->Get<Array*>() = new Array(arr);
    }

    void Clear(){
      typedef std::string StringType;
      switch ( flag_ )
      {
      case ValueFlag::Array:
      {
                             Array* p = *reinterpret_cast<Array**>(data_);
                             p->~Array();
                             delete p;
      }
      break;
      case ValueFlag::Object:
      {
                              Object * obj = *reinterpret_cast<Object**>(data_);
                              obj->~Object();
                              delete obj;
      }
      break;
      case ValueFlag::String:
      {
                              std::string * str = reinterpret_cast<std::string*>(data_);
                              //std::cout << *str << std::endl;
                              str->~StringType();
                              //std::_Destroy(reinterpret_cast<std::string&>(data_));
      }
      break;
      default:
      break;
      }
      flag_ = ValueFlag::None;
    };

    Value(const Value& v){
      switch ( v.flag_ )
      {
      case ValueFlag::Array:
      SetArray(v.GetArray());
      break;
      case ValueFlag::Object:
      SetObject(v.GetObject());
      break;
      case ValueFlag::String:
      SetString(v.GetString());
      break;
      default:
      DoCopy(data_, v.data_);
      break;
      }
      this->flag_ = v.flag_;
    };

    Value& operator=(const Value& v){
      this->Clear();
      switch ( v.flag_ )
      {
      case ValueFlag::Array:
      SetArray(v.GetArray());
      break;
      case ValueFlag::Object:
      SetObject(v.GetObject());
      break;
      case ValueFlag::String:
      SetString(v.GetString());
      break;
      default:
      DoCopy(data_, v.data_);
      break;
      }
      this->flag_ = v.flag_;
      return *this;
    };

    ~Value(){
      Clear();
    }

  private:
    template<class T>
    T& Get(){
      return *reinterpret_cast<T*>(data_);
    };

    template<class T>
    const T& Get() const {
      return *reinterpret_cast<const T*>(data_);
    };

    template<class T>
    void Set(T value){
      Get<T>() = value;
    };

    void SetFlag(ValueFlag f){
      flag_ = f;
    }

    ValueFlag flag_;

    static const int m_size = MaxOf<
      sizeof(uint64_t),
      sizeof(std::string),
      sizeof(Object*),
      sizeof(Array*)
    >::value;
    unsigned char data_[m_size];
  };

};

#endif
