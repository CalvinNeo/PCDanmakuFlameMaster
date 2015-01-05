/**
 * @file    Danmakus.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-01
 */

#ifndef _PCDFM_MODEL_DANMAKUS_HPP
#define _PCDFM_MODEL_DANMAKUS_HPP

#include <cstdint>
#include <set>
#include <mutex>
#include <string>
#include <memory>
#include "BaseDanmaku.hpp"

namespace PCDanmakuFlameMaster {
namespace model {

    typedef bool(*CompareFunction)(const BaseDanmaku&, const BaseDanmaku&);
    typedef std::set<BaseDanmaku, CompareFunction> DanmakuSet;

    class Danmakus {
    public:
        class DanmakuIterator {
        public:
            DanmakuIterator(DanmakuSet& datas);
            void reset();
            void setDatas(DanmakuSet& datas);
            BaseDanmaku& next();
            bool hasNext();
            void remove();
        private:
            DanmakuSet* mData = nullptr;
            DanmakuSet::iterator iter;
            bool mIteratorUsed = false;
        private:
            std::mutex mMutex;
        };
    public:
        Danmakus();
        Danmakus(int sortType);
        Danmakus(DanmakuSet& items);
        void setItems(DanmakuSet& items);
        DanmakuIterator iterator();
        bool addItem(BaseDanmaku& item);
        bool removeItem(BaseDanmaku& item);
        Danmakus subnew(time_t startTime, time_t endTime);
        Danmakus& sub(time_t startTime, time_t endTime);
        int size();
        void clear();
        BaseDanmaku& first();
        BaseDanmaku& last();
        bool contains(BaseDanmaku& item);
        bool isEmpty();
    private:
        DanmakuSet subset(time_t startTime, time_t endTime);
        BaseDanmaku createItem(const std::string& text);
    public:
        static const int ST_BY_TIME = 0;
        static const int ST_BY_YPOS = 1;
        static const int ST_BY_YPOS_DESC = 2;
        static const int ST_BY_LIST = 4;
    public:
        std::shared_ptr<DanmakuSet> items;
        std::mutex mutex;
    private:
        std::shared_ptr<Danmakus> subItems;
        std::shared_ptr<BaseDanmaku> startItem;
        std::shared_ptr<BaseDanmaku> endItem;
        std::shared_ptr<BaseDanmaku> endSubItem;
        std::shared_ptr<BaseDanmaku> startSubItem;
        std::shared_ptr<DanmakuIterator> iter;
        //int mSize = 0;
        int mSortType = ST_BY_TIME;
    };

}
}

#endif // _PCDFM_MODEL_DANMAKUS_HPP
