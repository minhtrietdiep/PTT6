#pragma once

#include <array>

enum class ErrorCode {
    ERR_OK,
    ERR_UNKNOWN_FUNC,
    ERR_UNKNOWN,
    ERR_PARSE,
    ERR_HW,
    ERR_TIMEOUT,
    ERR_FILE_OPEN,
    ERR_INVALID_ARG,
    ERR_NO_ITEM,
    Size // This is just a helper to make arrays.
};
// Please keep this equal with ErrorCode
const std::array<std::string, (int)ErrorCode::Size> ErrorCodeText = 
{
    { 
        "ERR_OK",
        "ERR_UNKNOWN_FUNC",
        "ERR_UNKNOWN",
        "ERR_PARSE",
        "ERR_HW",
        "ERR_TIMEOUT",
        "ERR_FILE_OPEN",
        "ERR_INVALID_ARG",
        "ERR_NO_ITEM",
    }
};