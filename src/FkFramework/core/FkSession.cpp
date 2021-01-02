/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkSession.h"

FkSession::FkSession() : FkObject() {

}

FkSession::~FkSession() {
    close();
}

FkResult FkSession::connectTo(const std::shared_ptr<FkQuark> quark) {
    std::lock_guard<std::mutex> guard(mtx);
    if (FkSession::kState::IDL != state) {
        FkLogW(FK_DEF_TAG, "Invalid state");
        return FK_INVALID_STATE;
    }
    if (nullptr == quark) {
        return FK_FAIL;
    }
    if (FK_OK == quark->accept(templateProtocol)) {
        link.emplace_back(quark);
        return FK_OK;
    }
    return FK_FAIL;
}

FkResult FkSession::disconnect(const std::shared_ptr<FkQuark> quark) {
    std::lock_guard<std::mutex> guard(mtx);
    if (FkSession::kState::IDL != state) {
        FkLogW(FK_DEF_TAG, "Invalid state");
        return FK_INVALID_STATE;
    }
    if (nullptr == quark) {
        return FK_FAIL;
    }
    auto itr = link.begin();
    while (link.end() != itr) {
        if ((*itr) == quark) {
            FkLogI(FK_DEF_TAG, "Disconnect quark %p", (void *) quark.get());
            link.erase(itr);
            return FK_OK;
        }
        ++itr;
    }
    return FK_FAIL;
}

FkResult FkSession::open() {
    std::lock_guard<std::mutex> guard(mtx);
    if (FkSession::kState::IDL != state) {
        FkLogW(FK_DEF_TAG, "Invalid state");
        return FK_INVALID_STATE;
    }
    state = FkSession::kState::OPENED;
    return FK_OK;
}

FkResult FkSession::close() {
    std::lock_guard<std::mutex> guard(mtx);
    if (FkSession::kState::OPENED != state) {
        FkLogW(FK_DEF_TAG, "Invalid state");
        return FK_INVALID_STATE;
    }
    link.clear();
    state = FkSession::kState::IDL;
    return FK_OK;
}

FkResult FkSession::send(std::shared_ptr<FkProtocol> protocol) {
    FkResult ret = FK_OK;
    for (auto &it : link) {
        if (FK_OK != it->dispatch(protocol)) {
            ret = FK_FAIL;
        }
    }
    return ret;
}
