#pragma once

#include <string>
#include <universalid.hpp>

struct Message
{
    enum Severity
    {
        Severity_Info = 0,         // no problem
        Severity_Warning = 1,      // a potential problem, but we are probably fine
        Severity_Error = 2,        // an error; we are not fine
        Severity_SeriousError = 3, // an error so bad we can't even be sure if we are
                                   // reporting it correctly
        Severity_Default = 4
    };

    UniversalId mId;
    std::string mMessage;
    std::string mHint;
    Severity mSeverity;

    Message();

    Message (const UniversalId& id, const std::string& message,
        const std::string& hint, Severity severity);

    static std::string toString (Severity severity);
};
