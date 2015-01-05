#ifndef _PCDFM_DEMO_TEST_DANMAKU_VIEW_HPP
#define _PCDFM_DEMO_TEST_DANMAKU_VIEW_HPP

#include <thread>
#include "SkStupidView.hpp"

using PCDanmakuFlameMaster::ui::SkStupidView;

namespace PCDFM_Demo {

    class TestDanmakuView : public SkStupidView {
    public:
        TestDanmakuView(void* nativeHandle) : SkStupidView(nativeHandle) {
            initialize();
        }
        virtual ~TestDanmakuView() {
            if (stopFlag == false) {
                stop();
            }
            //teardownBackend();
        }
        void initialize();
        void start();
        void stop();
    protected:
        void onAttach() override;
        void onDetach() override;
        void onResize() override;
    private:
        void working();
    private:
        SkSurface* surface = nullptr;
        SkCanvas* canvas = nullptr;
        std::thread renderThread;
        bool stopFlag = true;
    };

}

#endif // _PCDFM_DEMO_TEST_DANMAKU_VIEW_HPP
