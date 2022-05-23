# 编辑器、编译器、IDE集成开发环境：
  



# 编译器
## 常见的C++编译器：
    Gun Complier collection
    clang
    Microsoft C++ Complier
    ...
    
## 编译器为什么这么多种：
    为什么不同的处理器需要不同的C++编译器
        汇编指令集不同
    为什么把不同的操作系统厂商也要搞自己的C++编译器
        虽然C++标准一样，但是适配不同操作系统的自有头文件和动态库
    

### GCC (GUN Complier collection)
    GUN与Unix的关系
        Unix 商用操作系统 solaris等
        Gun 开发一套开源免费的操作系统，操作系统内核以及工具链
    Unix与Linux
        linux 参考 Unix设计思路,写出 Unix-like操作系统,Linux操作系统，遵循了 GUN开源协议
    GUN与Linux
        linux 内核出现，成长速度快于GUN内核，Gun的工具链被大量集成到linux中。
        
        
    GCC与Gun
    
    gcc与GCC
    
    gcc与g++
    
    
    WINGW与GCC
      window上使用GCC
      
    WLS
      
    Cygwin
    
    
### clang

    LLVM与clang

    至于为什么既要装Clang又要装MinGW，是因为Clang没有头文件



### MSVC
    MSVC编译器选项： https://docs.microsoft.com/zh-cn/cpp/build/reference/fsanitize?view=msvc-160

    通过命令行使用MSVC： https://docs.microsoft.com/zh-cn/cpp/build/building-on-the-command-line?view=msvc-160

    vscode 使用MSVC：  
      官方文档：https://code.visualstudio.com/docs/cpp/config-msvc
      博客：https://blog.csdn.net/qq_43116414/article/details/108430701

所以，学些C语言可以基于不同的操作系统。工作中，经常使用window桌面，但是项目工程是linux上。

WIN10 WSL搭建C语言开发环境
WSl使用：https://docs.microsoft.com/zh-cn/windows/wsl/install-win10
下载WSL linux内核  https://docs.microsoft.com/zh-cn/windows/wsl/install-manual

wsl 按住Ubuntu的路径
C:\Users\Admin\AppData\Local\Packages\CanonicalGroupLimited.Ubuntu18.04onWindows_79rhkp1fndgsc\LocalState\rootfs
