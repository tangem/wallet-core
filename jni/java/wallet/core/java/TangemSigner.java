package wallet.core.java;

import com.google.protobuf.MessageLite;
import com.google.protobuf.Parser;

import wallet.core.jni.CoinType;

public class TangemSigner {

    public static <T extends MessageLite> T signExternally(MessageLite input, CoinType coin, Parser<T> parser, Signer signer) throws Exception {
        byte[] data = input.toByteArray();
        byte[] outputData = nativeSignExternally(signer.getPublicKey().data(), data, coin.value(), signer);
        T output = parser.parseFrom(outputData);
        outputData = null;
        return output;
    }

    public static native byte[] nativeSignExternally(byte[] publicKey, byte[] data, int coin, Signer signer);

}
