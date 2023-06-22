// Copyright © 2017-2022 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Transaction.h"
#include "../proto/Cardano.pb.h"
#include "Data.h"

#include <string>
#include <map>
#include <utility>

namespace TW::Cardano {

typedef std::vector<std::pair<Data, Data>> SignaturePubkeyList;

class Signer {
public:
    /// Signs a Proto::SigningInput transaction
    static Proto::SigningOutput sign(const Proto::SigningInput& input) noexcept {
        Signer signer = Signer(input);
        return signer.sign();
    }

    // TANGEM
    /// SigningOutput with external signatures 
    static Proto::SigningOutput sign(const Proto::SigningInput& input, std::optional<SignaturePubkeyList> optionalExternalSigs) noexcept {
        Signer signer = Signer(input);
        return signer.sign(optionalExternalSigs);
    }

public:
    Proto::SigningInput input;
    TransactionPlan _plan;

    explicit Signer(Proto::SigningInput input): input(std::move(input)) {}

    Proto::SigningOutput sign();
    // TANGEM
    // Sign with external signatures 
    Proto::SigningOutput sign(std::optional<SignaturePubkeyList> optionalExternalSigs);

    // Sign using existing plan
    Proto::SigningOutput signWithPlan() const;

    // TANGEM
    // Sign with external signatures 
    Proto::SigningOutput signWithPlan(std::optional<SignaturePubkeyList> optionalExternalSigs) const;
    // Create plan from signing input
    TransactionPlan doPlan() const;
    /// Returns a transaction plan (utxo selection, fee estimation)
    static Proto::TransactionPlan plan(const Proto::SigningInput& input) noexcept {
        const auto signer = Signer(input);
        const auto plan = signer.doPlan();
        return plan.toProto();
    }
    // Build encoded transaction
    static Common::Proto::SigningError encodeTransaction(Data& encoded, Data& txId, const Proto::SigningInput& input, const TransactionPlan& plan, bool sizeEstimationOnly = false, std::optional<SignaturePubkeyList> optionalExternalSigs = {});
    // Build aux transaction object, using input and plan
    static Common::Proto::SigningError buildTransactionAux(Transaction& tx, const Proto::SigningInput& input, const TransactionPlan& plan);
    static Amount estimateFee(const Proto::SigningInput& input, Amount amount, const TokenBundle& requestedTokens, const std::vector<TxInput>& selectedInputs);
    static std::vector<TxInput> selectInputsWithTokens(const std::vector<TxInput>& inputs, Amount amount, const TokenBundle& requestedTokens);
    // Build list of public keys + signature
    static Common::Proto::SigningError assembleSignatures(std::vector<std::pair<Data, Data>>& signatures, const Proto::SigningInput& input, const TransactionPlan& plan, const Data& txId, bool sizeEstimationOnly = false);

    /// TANGEM
    /// Collect pre-image hashes to be signed
    static Proto::PreSigningOutput preImageHashes(const Proto::SigningInput& input) noexcept;
    static Common::Proto::SigningError collectPublicKeys(std::vector<Data>& publicKeys, const Proto::SigningInput& input, const TransactionPlan& plan);
};

} // namespace TW::Cardano
