// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <TrustWalletCore/TWAnySigner.h>

#include "Coin.h"

using namespace TW;

TWData* _Nonnull TWAnySignerSign(TWData* _Nonnull data, enum TWCoinType coin) {
    const Data& dataIn = *(reinterpret_cast<const Data*>(data));
    Data dataOut;
    TW::anyCoinSign(coin, dataIn, dataOut);
    return TWDataCreateWithBytes(dataOut.data(), dataOut.size());
}

// TANGEM
TWData* _Nonnull TWAnySignerSignExternally(TWData* _Nonnull data, enum TWCoinType coin, TWData *_Nonnull publicKey, std::function<const TWData *_Nonnull(const TWData *_Nonnull)> externalSigner) {
    // Just a conversion between TWData and TW::Data
    auto dataExternalSigner = [externalSigner](Data dataToSign) -> Data {
        const TWData* twDataToSign = TWDataCreateWithBytes(dataToSign.data(), dataToSign.size());
        const TWData* twDataSigned = externalSigner(twDataToSign);

        const Data& dataSigned = *(reinterpret_cast<const Data*>(twDataSigned));
        return dataSigned;
    };
    const Data& publicKeyData = *(reinterpret_cast<const Data*>(publicKey));
    const Data& dataIn = *(reinterpret_cast<const Data*>(data));
    Data dataOut;
    TW::anyCoinSignExternally(coin, dataIn, dataOut, publicKeyData, dataExternalSigner);
    return TWDataCreateWithBytes(dataOut.data(), dataOut.size());
}

TWData* _Nonnull TWAnySignerSignExternally(TWData* _Nonnull data, enum TWCoinType coin, TWData *_Nonnull publicKey, TWData* (*externalSigner)(TWData*)) {
    return TWAnySignerSignExternally(data, coin, publicKey, std::function(externalSigner));
}

TWString *_Nonnull TWAnySignerSignJSON(TWString *_Nonnull json, TWData *_Nonnull key, enum TWCoinType coin) {
    const Data& keyData = *(reinterpret_cast<const Data*>(key));
    const std::string& jsonString = *(reinterpret_cast<const std::string*>(json));
    auto result = TW::anySignJSON(coin, jsonString, keyData);
    return TWStringCreateWithUTF8Bytes(result.c_str());
}
extern bool TWAnySignerSupportsJSON(enum TWCoinType coin) {
    return TW::supportsJSONSigning(coin);
}

TWData* _Nonnull TWAnySignerPlan(TWData* _Nonnull data, enum TWCoinType coin) {
    const Data& dataIn = *(reinterpret_cast<const Data*>(data));
    Data dataOut;
    TW::anyCoinPlan(coin, dataIn, dataOut);
    return TWDataCreateWithBytes(dataOut.data(), dataOut.size());
}
