#include <stdio.h>
#include <stdlib.h>

#include "ziAPI.h"

void EventLoop( ziConnection Conn )
{

  ZI_STATUS RetVal;
  char* ErrBuffer;

  ziEvent* Event;
  unsigned int Cnt = 0;

  /* 
     allocate ziEvent in heap memory instead of 
     getting it from stack will secure 
     against stack overflows especially in windows
  */
  if( ( Event = malloc( sizeof( ziEvent ) )) == NULL )
    {
      fprintf( stderr, "Can't allocate memory\n" );
      return;
    }

  //subscribe to all nodes
  if( ( RetVal = ziAPISubscribe( Conn, "*" ) ) != ZI_SUCCESS )
    {

      ziAPIGetError( RetVal, &ErrBuffer, NULL );
      fprintf( stderr, "Can't subscribe: %s\n", ErrBuffer );

      free( Event );

      return;
    }  

  //loop 1000 times
  while( Cnt < 1000 )
    {

      //get all demod rates from all devices every 10th cycle
      if( ++Cnt % 10 == 0 )
        {
          if( ( RetVal = 
                ziAPIGetValueAsPollData( 
                    Conn, "*/demods/*/rate" ) ) != ZI_SUCCESS )
            {
              
              ziAPIGetError( RetVal, &ErrBuffer, NULL );
              fprintf( stderr, "Can't get value as poll data: %s\n", 
                       ErrBuffer );
              
              break;
            }          
        }

      //poll data until no more data is available
      while( 1 ) 
        {
          
          if( ( RetVal = ziAPIPollData( 
                    Conn, Event, 0 ) ) != ZI_SUCCESS )
            {
              
              ziAPIGetError( RetVal, &ErrBuffer, NULL );
              fprintf( stderr, "Can't poll data: %s\n", ErrBuffer );
              
              break;
            }
          else
            {
              
              //The field Count of the Event struct is zero when 
              //no data has been polled
              if( Event->Type != ZI_DATA_NONE && Event->Count > 0 )
                {
                  
                  /*
                    process the received event here
                  */
                  
                }
              else
                {
                  //no more data is available so go on
                  break;
                }
              
            }
          
        }
      
    }


  if( ziAPIUnSubscribe( Conn, "*" ) != ZI_SUCCESS )
    {
      ziAPIGetError( RetVal, &ErrBuffer, NULL );
      fprintf( stderr, "Can't unsubscribe: %s\n", ErrBuffer );
    }  

  free( Event );

}
