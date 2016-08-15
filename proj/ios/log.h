//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#pragma once

#include <cstdio>

#ifdef DEBUG

#define  DLOG(...)  fprintf(stderr,"DLOG:\t");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");fflush(stderr)
#define  ILOG(...)  fprintf(stderr,"ILOG:\t");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");fflush(stderr)
#define  WLOG(...)  fprintf(stderr,"WLOG:\t");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");fflush(stderr)
#define  ELOG(...)  fprintf(stderr,"ELOG:\t");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");fflush(stderr)
#define  FLOG(...)  fprintf(stderr,"FLOG:\t");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");fflush(stderr)

#else

#define  DLOG(...)
#define  ILOG(...)
#define  WLOG(...)  fprintf(stderr,"WLOG:\t");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");fflush(stderr)
#define  ELOG(...)  fprintf(stderr,"ELOG:\t");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");fflush(stderr)
#define  FLOG(...)  fprintf(stderr,"FLOG:\t");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");fflush(stderr)

#endif
