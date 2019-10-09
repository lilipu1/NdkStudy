//
// Created by frank on 2019/10/8.
//
#include <jni.h>
#include <string>
#include "FirstCFile.h"

#include <android/log.h>

#define TAG "frank"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
#define TESTFUN(name)Java_com_frank_myndkmodule_TestAct_##name

extern "C" JNIEXPORT jstring
JNICALL
TESTFUN(stringFromJNI)(JNIEnv *env, jobject) {
    LOGE("你好,jni");
    return env->NewStringUTF("Hello,JNI");
}

extern "C" JNIEXPORT void
JNICALL
TESTFUN(processFile)(JNIEnv *env, jclass clazz, jstring path) {
    const char *file_path = env->GetStringUTFChars(path, NULL);
    if (file_path != NULL) {
        LOGE("from c file_path %s", file_path);
    }
    FILE *file = fopen(file_path, "a+");
    if (file != NULL) {
        LOGE("from c open file success");
    }
    char data[] = "i am a boy";
    int count = fwrite(data, strlen(data), 1, file);
    if (count > 0) {
        fclose(file);
    }
    env->ReleaseStringUTFChars(path, file_path);
}

extern "C" JNIEXPORT jintArray JNICALL TESTFUN(processIntArray)(JNIEnv *env,jclass clazz,jintArray array){
    jint nativeArray[5];
    env->GetIntArrayRegion(array,0,5,nativeArray);
    int i;
    for(i=0;i<5;i++){
        nativeArray[i] += 5;
        LOGE("from c int %d",nativeArray[i]);
    }
    env->SetIntArrayRegion(array,0,5,nativeArray);
    return array;
}
