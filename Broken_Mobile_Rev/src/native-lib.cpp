#include <jni.h>
#include <string>
#include <iostream>
void xor_strings(char str1[], char str2[], int len1, int len2, char result[]) {
    int i;
    for (i = 0; i < len1; i++) {
        result[i] = str1[i] ^ str2[i % len2];
    }
}

char *generator(char key[24])
{
    char *secret;
    int len = strlen("a49895d0bb9589d09983d0b2a49895d0bb9589d09983d0b2");
    unsigned char data[len / 2 + 1];
    int i;

    for (i = 0; i < len; i += 2)
    {
        data[i / 2] = (unsigned char)((strtol("a49895d0bb9589d09983d0b2a49895d0bb9589d09983d004" + i, NULL, 16) << 4) + strtol("a49895d0bb9589d09983d0b2a49895d0bb9589d099a49895" + i + 1, NULL, 16));
    }

    unsigned char AA[len / 2];
    int v16 = 0;
    int v20;
    for (v20 = 0; v16 < len / 2; ++v20)
    {
        AA[v20] = (unsigned char)(data[v16] ^ 0xF0);
        ++v16;
    }

    char ResultData[len];
    memset(ResultData, 0, len);
    int v5_1;
    for (v5_1 = 0; v5_1 < len / 2; ++v5_1)
    {
        sprintf(ResultData + strlen(ResultData), "%x", (AA[v5_1] >> 4 & 15));
        sprintf(ResultData + strlen(ResultData), "%x", (AA[v5_1]) & 15);
    }

    secret = strdup(ResultData);

    secret[46] = '0';

    int leng = strlen(secret);
    char secretkey[leng / 2 + 1];

    for (int i = 0; i < leng; i += 2){
        sscanf(secret + i, "%2x", &secretkey[i / 2]);
    }
    secretkey[len / 2] = '\0';

    int len1 = strlen(secretkey);
    int len2 = strlen(key);
    static char flag[24];

    xor_strings(secretkey, key, len1, len2, flag);

    return flag;
}

extern "C" JNIEXPORT jboolean JNICALL Java_com_dreamhack_reversing_CodeCheck_keyme(
        JNIEnv* env,
        jobject, jstring arg1) {
    char key[24];

    // Broken Parsing!!
    // Therefore, hooking using frida is not possible
    /*
    const char *arg = env->GetStringUTFChars(arg1, 0);
    env->ReleaseStringUTFChars(arg1, arg);
    */
    memcpy(key, arg, 24);

    generator(key);

    return 1;
}

