//
//  CrashlyticsProtocol.hpp
//  ee-crashlytics
//
//  Created by Zinge on 7/4/16.
//
//

#ifndef EE_CRASHLYTICS_CRASHLYTICS_PROTOCOL_HPP_
#define EE_CRASHLYTICS_CRASHLYTICS_PROTOCOL_HPP_

#include <memory>
#include <string>

namespace ee {
namespace core {
class LogLevel;
class PluginProtocol;
} // namespace core

namespace crashlytics {
class CrashlyticsProtocol final {
public:
    CrashlyticsProtocol();
    ~CrashlyticsProtocol();

    void causeCrash() const;

    void causeException() const;

    void log(const core::LogLevel& level, const std::string& tag,
             const std::string& message) const;

    void setString(const std::string& key, const std::string& value) const;

    void setBool(const std::string& key, bool value) const;

    void setInt(const std::string& key, int value) const;

    void setUserIdentifier(const std::string& identifier) const;

    void setUserName(const std::string& name) const;

    void setUserEmail(const std::string& email) const;

private:
    std::unique_ptr<core::PluginProtocol> protocol_;
};
} // namespace crashlytics
} // namespace ee

#endif /* CrashlyticsProtocol_hpp */