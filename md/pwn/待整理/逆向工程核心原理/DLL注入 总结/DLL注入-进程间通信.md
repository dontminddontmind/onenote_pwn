---
title: DLL注入-进程间通信
updated: 2021-04-09T17:10:46.0000000+08:00
created: 2021-04-07T14:26:39.0000000+08:00
---

Three Ways to Inject Your Code into Another Process

*来自 \<<https://www.codeproject.com/Articles/4610/Three-Ways-to-Inject-Your-Code-into-Another-Proces>\>*
**Interprocess Communications**
Until now, we only talked about how to inject the DLL to the remote process. However, in most situations the injected DLL will need to communicate with your original application in some way (recall that the DLL is mapped into some remote process now, not to our local application!). Take our Password Spy: The DLL has to know the handle to the control that actually contains the password. Obviously, this value can't be hardcoded into it at compile time. Similarly, once the DLL gets the password, it has to send it back to our application so we can display it appropriately.
Fortunately, there are many ways to deal with this situation: File Mapping,WM_COPYDATA, the Clipboard, and the sometimes very handy#pragma data_seg, to name just a few. I won't describe these techniques here because they are all well documented either in MSDN (see Interprocess Communications) or in other tutorials. Anyway, I used solely the#pragma data_segin the LibSpy example.
You will find LibSpy and its sources in the download package[at the beginning](https://www.codeproject.com/Articles/4610/Three-Ways-to-Inject-Your-Code-into-Another-Proces#__top)of the article.

