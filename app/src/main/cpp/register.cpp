//
// Created by Administrator on 2019-05-05.
//
#include <iostream>
#include "com_chinaso_addnative_Register.h"
jstring  Java_com_chinaso_addnative_Register_staticRegister
        (JNIEnv *jniEnv, jclass ){
    return jniEnv->NewStringUTF("static Register");
}
void callJavaMethod (JNIEnv *env, jobject thiz) {
    jclass clazz = env->FindClass("com/chinaso/addnative/MainActivity");//在哪个类中
    if (clazz == NULL) {
        std::cout << "find class MainActivity error" <<std::endl;
        return;
    }
    jmethodID id = env->GetStaticMethodID(clazz, "methodCalledByJni","(Ljava/lang/String;)V");//找到方法ID和签名
    if (id == NULL) {
        std::cout << "find method methodCalledByJni error" <<std::endl;
    }
    jstring msg = env->NewStringUTF("called JavaMethod");
    env->CallStaticVoidMethod(clazz, id, msg);//调用
}
/**
 * 可以自己随便命名的本地方法，只需要在对应的数据结构中注册
 * @param env
 * @param jobj
 * @return
 */
jstring dynamic_register(JNIEnv *env,jobject jobj){
    char* str = "dynamic register";
    callJavaMethod(env, jobj);//调用java层的方法。
    return env->NewStringUTF(str);
}
/**
 *c++ 函数名与JAVA函数名的映射表{Java中的函数名，（函数参数表）返回值签名，C++中的函数名}
 * 其中参数表返回值签名是为了重载同名函数能够有所区分
 *
 *  JNINativeMethod 结构体的数组是固有的。
 * 结构体参数1：对应java类总的native方法
 * 结构体参数2：函数签名
 * 结构体参数3：c/c++ 种对应的方法名
 */
static JNINativeMethod gMethods[] = {
        {"dynamicRegister","()Ljava/lang/String;",(void *)dynamic_register }
};

JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = JNI_FALSE;
    if (jvm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }
    if (env == NULL) {
        return result;
    }
    jclass clazz = env->FindClass("com/chinaso/addnative/Register");
    if (clazz == NULL) {
        return result;
    }
    if(env->RegisterNatives(clazz, gMethods, sizeof(gMethods)/ sizeof(gMethods[0]))<0) {
        return result;
    }
    result = JNI_VERSION_1_6;
    return result;
}

