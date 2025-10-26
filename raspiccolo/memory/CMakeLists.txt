# 2K is 2048 Bytes which, as Hex =0x800 4K is 4096 Bytes which, as Hex =0x1000
# 8K is 8192 Bytes which, as Hex =0x2000 16K is 16384 Bytes which, as Hex
# =0x4000 32K is 32768 Bytes which, as Hex =0x8000 64K is 65536 Bytes which, as
# Hex =0x10000 128K is 131072 Bytes which, as Hex =0x20000 256K is 262144 Bytes
# which, as Hex =0x40000 512K is 524288 Bytes which, as Hex =0x80000
#

set(MEMORY_MODULE_ROOT "${MODULE_ROOT}/raspiccolo/memory")

set(c_sources "qmalloc.c")
set(memory_module "${MEMORY_MODULE_ROOT}/qmalloc.h")

set(QMALLOC_LINKER_SCRIPT_IN
    "${CMAKE_CURRENT_LIST_DIR}/quick_malloc.template.ld")
set(QMALLOC_LINKER_SCRIPT_OUT "${CMAKE_CURRENT_BINARY_DIR}/quick_malloc.ld")

# I clearly still do not understand INTERFACE Libraries as I cant get the C
# files to compile!!! Okay I can now but...! I have to use target_sources not
# adding them here (so weird!)
add_library(raspiccolo_memory INTERFACE) # ${c_sources}) # ${cpp_sources})
# add_library(raspiccolo_memory STATIC ${c_sources}) # ${cpp_sources})

target_sources(
  raspiccolo_memory
  PUBLIC FILE_SET
         HEADERS
         TYPE
         HEADERS
         BASE_DIRS
         ${MODULE_ROOT}
         FILES
         ${memory_module})

target_sources(raspiccolo_memory INTERFACE ${c_sources})

target_compile_definitions(raspiccolo_memory INTERFACE c_std_11)

set(QHEAP_SIZE "1K" CACHE STRING
          "QHeap (quick heap) size (subtracted from the \"normal heap\")")
        
set(QHEAP_ALIGNMENT "4" CACHE STRING "QHeap (quick heap) alignment")

configure_file(${QMALLOC_LINKER_SCRIPT_IN} ${QMALLOC_LINKER_SCRIPT_OUT} @ONLY
               NEWLINE_STYLE UNIX)
set_target_properties(raspiccolo_memory PROPERTIES LINK_DEPENDS
                                                   ${QMALLOC_LINKER_SCRIPT_OUT})
target_link_options(raspiccolo_memory INTERFACE
                    "LINKER:-T,${QMALLOC_LINKER_SCRIPT_OUT}")

add_library(raspiccolo::memory ALIAS raspiccolo_memory)


# Can't modify (as don't want to rewrite) and cant "hook" into it so we can't
# use the custom linker script the way I wanted to to add a new section at the
# end of the heap for our quick heap (qheap) for quick malloc (qmalloc).
#
# However we will use a linker script for setting the size and start of the
# quick heap although not with a new region of memory (for now) just a few
# linker variables.

# set(LINKER_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/memmap_custom_malloc.ld")
# pico_set_linker_script(RC_Car ${LINKER_SCRIPT})
