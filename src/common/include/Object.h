/*
 * Copyright (c) 2018-present, lmyooyo@gmail.com.
 *
 * This source code is licensed under the GPL license found in the
 * LICENSE file in the root directory of this source tree.
 */
#ifndef HARDWAREVIDEOCODEC_OBJECT_H
#define HARDWAREVIDEOCODEC_OBJECT_H

#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;

#define al_class_ex(cls, parent) \
class cls : public parent \

#define al_class(cls) al_class_ex(cls, Object)

#define al_interface(cls) \
class cls : public Object \


class Object {
public:
    Object();

    virtual ~Object();

    virtual std::string toString();
};


#endif //HARDWAREVIDEOCODEC_OBJECT_H
