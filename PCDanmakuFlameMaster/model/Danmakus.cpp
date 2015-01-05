/**
 * @file    Danmakus.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-01
 */

#include <cstdint>
#include <set>
#include <memory>
#include <exception>
#include "BaseDanmaku.hpp"
#include "Danmaku.hpp"
#include "../utilities/DanmakuUtils.hpp"
#include "Danmakus.hpp"

using namespace PCDanmakuFlameMaster::util::DanmakuUtils;

namespace PCDanmakuFlameMaster {
namespace model {

    bool compareByTime(const BaseDanmaku& obj1, const BaseDanmaku& obj2);
    bool compareByYPos(const BaseDanmaku& obj1, const BaseDanmaku& obj2);
    bool compareByYPosDesc(const BaseDanmaku& obj1, const BaseDanmaku& obj2);

    Danmakus::Danmakus() {
        Danmakus(ST_BY_TIME);
    }

    Danmakus::Danmakus(int sortType) {
        CompareFunction cf = nullptr;

        if (sortType == ST_BY_TIME) {
            cf = compareByTime;
        } else if (sortType == ST_BY_YPOS) {
            cf = compareByYPos;
        } else if (sortType == ST_BY_YPOS_DESC) {
            cf = compareByYPosDesc;
        } else {
            throw std::exception("unsupported sortType");
        }

        items = std::make_shared<DanmakuSet>(cf);
        mSortType = sortType;
        iter = std::make_shared<DanmakuIterator>(*items);
    }

    Danmakus::Danmakus(DanmakuSet& items) {
        setItems(items);
    }

    void Danmakus::setItems(DanmakuSet& items) {
        this->items = std::make_shared<DanmakuSet>(items);
        
        if (iter == nullptr) {
            iter = std::make_shared<DanmakuIterator>(*this->items);
        } else {
            iter->setDatas(*this->items);
        }
    }

    Danmakus::DanmakuIterator Danmakus::iterator() {
        iter->reset();
        return *iter;
    }

    bool Danmakus::addItem(BaseDanmaku& item) {
        if (items != nullptr) {
            if (items->insert(item).second) {
                return true;
            }
        }
        return false;
    }

    bool Danmakus::removeItem(BaseDanmaku& item) {
        if (items == nullptr)
            return false;

        if (item.isOutside())
            item.setVisibility(false);

        items->erase(item);
        return true;
    }

    DanmakuSet Danmakus::subset(time_t startTime, time_t endTime) {
        if (items == nullptr || items->size() == 0) {
            //throw std::exception("items is NullPtr or has no elements");
            return *static_cast<DanmakuSet*>(nullptr);
        }

        //if (subItems == nullptr) {
        //    subItems = std::make_shared<Danmakus>();
        //}
        if (startSubItem == nullptr) {
            startSubItem = std::make_shared<BaseDanmaku>(createItem("start"));
        }
        if (endSubItem == nullptr) {
            endSubItem = std::make_shared<BaseDanmaku>(createItem("end"));
        }

        startSubItem->time = startTime;
        endSubItem->time = endTime;

        DanmakuSet::iterator iterBegin = items->lower_bound(*startItem);
        DanmakuSet::iterator iterEnd = items->upper_bound(*endItem);

        return DanmakuSet(iterBegin, iterEnd);
    }

    Danmakus Danmakus::subnew(time_t startTime, time_t endTime) {
        return Danmakus(subset(startTime, endTime));
    }

    Danmakus& Danmakus::sub(time_t startTime, time_t endTime) {
        if (items == nullptr || items->size() == 0) {
            //throw std::exception("items is NullPtr or has no elements");
            return *static_cast<Danmakus*>(nullptr);
        }

        if (subItems == nullptr) {
            subItems = std::make_shared<Danmakus>();
        }
        if (startItem == nullptr) {
            startItem = std::make_shared<BaseDanmaku>(createItem("start"));
        }
        if (endItem == nullptr) {
            endItem = std::make_shared<BaseDanmaku>(createItem("end"));
        }

        if (subItems != nullptr) {
            time_t dTime = startTime - startItem->time;
            if (dTime > 0 && endTime <= endItem->time) {
                return *subItems;
            }
        }

        startItem->time = startTime;
        endItem->time = endTime;

        DanmakuSet::iterator iterBegin = items->lower_bound(*startItem);
        DanmakuSet::iterator iterEnd = items->upper_bound(*endItem);

        subItems->setItems(DanmakuSet(iterBegin, iterEnd));
        return *subItems;
    }

    BaseDanmaku Danmakus::createItem(const std::string& text) {
        return Danmaku(text);
    }

    int Danmakus::size() {
        return items->size();
    }

    void Danmakus::clear() {
        if (items != nullptr) {
            items->clear();
        }
    }

    BaseDanmaku& Danmakus::first() {
        if (items != nullptr && (!items->empty())) {
            return const_cast<BaseDanmaku&>(*(items->begin()));
        } else {
            return *static_cast<BaseDanmaku*>(nullptr);
        }
    }

    BaseDanmaku& Danmakus::last() {
        if (items != nullptr && (!items->empty())) {
            return const_cast<BaseDanmaku&>(*(--items->end()));
        } else {
            return *static_cast<BaseDanmaku*>(nullptr);
        }
    }

    bool Danmakus::contains(BaseDanmaku& item) {
        return (items != nullptr && items->count(item) == 1);
    }

    bool Danmakus::isEmpty() {
        return (items != nullptr && items->empty());
    }

    bool compareByTime(const BaseDanmaku& obj1, const BaseDanmaku& obj2) {
        return (compare(obj1, obj2) == -1);
    }

    bool compareByYPos(const BaseDanmaku& obj1, const BaseDanmaku& obj2) {
        auto diff = obj1.getTop() - obj2.getTop();

        if (diff != 0) {
            return (diff < 0);
        }

        return (compare(obj1, obj2) == -1);
    }

    bool compareByYPosDesc(const BaseDanmaku& obj1, const BaseDanmaku& obj2) {
        auto diff = obj1.getTop() - obj2.getTop();

        if (diff != 0) {
            return (diff > 0);
        }

        return (compare(obj1, obj2) == -1);
    }

}
}
