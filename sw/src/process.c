/**
 * Martin Wuerms
 * 2015-07-31
 *
 */

/* - includes --------------------------------------------------------------- */
#include "process.h"
#include "fifo.h"

/* - typedefs --------------------------------------------------------------- */

/* - private variables ------------------------------------------------------ */
static fifo_index_t event_queue_index;
static uint8_t event_queue[cNB_OF_EVENTS_IN_QUEUE];

static process_t *process_list[cNB_OF_PROCESSES];	// pid = 0: unused, free; =1...N-1: pid set
static uint8_t process_count;

/* - private (static) functions --------------------------------------------- */

/**
 * initialize the event queue
 */
static inline void evQueue_Init(void) {
	fifo_Init(&event_queue_index, cNB_OF_EVENTS_IN_QUEUE);
	memset(&event_queue, 0, sizeof(event_queue));
}

/**
 * write an event to the event queue
 * @param   event   pointer to event to put into event_queue
 * @return  =1: OK, writing event successfull
 *          =0: Error, could not write, queue is full
 */
static inline uint8_t evQueue_Write(event_t *ev) {
    // sanity checks
	if(ev == NULL)
		return(0);

	if(fifo_IncWriteIndex(&event_queue_index) == 0) {
		// event queue is full
		return(0);
	}
	
	memcpy(ev, &event_queue[event_queue_index.write], sizeof(*ev));
	return(1);
}

/**
 * read an event from the event queue
 * @param   event   pointer to event to read from event_queue
 * @return  =1: OK, reading event successfull, event is valid
 *          =0: Error, could not read, event_queue is empty
 */
static inline uint8_t evQueue_Read(event_t *ev) {
    // sanity checks
	if(ev == NULL)
		return(0);
		
	if(fifo_IncReadIndex(&event_queue_index) == 0) {
		// event queue is full
		return(0);
	}
	
	memcpy(&event_queue[event_queue_index.read], ev, sizeof(*ev));
	return(1);
}


/**
 * execute a process given by its PID
 * @param	pid		process identifier
 * @param	event	event for the process to execute
 * @param	data	additional data to process (if unused = NULL)
 * @return	status 	=1: OK, could execute process
 *					=0: error, could not execute process
 */
static int8_t process_Exec(uint8_t pid, uint8_t event, void *data) {
	// sanity test, does pid exist?
	if(process_list[pid]->pid != pid) {
		// error, pid is not set
		return(0);
	}
	// sanity test, is pointer to process to execute correctly set?
	if(process_list[pid]->process == NULL) {
		// error, pid is not set
		return(0);
	}
    // check if process is not yet started
    if(process_list[pid]->state == cPROCESS_STATE_NONE) {
        // process is not active
        return(0);
    }
    
	// OK, execute process
	process_list[pid]->state = cPROCESS_STATE_RUNNING;
	if(process_list[pid]->process(event, data) == 0) {
	    // do not run this process anymore
		process_list[pid]->state = cPROCESS_STATE_NONE;
	}
	else {
    	// process remains active
		process_list[pid]->state = cPROCESS_STATE_ACTIVE;
	}
	return(1);
}

/* - public functions ------------------------------------------------------- */
/**
 * add a new process and send the start event to this process
 * @param	p	pointer to process context
 * @return	status 	=1: OK, could add process to process_list and start it
 *					=0: error, could not add process to process_list
 */
int8_t process_Add(process_t *p) {
	uint8_t pid;
	// sanity tests
	if(p == NULL) {
		// error, no process
		return(0);
	}
	if(p->process == NULL) {
		// error, no process_function defined
		return(0);
	}
	
	// place process in process_list
	if(process_count >= cNB_OF_PROCESSES) {
		// error, no more space for an additional process in the process_list
		return(0);
	}
	
	// add process to process_list
	pid = process_count;
	process_count++;
    process_list[pid] = p;
    process_list[pid]->state = cPROCESS_STATE_NONE;

    return(1);
}

/**
 * start a process
 * @param	pid		process identifier
 * @return	status 	=1: OK, could start process
 *					=0: error, could not start process
 */
int8_t process_Start(uint8_t pid) {
    // check if pid may be valid
	if(pid >= process_count) {
		// error, pid is invalid
		return(0);
	}
    // check if process exists
    if((process_list[pid]->process == NULL) ||
       (process_list[pid]->pid != pid)) {
        // error, process does not exist
        return(0);
    }
    // check if process is not yet started
    if(process_list[pid]->state != cPROCESS_STATE_NONE) {
        // process does not exist
        return(0);
    }
    
	// start process
	process_list[pid]->state = cPROCESS_STATE_ACTIVE;
	return(process_SendEvent(pid, cEV_START, NULL));
}

/**
 * send an event to a process given by its PID
 * @param	pid		process identifier
 * @param	event	event for the process to execute
 * @param	data	additional data to process (if unused = NULL)
 * @return	status 	=1: OK, could add event to queue
 *					=0: error, could not add event to queue
 */
int8_t process_SendEvent(uint8_t pid, uint8_t event, void *data) {
	event_t ev;
	
	// check if pid may be valid
	if(pid >= process_count) {
		// error, pid is invalid
		return(0);
	}
    // check if process exists
    if((process_list[pid]->process == NULL) ||
       (process_list[pid]->pid != pid)) {
        // error, process does not exist
        return(0);
    }
    
	ev.pid = pid;
	ev.event = event;
	ev.data = data;
	return(evQueue_Write(&ev));
}

/**
 * check if event queue is empty
 * @return  =1: event queue is empty
 *          =0: event queue is not empty
 */
int8_t process_IsEventQueueEmpty(void) {
    return(fifo_IsEmpty(&event_queue_index));
}

/**
 * run the process scheduler
 * note: this function should never return (endless loop)
 * @return	=0: error
 */
int8_t process_Run(void) {
	static event_t ev;
	static int8_t ret;
	
	while(1) {
		// get next event
		ret = evQueue_Read(&ev);
		if(ret == 1) {
			// got a valid event, send it to the process
			process_Exec(ev.pid, ev.event, ev.data);
		}
		else {
			// event_queue is empty, execute the idle task
			process_Exec(0, 0, NULL);
		}
	}
	return(0);
}

/**
 * the idle task
 * stay here as long there is no event in the event_queue available
 * @param	event	event for the process to execute
 * @param	data	additional data to process (if unused = NULL)
 * @return	status 	=1: OK, could execute process
 *					=0: error, could not execute process
 */
int8_t idleTask_Process(uint8_t event, void *data) {
	// check for start event
	if(event == cEV_START) {
		// do ? nothing to initialize
	}

	// stay here as long there is no event available
	while(1) {
		// check if event_queue is empty
		if(process_IsEventQueueEmpty() == 1) {
			// find lowest power mode
			// go to sleep
		}
		else {
			break;
		}
	}
	return(0);
}

static char idle_task_name[] = "idle task";
static process_t idle_task;

/**
 * initialize the process module
 * idle task is set in this function
 * @param	idle_task	pointer to process context of the idle_task
 */
void process_Init(void) {
	// vars
	process_count = 0;
	memset(process_list, 0, sizeof(process_list));
	
	evQueue_Init();
	
	idle_task.process = idleTask_Process;
	process_Add(&idle_task);
}

