#include <stdlib.h>
#include <stdio.h>

#include "ziAPI.h"

void UpdateValue( ziConnection Conn )
{

  ZI_STATUS RetVal;
  char* ErrBuffer;
  ziDoubleType ValueD;

  if( ( RetVal = ziAPISetValueI( Conn, 
                                 "DEV1046/demods/*/rate", 
                                 100 ) ) != ZI_SUCCESS )
    {
      ziAPIGetError( RetVal, &ErrBuffer, NULL );
      fprintf( stderr, "Can't set Parameter: %s\n", ErrBuffer );
    }
  
  if( ( RetVal = ziAPIGetValueD( Conn, 
                                 "DEV1046/demods/0/rate", 
                                 &ValueD ) ) != ZI_SUCCESS )
    {
      ziAPIGetError( RetVal, &ErrBuffer, NULL );
      fprintf( stderr, "Can't get Parameter: %s\n", ErrBuffer );
    }
  else
    {
      printf( "Value = %f\n", ValueD );
    }

}
