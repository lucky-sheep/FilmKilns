/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef HWVC_ANDROID_ALVEC4_H
#define HWVC_ANDROID_ALVEC4_H

#include "Object.h"
#include "AlMatrix.h"

al_class(AlVec4) {
public:
    AlVec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);

    AlVec4(const AlVec4 &o);

    virtual ~AlVec4();

    /// 设置向量下标对应的值
    /// \param i 下标，0为x，1为y，以此类推
    /// \param val 值
    void set(int32_t i, float val);

    /// 向量于矩阵相乘
    /// \param mat 矩阵
    /// \param pre 前乘或后乘，默认false表示后乘
    void multiply(AlMatrix mat, bool pre = false);

    void dump();
public:
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;
};


#endif //HWVC_ANDROID_ALVEC4_H
