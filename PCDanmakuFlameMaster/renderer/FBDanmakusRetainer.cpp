/**
 * @file    FBDanmakuRetainer.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-04
 */

#include "../utilities/DanmakuUtils.hpp"
#include "FBDanmakusRetainer.hpp"

using namespace PCDanmakuFlameMaster::util;

namespace PCDanmakuFlameMaster {
namespace renderer {

    void FBDanmakusRetainer::fix(BaseDanmaku& drawItem, IDisplayer& disp) {
        if (drawItem.isOutside())
            return;
        bool shown = drawItem.isShown();
        float topPos = drawItem.getTop();
        if (topPos < 0) {
            topPos = disp.getHeight() - drawItem.paintHeight;
        }

        BaseDanmaku *removeItem = nullptr, *firstItem = nullptr;
        if (!shown) {
            mCancelFixingFlag = false;
            auto iter = mVisibleDanmakus.iterator();
            while (!mCancelFixingFlag && iter.hasNext()) {
                BaseDanmaku& item = iter.next();

                if (&item == &drawItem) {
                    removeItem = nullptr;
                    break;
                }

                if (firstItem == nullptr) {
                    firstItem = &item;
                    if (firstItem->getBottom() != disp.getWidth()) {
                        break;
                    }
                }

                if (topPos < 0) {
                    removeItem = nullptr;
                    break;
                }

                bool willHit = DanmakuUtils::willHitInDuration(disp, item, drawItem, drawItem.getDuration(), drawItem.getTimer().currMillisecond);
                if (!willHit) {
                    removeItem = &item;
                    break;
                }

                topPos = item.getTop() - drawItem.paintHeight;
            }
            topPos = checkVerticalEdge(false, drawItem, disp, topPos, *firstItem, *static_cast<BaseDanmaku*>(nullptr));
        }

        drawItem.layout(disp, drawItem.getLeft(), topPos);

        if (!shown) {
            mVisibleDanmakus.removeItem(*removeItem);
            mVisibleDanmakus.addItem(drawItem);
        }
    }

    float FBDanmakusRetainer::checkVerticalEdge(bool overwriteInsert, const BaseDanmaku& drawItem, IDisplayer& disp, float topPos, const BaseDanmaku& firstItem, const BaseDanmaku& lastItem) {
        if (topPos < 0 || (firstItem.getBottom() != disp.getHeight())) {
            topPos = disp.getHeight() - drawItem.paintHeight;
            clear();
        }
        return topPos;
    }

    void FBDanmakusRetainer::clear() {
        mCancelFixingFlag = true;
        mVisibleDanmakus.clear();
    }

}
}
