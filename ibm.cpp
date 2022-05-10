#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <sstream>
#define SERVER_PORT  12345

#define TRUE             1
#define FALSE            0

#include "Server.hpp"
#include "User.hpp"

void check_connection(fd_set master_set, int listen_sd, int max_sd)
{
   for (int x = listen_sd; x <= max_sd + 1; x++)
   {
      if (FD_ISSET(x, &master_set) == 1 && x == listen_sd) // new_sd > max_sd))
         printf("Listening socket : %d is connected\n", x);
      else if (FD_ISSET(x, &master_set) == 1)
         printf("SD %d is connected\n", x);
      else
         std::cout << "SD " << x << "not set" << std::endl;
   }
}



int    main(int argc, char* argv[])
{

   Server s;
   User users[10]; // 10 user 

   while (s.end_server == 0)
   {
      out ("Listening socket = " << s.listen_sd);
      printf("Waiting on select()...\n");
      memcpy(&s.working_set, &s.master_set, sizeof(s.master_set));
      int rc = select(s.max_sd + 1, &s.working_set, NULL, NULL, &s.timeout);
      if (rc < 0)
      {
         perror("select() failed");
         break;
      }
      if (rc == 0) // timeout 
      {
         printf("  select() timed out.  End program.\n");
         break;
      }
      out ("1")
      /**********************************************************/
      /* One or more descriptors are readable.  Need to         */
      /* determine which ones they are.                         */
      /**********************************************************/
      s.desc_ready = rc; // descriptor ready 
      out (rc)
      for (int i = 0; i <= s.max_sd && s.desc_ready > 0; ++i)
      {
         /*******************************************************/
         /* Check to see if this descriptor is ready            */
         /*******************************************************/
         if (FD_ISSET(i, &s.working_set))
         {
            out ("2")
            /****************************************************/
            /* A descriptor was found that was readable - one   */
            /* less has to be looked for.  This is being done   */
            /* so that we can stop looking at the working set   */
            /* once we have found all of the descriptors that   */
            /* were ready.                                      */
            /****************************************************/
            s.desc_ready -= 1;

            /****************************************************/
            /* Check to see if this is the listening socket     */
            /****************************************************/
            if (i == s.listen_sd)
            {
               //printf("Listening socket is readable\n");
               /*************************************************/
               /* Accept all incoming connections that are      */
               /* queued up on the listening socket before we   */
               /* loop back and call select again.              */
               /*************************************************/
               int new_sd = 0;
               while (new_sd != -1)
               {
                  /**********************************************/
                  /* Accept each incoming connection.  If       */
                  /* accept fails with EWOULDBLOCK, then we     */
                  /* have accepted all of them.  Any other      */
                  /* failure on accept will cause us to end the */
                  /* server.                                    */
                  /**********************************************/
                  new_sd = accept(s.listen_sd, NULL, NULL);
                  out ("ACCEPTED NEW SD")
                  if (new_sd < 0)
                  {
                     out (" NEW SD < 0")
                     if (errno != EWOULDBLOCK)
                     {
                        perror("  accept() failed");
                        s.end_server = TRUE;
                     }
                     break;
                  }

                  /**********************************************/
                  /* Add the new incoming connection to the     */
                  /* master read set                            */
                  /**********************************************/
                  printf("New incoming connection - %d\n", new_sd);
                  std::stringstream ss;
                  ss << new_sd;
                  std::string str = ss.str();
                  std::string tmp = "Guest " + str;
                  users[new_sd].nickname = tmp;
                  FD_SET(new_sd, &s.master_set);  // add new SD to master set 
                  if (new_sd > s.max_sd)
                     s.max_sd = new_sd;

                  /**********************************************/
                  /* Loop back up and accept another incoming   */
                  /* connection                                 */
                  /**********************************************/
               } 
            }
            /****************************************************/
            /* This is not the listening socket, therefore an   */
            /* existing connection must be readable             */
            /****************************************************/
            else
            {
              // printf("Descriptor %d is readable\n", i); // i = the SD 
               s.close_conn = FALSE;
               /*************************************************/
               /* Receive all incoming data on this socket      */
               /* before we loop back and call select again.    */
               /*************************************************/
               do
               {
                  /**********************************************/
                  /* Receive data on this connection until the  */
                  /* recv fails with EWOULDBLOCK.  If any other */
                  /* failure occurs, we will close the          */
                  /* connection.                                */
                  /**********************************************/
                  rc = recv(i, s.buffer, sizeof(s.buffer), 0);
                  if (rc < 0)
                  {
                     if (errno != EWOULDBLOCK)
                     {
                        perror("  recv() failed");
                        s.close_conn = TRUE;
                     }
                     break;
                  }
                  /**********************************************/
                  /* Check to see if the connection has been    */
                  /* closed by the client                       */
                  /**********************************************/
                  if (rc == 0)
                  {
                     printf("  Connection closed\n");
                     s.close_conn = TRUE;
                     break;
                  }

                  /**********************************************/
                  /* Data was received                          */
                  /**********************************************/
                  int len = rc;
                  std::cout << users[i].nickname << " says : " << s.buffer;
                 // printf("%d bytes received from SD %d\n", len, i);
                  //write(1, s.buffer, len); // << std::endl;
                  char *tokens = strtok(s.buffer, " ") ;
                  if (strcmp(tokens, "/nick") == 0)
                  {
                     tokens = strtok (NULL, " ");
                     std::stringstream trimmer;
                     trimmer << tokens;
                     trimmer >> tokens;
                     users[i].nickname = tokens;
                     out ("nickname set to " <<  users[i].nickname)
                  }
                  bzero(s.buffer, 80);

                  /**********************************************/
                  /* Echo the data back to the client           */
                  /**********************************************/
                  rc = send(i, "Message recu !", 15, 0);
                  if (rc < 0)
                  {
                     perror("  send() failed");
                     s.close_conn = TRUE;
                     break;
                  }

               } while (FALSE); // TEST 

               /*************************************************/
               /* If the close_conn flag was turned on, we need */
               /* to clean up this active connection.  This     */
               /* clean up process includes removing the        */
               /* descriptor from the master set and            */
               /* determining the new maximum descriptor value  */
               /* based on the bits that are still turned on in */
               /* the master set.                               */
               /*************************************************/
               if (s.close_conn)
               {
                  out ("Closing fd")
                  close(i);
                  FD_CLR(i, &s.master_set);
                  if (i == s.max_sd)
                  {
                     while (FD_ISSET(s.max_sd, &s.master_set) == FALSE)
                        s.max_sd -= 1;
                  }
               }
            } /* End of existing connection is readable */
         } /* End of if (FD_ISSET(i, &working_set)) */
      } /* End of loop through selectable descriptors */

   } 

   /*************************************************************/
   /* Clean up all of the sockets that are open                 */
   /*************************************************************/
   for (int i = 0; i <= s.max_sd; ++i)
   {
      if (FD_ISSET(i, &s.master_set))
         close(i);
   }
}