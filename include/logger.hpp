#ifndef STXA_LOGGER_HPP
#define STXA_LOGGER_HPP

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

namespace stxa {
// Log functions
#define LOG_INFO(...) spdlog::info(__VA_ARGS__)

#define LOG_WARN(...) spdlog::warn(__VA_ARGS__)

#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)

#define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)

#define LOG_DEBUG(...) spdlog::debug(_VA_ARGS__)
} // namespace stxa

#endif