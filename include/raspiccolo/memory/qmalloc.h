#ifndef __RASPICCOLO_MEMORY_QMALLOC_H__
#define __RASPICCOLO_MEMORY_QMALLOC_H__

void init_quick_alloc(void);

void* qmalloc(unsigned int nbytes);

void qfree(void *ptr);

#endif