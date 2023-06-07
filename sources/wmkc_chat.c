#include <wmkc_chat.h>

/**
 * @brief 初始化对应用户的盐和密钥与初始向量
 * @authors SN-Grotesque
 * @note 无
 * @param obj 这是一个指针，指向wmkcChat对象的地址
 * @param password 这是一个指针，指向用户的密码口令字符串的地址
 * @return 返回一个wmkcErr对象，code为0代表无错误，如果为
 *         其他值，那么需检查message与code。
 */
WMKC_PRIVATE(wmkcErr_obj) wmkcChat_initCipher WMKC_OPEN_API
WMKC_OF((wmkcChat_obj *obj, wmkcString password))
{
    wmkcErr_obj error;
    if(!obj || !password) {
        wmkcErr_return(error, wmkcErr_ErrMemory,
            "wmkcChat_initCipher: obj or password is NULL.");
    }

    wmkcByte salt[WMKC_CHAT_SALT_SIZE]; // 声明临时盐
    wmkcByte *_key = wmkcNull; // 声明临时密钥指针
    wmkcByte *_iv = wmkcNull;  // 声明临时初始向量指针
    wmkcByte *buf = wmkcNull;  // 声明缓冲区指针

    // 为缓冲区申请内存空间
    if(!wmkcMemoryNew(wmkcByte *, buf, obj->snc->KN + SNC_BLOCKLEN)) {
        wmkcErr_return(error, wmkcErr_ErrMemory,
            "wmkcChat_initCipher: buf failed to apply for memory.");
    }
    // 初始化缓冲区和临时盐
    wmkcMemoryZero(buf, obj->snc->KN + SNC_BLOCKLEN);
    wmkcMemoryZero(salt, WMKC_CHAT_SALT_SIZE);

    // 将密钥和初始向量指针指向正确的缓冲区位置
    _key = buf;
    _iv = buf + obj->snc->KN;

    // 使用系统函数来生成密码学安全随机数
    error = wmkcRandom_urandom(salt, WMKC_CHAT_SALT_SIZE);
    if(error.code) {
        return error;
    }

    // 将临时盐的内容复制到wmkcChat对象的salt成员
    memcpy(obj->salt, salt, WMKC_CHAT_SALT_SIZE);

    // 通过用户密码口令和盐生成SNC加密算法的密钥和初始向量并储存至缓冲区。
    PKCS5_PBKDF2_HMAC(password, strlen(password), obj->salt, WMKC_CHAT_SALT_SIZE, 16,
        EVP_sha384(), obj->snc->KN + SNC_BLOCKLEN, buf);

    // 使用缓冲区内的密钥与初始向量来初始化SNC加密算法
    SNC_init(obj->snc, _key, _iv);

    // 将缓冲区的内容清零并释放其内存空间
    wmkcMemoryZero(buf, obj->snc->KN + SNC_BLOCKLEN);
    wmkcMemoryFree(buf);

    wmkcErr_return(error, wmkcErr_OK, "OK.");
}

/**
 * @brief 给wmkcChat对象申请内存空间
 * @authors SN-Grotesque
 * @note 无
 * @param obj 这是一个指针，指向wmkcChat对象指针的地址
 * @return 返回一个wmkcErr对象，code为0代表无错误，如果为
 *         其他值，那么需检查message与code。
 */
WMKC_PUBLIC(wmkcErr_obj) wmkcChat_new WMKC_OPEN_API
WMKC_OF((wmkcChat_obj **obj))
{
    wmkcErr_obj error;
    if(!obj) {
        wmkcErr_return(error, wmkcErr_ErrNULL, "wmkcChat_new: obj is NULL.");
    }
    // 为wmkcChat对象申请内存空间
    if(!wmkcMemoryNew(wmkcChat_obj *, (*obj), sizeof(wmkcChat_obj))) {
        wmkcErr_return(error, wmkcErr_ErrMemory,
            "wmkcChat_new: (*obj) failed to apply for memory.");
    }

    // 为wmkcChat对象name成员申请内存空间
    if(!wmkcMemoryNew(wmkcChar *, (*obj)->name, WMKC_CHAT_USERNAME_SIZE)) {
        wmkcErr_return(error, wmkcErr_ErrMemory,
            "wmkcChat_new: (*obj)->name failed to apply for memory.");
    }

    // 为wmkcChat对象hash成员申请内存空间
    if(!wmkcMemoryNew(wmkcByte *, (*obj)->hash, WMKC_CHAT_HASH_SIZE)) {
        wmkcErr_return(error, wmkcErr_ErrMemory,
            "wmkcChat_new: (*obj)->hash failed to apply for memory.");
    }

    // 为wmkcChat对象salt成员申请内存空间
    if(!wmkcMemoryNew(wmkcByte *, (*obj)->salt, WMKC_CHAT_SALT_SIZE)) {
        wmkcErr_return(error, wmkcErr_ErrMemory,
            "wmkcChat_new: (*obj)->salt failed to apply for memory.");
    }

    // 将wmkcChat对象的所有成员初始化
    wmkcMemoryZero((*obj)->name, WMKC_CHAT_USERNAME_SIZE);
    wmkcMemoryZero((*obj)->hash, WMKC_CHAT_HASH_SIZE);
    wmkcMemoryZero((*obj)->salt, WMKC_CHAT_SALT_SIZE);
    error = SNC_new(&((*obj)->snc), WMKC_CHAT_CIPHER_MODE);

    // 如果SNC_new函数出现错误就返回错误代码
    if(error.code) {
        return error;
    }

    wmkcErr_return(error, wmkcErr_OK, "OK.");
}

/**
 * @brief 释放wmkcChat对象的内存空间
 * @authors SN-Grotesque
 * @note 无
 * @param obj 这是一个指针，指向wmkcChat对象指针的地址
 * @return 返回一个wmkcErr对象，code为0代表无错误，如果为
 *         其他值，那么需检查message与code。
 */
WMKC_PUBLIC(wmkcErr_obj) wmkcChat_free WMKC_OPEN_API
WMKC_OF((wmkcChat_obj **obj))
{
    wmkcErr_obj error;
    if(!obj) {
        wmkcErr_return(error, wmkcErr_ErrNULL, "wmkcChat_free: obj is NULL.");
    }

    // 将wmkcChat对象的所有成员清零并释放内存空间以及wmkcChat对象的内存空间
    wmkcMemoryZero((*obj)->name, WMKC_CHAT_USERNAME_SIZE);
    wmkcMemoryZero((*obj)->hash, WMKC_CHAT_HASH_SIZE);
    wmkcMemoryZero((*obj)->salt, WMKC_CHAT_SALT_SIZE);
    wmkcMemoryFree((*obj)->name);
    wmkcMemoryFree((*obj)->hash);
    wmkcMemoryFree((*obj)->salt);
    error = SNC_free(&((*obj)->snc));
    if(error.code) {
        // 如果SNC_new函数出现错误就返回错误代码
        return error;
    }
    wmkcMemoryFree((*obj));

    wmkcErr_return(error, wmkcErr_OK, "OK.");
}

/**
 * @brief 创建用户并计算出其对应的数据内容
 * @authors SN-Grotesque
 * @note 对于UID，目前的生成方式不能采用，请后续修改
 * @param obj 这是一个指针，指向wmkcChat对象的地址
 * @return 返回一个wmkcErr对象，code为0代表无错误，如果为
 *         其他值，那么需检查message与code。
 */
WMKC_PUBLIC(wmkcErr_obj) wmkcChat_createUser WMKC_OPEN_API
WMKC_OF((wmkcChat_obj *obj))
{
    wmkcErr_obj error;
    if(!obj) {
        wmkcErr_return(error, wmkcErr_ErrNULL, "wmkcChat_createUser: obj is NULL.");
    }

    // 声明用户名变量与密码口令变量
    wmkcChar name[WMKC_CHAT_USERNAME_SIZE + 1];
    wmkcChar pass[WMKC_CHAT_PASSWORD_SIZE + 1];

    // 将name与pass指向的内存地址的内容清零
    wmkcMemoryZero(name, WMKC_CHAT_USERNAME_SIZE + 1);
    wmkcMemoryZero(pass, WMKC_CHAT_PASSWORD_SIZE + 1);

    printf("请输入用户名(Max: %u bytes.)：", WMKC_CHAT_USERNAME_SIZE);
    wmkcStream_Scanf((wmkcByte *)name, WMKC_CHAT_USERNAME_SIZE);
    printf("请输入密码(Max: %u bytes.)：", WMKC_CHAT_PASSWORD_SIZE);
    wmkcStream_Scanf((wmkcByte *)pass, WMKC_CHAT_PASSWORD_SIZE);

    // 将用户名复制到wmkcChat对象的name成员中
    memcpy(obj->name, name, strlen(name));

    // 初始化对应用户的盐和密钥与初始向量
    error = wmkcChat_initCipher(obj, pass);
    if(error.code) {
        return error;
    }

    // 使用随机函数生成UID
    wmkcRandom_seed();
    obj->uid = wmkcRandom_randint(1, 999999);

    // 将密码口令清零并交由操作系统释放
    wmkcMemoryZero(pass, WMKC_CHAT_PASSWORD_SIZE);

    wmkcErr_return(error, wmkcErr_OK, "OK.");
}

/**
 * @brief 生成用户哈希摘要
 * @authors SN-Grotesque
 * @note 无
 * @param obj 这是一个指针，指向wmkcChat对象的地址
 * @return 返回一个wmkcErr对象，code为0代表无错误，如果为
 *         其他值，那么需检查message与code。
 */
WMKC_PUBLIC(wmkcErr_obj) wmkcChat_getUserHash WMKC_OPEN_API
WMKC_OF((wmkcChat_obj *obj))
{
    wmkcErr_obj error;
    if(!obj) {
        wmkcErr_return(error, wmkcErr_ErrNULL, "wmkcChat_getUserHash: obj is NULL.");
    }

    // 声明EVP_MD对象，声明wmkcHash对象
    EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
    wmkcHash_obj *hash = wmkcNull;

    // 为wmkcHash申请内存空间并初始化EVP_MD对象
    wmkcHash_new(&hash, wmkcHash_SHA256);
    EVP_DigestInit_ex(md_ctx, hash->md, wmkcNull);

    /*
    * 使用以下内容来计算一个用户的哈希值
    *     obj->uid             size of 8
    *     obj->name            size of strlen(obj->name)
    *     obj->salt            size of WMKC_CHAT_SALT_SIZE
    *     obj->snc->iv         size of SNC_BLOCKLEN
    *     obj->snc->roundKey   size of (obj->snc->KN * obj->snc->NR)
    */
    EVP_DigestUpdate(md_ctx, &obj->uid, sizeof(obj->uid));
    EVP_DigestUpdate(md_ctx, obj->name, strlen(obj->name));
    EVP_DigestUpdate(md_ctx, obj->salt, WMKC_CHAT_SALT_SIZE);
    EVP_DigestUpdate(md_ctx, obj->snc->iv, SNC_BLOCKLEN);
    EVP_DigestUpdate(md_ctx, obj->snc->roundKey, obj->snc->KN * obj->snc->NR);

    // 释放EVP_MD对象
    EVP_DigestFinal_ex(md_ctx, hash->digest, wmkcNull);
    EVP_MD_CTX_free(md_ctx);

    // 将哈希摘要复制到wmkcChat对象的hash成员中
    memcpy(obj->hash, hash->digest, WMKC_CHAT_HASH_SIZE);

    wmkcErr_return(error, wmkcErr_OK, "OK.");
}