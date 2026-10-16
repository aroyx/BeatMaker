#pragma once

void msg_log(const char *msg, ...);
void msg_logw(const char *msg, ...);

void msg_logI(int catagory, const char *msg, ...);
void msg_logwI(int catagory, const char *msg, ...);

void msg_logW(int catagory, const char *msg, ...);
void msg_logwW(int catagory, const char *msg, ...);

void msg_logE(int catagory, const char *msg, ...);
void msg_logwE(int catagory, const char *msg, ...);
