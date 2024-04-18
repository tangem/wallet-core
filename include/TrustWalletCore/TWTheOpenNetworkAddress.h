// SPDX-License-Identifier: Apache-2.0
//
// Copyright © 2017 Trust Wallet.

// TANGEM

#pragma once

#include "TWBase.h"
#include "TWString.h"
#include "TWData.h"

TW_EXTERN_C_BEGIN

struct TWPublicKey;

/// Represents a TheOpenNetwork address.
TW_EXPORT_CLASS
struct TWTheOpenNetworkAddress;

/// Compares two addresses for equality.
///
/// \param lhs left Non-null TheOpenNetwork address to be compared
/// \param rhs right Non-null TheOpenNetwork address to be compared
/// \return true if both address are equal, false otherwise
TW_EXPORT_STATIC_METHOD
bool TWTheOpenNetworkAddressEqual(struct TWTheOpenNetworkAddress *_Nonnull lhs, struct TWTheOpenNetworkAddress *_Nonnull rhs);

/// Determines if the string is a valid TheOpenNetwork address.
///
/// \param string Non-null string.
/// \return true if it's a valid address, false otherwise
TW_EXPORT_STATIC_METHOD
bool TWTheOpenNetworkAddressIsValidString(TWString *_Nonnull string);

/// Create an address from a base58 string representation.
///
/// \param string Non-null string
/// \note Must be deleted with \TWTheOpenNetworkAddressDelete
/// \return Non-null TheOpenNetworkAddress
TW_EXPORT_STATIC_METHOD
struct TWTheOpenNetworkAddress *_Nullable TWTheOpenNetworkAddressCreateWithString(TWString *_Nonnull string);

/// Create an address from a public key and a prefix byte.
///
/// \param publicKey Non-null public key
/// \param prefix public key prefix
/// \note Must be deleted with \TWTheOpenNetworkAddressDelete
/// \return Non-null TheOpenNetworkAddress
TW_EXPORT_STATIC_METHOD
struct TWTheOpenNetworkAddress *_Nonnull TWTheOpenNetworkAddressCreateWithPublicKey(struct TWPublicKey *_Nonnull publicKey);

/// Delete a TheOpenNetwork address
///
/// \param address Non-null TheOpenNetworkAddress
TW_EXPORT_METHOD
void TWTheOpenNetworkAddressDelete(struct TWTheOpenNetworkAddress *_Nonnull address);

/// Returns the address string representation.
///
/// \param address Non-null TheOpenNetworkAddress
/// \return Address description as a non-null string
TW_EXPORT_PROPERTY
TWString *_Nonnull TWTheOpenNetworkAddressDescription(struct TWTheOpenNetworkAddress *_Nonnull address);

/// Returns the address string representation with additional parameters.
///
/// \param address Non-null TheOpenNetworkAddress
/// \return Address description as a non-null string
TW_EXPORT_METHOD
TWString *_Nonnull TWTheOpenNetworkAddressStringRepresentation(struct TWTheOpenNetworkAddress *_Nonnull address, bool userFriendly, bool bounceable, bool testOnly);

TW_EXTERN_C_END
