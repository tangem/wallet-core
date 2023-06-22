// Copyright © 2017-2022 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Entry.h"

#include "AddressV3.h"
#include "Signer.h"

namespace TW::Cardano {

// Note: avoid business logic from here, rather just call into classes like Address, Signer, etc.

bool Entry::validateAddress([[maybe_unused]] TWCoinType coin, const std::string& address, [[maybe_unused]] const PrefixVariant& addressPrefix) const {
    return AddressV3::isValidLegacy(address);
}

std::string Entry::deriveAddress([[maybe_unused]] TWCoinType coin, const PublicKey& publicKey, [[maybe_unused]] TWDerivation derivation, [[maybe_unused]] const PrefixVariant& addressPrefix) const {
    return AddressV3(publicKey).string();
}

Data Entry::addressToData([[maybe_unused]] TWCoinType coin, const std::string& address) const {
    return AddressV3(address).data();
}

void Entry::sign([[maybe_unused]] TWCoinType coin, const TW::Data& dataIn, TW::Data& dataOut) const {
    signTemplate<Signer, Proto::SigningInput>(dataIn, dataOut);
}

void Entry::plan([[maybe_unused]] TWCoinType coin, const Data& dataIn, Data& dataOut) const {
    planTemplate<Signer, Proto::SigningInput>(dataIn, dataOut);
}

/// TANGEM
Data Entry::preImageHashes([[maybe_unused]] TWCoinType coin, const Data& txInputData) const {
    return txCompilerTemplate<Proto::SigningInput, Proto::PreSigningOutput>(
        txInputData, [](auto&& input, auto&& output) { output = Signer::preImageHashes(input); });
}
/// TANGEM
void Entry::compile([[maybe_unused]] TWCoinType coin, const Data& txInputData, const std::vector<Data>& signatures,
                    const std::vector<PublicKey>& publicKeys, Data& dataOut) const {
    auto txCompilerFunctor = [&signatures, &publicKeys](auto&& input, auto&& output) noexcept {
        if (signatures.empty() || publicKeys.empty()) {
            output.set_error(Common::Proto::Error_invalid_params);
            output.set_error_message("empty signatures or publickeys");
            return;
        }

        if (signatures.size() != publicKeys.size()) {
            output.set_error(Common::Proto::Error_invalid_params);
            output.set_error_message("signatures size and publickeys size not equal");
            return;
        }

        HashPubkeyList externalSignatures;
        auto insertFunctor = [](auto&& signature, auto&& pubkey) noexcept {
            return std::make_pair(signature, pubkey.bytes);
        };
        transform(begin(signatures), end(signatures), begin(publicKeys),
                  back_inserter(externalSignatures), insertFunctor);

        output = Signer::sign(input, externalSignatures);
    };

    dataOut = txCompilerTemplate<Proto::SigningInput, Proto::SigningOutput>(txInputData,
                                                                            txCompilerFunctor);
}

} // namespace TW::Cardano
