#ifndef MEDIA_STRINGUTILS_H
#define MEDIA_STRINGUTILS_H

#include <string>
#include <algorithm>
#include <cctype>

namespace media {
inline std::string toLowerCase(const std::string& str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return lower;
}

inline bool stringContainsIgnoreCase(const std::string& text, const std::string& pattern) {
    return toLowerCase(text).find(toLowerCase(pattern)) != std::string::npos;
}
}
#endif // MEDIA_STRINGUTILS_H
