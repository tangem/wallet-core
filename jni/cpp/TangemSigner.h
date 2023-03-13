#ifndef JNI_TW_TANGEMSIGNER_H
#define JNI_TW_TANGEMSIGNER_H

#include <jni.h>
#include <TrustWalletCore/TWBase.h>

TW_EXTERN_C_BEGIN

JNIEXPORT
jbyteArray JNICALL Java_wallet_core_java_TangemSigner_nativeSignExternally(JNIEnv *env, jclass thisClass, jbyteArray publicKey, jbyteArray input, jint coin, jobject signer);

TW_EXTERN_C_END

#endif // JNI_TW_TANGEMSIGNER_H