#include <stdlib.h>
#include <stdio.h>

#include "ziAPI.h"

void GetSample( ziConnection Conn )
{
  
  ZI_STATUS RetVal;
  char* ErrBuffer;

  DemodSample ValueS;

  if( ( RetVal = ziAPIGetValueS( Conn, 
                                 "DEV1046/demods/0/sample", 
                                 &ValueS ) ) != ZI_SUCCESS )
    {
      ziAPIGetError( RetVal, &ErrBuffer, NULL );
      fprintf( stderr, "Can't get Parameter: %s\n", ErrBuffer );
    }
  else
    {
      printf( "TS = %f, X=%f, Y=%f\n", 
              ValueS.TimeStamp, 
              ValueS.X, 
              ValueS.Y );
    }

}
