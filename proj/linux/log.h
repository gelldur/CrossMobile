//
// Created by Dawid Drozd aka Gelldur on 03.02.16.
//

#pragma once

#include <cstdio>

#define  DLOG(...)  printf("DLOG:\t");printf(__VA_ARGS__);printf("\n");fflush(stdout)
#define  ILOG(...)  printf("ILOG:\t");printf(__VA_ARGS__);printf("\n");fflush(stdout)
#define  WLOG(...)  printf("WLOG:\t");printf(__VA_ARGS__);printf("\n");fflush(stdout)
#define  ELOG(...)  printf("ELOG:\t");printf(__VA_ARGS__);printf("\n");fflush(stdout)
#define  FLOG(...)  printf("FLOG:\t");printf(__VA_ARGS__);printf("\n");fflush(stdout)
