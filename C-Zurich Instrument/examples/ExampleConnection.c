#include <stdio.h>

#include "ziAPI.h"

int main( )
{

  ZI_STATUS RetVal;
  char* ErrBuffer;

  ziConnection Conn;

  if( ( RetVal = ziAPIInit( &Conn ) ) != ZI_SUCCESS )
    {
      ziAPIGetError( RetVal, &ErrBuffer, NULL );
      fprintf( stderr, "Can't init Connection: %s\n", ErrBuffer );
      return 1;
    }

  //connect to the ziServer set as default using the default port
  if( ( RetVal = ziAPIConnect( Conn, NULL, 0 ) ) != ZI_SUCCESS )
    {
      ziAPIGetError( RetVal, &ErrBuffer, NULL );
      fprintf( stderr, "Can't connect to ziServer: %s\n", ErrBuffer );
    }
  else
    {      

      /* 
	 do something using the ziConnection here 
      */

      //since ZIAPIDisconnect always returns ZI_SUCCESS 
      //no error handling is required
      ziAPIDisconnect( Conn );
    
    }
  
  //since ZIAPIDestroy always returns ZI_SUCCESS 
  //no error handling is required
  ziAPIDestroy( Conn );

  return 0;  
}
