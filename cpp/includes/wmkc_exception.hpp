#include <wmkc_conf.hpp>

#if WMKC_SUPPORT
#ifndef WMKC_CPP_EXCEPTION
#define WMKC_CPP_EXCEPTION
#include <wmkc_error.h>

void wmkcErr_exception(wmkcErr_obj err);

#endif
#endif