#pragma once

enum class ErrorCode {
    OK,
    ERR_UNKNOWN_FUNC,
    ERR_UNKNOWN,
    ERR_PARSE,
    ERR_HW,
    ERR_TIMEOUT,
    Size // This is just a helper to make arrays.
};
// Please keep this equal with ErrorCode
const std::array<std::string, (int)ErrorCode::Size> ErrorCodeText = 
{
    { 
        "OK",
        "ERR_UNKNOWN_FUNC",
        "ERR_UNKNOWN",
        "ERR_PARSE",
        "ERR_HW",
        "ERR_TIMEOUT"
    }
};
