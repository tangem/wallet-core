#include <jni.h>
#include <stdio.h>
#include <vector>
#include <string.h>

#include "TangemSigner.h"
#include "TWJNI.h"
#include <TrustWalletCore/TWAnySignerTangem.h>

static JavaVM* cachedJVM;

TWData *_Nonnull callbackFunc(jobject signer, TWData *_Nonnull data) {
    JNIEnv *env;
    cachedJVM -> AttachCurrentThread(&env, NULL);

    jbyteArray a = TWDataJByteArray(data, env);
    jclass cls = env -> GetObjectClass(signer);
    jmethodID signMethodId = env -> GetMethodID(cls, "sign", "([B)[B");
    jbyteArray aret = (jbyteArray) env -> CallObjectMethod(signer, signMethodId, a);

    TWData *ret = TWDataCreateWithJByteArray(env, aret);
    cachedJVM -> DetachCurrentThread();
    return ret;
}

jbyteArray Java_wallet_core_java_TangemSigner_nativeSignExternally(JNIEnv *env, jclass thisClass, jbyteArray publicKey, jbyteArray input, jint coin, jobject signer) {
    env -> GetJavaVM(&cachedJVM);
    TWData *inputData = TWDataCreateWithJByteArray(env, input);
    TWData *publicKeyData = TWDataCreateWithJByteArray(env, publicKey);

    jobject globalSigner = env -> NewGlobalRef(signer);
    std::function<const TWData *_Nonnull(const TWData *_Nonnull)> externalSigner = std::bind(callbackFunc, globalSigner, std::placeholders::_1);
    TWData *outputData = TWAnySignerSignExternallyAndroid(inputData, static_cast<TWCoinType>(coin), publicKeyData, externalSigner);
    jbyteArray resultData = TWDataJByteArray(outputData, env);

    env -> DeleteGlobalRef(globalSigner);
    TWDataDelete(inputData);
    TWDataDelete(publicKeyData);
    return resultData;
}
