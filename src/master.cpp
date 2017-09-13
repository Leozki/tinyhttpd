#include "master.h"
#include "worker.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>

Master::Master()
{
	m_base = NULL;
	m_exit_event  = NULL;
	m_chld_event  = NULL;
	nums_of_child = 4;
}

Master::~Master()
{
	if (m_base)
	{
		event_free(m_exit_event);
		event_free(m_chld_event);
		event_base_free(m_base);
	}
	std::cout << "Master Clsoed" << std::endl;
}

bool Master::StartMaster()
{
	std::cout << "Start Master" << std::endl;
	worker.master = this;
	while (nums_of_child > 0)
	{
		switch (fork())
		{
			case -1:
				return false;
			case 0:
			{
				worker.Run(); // worker 子程序入口
				return true;
			}
			default:
			--nums_of_child;
			break;
		}
	}

	// Master监听信号，一个用于退出，一个用于处理结束的子进程
	m_base = event_base_new();
	m_exit_event = evsignal_new(m_base, SIGINT, Master::MasterExitSignal, m_base);
	m_chld_event = evsignal_new(m_base, SIGCHLD, Master::MasterChldSignal, this);
	evsignal_add(m_exit_event, NULL);
	evsignal_add(m_chld_event, NULL);

	// 开始event循环
	event_base_dispatch(m_base);
	return true;
}

void Master::MasterExitSignal(evutil_socket_t signo, short event, void *arg)
{
	// 结束事件循环
	event_base_loopexit((struct event_base*)arg, NULL);
}

// 防止子进程僵死，使用waitpid而不是wait
// 多个子进程可能同时关闭
void Master::MasterChldSignal(evutil_socket_t signo, short event, void *arg)
{
	Master *master = (Master *)arg;
	pid_t	pid;
	int 	stat;
	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
	{
		++(master->nums_of_child);
		std::cout << "Child " << pid << " terminated " << std::endl;
	}
}




