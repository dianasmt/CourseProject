// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "framework.h"
#include <cstdlib>
#include <list>
#include <string>
#include <locale>
#include"boost/archive/binary_iarchive.hpp"
#include"boost/archive/binary_oarchive.hpp"
#include"boost/iostreams/device/back_inserter.hpp"
#include"boost/iostreams/stream.hpp"
#include"boost/serialization/list.hpp"
#endif //PCH_H
