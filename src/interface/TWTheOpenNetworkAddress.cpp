// TANGEM
#include <TrustWalletCore/TWTheOpenNetworkAddress.h>
#include <TrustWalletCore/TWPublicKey.h>

#include "../TheOpenNetwork/Address.h"
#include "../TheOpenNetwork/wallet/WalletV4R2.h"
#include "../TheOpenNetwork/WorkchainType.h"

#include <cstring>

bool TWTheOpenNetworkAddressEqual(struct TWTheOpenNetworkAddress* _Nonnull lhs, struct TWTheOpenNetworkAddress* _Nonnull rhs) {
    return lhs->impl.string(false) == rhs->impl.string(false);
}

bool TWTheOpenNetworkAddressIsValidString(TWString* _Nonnull string) {
    auto& s = *reinterpret_cast<const std::string*>(string);
    return TW::TheOpenNetwork::Address::isValid(s);
}

struct TWTheOpenNetworkAddress* _Nullable TWTheOpenNetworkAddressCreateWithString(TWString* _Nonnull string) {
    auto& s = *reinterpret_cast<const std::string*>(string);
    if (!TW::TheOpenNetwork::Address::isValid(s)) {
        return nullptr;
    }
    return new TWTheOpenNetworkAddress{TW::TheOpenNetwork::Address(s)};
}

struct TWTheOpenNetworkAddress* _Nonnull TWTheOpenNetworkAddressCreateWithPublicKey(struct TWPublicKey* _Nonnull publicKey) {
    return new TWTheOpenNetworkAddress{TW::TheOpenNetwork::WalletV4R2(publicKey->impl, TW::TheOpenNetwork::WorkchainType::Basechain).getAddress()};
}

void TWTheOpenNetworkAddressDelete(struct TWTheOpenNetworkAddress* _Nonnull address) {
    delete address;
}

TWString* _Nonnull TWTheOpenNetworkAddressDescription(struct TWTheOpenNetworkAddress* _Nonnull address) {
    const auto str = address->impl.string();
    return TWStringCreateWithUTF8Bytes(str.c_str());
}

TWString* _Nonnull TWTheOpenNetworkAddressStringRepresentation(struct TWTheOpenNetworkAddress* _Nonnull address, bool userFriendly, bool bounceable, bool testOnly) {
    const auto str = address->impl.string(userFriendly, bounceable, testOnly);
    return TWStringCreateWithUTF8Bytes(str.c_str());
}
