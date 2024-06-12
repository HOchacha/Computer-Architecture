#pragma once
#include "../../component/latch/latch.h"

#ifndef MEMORY_ACCESS
#define MEMORY_ACCESS
MEM_WB_SLOT memory_access_pipe(EX_MEM_SLOT latch_out);
#endif
