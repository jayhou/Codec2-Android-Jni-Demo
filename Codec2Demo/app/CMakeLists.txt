# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

set(CODEC2_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/dump.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/lpc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/nlp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/postfilter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/sine.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/codec2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/codec2_fft.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/cohpsk.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/fifo.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/fdmdv.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/fm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/fsk.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/fmfsk.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/kiss_fft.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/kiss_fftr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/linreg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/interp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/lsp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/mbest.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/newamp1.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/phase.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/quantise.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/pack.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/codebook.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/codebookd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/codebookjvm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/codebookmel.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/codebooklspmelvq.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/codebookge.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/codebooknewamp1.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/codebooknewamp1_energy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/golay23.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/freedv_api.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/freedv_vhf_framing.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/freedv_data_channel.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/varicode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/codec2_0_6/modem_stats.c
)

add_library( # Sets the name of the library.
             coded2-jni

             SHARED

             src/main/cpp/codec2_jni.cpp ${CODEC2_SRCS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/include/)

#add_library(codec2 SHARED IMPORTED)
#set_target_properties(codec2
#                       PROPERTIES IMPORTED_LOCATION
#                       ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libcodec2.so)

#
# codec2 library sources
#


#
# Setup the codec2 library
#
#Message(${CMAKE_CURRENT_SOURCE_DIR})
#add_library(codec2 SHARED ${CODEC2_SRCS})
#target_link_libraries(codec2 ${CMAKE_REQUIRED_LIBRARIES})

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       coded2-jni

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib})
