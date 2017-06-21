package com.huami.watch.codec2demo;

/**
 * Created by jayhou on 17-6-21.
 */

public class MemoryUtils {
    private MemoryUtils() {
    }

    public static byte[] toByteArray(short[] src, int len) {
        if (len <= 0) {
            return null;
        }
        byte[] dest = new byte[len * 2];
        for (int i = 0; i < len; ++i) {
            dest[i * 2 + 1] = (byte) (src[i] >> 8);
            dest[i * 2] = (byte) (src[i] >> 0);
        }
        return dest;
    }

    public static short[] toShortArray(byte[] src, int start, int len) {
        if (len < 0 || start % 2 != 0 || len % 2 != 0) {
            return null;
        }
        short[] dest = new short[(len - start) / 2];
        for (int i = 0; i < dest.length; ++i) {
            dest[i] = (short) ((0xff & src[i * 2 + 1]) << 8);
            dest[i] = (short) (dest[i] | 0xff & src[i * 2 ]);
        }
        return dest;
    }
}