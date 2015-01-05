/**
 * @file    DanmakuIterator.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-01
 */

#include <mutex>
#include "Danmakus.hpp"

using DanmakuIter = PCDanmakuFlameMaster::model::Danmakus::DanmakuIterator;

namespace PCDanmakuFlameMaster {
namespace model {

    DanmakuIter::DanmakuIterator(DanmakuSet& datas) : mData(&datas) {
        // do nothing
    }

    void DanmakuIter::reset() {
        mMutex.lock();
        
        if (mData != nullptr && mData->size() > 0) {
            iter = mData->begin();
        } else {
            
        }

        mMutex.unlock();
    }

    void DanmakuIter::setDatas(DanmakuSet& datas) {
        mMutex.lock();

        if (mData != &datas) {
            mIteratorUsed = false;
            mData = &datas;
        }

        mMutex.unlock();
    }

    BaseDanmaku& DanmakuIter::next() {
        mMutex.lock();

        mIteratorUsed = true;
        ++iter;

        mMutex.unlock();
        return const_cast<BaseDanmaku&>(*iter);
    }

    bool DanmakuIter::hasNext() {
        mMutex.lock();
        
        bool result = (iter != mData->end());

        mMutex.unlock();
        return result;
    }

    void DanmakuIter::remove() {
        mMutex.lock();

        mIteratorUsed = true;
        mData->erase(iter);
        
        mMutex.unlock();
    }

}
}
