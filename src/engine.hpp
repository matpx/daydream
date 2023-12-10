#pragma once

#include <cstdio>

#ifndef NDEBUG
#define DD_LOG_DEBUG(MSG) printf(MSG); printf("\n");
#else
#define DD_LOG_DEBUG(MSG)
#endif
#define DD_LOG_INFO(MSG) printf(MSG); printf("\n");
