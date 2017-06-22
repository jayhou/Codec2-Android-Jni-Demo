# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 2.8)

#
# codec2 library sources
#

set(CODEC2_SRCS
    dump.c
    lpc.c
    nlp.c
    postfilter.c
    sine.c
    codec2.c
    codec2_fft.c
    cohpsk.c
    fifo.c
    fdmdv.c
    fm.c
    fsk.c
    fmfsk.c
    kiss_fft.c
    kiss_fftr.c
    linreg.c
    interp.c
    lsp.c
    mbest.c
    newamp1.c
    phase.c
    quantise.c
    pack.c
    codebook.c
    codebookd.c
    codebookjvm.c
    codebookmel.c
    codebooklspmelvq.c
    codebookge.c
    codebooknewamp1.c
    codebooknewamp1_energy.c
    golay23.c
    freedv_api.c
    freedv_vhf_framing.c
    freedv_data_channel.c
    varicode.c
    modem_stats.c
)

set(CODEC2_PUBLIC_HEADERS
    golay23.h
    codec2.h
    codec2_fdmdv.h
    codec2_cohpsk.h
    codec2_fm.h
    fsk.h
    codec2_fifo.h
    comp.h
    comp_prim.h
    modem_stats.h
    kiss_fft.h
    freedv_api.h
    varicode.h
    freedv_api_internal.h
)

#
# Setup the codec2 library
#
add_library(codec2 SHARED ${CODEC2_SRCS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(codec2 ${CMAKE_REQUIRED_LIBRARIES})
