#pragma once
#include <array>
#include <cstdint>
#include <cstdio>
#include <format>

namespace Gas {

    class Logger
    {
    public:
        enum class TextColor
        {
            Black,
            Red,
            Green,
            Yellow,
            Blue,
            Magenta,
            Cyan,
            White,
            Bright_Black,
            Bright_Red,
            Bright_Green,
            Bright_Yellow,
            Bright_Blue,
            Bright_Magenta,
            Bright_Cyan,
            Bright_White,
            Count,
        };

        template <typename... Args>
        static void s_log(const char* prefix, const char* message, TextColor color, Args... args)
        {
            static std::array<const char*, static_cast<int>(TextColor::Count)> textColorTable {
                "\x1b[30m", // Black
                "\x1b[31m", // Red
                "\x1b[32m", // Green
                "\x1b[33m", // Yellow
                "\x1b[34m", // Blue
                "\x1b[35m", // Magenta
                "\x1b[36m", // Cyan
                "\x1b[37m", // White
                "\x1b[90m", // Bright Black
                "\x1b[91m", // Bright Red
                "\x1b[92m", // Bright Green
                "\x1b[93m", // Bright Yellow
                "\x1b[94m", // Bright Blue
                "\x1b[95m", // Bright Magenta
                "\x1b[96m", // Bright Cyan
                "\x1b[97m", // Bright White
            };

            // std::array<char, 8192> formatBuffer {};
            // sprintf(formatBuffer.data(), "%s %s %s \x1b[m", textColorTable[static_cast<int>(color)], prefix, message);
            //
            // std::array<char, 8192> textBuffer {};
            // sprintf(textBuffer.data(), formatBuffer.data(), args...);
            //
            // puts(textBuffer.data());

            std::string formatString = std::format("{} {} {} \x1b[m", textColorTable[static_cast<int>(color)], prefix, message);
            std::string text = std::vformat(formatString, std::make_format_args(args...));

            puts(text.c_str());
        }
    };

}

#define GAS_TRACE(msg, ...) Gas::Logger::s_log("TRACE: ", msg, Gas::Logger::TextColor::Green, ##__VA_ARGS__)
#define GAS_WARN(msg, ...)  Gas::Logger::s_log("WARN: ", msg, Gas::Logger::TextColor::Yellow, ##__VA_ARGS__)
#define GAS_ERROR(msg, ...) Gas::Logger::s_log("ERROR: ", msg, Gas::Logger::TextColor::Red, ##__VA_ARGS__)
