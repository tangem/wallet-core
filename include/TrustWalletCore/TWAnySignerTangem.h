#pragma once

#include </Applications/Xcode_15.4.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/functional"
#include "TWBase.h"
#include "TWCoinType.h"
#include "TWData.h"
#include "TWString.h"

// TANGEM
extern TWData *_Nonnull TWAnySignerSignExternally(TWData* _Nonnull data, enum TWCoinType coin, TWData *_Nonnull publicKey, std::function<const TWData *_Nonnull(const TWData *_Nonnull)> externalSigner);
