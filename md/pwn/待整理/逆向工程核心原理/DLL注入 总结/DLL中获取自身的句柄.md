---
title: DLL中获取自身的句柄
updated: 2021-04-09T14:18:56.0000000+08:00
created: 2021-04-09T11:17:01.0000000+08:00
---

\<strong\>方法1\</strong\>：
注意：TRUE会导致DLL引用计数加1，FALSE不会改变引用计数，通常用FALSE
HMODULE GetCurrentModule(BOOL bRef/\* = FALSE\*/)
{
HMODULE hModule = NULL;

if (GetModuleHandleEx(bRef ? GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS : (GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS

\| GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT), (LPCSTR)GetCurrentModule, &hModule))

{

return hModule;

}

return NULL;
}
GetModuleHandleEx(dwFlags, lpModuleName, phModule)
dwFlags:

如果是0，则当调用该函数时，模块的引用计数自动增加，调用者在使用完模块句柄后，必须调用一次FreeLibrary

如果是GET_MODULE_HANDLE_EX_FLAG_PIN,则模块一直映射在调用该函数的进程中，直到该进程结束，不管调用多少次FreeLibrary

如果是GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,则同GetModuleHandle相同，不增加引用计数

如果是GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,则lpModuleName是模块中的一个地址

phModule存储要找的句柄。其他都和GetModuleHandle函数相同
*来自 \<<https://blog.csdn.net/jiangqin115/article/details/45312773>\>*

DLL获取自己的模块句柄的方法

HMODULE GetSelfModuleHandle()
{
    MEMORY_BASIC_INFORMATION mbi;

    return ((::VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0)
      ? (HMODULE) mbi.AllocationBase : NULL);
}

进程载入dll内存空间是由**<u>VirtualAlloc</u>**分配的

AllocationBase 是页的基地址，**BaseAddress**也是页的基地址，唯一不同的是，**BaseAddress**是**<u>VirtualAlloc</u>**分配内存后第一页的地址，AllocationBase 是每一页的地址。

当AllocationBase == BaseAddress的时候，AllocationBase 就是模块在进程内存中的起始地址，即HMODULE

VirtualQuery的功能就是：以页为单位，遍历进程虚拟空间

*来自 \<<https://blog.csdn.net/yaosan/article/details/3459756>\>*
