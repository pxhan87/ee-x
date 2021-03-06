//
//  AppLovin.cpp
//  ee_x_test
//
//  Created by Zinge on 10/16/17.
//
//

#include "AppLovin.hpp"

#include "Utils.hpp"

namespace eetest {
ee::AppLovin* getAppLovin() {
    static auto plugin = ee::AppLovin();
    static bool initialized;
    if (not initialized) {
        ee::runOnUiThreadAndWait([] {
            plugin.initialize(
                R"(gG8pkErh1_fQo-4cNDXGnxGyb9H4qz6VDEJyS8eU8IvxH-XeB4wy0BubKAg97neL0yIT4xyDEs8WqfA0l4zlGr)");
            plugin.setTestAdsEnabled(true);
            plugin.setVerboseLogging(true);
        });
        initialized = true;
    }
    return &plugin;
}

void testAppLovinRewardedVideo() {
    auto rewardedVideo = getAppLovin()->createRewardedVideo();
    rewardedVideo->setResultCallback([](bool result) {
        logCurrentThread();
        getLogger().info("Result = ", result ? "succeeded" : "failed");
    });

    float delay = 0.0f;
    scheduleForever(delay += 1.0f, 3.0f, [rewardedVideo] {
        getLogger().info("Load AppLovin rewarded video");
        rewardedVideo->load();
    });
    scheduleForever(delay += 1.0f, 3.0f, [rewardedVideo] {
        getLogger().info("Show AppLovin rewarded video");
        rewardedVideo->show();
    });
}
} // namespace eetest
