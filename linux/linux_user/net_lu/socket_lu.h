
/* socklent_t   uint32_t */

#include<netinet/in.h>

struct sockaddr {          /*通用套接字地址结构*/
  uint8_t      sa_len;
  sa_family_t  sa_family;    /* address family: AF_xxx value */
  char         sa_data[14];  /* protocol-specific address */
};


struct in_addr {
  in_addr_t   s_addr;           /* 32-bit IPv4 address network byte ordered */
};

struct sockaddr_in {         /*ipv4套接字地址结构*/
  uint8_t         sin_len;      /* length of structure (16) */
  sa_family_t     sin_family;   /* AF_INET */
  in_port_t       sin_port;     /* 16-bit TCP or UDP port number network byte ordered */
  struct in_addr  sin_addr;     /* 32-bit IPv4 address  network byte ordered */
  char            sin_zero[8];  /* unused */
};

/*
---->套接字地址
每个协议族都定义它自己的套接字地址结构。

ipv4套接字地址结构,也称为网际套接字地址结构 struct sockaddr_in
通用套接字地址结构 

套接字是通信端点的抽象，访问套接字需要使用套接字描述符(与文件描述符类似)。 
套接字描述符在UNIX系统是用文件描述符实现的。

