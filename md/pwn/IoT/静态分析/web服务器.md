---
title: web服务器
updated: 2022-05-14T14:45:40.0000000+08:00
created: 2022-05-10T16:50:07.0000000+08:00
---

CGI就是可以运行的程序，如login.cgi，web服务器读取表单，传给cgi
![image1](../../../resources/image1-3.jpg)
basic认证
**步骤1：用户访问受限资源**

如下，用户访问受限资源 /protected_docs。请求报文如下：

GET /protected_docs HTTP/1.1  
Host: 127.0.0.1:3000

**步骤2：服务端返回401要求身份认证**

服务端发现 /protected_docs 为受限资源，于是向用户发送401状态码，要求进行身份认证。

HTTP/1.1 401 Unauthorized  
WWW-Authenticate: Basic realm=protected_docs

响应首部中，通过WWW-Authenticate告知客户端，认证的方案是basic。同时以realm告知认证的范围。

WWW-Authenticate: Basic realm=\<需要保护资源的范围\>

**步骤3：用户发送认证请求**

用户收到服务端响应后，填写用户名、密码，然后向服务端发送认证请求。

以下为请求报文。Authorization请求首部中，包含了用户填写的用户名、密码。

GET /protected_docs HTTP/1.1  
Authorization: Basic Y2h5aW5ncDoxMjM0NTY=

Authorization首部的格式为Basic base64(userid:password)。实际代码如下：

Buffer.from('chyingp:123456').toString('base64'); // Y2h5aW5ncDoxMjM0NTY=

**步骤4：服务端验证请求**

服务端收到用户的认证请求后，对请求进行验证。验证包含如下步骤：
1.  根据用户请求资源的地址，确定资源对应的realm。
2.  解析 Authorization 请求首部，获得用户名、密码。
3.  判断用户是否有访问该realm的权限。
4.  验证用户名、密码是否匹配。
一旦上述验证通过，则返回请求资源。如果验证失败，则返回401要求重新认证，或者返回403（Forbidden）。
