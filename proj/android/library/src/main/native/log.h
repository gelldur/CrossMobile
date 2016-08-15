//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#pragma once

#include <android/log.h>

#ifdef DEBUG

#define  DLOG(...)  __android_log_print(ANDROID_LOG_DEBUG,"JNI",__VA_ARGS__)
#define  ILOG(...)  __android_log_print(ANDROID_LOG_INFO,"JNI",__VA_ARGS__)
#define  WLOG(...)  __android_log_print(ANDROID_LOG_WARN,"JNI",__VA_ARGS__)
#define  ELOG(...)  __android_log_print(ANDROID_LOG_ERROR,"JNI",__VA_ARGS__)
#define  FLOG(...)  __android_log_print(ANDROID_LOG_FATAL,"JNI",__VA_ARGS__)

#else

#define  DLOG(...)
#define  ILOG(...)
#define  WLOG(...)  __android_log_print(ANDROID_LOG_WARN,"JNI",__VA_ARGS__)
#define  ELOG(...)  __android_log_print(ANDROID_LOG_ERROR,"JNI",__VA_ARGS__)
#define  FLOG(...)  __android_log_print(ANDROID_LOG_FATAL,"JNI",__VA_ARGS__)

#endif
