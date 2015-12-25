#ifndef _DES
#define _DES

#define ENCRYPT 0
#define DECRYPT 1
#define ENCRYPT_KEY "whosisyourdad"

#ifndef ONE_DES
#define  ONE_DES	1
#define  TRI_DES 	3
#endif

#define LOG_TAG "encryptor"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

void function_des(char cryp_decrypt, unsigned char* DES_DATA, unsigned char* DESKEY, unsigned char* DES_RESULT);

#endif
