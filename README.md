# JNILocalRef
jni 局部引用的内存泄漏及避免

Local Reference 在 native method 执行完成后，会自动被释放，似乎不会造成任何的内存泄漏。但这是错误的。对 Local Reference 的理解不够，会造成潜在的内存泄漏。

实例
JNIEXPORT void JNICALL
Java_com_kun_jnilocalref_MainActivity_createNativeLocalRef(JNIEnv *env, jobject instance,
                                                           jint count) {
    int i = 0;
    for (; i < count; ++i) {
        jstring str = env->NewStringUTF("hello");
    }
    LOGE("count :%d", i);

}

运行结果
/DEBUG: *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** ***
/DEBUG: Build fingerprint: 'honor/FRD-AL00/HWFRD:6.0/HUAWEIFRD-AL00/C00B153:user/release-keys'
/DEBUG: Revision: '0'
/DEBUG: ABI: 'arm64'
/DEBUG: pid: 27947, tid: 27947, name: un.jni_callback >>> com.kun.jni_callback <<<
/DEBUG: signal 6 (SIGABRT), code -6 (SI_TKILL), fault addr --------
/DEBUG: Abort message: 'art/runtime/indirect_reference_table.cc:125] JNI ERROR (app bug): local reference table overflow (max=512)'



正确的修改方法：

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
