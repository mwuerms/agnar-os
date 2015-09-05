/**
 * Martin Wuerms
 * 2015-07-31
 *
 */

/* - includes --------------------------------------------------------------- */
#include "project.h"
#include "process.h"
#include "fifo.h"

/* - typedefs --------------------------------------------------------------- */

/* - private variables ------------------------------------------------------ */
static fifo_index_t event_queue_index;
static uint8_t event_queue[cNB_OF_EVENTS_IN_QUEUE];

static process_t *idle_process;
static process_t *process_list[cNB_OF_PROCESSES];	// =NULL: unused, free
static uint8_t process_count;
static uint8_t pid_count; /// pid == 0 should not exist

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
 * find the process in the list by given pid
 * find only first occurence
 * @param   pid of process to find
 * @reutn   pointert to process_t   =NULL: could not find process with given pid
 *                                  else: valid pointer
 */
static process_t *process_FindByPID(uint8_t pid) {
    uint8_t n;
    for(n = 0; n < cNB_OF_PROCESSES; n++) {
        if(process_list[n] != NULL) {
            if(process_list[n]->pid == pid) {
                // found process with same pid
                return(process_list[n]);
            }
        }
    }
    // no process in list found
    return(NULL);
}

/**
 * remove a process from process_list given by pid
 * @param   pid of process to remove
 * @return  status =1: successfully removed process from process_list
 *                 =0: could not remove process from process_list
 * /
static int8_t process_RemoveFromProcessList(uint8_t pid);*/

/**
 * execute a process given by its PID
 * @param	pid		process identifier
 * @param	event	event for the process to execute
 * @param	data	additional data to process (if unused = NULL)
 * @return	status 	=1: OK, could execute process
 *					=0: error, could not execute process
 */
static int8_t process_Exec(uint8_t pid, uint8_t event, void *data) {
    process_t *p;
    // check if process exists
    if((p = process_FindByPID(pid)) == NULL) {
        // error, process does not exist
        return(0);
    }
    
   	// is function pointer correctly set?
	if(p->process == NULL) {
		// error, function pointer is not set
		return(0);
	}
    // check if process is not yet started
    if(p->state == cPROCESS_STATE_NONE) {
        // process is not active
        return(0);
    }
    
    DEBUG_MESSAGE("execute process \"%s\" (pid: %d, event: %d, data: %p)\n", 
        p->name, p->pid, event, data);
    
	// OK, execute process
	p->state = cPROCESS_STATE_RUNNING;
	if(p->process(event, data) == 0) {
	    // do not run this process anymore
		p->state = cPROCESS_STATE_NONE;
	}
	else {
    	// process remains active
		p->state = cPROCESS_STATE_ACTIVE;
	}
	return(1);
}

/* - public functions ------------------------------------------------------- */

/**
 * initialize the process module
 */
void process_Init(void) {
	// vars
	process_count = 0;
	pid_cound = 0;  // 1st time: ++
	idle_process = NULL;
	memset(process_list, 0, sizeof(process_list));
	
	evQueue_Init();
}

/**
 * add a new process
 * @param	p	pointer to process context
 * @return	status 	=1: OK, could add process to process_list
 *					=0: error, could not add process to process_list
 */
int8_t process_Add(process_t *p) {
    uint8_t n;
    
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
    for(n = 0; n < cNB_OF_PROCESSES; n++) {
        if(process_list[n] == NULL) {
            // found empty space in process_list
            break;
        }
    }
    if(n >= cNB_OF_PROCESSES) {
        // error, could not add process to list, no more space available
	    return(0);
    }
    
    // found empty space, add process to process_list
    process_list[n] = p;
    process_count++;
    if(pid_count == 0) {
        pid_count = 1;
    }
    else {
        pid_count++;
    }
    // success, added process to process_list
    p->pid = pid_count;
    p->state = cPROCESS_STATE_NONE;
        
    DEBUG_MESSAGE("process_Add: %s, pid: %d\n",
    		p->name,
			p->pid);
    return(1);
}


/**
 * removes an existing  process
 * @param	pid		process identifier
 * @return	status 	=1: OK, could remove process from process_list
 *					=0: error, could not remove process to process_list
 */
int8_t process_Remove(process_t *p) {
    return(0);
}

/**
 * start an existing process
 * @param	pid		process identifier
 * @return	status 	=1: OK, could start process
 *					=0: error, could not start process
 */
int8_t process_Start(uint8_t pid) {
    process_t *p;
    // check if process exists
    if((p = process_FindByPID(pid)) == NULL) {
        // error, process does not exist
        return(0);
    }
    // check if process is already started
    if(p->state != cPROCESS_STATE_NONE) {
        // error, process is already started
        return(0);
    }
    
	// start process
	p->state = cPROCESS_STATE_ACTIVE;
	DEBUG_MESSAGE("process_Start: %s, pid: %d, state: %d\n",
			p->name,
			p->pid,
			p->state);
	return(process_SendEvent(pid, cEV_START, NULL));
}

/**
 * stop an existing process
 * @param	pid		process identifier
 * @return	status 	=1: OK, could stop process
 *					=0: error, could not stop process
 */
int8_t process_Stop(uint8_t pid) {
    return(0);
}

/**
 * add the idle process, this process does not need to be started
 * @param	p	pointer to process context
 * @return	status 	=1: OK, could add process to process_list
 *					=0: error, could not add process to process_list
 */
int8_t process_AddIdle(process_t *p) {
	// sanity tests
	if(p == NULL) {
		// error, no process
		return(0);
	}
	if(p->process == NULL) {
		// error, no process_function defined
		return(0);
	}
	
	// success, add process to idle_process
    idle_process = p;
	p->pid = cPROCESS_PID_IDLE;
	p->state = cPROCESS_STATE_NONE; // does not matter for idle_process
    DEBUG_MESSAGE("process_AddStartIdle: %s, pid: %d\n",
    			p->name,
				p->pid);

    return(1);
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
	int8_t ret;
	uint8_t sr;
	
	ev.pid = pid;
	ev.event = event;
	ev.data = data;
	lock_interrupt(sr);
	ret = evQueue_Write(&ev);
	release_interrupt(sr);
	return(ret);
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
			if(idle_process != NULL) {
			    DEBUG_MESSAGE("execute idle process \"%s\" (pid: %d, event: %d, data: %p)\n", 
                    idle_process->name, idle_process->pid, 0, NULL);
    			idle_process(cPROCESS_PID_IDLE, 0, NULL);
			}
		}
	}
	return(0);
}

