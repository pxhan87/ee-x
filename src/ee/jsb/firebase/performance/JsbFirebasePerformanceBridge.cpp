//
//  JsbFirebasePerformance.cpp
//  ee-x
//
//  Created by eps on 3/25/19.
//

#include "ee/jsb/firebase/performance/JsbFirebasePerformanceBridge.hpp"

#include <ee/firebase/performance/FirebasePerformanceBridge.hpp>
#include <ee/jsb/JsbCore.hpp>

namespace ee {
namespace firebase {
namespace performance {
namespace {
se::Class* clazz = nullptr;

using Self = Bridge;

// clang-format off
constexpr auto constructor              = &core::makeConstructor<Self>;
constexpr auto finalize                 = &core::makeFinalize<Self>;
constexpr auto setDataCollectionEnabled = &core::makeMethod<&Self::setDataCollectionEnabled>;
constexpr auto isDataCollectionEnabled  = &core::makeMethod<&Self::isDataCollectionEnabled>;
constexpr auto startTrace               = &core::makeMethod<&Self::startTrace>;
constexpr auto newTrace                 = &core::makeMethod<&Self::newTrace>;
// clang-format on

SE_BIND_FINALIZE_FUNC(finalize);
SE_BIND_CTOR(constructor, clazz, finalize);
SE_BIND_FUNC(setDataCollectionEnabled);
SE_BIND_FUNC(isDataCollectionEnabled);
SE_BIND_FUNC(startTrace);
SE_BIND_FUNC(newTrace);
} // namespace

bool registerJsbBridge(se::Object* global) {
    auto scope = core::getPath(global, "ee");
    auto cls = se::Class::create("FirebasePerformance", scope, nullptr,
                                 _SE(constructor));
    cls->defineFinalizeFunction(_SE(finalize));

    EE_JSB_DEFINE_FUNCTION(cls, setDataCollectionEnabled);
    EE_JSB_DEFINE_FUNCTION(cls, isDataCollectionEnabled);
    EE_JSB_DEFINE_FUNCTION(cls, startTrace);
    EE_JSB_DEFINE_FUNCTION(cls, newTrace);

    cls->install();

    JSBClassType::registerClass<Self>(cls);
    clazz = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
} // namespace performance
} // namespace firebase
} // namespace ee