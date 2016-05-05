#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <stdio.h>

/* This function calls select to wait for data to read from */
/* one of the sockets passed as a parameter.                */
/* If more than 3 seconds elapses, it returns.              */
/* Return value flags. These indicate the readiness of      */
/* each socket for read.                                    */
#define S1READY 0x01
#define S2READY 0X02

waittoread(int s1,int s2)
{
   fd_set fds;
   struct timeval timeout;
   int rc, result;

      /* Set time limit. */
   timeout.tv_sec = 3;
   timeout.tv_usec = 0;
      /* Create a descriptor set containing our two sockets.  */
   FD_ZERO(&fds);
   FD_SET(s1, &fds);
   FD_SET(s2, &fds);
   rc = select(sizeof(fds)*8, &fds, NULL, NULL, &timeout);
   if (rc==-1) {
      perror("select failed");
      return -1;
   }

   result = 0;
   if (rc > 0)
   {
      if (FD_ISSET(s1, &fds)) result |= S1READY;
      if (FD_ISSET(s2, &fds)) result |= S2READY;
   }

   return result;
}