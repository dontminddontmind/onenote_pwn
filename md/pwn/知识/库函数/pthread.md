---
title: pthread
updated: 2023-03-06T20:27:24.0000000+08:00
created: 2021-09-19T14:20:53.0000000+08:00
---

函数原型

int pthread_create(pthread_t \*tidp, const pthread_attr_t \*attr,
( void \*)(\*start_rtn)( void \*), void \*arg);
若线程创建成功，则返回0。若线程创建失败，则返回出错编号

返回成功时，由tidp指向的内存单元被设置为新创建线程的线程ID

新创建的线程从start_rtn函数的地址开始运行，arg是指针参数，如果需要向start_rtn函数传递的参数不止一个，那么需要把这些参数放到一个结构中，然后把这个结构的地址作为arg的参数传入

来自https://blog.csdn.net/zhou1021jian/article/details/71514738

函数原型

int pthread_join(pthread_t thread, void \*\*retval);
以阻塞的方式等待thread指定的线程结束。当函数返回时，被等待线程的资源被收回。如果线程已经结束，那么该函数会立即返回

retval中存储被等待线程的返回值，0代表成功，失败，返回的则是错误号

来自https://blog.csdn.net/qq_37858386/article/details/78185064

pthread_join的使用
在Linux中，新建的线程并不是在原先的进程中，而是系统通过一个系统调用clone()。该系统调用clone() copy了一个和原先进程完全一样的进程，并在这个进程中执行线程函数。不过这个copy过程和fork不一样。 copy后的进程和原先的进程共享了所有的变量，运行环境。这样，原先进程中的变量变动在copy后的进程中便能体现出来。

那么pthread_join函数有什么用呢？？？

pthread_join使一个线程等待另一个线程结束。

代码中如果没有pthread_join主线程会很快结束从而使整个进程结束，从而使创建的线程没有机会开始执行就结束了。加入pthread_join后，主线程会一直等待直到等待的线程结束自己才结束，使创建的线程有机会执行。

所有线程都有一个线程号，也就是Thread ID。其类型为pthread_t。通过调用pthread_self()函数可以获得自身的线程号。

如果你的**主线程，也就是main函数执行的那个线程**，在你其他线程退出之前就已经退出，那么带来的bug则不可估量。通过pthread_join函数会让主线程阻塞，直到所有线程都已经退出。

**detach**

可以通过pthread_join()函数来使主线程阻塞等待其他线程退出，这样主线程可以清理其他线程的环境。但是还有一些线程，更喜欢自己来清理退出 的状态，他们也不愿意主线程调用pthread_join来等待他们。我们将这一类线程的属性称为detached（分离的）。如果我们在调用 pthread_create()函数的时候将属性设置为NULL，则表明我们希望所创建的线程采用默认的属性，也就是jionable（此时不是detached）。

如果需要将属性 设置为detached。则应该如下设定：

pthread_attr_t attr*;*

pthread_attr_init(&attr)*;*

pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)*;*

pthread_create(&pthreadid, &attr, myprocess, &arg)*;*

警告：

在线程设置为joinable后，可以调用pthread_detach()使之成为detached。但是相反的操作则不可以。还有，如果线程已经调用pthread_join()后，则再调用pthread_detach()则不会有任何效果。

线程可以通过自身执行结束来结束，也可以通过调用pthread_exit()来结束线程的执行。另外，线程甲可以被线程乙被动结束。这个通过调用pthread_cancel()来达到目的。

int pthread_cancel(pthread_tthread);

函数调用成功返回0。

当然，线程也不是被动的被别人结束。它可以通过设置自身的属性来决定如何结束

线程的被动结束分为两种，一种是异步终结，另外一种是同步终结。

异步终结就是当其他线程调用pthread_cancel的时候，线程就立刻被结束。

而同 步终结则不会立刻终结，它会继续运行，直到到达下一个结束点（cancellation point）。当一个线程被按照默认的创建方式创建，那么它的属性是同步终结。

*来自 \<<https://blog.csdn.net/heybeaman/article/details/90896663>\>*

