package com.huami.watch.codec2;

/**
 * Created by jayhou on 17-6-19.
 */

public class Codec2 {

    public static final int CODEC2_MODE_3200 = 0;
    public static final int CODE2_MODE_2400 = 1;
    public static final int CODEC2_MODE_1600 = 2;
    public static final int CODEC2_MODE_1400 = 3;
    public static final int CODEC2_MODE_1300 = 4;
    public static final int CODEC2_MODE_1200 = 5;
    public static final int CODEC2_MODE_700 = 6;
    public static final int CODEC2_MODE_700B = 7;
    public static final int CODEC2_MODE_700C = 8;

    static {
        System.loadLibrary("coded2-jni");
    }

    public static native void initCodec2(int mode);
    public static native int getDecodeDataLen();
    public static native int getEncodeDataLen();
    public static native byte[] codec2Encode(short[] input, int len);
    public static native short[] codec2Decode(byte[] input, int len);
    public static native void codec2Destroy();
}
