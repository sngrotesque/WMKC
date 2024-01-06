#include <wmkc_conf.hpp>

#if WMKC_SUPPORT
#ifndef WMKC_CPP_EXCEPTION
#define WMKC_CPP_EXCEPTION
#include <errno.h>    // 错误处理库

typedef struct {
    wmkcCSTR message; // 错误消息
    wmkcCSTR func;    // 发送错误的函数的名称
    wmkcSSize code;   // 错误代码
} wmkcErr_obj;

#define wmkcErr_OK 0 // 表示一切正常，不需要注意任何错误。

#define wmkcErr_Err64           -1LL // 一般的错误，用于表示64位的错误代码。
#define wmkcErr_Err32           -1   // 一般的错误，用于表示32位的错误代码。
#define wmkcErr_ErrNULL         -2LL // 错误的空数据，表示不应该传入一个空的数据（包含指针）。
#define wmkcErr_ErrType         -3LL // 错误的类型，表示传入的参数和函数要求的参数类型不一致。
#define wmkcErr_ErrOutRange     -4LL // 错误的范围，表示传入的范围参数超过函数规定的最大范围。
#define wmkcErr_ErrInvalidRange -5LL // 错误的范围，表示传入的范围参数中起始下标超过了末尾下标。
#define wmkcErr_ErrSysFunc      -6LL // 错误的调用，表示调用系统函数后返回了错误代码。
#define wmkcErr_ErrMemory       -7LL // 错误的内存，只能用作申请内存失败时。
#define wmkcErr_FileFolderPath  32LL // 错误的路径，此错误类型表示用户指定的路径没有文件或（和）文件夹。
#define wmkcErr_FileNull     33LL // 此值表示用户不应该读取一个空文件或不应该写入一个空的数据到文件。
#define wmkcErr_FileOpen     34LL // 此值表示调用fopen函数或_wfopen来打开文件失败了。
#define wmkcErr_FileClose    35LL // 此值表示调用fclose函数来关闭文件失败了。
#define wmkcErr_ThreadCreate 48LL // 此值表示线程创建时出现错误
#define wmkcErr_ThreadJoin   49LL // 此值表示线程阻塞出现错误
#define wmkcErr_ThreadStart  50LL // 此指表示线程启动出现错误

void wmkcErr_exception(wmkcErr_obj err);
void wmkcErr_exception(wmkcSSize errCode, std::string funcName, std::string errMessage);

#endif /* WMKC_CPP_EXCEPTION */
#endif /* WMKC_SUPPORT */
