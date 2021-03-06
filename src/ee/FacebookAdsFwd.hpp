//
//  FacebookAds.h
//  ee_x
//
//  Created by Pham Xuan Han on 5/12/17.
//
//

#ifndef EE_X_FACEBOOK_ADS_FWD_HPP_
#define EE_X_FACEBOOK_ADS_FWD_HPP_

#include <ee/AdsFwd.hpp>

namespace ee {
namespace facebook_ads {
enum class BannerAdSize;

class Bridge;
class BannerAd;
class NativeAd;
class NativeAdLayout;
class InterstitialAd;
class RewardedVideo;
} // namespace facebook_ads

using FacebookAds = facebook_ads::Bridge;
using FacebookBannerAdSize = facebook_ads::BannerAdSize;
using FacebookNativeAdLayout = facebook_ads::NativeAdLayout;
} // namespace ee

#endif /* EE_X_FACEBOOK_ADS_FWD_HPP_ */
