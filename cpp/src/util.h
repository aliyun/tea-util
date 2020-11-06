//
// Created by Axios on 2020/11/6.
//

#ifndef DARABONBA_UTIL_SRC_UTIL_H
#define DARABONBA_UTIL_SRC_UTIL_H

#include <memory>
#include <boost/any.hpp>

using namespace std;

template<typename T>
shared_ptr<T> cast_any(boost::any value) {
  if (typeid(shared_ptr<void>) == value.type()) {
    shared_ptr<void> v = boost::any_cast<shared_ptr<void>>(value);
    return static_pointer_cast<T>(v);
  } else if (typeid(shared_ptr<T>) == value.type()) {
    return boost::any_cast<shared_ptr<T>>(value);
  }
  return nullptr;
}

#endif //DARABONBA_UTIL_SRC_UTIL_H
