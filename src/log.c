#include <stdarg.h>

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_messagebox.h>

#include "log.h"
#include "global.h"

void msg_log(const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, msg, args);
    va_end(args);
}

void msg_logw(const char *msg, ...)
{
    char t_msg[256];
    va_list args;
    va_start(args, msg);
    SDL_vsnprintf(t_msg, sizeof(t_msg), msg, args);
    va_end(args);

    SDL_Log("%s", t_msg);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Info!", t_msg, global.window);
}

void msg_logI(int category, const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    SDL_LogMessageV(category, SDL_LOG_PRIORITY_INFO, msg, args);
    va_end(args);
}

void msg_logwI(int category, const char *msg, ...)
{
    char t_msg[256];
    va_list args;
    va_start(args, msg);
    SDL_vsnprintf(t_msg, sizeof(t_msg), msg, args);
    va_end(args);

    SDL_LogInfo(category, "%s", t_msg);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Info!", t_msg, global.window);
}

void msg_logW(int category, const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    SDL_LogMessageV(category, SDL_LOG_PRIORITY_WARN, msg, args);
    va_end(args);
}

void msg_logwW(int category, const char *msg, ...)
{
    char t_msg[256];
    va_list args;
    va_start(args, msg);
    SDL_vsnprintf(t_msg, sizeof(t_msg), msg, args);
    va_end(args);

    SDL_LogWarn(category, "%s", t_msg);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Warning!", t_msg, global.window);
}

void msg_logE(int category, const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    SDL_LogMessageV(category, SDL_LOG_PRIORITY_ERROR, msg, args);
    va_end(args);
}

void msg_logwE(int category, const char *msg, ...)
{
    char t_msg[256];
    va_list args;
    va_start(args, msg);
    SDL_vsnprintf(t_msg, sizeof(t_msg), msg, args);
    va_end(args);

    SDL_LogError(category, "%s", t_msg);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", t_msg, global.window);
}
