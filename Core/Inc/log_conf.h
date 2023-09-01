#ifndef LOG_CONF_H
#define LOG_CONF_H

/// @brief Enable colors in standard output
#define LOGC__STDOUT_COLOR

/// @brief Maximum number of callback functions
#define LOGC__MAX_CALLBACKS     1

/// @brief Standard output to write to (stdout/stderr)
#define LOGC__DEFAULT_STDOUT    stdout

/// @brief Time format used in the logs.
///        2 for local time string
///        1 for epoch
///        0 for none
#define LOGC__TIME_FORMAT       1

#endif // LOG_CONF_H