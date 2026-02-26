// SPDX-License-Identifier: Apache-2.0
// Copyright © 2025-2026 James Calo

#ifndef __RASPICCOLO_MEMORY_QMALLOC_H__
#define __RASPICCOLO_MEMORY_QMALLOC_H__

void init_quick_alloc(void);

void* qmalloc(unsigned int nbytes);

void qfree(void *ptr);

#endif
