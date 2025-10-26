
SECTIONS 
{
  __qheap_size = @QHEAP_SIZE@;
  __total_heap_limit = __HeapLimit;
  __HeapLimit -= __qheap_size;
  /* .qheap __HeapLimit (NOLOAD): */
  /*  (non constant so not alowed ->)ALIGN(ALIGNOF(.heap)) */
  .qheap __HeapLimit (COPY): ALIGN(@QHEAP_ALIGNMENT@) /* <-???? */
  {
    __qheap_start = .;
    /* . += __qheap_size; */
    __qheap_end = __qheap_start + __qheap_size;
  }
}
