#pragma once

#if defined(unix) || defined(__unix) || defined(__unix__)
	#define PN_OS_UNIX
#endif

#if defined(__linux__)
	#define PN_OS_LINUX
#endif

#if defined(__APPLE__) || defined(__MACH__)
	#define PN_OS_MACOS
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
	#define PN_OS_WINDOWS
#endif

#if defined(__ANDROID__)
	#define PN_OS_ANDROID
#endif

#if defined(__FreeBSD__)
	#define PN_OS_FreeBSD
#endif


// LINUX
#ifdef PN_OS_LINUX
	#include <sys/resource.h>

	// NOTE: Tested on Arch Linux, Kernel: 5.14.30-arch1-1.
	void pn_sys_print_memory_usage();
#endif


// WINDOWS
#ifdef PN_OS_WINDOWS
	#include <windows.h>

	// TODO: Finish this function. 
	void pn_sys_print_memory_usage();
#endif