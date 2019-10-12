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

extern "C" JNIEXPORT jintArray JNICALL
TESTFUN(processIntArray)(JNIEnv *env, jclass clazz, jintArray array) {
    /*jint nativeArray[5];
    env->GetIntArrayRegion(array,0,5,nativeArray);
    int i;
    for(i=0;i<5;i++){
        nativeArray[i] += 5;
        LOGE("from c int %d",nativeArray[i]);
    }
    env->SetIntArrayRegion(array,0,5,nativeArray);*/
    jint *nativeArray = env->GetIntArrayElements(array, NULL);
    jsize length = env->GetArrayLength(array);
    int i;
    for (i = 0; i < length; i++) {
        nativeArray[i] = nativeArray[i] + 3;
        LOGE("from c int %d", nativeArray[i]);
    }
    env->ReleaseIntArrayElements(array, nativeArray, 0);//模式0,释放指针,同时把操作后的数组拷贝到原数组中
    return array;
}

extern "C" JNIEXPORT void JNICALL TESTFUN(invokeKotlinStaticMethod)(JNIEnv *env, jclass clazz) {
    jstring path = env->NewStringUTF("com/frank/myndkmodule/TestAct");
    jstring methodName = env->NewStringUTF("sayHello");
    jclass clazzA = env->FindClass(env->GetStringUTFChars(path, NULL));
    jmethodID staticMethodId = env->GetStaticMethodID(clazzA,
                                                      env->GetStringUTFChars(methodName, NULL),
                                                      "()V");
    env->CallStaticVoidMethod(clazzA, staticMethodId);

    jstring name = env->NewStringUTF("frank");
    jfieldID staticFieldId = env->GetStaticFieldID(clazzA, "name", "Ljava/lang/String;");
    if (staticFieldId != NULL) {
        env->SetStaticObjectField(clazzA, staticFieldId, name);
    }

    env->DeleteLocalRef(path);
    env->DeleteLocalRef(methodName);
    env->DeleteLocalRef(clazzA);
    env->DeleteLocalRef(name);
}

extern "C" JNIEXPORT void JNICALL
TESTFUN(invokeKotlinMethod)(JNIEnv *env, jclass clazz, jstring name) {
    jstring path = env->NewStringUTF("com/frank/myndkmodule/TestAct");
    jclass clazzA = env->FindClass(env->GetStringUTFChars(path, NULL));
    jstring constructStringName = env->NewStringUTF("<init>");
    const char *constructChar = env->GetStringUTFChars(constructStringName, NULL);
    jmethodID constructId = env->GetMethodID(clazzA, constructChar, "()V");
    jobject act = env->NewObject(clazzA, constructId);

    jfieldID id = env->GetFieldID(clazzA, "address", "Ljava/lang/String;");
    jstring add = env->NewStringUTF("长沙");
    env->SetObjectField(act, id, add);

    jstring methodName = env->NewStringUTF("printAddress");
    const char *methodStringName = env->GetStringUTFChars(methodName, NULL);
    jmethodID methodId = env->GetMethodID(clazzA, methodStringName, "()Ljava/lang/String;");
    env->CallObjectMethod(act, methodId);

    env->DeleteLocalRef(path);
    env->DeleteLocalRef(clazzA);
    env->ReleaseStringUTFChars(constructStringName, constructChar);
    env->DeleteLocalRef(constructStringName);
    env->DeleteLocalRef(act);
    env->ReleaseStringUTFChars(methodName, methodStringName);
    env->DeleteLocalRef(methodName);
    env->DeleteLocalRef(add);
}
