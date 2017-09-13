#ifndef _WORKER_H_
#define _WORKER_H_

#include <string>
#include <map>

#include <event2/event.h>
#include <event2/util.h>


class Master;
class Connection;

class Worker
{
public:        
	typedef std::map<evutil_socket_t, Connection*> ConnectionMap;
	Worker();
     ~Worker();

	void Run();

	static void WorkerExitSignal(evutil_socket_t signo, short event, void *arg);

	Master        *master;
	ConnectionMap  con_map;

	struct event_base *w_base;
	struct event      *w_exit_event;

	std::string        s_inbuf;
	std::string        s_intmp;
	std::string        s_outbuf;
};
#endif
