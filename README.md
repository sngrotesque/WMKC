# Wizard Magic Key Cyber
> `Wizard Magic Key Cyber` by SN-Grotesque

### Author(s):
 - [SN-Grotesque](https://github.com/sngrotesque)
 - [R7](https://github.com/r7z7)

### 特别鸣谢
| Project name                                    | Description                          |
| :---                                            | :---                                 |
| [OpenSSL](https://github.com/openssl/openssl)   | 本库使用了OpenSSL库的密码库，哈希库，网络库。 |
| [libpng](http://libpng.org/pub/png/)            | 本库使用了libpng库来实现PNG图像的读写。 |
| [Python](https://www.python.org/)               | 本库的绝大多数语法和代码风格均参考过Python的源代码。 |
| [cJSON](https://github.com/DaveGamble/cJSON/)   | 本库采用cJSON库来处理JSON数据。 |
| [Zlib](https://github.com/madler/zlib)          | 本库使用了Zlib库摘要算法库以及参考过源代码的风格。 |
| [iconv](https://www.gnu.org/software/libiconv/) | 本库使用iconv库对编码进行转换。 |

### 开发文档
 -  关于更新：
> 此库的所有更新必须写在更新日志中。
 -  关于第三方库：
> 如果使用了任何第三方库，请在对应的文件中列出，并在此文档的`特别鸣谢`中指出库的名称与对应的链接。

### 版本更新日志
> 修改了版本后需要更改的文件  
> upload.py  
> READMKE.md

#### v7.0.0
1.  所有C++代码重新组织代码结构，将所有功能列入wmkc命名空间，并将原有的类更名。  
    例如：wmkcBase64变为`wmkc::base64`，其中的方法encode变为`wmkc::base64().encode()`
2.  重新优化所有代码。
3.  修复了FEA加密算法的一个密钥长度隐患。
4.  完成了`wmkc::structure::pack`，但是需要使用者注意`C/C++`的特性，解释在[wmkc_struct.hpp](includes/wmkc_struct.hpp)头部。

#### v6.6.6
1.  C++代码为完全复刻C代码的内容，但是修复了各种问题与难用性。
2.  C代码暂时停止维护，其中存在内存泄露等问题，如需使用，请尽可能使用C++代码。

#### v6.5.0
1.  新增C++代码

#### v6.4.0-dev
1.  重构wmkcNet库与wmkcError结构。
2.  优化了wmkc_obj结构。
3.  优化了wmkc_file库的编码转换功能。
4.  新增了wmkcSSL库用于进行HTTPS通信。
5.  新增了C++代码，以便于实现各种面向对象的功能。

#### v6.3.0-canary
1.  预计将所有实现改为内部实现，然后将函数作为类成员的方式使用（由于效率原因已弃之）。
2.  修复了network/wmkc_net库中对于wmkcNet_timeout函数的实现，  
    傻逼微软你妈死了，弄你妈的毫秒单位啊。

#### v6.2.0-canary
1.  将修改wmkcNet库，以支持一定情况下的OpenSSL组件，以便于进行HTTPS通信。
2.  将完善wmkcFile库，更好的支持对于不同操作系统的文件操作函数。
3.  将针对所有WMKC库进行优化。

#### v6.1.0-dev
1.  将wmkc_chat库中的对象指针成员修改为数组成员，  
    否则会导致无意义的代码过长。
2.  重构了wmkc_file库，删除了wmkcFile对象。
3.  放弃使用icu4c库对编码进行转换，改用iconv库。
4.  小幅度修改了wmkc_pad，wmkc_base64库。
5.  删除了wmkcFloat，wmkcFile类型，多余而且扰乱思绪。
6.  将wmkcMisc_PRINT_RAW函数修改为了类似Python中的print bytes类型的实现。

#### v6.0.0-dev
1.  将wmkc_base修改为wmkc_base64，因考虑到  
    不会添加base16（因为此编码可以使用wmkc_binascii库实现）  
    不会添加Base32（因为此编码实在没有必要添加）  
    不会添加Base85（因为此编码（又称Ascii85）目前还没有一个完美的标准）  
    并将Base64的编码与解码库重新设计，去掉了基于wmkc对象的形式。
2.  添加了wmkc_dict库，更好的操作键值对类型的数据。
3.  修改了关于颜色的宏。
4.  修复了wmkc_misc库的BUG。
5.  部署了libpng库，重新构建了zlib库文件。
6.  修复了wmkc_stream库中wmkc_scanf函数的隐藏BUG。
7.  将wmkcStream库中的wmkcStream_scanf函数移动到wmkc_common库并更名为wmkc_scanf。

#### v5.1.0-dev
1.  修改了wmkc_random，wmkc_time库的实现。
2.  修复了wmkc_base库的错误信息不全的问题。
3.  修改了对于系统宏的名称标识。
4.  增加了适当的文档与注释。
5.  增加了wmkc_thread库用于多线程编程。

#### v5.0.0-dev
1.  将库更名为Wizard Magic Key Cyber，原因是与目前某一组织名称重合。
2.  将库函数与一般变量类型与宏函数做了更名。
3.  修改了一些针对不同操作系统的支持。
