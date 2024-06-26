// SPDX-License-Identifier: Apache-2.0
//
// Copyright © 2017 Trust Wallet.

@testable import WalletCore
import XCTest

class ScrollTests: XCTestCase {
    func testAddress() {
        let key = PrivateKey(data: Data(hexString: "828c4c48c2cef521f0251920891ed79e871faa24f64f43cde83d07bc99f8dbf0")!)!
                let pubkey = key.getPublicKeySecp256k1(compressed: false)
                let address = AnyAddress(publicKey: pubkey, coin: .scroll)
                let expected = AnyAddress(string: "0xe32DC46bfBF78D1eada7b0a68C96903e01418D64", coin: .scroll)!
        
                XCTAssertEqual(address.description, expected.description)
    }
}
