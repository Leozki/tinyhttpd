#tinyhttpd

##Master
负责插件加载工作等、子进程创建、监听SIGCHLD信号等，包含数据成员worker——用于处理具体的事务；

##Worker
管理监听（listener成员）、连接（connection）等事务，进行event loop；
