//
//  EEAppsFlyer.hpp
//  ee_x_mobile_apps_flyer
//
//  Created by eps on 6/26/18.
//

#import <Foundation/Foundation.h>

/// https://support.appsflyer.com/hc/en-us/articles/207032066-AppsFlyer-SDK-Integration-iOS
@interface EEAppsFlyer : NSObject

- (void)initialize:(NSString* _Nonnull)devKey appId:(NSString* _Nonnull)appId;

- (NSString* _Nonnull)getDeviceId;

/// If enabled, AppsFlyer SDK logs are shown in the XCode console.
- (void)setDebugEnabled:(BOOL)enabled;

- (void)trackEvent:(NSString* _Nonnull)name values:(NSDictionary* _Nonnull)dict;

@end