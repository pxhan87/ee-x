//
//  FacebookRewardVideoAd.cpp
//  ee_x
//
//  Created by Zinge on 10/11/17.
//
//

#include "ee/ads/internal/MediationManager.hpp"
#include "ee/core/Logger.hpp"
#include "ee/core/MessageBridge.hpp"
#include "ee/core/Utils.hpp"
#include "ee/facebookads/FacebookAdsBridge.hpp"
#include "ee/facebookads/internal/FacebookRewardVideoAd.hpp"
#include "ee/ads/internal/MediationManager.hpp"
#include <cassert>
namespace ee {
namespace facebook {
using Self = RewardedVideo;
namespace {

auto k__createInternalVideo(const std::string& id) {
    return "FacebookAds_createInternalVideo_" + id;
}

auto k__destroyInternalVideo(const std::string& id) {
    return "FacebookAds_destroyInternalVideo_" + id;
}

auto k__hasRewardedVideo(const std::string& id) {
    return "FacebookAds_hasRewardedVideo_" + id;
}

auto k__loadRewardedVideo(const std::string& id) {
    return "FacebookAds_loadRewardedVideo_" + id;
}

auto k__showRewardedVideo(const std::string& id) {
    return "FacebookAds_showRewardedVideo_" + id;
}

auto k__onRewarded(const std::string& id) {
    return "FacebookAds_Video_onRewarded_" + id;
}

auto k__onFailedToLoad(const std::string& id) {
    return "FacebookAds_Video_onFailedToLoad_" + id;
}
auto k__onLoaded(const std::string& id) {
    return "FacebookAds_Video_onLoaded_" + id;
}
auto k__onOpened(const std::string& id) {
    return "FacebookAds_Video_onOpened_" + id;
}
auto k__onClosed(const std::string& id) {
    return "FacebookAds_Video_onClosed_" + id;
}
} // namespace

Self::RewardedVideo(const std::string& adId) {
    Logger::getSystemLogger().debug("%s", __PRETTY_FUNCTION__);
    adId_ = adId;

    auto&& bridge = MessageBridge::getInstance();
    bridge.registerHandler(
        [this](const std::string& message) {
            onReward();
            return "";
        },
        k__onRewarded(adId_));
    bridge.registerHandler(
        [this](const std::string& message) {
            onFailedToLoad(message);
            return "";
        },
        k__onFailedToLoad(adId_));
    bridge.registerHandler(
        [this](const std::string& message) {
            onLoaded();
            return "";
        },
        k__onLoaded(adId_));
    bridge.registerHandler(
        [this](const std::string& message) {
            onOpened();
            return "";
        },
        k__onOpened(adId_));
    bridge.registerHandler(
        [this](const std::string& message) {
            onClosed();
            return "";
        },
        k__onClosed(adId_));
}

Self::~RewardedVideo() {
    Logger::getSystemLogger().debug("%s", __PRETTY_FUNCTION__);
    auto&& bridge = MessageBridge::getInstance();
    bridge.deregisterHandler(k__onRewarded(adId_));
    bridge.deregisterHandler(k__onFailedToLoad(adId_));
    bridge.deregisterHandler(k__onLoaded(adId_));
    bridge.deregisterHandler(k__onOpened(adId_));
    bridge.deregisterHandler(k__onClosed(adId_));
}

bool Self::isLoaded() const {
    auto&& bridge = MessageBridge::getInstance();
    auto response = bridge.call(k__hasRewardedVideo(adId_));
    return core::toBool(response);
}

void Self::load() {
    Logger::getSystemLogger().debug("%s", __PRETTY_FUNCTION__);
    auto&& bridge = MessageBridge::getInstance();
    bridge.call(k__loadRewardedVideo(adId_));
}

bool Self::show() {
    if(not isLoaded())
    {
        return false;
    }

    Logger::getSystemLogger().debug("%s", __PRETTY_FUNCTION__);
    auto&& bridge = MessageBridge::getInstance();
    auto response = bridge.call(k__showRewardedVideo(adId_));
    if (not core::toBool(response)) {
        return false;
    }

    auto&& mediation = ads::MediationManager::getInstance();
    auto successful = mediation.startRewardedVideo([this](bool rewarded) { //
        this->setResult(rewarded);

        this->destroyInternalVideo();
        this->createInternalVideo();
    });
    assert(successful);

    return true;
}

void Self::createInternalVideo() {
    Logger::getSystemLogger().debug("%s", __PRETTY_FUNCTION__);
    auto&& bridge = MessageBridge::getInstance();
    auto response = bridge.call(k__createInternalVideo(adId_));
}
    
void Self::destroyInternalVideo() {
    Logger::getSystemLogger().debug("%s", __PRETTY_FUNCTION__);
    auto&& bridge = MessageBridge::getInstance();
    auto response = bridge.call(k__destroyInternalVideo(adId_));
}
#pragma mark - on
void Self::onLoaded() {
    Logger::getSystemLogger().debug("%s", __PRETTY_FUNCTION__);
}

void Self::onFailedToLoad(const std::string& message) {
    Logger::getSystemLogger().debug("%s", __PRETTY_FUNCTION__);
}

void Self::onOpened() {
    Logger::getSystemLogger().debug("%s", __PRETTY_FUNCTION__);
    rewarded_ = false;
}

void Self::onReward() {
    Logger::getSystemLogger().debug("%s", __PRETTY_FUNCTION__);
    rewarded_ = true;
}

void Self::onClosed() {
    Logger::getSystemLogger().debug("%s", __PRETTY_FUNCTION__);

    auto&& mediation = ads::MediationManager::getInstance();
    auto successful = mediation.finishRewardedVideo(rewarded_);
    assert(successful);
}
} // namespace facebook
} // namespace ee