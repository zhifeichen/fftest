#include "NetCommon.h"

#if  defined(__WIN32__) || defined(_WIN32)

static int _haveInitializedWinsock = 0;
int initializeWinsockIfNecessary(void)
{
	/* We need to call an initialization routine before
	 * we can do anything with winsock.  (How fucking lame!):
	 */
	
	WSADATA	wsadata;

	if (!_haveInitializedWinsock) {
		if (WSAStartup(MAKEWORD(2,2),  &wsadata) != 0) {
			return 0; /* error in initialization */
		}
	    	if (wsadata.wVersion != MAKEWORD(2,2)) {
	        	WSACleanup();
				return 0; /* desired Winsock version was not available */
		}
		_haveInitializedWinsock = 1;
	}

	return 1;
}

void uninitializeWinsockIfNecessary(void)
{
	if(_haveInitializedWinsock){
		WSACleanup();
		_haveInitializedWinsock = 0;
	}
}
#else
/* Unix */
#endif //#if  defined(__WIN32__) || defined(_WIN32)