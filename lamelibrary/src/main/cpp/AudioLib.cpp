//
// Created by frank on 2019/10/11.
//
#include <jni.h>
#include <string>
#include <android/log.h>
#include "include/lame/lame.h"

#define TAG "AudioLib"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
#define FUN_PREFIX(name)Java_com_frank_lamelibrary_MP3Encoder_00024Companion_##name

extern "C" JNIEXPORT jstring JNICALL FUN_PREFIX(getLameVersion)(JNIEnv *env, jclass) {
    const char *versionChar = get_lame_version();
    jstring version = env->NewStringUTF(versionChar);
    return version;
};


extern "C" JNIEXPORT jint JNICALL FUN_PREFIX(init)(JNIEnv *env, jclass, jstring pPath, jstring mPath) {
    int ret = -1;
    const char *pcmPath = env->GetStringUTFChars(pPath, NULL);
    const char *mp3Path = env->GetStringUTFChars(mPath, NULL);
    FILE *pcmFile = fopen(pcmPath, "rb");
    if (pcmFile) {
        FILE *mp3File = fopen(mp3Path, "wb");
        if (mp3File) {
            lame_global_flags *lameClient = lame_init();
            lame_set_in_samplerate(lameClient, 44100);
            lame_set_out_samplerate(lameClient, 44100);
            lame_set_num_channels(lameClient, 2);
            lame_set_brate(lameClient, 16);
            lame_init_params(lameClient);
            ret = 0;
        }
    }
    if (env->ExceptionCheck()) {
        LOGE("init方法异常");
    }

    env->ReleaseStringUTFChars(pPath, pcmPath);
    env->ReleaseStringUTFChars(mPath, mp3Path);
    return ret;
};

