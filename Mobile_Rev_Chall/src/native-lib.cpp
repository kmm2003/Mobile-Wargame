#include <jni.h>
#include <string>
#include <iostream>
#include <cstring>

void xor_strings(const char str1[], const char str2[], int len1, int len2, char result[]) {
    int min_len = len1 < len2 ? len1 : len2;
    for (int i = 0; i < min_len; i++) {
        result[i] = str1[i] ^ str2[i % len2];
    }
}

char* generator(const char key[36]) {
    const char* secret_data = "c2890d44d06bafb6c7b4aa194857ccbc12450118a063b4aae95277f0bc1752c75abf0124";
    const int len = strlen(secret_data) / 2;

    unsigned char data[len + 1];
    for (int i = 0; i < len; i++) {
        data[i] = (unsigned char)((strtol(secret_data + i * 2, NULL, 16) << 4) + strtol(secret_data + i * 2 + 1, NULL, 16));
    }
    data[len] = '\0';

    unsigned char AA[len];
    for (int i = 0; i < len; ++i) {
        AA[i] = data[i] ^ 0xF0;
    }

    char ResultData[len * 2 + 1];
    memset(ResultData, 0, len * 2 + 1);

    for (int i = 0; i < len; ++i) {
        sprintf(ResultData + strlen(ResultData), "%02x", AA[i]);
    }

    char* secret = strdup(ResultData);

    secret[72] = '0';

    int leng = strlen(secret);
    char secretkey[leng / 2 + 1];

    for (int i = 0; i < leng; i += 2){
        sscanf(secret + i, "%2x", &secretkey[i / 2]);
    }
    secretkey[leng / 2] = '\0';

    int len1 = strlen(secretkey);
    int len2 = 36; // flag 배열의 크기를 36으로 설정
    char* flag = new char[len2];

    xor_strings(secretkey, key, len1, len2, flag);

    free(secret);

    return flag;
}

extern "C" JNIEXPORT jboolean JNICALL Java_com_dreamhack_reversing_CodeCheck_chall(
        JNIEnv* env,
        jobject, jstring arg1) {
    char key[36];
    char *flag;

    const char *arg = env->GetStringUTFChars(arg1, 0);
    env->ReleaseStringUTFChars(arg1, arg);

    memcpy(key, arg, 36);

    flag = generator(key);

    //printf("%s", flag);

    delete[] flag;  // 동적으로 할당된 메모리 해제

    return 1;
}
