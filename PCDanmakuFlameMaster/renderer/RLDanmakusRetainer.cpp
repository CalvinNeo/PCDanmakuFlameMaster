/**
 * @file    RLDanmakuRetainer.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-03
 */

#include "../model/BaseDanmaku.hpp"
#include "../model/IDisplayer.hpp"
#include "../model/Danmakus.hpp"
#include "../utilities/DanmakuUtils.hpp"
#include "RLDanmakusRetainer.hpp"

using PCDanmakuFlameMaster::model::BaseDanmaku;
using PCDanmakuFlameMaster::model::IDisplayer;
using PCDanmakuFlameMaster::model::Danmakus;
using namespace PCDanmakuFlameMaster::util;

namespace PCDanmakuFlameMaster {
namespace renderer {

    void RLDanmakusRetainer::fix(BaseDanmaku& drawItem, IDisplayer& disp) {
        if (drawItem.isOutside())
            return;
        float topPos = 0;
        bool shown = drawItem.isShown();

        if (!shown) {
            mCancelFixingFlag = false;
            auto iter = mVisibleDanmakus.iterator();
            BaseDanmaku *insertItem = nullptr, *firstItem = nullptr, *lastItem = nullptr, *minRightRow = nullptr;
            bool overwriteInsert = false;

            while (!mCancelFixingFlag && iter.hasNext()) {
                BaseDanmaku& item = iter.next();

                if (&item == &drawItem) {
                    insertItem = &item;
                    lastItem = nullptr;
                    shown = true;
                    break;
                }

                if (firstItem == nullptr)
                    firstItem = &item;

                if (drawItem.paintHeight + item.getTop() > disp.getHeight()) {
                    overwriteInsert = true;
                    break;
                }

                if (minRightRow == nullptr) {
                    minRightRow = &item;
                } else {
                    if (minRightRow->getRight() >= item.getRight()) {
                        minRightRow = &item;
                    }
                }

                bool willHit = DanmakuUtils::willHitInDuration(disp, item, drawItem, drawItem.getDuration(), drawItem.getTimer().currMillisecond);
                if (!willHit) {
                    insertItem = &item;
                    break;
                }

                lastItem = &item;
            }

            if (insertItem != nullptr) {
                if (lastItem != nullptr) {
                    topPos = lastItem->getBottom();
                } else {
                    topPos = insertItem->getTop();
                }
                if (insertItem != &drawItem) {
                    mVisibleDanmakus.removeItem(*insertItem);
                    shown = false;
                }
            } else if (overwriteInsert) {
                if (minRightRow != nullptr) {
                    topPos = minRightRow->getTop();
                    if (minRightRow->paintWidth < drawItem.paintWidth) {
                        mVisibleDanmakus.removeItem(*minRightRow);
                        shown = false;
                    }
                }
            } else if (lastItem != nullptr) {
                topPos = lastItem->getBottom();
            } else if (firstItem != nullptr) {
                topPos = firstItem->getTop();
                mVisibleDanmakus.removeItem(*firstItem);
                shown = false;
            } else {
                topPos = 0;
            }

            topPos = checkVerticalEdge(overwriteInsert, drawItem, disp, topPos, *firstItem, *lastItem);
            if (topPos == 0 && mVisibleDanmakus.isEmpty()) {
                shown = false;
            }
        }

        drawItem.layout(disp, drawItem.getLeft(), topPos);

        if (!shown)
            mVisibleDanmakus.addItem(drawItem);

    }

    float RLDanmakusRetainer::checkVerticalEdge(bool overwriteInsert, const BaseDanmaku& drawItem, IDisplayer& disp, float topPos, const BaseDanmaku& firstItem, const BaseDanmaku& lastItem) {
        if (topPos < 0 || firstItem.getTop() > 0 || topPos + drawItem.paintHeight > disp.getHeight()) {
            topPos = 0;
            clear();
        }
        return topPos;
    }

    void RLDanmakusRetainer::clear() {
        mCancelFixingFlag = true;
        mVisibleDanmakus.clear();
    }

}
}
