// SPDX-License-Identifier: Apache-2.0
//
// Copyright © 2017 Trust Wallet.

#pragma once

#include "Data.h"
#include "PrivateKey.h"
#include "wallet/Wallet.h"

#include "proto/TheOpenNetwork.pb.h"

namespace TW::TheOpenNetwork {

/// Helper class that performs TheOpenNetwork transaction signing.
class Signer {
public:
    /// Hide default constructor
    Signer() = delete;

    /// Creates a signed transfer message
    static Data createTransferMessage(std::shared_ptr<Wallet> wallet, const PrivateKey& privateKey, const Proto::Transfer& transfer);
    
    // TANGEM
    static Data createTransferMessage(std::shared_ptr<Wallet> wallet, const PrivateKey& privateKey, const Proto::Transfer& transfer, const std::function<Data(Data)> externalSigner);

    /// Creates a signed jetton transfer message
    static Data createJettonTransferMessage(std::shared_ptr<Wallet> wallet, const PrivateKey& privateKey, const Proto::JettonTransfer& transfer);
    
    // TANGEM
    static Data createJettonTransferMessage(std::shared_ptr<Wallet> wallet, const PrivateKey& privateKey, const Proto::JettonTransfer& jettonTransfer, const std::function<Data(Data)> externalSigner);

    /// Signs a Proto::SigningInput transaction
    static Proto::SigningOutput sign(const Proto::SigningInput& input) noexcept;
    
    // TANGEM
    static Proto::SigningOutput sign(const Proto::SigningInput& input, const Data& publicKey, const std::function<Data(Data)> externalSigner) noexcept;
};

} // namespace TW::TheOpenNetwork
