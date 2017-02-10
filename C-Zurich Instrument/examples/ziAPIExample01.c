#include <stdlib.h>
#include <stdio.h>

#include "ziAPI.h"

int main( int argc, char** argv )
{
  
  ZI_STATUS RetVal;
  char* ErrBuffer;

  ziConnection Conn;

  //initialize the ziConnection
  if( ( RetVal = ziAPIInit( &Conn ) ) != ZI_SUCCESS )
    {
      ziAPIGetError( RetVal, &ErrBuffer, NULL );
      fprintf( stderr, "Can't init Connection: %s\n", ErrBuffer );
      return 1;
    }

  //connect to the ziServer running on localhost
  //using the port 8005 (default)
  if( ( RetVal = ziAPIConnect( Conn, 
                               "localhost", 
                               8005 ) ) != ZI_SUCCESS )
    {
      ziAPIGetError( RetVal, &ErrBuffer, NULL );
      fprintf( stderr, "Can't connect: %s\n", ErrBuffer );
    }
  else
    {

      //set all demodulator rates of all devices to 150Hz
      if( ( RetVal = ziAPISetValueD( Conn, 
                                     "*/demods/*/rate", 
                                     150 ) ) != ZI_SUCCESS )
        {
          ziAPIGetError( RetVal, &ErrBuffer, NULL );
          fprintf( stderr, "Can't set parameter: %s\n", ErrBuffer );
        }
      
      //disconnect from the ziServer
      //since ZIAPIDisconnect always returns ZI_SUCCESS
      //no error handling is required
      ziAPIDisconnect( Conn );

    }  

  //destroy the ziConnection
  //since ZIAPIDestroy always returns ZI_SUCCESS
  //no error handling is required
  ziAPIDestroy( Conn );

  return 0;
}
