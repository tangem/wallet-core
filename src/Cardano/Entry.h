// SPDX-License-Identifier: Apache-2.0
//
// Copyright © 2017 Trust Wallet.

#pragma once

#include "../CoinEntry.h"

namespace TW::Cardano {

/// Entry point for implementation of Cardano coin.
/// Note: do not put the implementation here (no matter how simple), to avoid having coin-specific includes in this file
class Entry final : public CoinEntry {
public:
    bool validateAddress(TWCoinType coin, const std::string& address, const PrefixVariant& addressPrefix) const;
    std::string deriveAddress(TWCoinType coin, const PublicKey& publicKey, TWDerivation derivation, const PrefixVariant& addressPrefix) const;
    Data addressToData(TWCoinType coin, const std::string& address) const;
    void sign(TWCoinType coin, const Data& dataIn, Data& dataOut) const;
    void plan(TWCoinType coin, const Data& dataIn, Data& dataOut) const;

    Data preImageHashes(TWCoinType coin, const Data& txInputData) const;
    void compile(TWCoinType coin, const Data& txInputData, const std::vector<Data>& signatures, const std::vector<PublicKey>& publicKeys, Data& dataOut) const;
    void compileWithMultipleSignatures(TWCoinType coin, const Data& txInputData, const std::vector<Data>& signatures, const std::vector<PublicKey>& publicKeys, Data& dataOut) const;

};

} // namespace TW::Cardano
