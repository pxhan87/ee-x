//
//  PluginProtocol.m
//  ee-core
//
//  Created by Zinge on 7/1/16.
//
//

#include "ee/core/internal/MessageBridge.hpp"

#import "ee/core/internal/EEMessageBridge.h"

namespace ee {
namespace core {
std::string MessageBridge::call(const std::string& tag,
                                const std::string& msg) {
    NSString* result =
        [[EEMessageBridge getInstance] call:@(tag.c_str()) msg:@(msg.c_str())];
    return [result UTF8String];
}
} // namespace core
} // namespace ee