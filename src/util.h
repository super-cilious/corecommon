// Automatically generated header.

#pragma once
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#ifdef UTIL_TRACE
#include <execinfo.h>
#endif
#if !defined(_WIN32) && !defined(__EMSCRIPTEN__)
#define UTIL_TRACE
#endif
#define TRACE_SIZE 10
typedef struct {
	void* stack[TRACE_SIZE];
} trace_t;
#ifdef BUILD_DEBUG
void memcheck_init();
#endif
void drop(void* ptr);
#ifdef UTIL_TRACE
trace_t stacktrace();
#endif
#ifdef UTIL_TRACE
void print_trace(trace_t* trace_t);
#endif
void* heap(size_t size);
void* heapcpy(size_t size, const void* val);
char* heapcpystr(const char* str);
char* heapcpysubstr(const char* begin, size_t len);
char* heapstr(const char* fmt, ...);
char* stradd(char* str1, char* str2);
char* strpre(char* str, char* prefix);
char* straffix(char* str, char* affix);
int streq(char* str1, char* str2);
void* resize(void* ptr, size_t size);
char* getpath(char* path);
char* read_file(char* path);
#ifndef _WIN32 //already defined
int max(int a, int b);
#endif
#ifndef _WIN32 //already defined
int min(int a, int b);
#endif
char* path_trunc(char* path, unsigned up);
char *ext(char *filename);
#ifdef BUILD_DEBUG
#ifdef UTIL_TRACE
void memcheck();
#endif
#endif
char hexchar(char hex);
void charhex(unsigned char chr, char* out);
unsigned char* bit_reinterpret(unsigned char* src, unsigned inlen, unsigned* outlen, unsigned char inl, unsigned char outl);
char* base64_encode(char* src, unsigned len);
char* base64_decode(char* src, unsigned* len);
void perrorx(char* err);
void errx(char* err);
