#include "pn_sys.h"
#include "pn_log.h"

#ifdef PN_OS_LINUX
	void pn_sys_print_memory_usage(void) {
		struct rusage usage;
		int error = getrusage(RUSAGE_SELF, &usage);

		if(!error) {
			pn_debug("MEM: %ld KB", usage.ru_maxrss);
		} else { 
			pn_error("Failed to get memory usage. Error: ", error);
		}
	}

#endif