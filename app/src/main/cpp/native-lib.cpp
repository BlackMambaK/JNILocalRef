#include <jni.h>
#include <string>
#include <android/log.h>


static const char *kTAG = "LocalRef";

#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))

extern "C" {
JNIEXPORT jstring

JNICALL
Java_com_kun_jnilocalref_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT void JNICALL
Java_com_kun_jnilocalref_MainActivity_createNativeLocalRef(JNIEnv *env, jobject instance,
                                                           jint count) {
    int i = 0;
    for (; i < count; ++i) {
        jstring str = env->NewStringUTF("hello");
    }
    LOGE("count :%d", i);

}

JNIEXPORT void JNICALL
Java_com_kun_jnilocalref_MainActivity_createNativeLocalRef1(JNIEnv *env, jobject instance,
                                                            jint count) {

    int i = 0;
    for (; i < count; ++i) {
        if (env->PushLocalFrame(10) != 0) {
            LOGE("out of memory");
            break;
        }
        jstring str = env->NewStringUTF("hello");
        env->PopLocalFrame(NULL);
    }

    LOGE("count :%d", i);
}

JNIEXPORT void JNICALL
Java_com_kun_jnilocalref_MainActivity_createNativeLocalRef2(JNIEnv *env, jobject instance,
                                                            jint count) {

    if (env->EnsureLocalCapacity(count) != 0) {
        LOGE("out of memory");
        return;
    }
    int i = 0;
    for (; i < count; ++i) {
        jstring str = env->NewStringUTF("hello");
    }
    LOGE("count :%d", i);
}

JNIEXPORT void JNICALL
Java_com_kun_jnilocalref_MainActivity_createNativeLocalRef3(JNIEnv *env, jobject instance,
                                                            jint count) {

    int i = 0;
    for (; i < count; ++i) {
        jstring str = env->NewStringUTF("hello");
        env->DeleteLocalRef(str);
    }
    LOGE("count :%d", i);
}
}
