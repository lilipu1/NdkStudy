//
// Created by frank on 2019/10/8.
//
#include <jni.h>
#include <string>
#include "FirstCFile.h"

#include <android/log.h>

#define TAG "frank"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

extern "C" JNIEXPORT jstring
JNICALL
Java_com_frank_myndkmodule_TestAct_stringFromJNI(JNIEnv* env, jobject) {
    LOGE("你好,jni");
    std::string hello = "Hello,JNI";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring
JNICALL
Java_com_frank_myndkmodule_TestAct_processFile(JNIEnv* env, jclass clazz, jstring path) {
    const char *file_path = env->GetStringUTFChars(path, NULL);
    if(file_path != NULL){
        LOGE("from c file_path %s",file_path);
    }
    FILE* file = fopen(file_path,"a+");
    if(file != NULL){
       LOGE("from c open file success");
    }
    char data[] = "i am a boy";
    int count = fwrite(data,strlen(data),1,file);
    if(count>0){
        fclose(file);
    }
    env->ReleaseStringUTFChars(path,file_path);
}
