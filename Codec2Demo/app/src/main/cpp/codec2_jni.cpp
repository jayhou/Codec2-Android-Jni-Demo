#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/LogUtils.h"
#include "include/codec2.h"
#include "include/codec2_internal.h"

static short *buf;
static unsigned char *bits;
static int nsam, nbit, nbyte;
static struct CODEC2 *codec2;

extern "C"
void
Java_com_huami_watch_codec2_Codec2_initCodec2(
        JNIEnv *env,
        jobject obj,
        jint mode

) {
    codec2 = codec2_create(mode);
    nsam = codec2_samples_per_frame(codec2);
    buf = (short *) malloc(nsam * sizeof(short));
    nbit = codec2_bits_per_frame(codec2);
    nbyte = (nbit + 7) / 8;
    bits = (unsigned char *) malloc(nbyte * sizeof(char));
    LOGD("length of bits:%d, lenght of short:%d", nbyte, nsam);
}

extern "C"
jint
Java_com_huami_watch_codec2_Codec2_getDecodeDataLen(
        JNIEnv *env,
        jobject obj
) {
    return nbyte;
}

extern "C"
jint Java_com_huami_watch_codec2_Codec2_getEncodeDataLen(
        JNIEnv *env,
        jobject obj
) {
    return nsam;
}

extern "C"
jbyteArray
Java_com_huami_watch_codec2_Codec2_codec2Encode(
        JNIEnv *env,
        jobject obj,
        jshortArray input,
        jint data_len) {

    if (data_len != nsam) {
        LOGE("wrong data length!!, expect:%d, but:%d", nsam, data_len);
        return NULL;
    }

    if (input == NULL) {
        LOGE("NULL input array !!!");
        return NULL;
    }

    jshort *input_data = env->GetShortArrayElements(input, NULL);

    if (input_data == NULL) {
        LOGE("error GetShortArrayElements of input");
        return NULL;
    }

    jint length = env->GetArrayLength(input);
    int i;
    int len = length;
    if (data_len != len) {
        LOGE("wrong input data array len!! expect:%d, but:%d", data_len, len);
        env->ReleaseShortArrayElements(input, input_data, 0);
        return NULL;
    }

    LOGD("short buf(save input data) len:%d, input_data len:%d, bytes bits(encode result) len:%d",
         nsam, len, nbyte);

    for (i = 0; i < len; i++) {
        buf[i] = input_data[i];
    }
    codec2_encode(codec2, bits, buf);


    if (bits == 0) {
        LOGE("encode error!!!");
        return NULL;
    }
    LOGD("nsam :%d   nbit:%d   nbyte:%d  gray:%d", nsam, nbit, nbyte, codec2->gray);
    for (i = 0; i < nsam; i++) {
        LOGD("%d ", buf[i]);
    }
    jbyteArray out = NULL;
    out = env->NewByteArray(nbyte);
    jbyte *bitsBuf = (jbyte *) malloc(nbyte * sizeof(jbyte));

    if (bitsBuf == NULL) {
        LOGE("no space for malloc bitsBuff of %d Bytes", nbyte * sizeof(jbyte));
        return NULL;
    }

    for (i = 0; i < nbyte; i++) {
        bitsBuf[i] = bits[i];
    }
    env->SetByteArrayRegion(out, 0, nbyte, bitsBuf);
    env->ReleaseShortArrayElements(input, input_data, 0);
    free(bitsBuf);
    return out;
}


extern "C"
jshortArray
Java_com_huami_watch_codec2_Codec2_codec2Decode(
        JNIEnv *env,
        jobject obj,
        jbyteArray decode_data,
        jint data_len) {
    if (data_len != nbyte) {
        LOGE("wrong data length!! expect:%d, but:%d", nbyte, data_len);
        return NULL;
    }

    unsigned char *data = (unsigned char *) malloc(data_len * sizeof(char));

    if (data == NULL) {
        LOGE("nospace for malloc %d bytes", data_len * sizeof(char));
        return NULL;
    }

    jbyte *jbyte_data = env->GetByteArrayElements(decode_data, NULL);
    if (jbyte_data == NULL) {
        LOGE("error GetByteArrayElements of decode_data");
        return NULL;
    }
    jint lenght = env->GetArrayLength(decode_data);
    LOGD("lenght of decode_data:%d", lenght);
    int i;
    for (i = 0; i < lenght; i++) {
        data[i] = jbyte_data[i];
    }

    codec2_decode(codec2, buf, data);

    if (buf == NULL) {
        LOGE("decode error!!!");
    }

    jshortArray out_decode = NULL;
    out_decode = env->NewShortArray(nsam);
    jshort *short_buf = (jshort *) malloc(nsam * sizeof(jshort));
    for (i = 0; i < nsam; i++) {
        short_buf[i] = buf[i];
    }
    env->SetShortArrayRegion(out_decode, 0, nsam, short_buf);
    env->ReleaseByteArrayElements(decode_data, jbyte_data, 0);
    free(short_buf);
    return out_decode;
}

extern "C"
void
Java_com_huami_watch_codec2_Codec2_codec2Destroy(
        JNIEnv *env,
        jobject obj
) {
    free(buf);
    free(bits);
    codec2_destroy(codec2);
}
