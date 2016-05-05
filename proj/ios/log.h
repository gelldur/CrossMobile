//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#pragma once

#define  DLOG(...)  fprintf(stderr,"DLOG:\t");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n")
#define  ILOG(...)  fprintf(stderr,"ILOG:\t");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n")
#define  WLOG(...)  fprintf(stderr,"WLOG:\t");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n")
#define  ELOG(...)  fprintf(stderr,"ELOG:\t");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n")
#define  FLOG(...)  fprintf(stderr,"FLOG:\t");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n")
