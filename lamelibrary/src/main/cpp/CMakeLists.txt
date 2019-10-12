cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSTDC_HEADERS")

add_library(
        lame SHARED
        include/lame/bitstream.c
        include/lame/encoder.c
        include/lame/fft.c
        include/lame/gain_analysis.c
        include/lame/id3tag.c
        include/lame/lame.c
        include/lame/mpglib_interface.c
        include/lame/newmdct.c
        include/lame/presets.c
        include/lame/psymodel.c
        include/lame/quantize.c
        include/lame/quantize_pvt.c
        include/lame/reservoir.c
        include/lame/set_get.c
        include/lame/tables.c
        include/lame/takehiro.c
        include/lame/util.c
        include/lame/vbrquantize.c
        include/lame/VbrTag.c
        include/lame/version.c
        include/lame/vector/xmm_quantize_sub.c
        Mp3Encoder.c
)

add_library(
        audio-lib
        SHARED
        AudioLib.cpp
)

target_link_libraries(audio-lib
        lame
        android
        log)