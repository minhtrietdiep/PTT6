#pragma once
#include <string>

enum class JSONError 
{
	NONE = 0,
	VAR_NULL = -1,
	PARSE_ERROR = -2
};

inline const std::string GetJSONErrorString(JSONError err) {
    switch (err) {
        case JSONError::NONE:
            return "NONE";
        case JSONError::VAR_NULL:
            return "VAR_NULL";
        case JSONError::PARSE_ERROR:
            return "PARSE_ERROR";
        default:
            return "Invalid Error";
    }
}
