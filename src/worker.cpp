#include "worker.h"
#include "master.h"

#include <signal.h>
#include <stdlib.h>
#include <iostream>

Worker::Worker()
{
	master		 = NULL;
	w_base		 = NULL;
	w_exit_event = NULL;
}


Worker::~Worker()
{
	if (w_exit_event)
		event_free(w_exit_event);

	if (w_base)
		event_base_free(w_base);

	std::cout << "Worker closed" << std::endl;
}


void Worker::Run()
{
	w_base = event_base_new();
	w_exit_event = evsignal_new(w_base, SIGINT, Worker::WorkerExitSignal, w_base);
	evsignal_add(w_exit_event, NULL);

	event_base_dispatch(w_base);
	return;
}

void Worker::WorkerExitSignal(evutil_socket_t signo, short event, void *arg)
{
	event_base_loopexit((struct event_base*)arg, NULL);
}
