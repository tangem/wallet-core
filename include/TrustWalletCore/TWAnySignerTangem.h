#include <functional>
#include "TWBase.h"
#include "TWCoinType.h"
#include "TWData.h"
#include "TWString.h"

extern TWData *_Nonnull TWAnySignerSignExternallyAndroid(TWData* _Nonnull input, enum TWCoinType coin, TWData *_Nonnull publicKey, std::function<const TWData *_Nonnull(const TWData *_Nonnull)> externalSigner);