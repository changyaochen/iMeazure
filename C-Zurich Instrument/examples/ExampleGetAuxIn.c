#include <stdlib.h>
#include <stdio.h>

#include "ziAPI.h"

void GetSample( ziConnection Conn )
{
  
  ZI_STATUS RetVal;
  char* ErrBuffer;
  
  AuxInSample ValueAuxIn;
  
  if( ( RetVal = ziAPIGetValueAuxIn( Conn, 
                                     "DEV1046/auxins/0/sample", 
                                     &ValueAuxIn ) ) != ZI_SUCCESS )
    {
      ziAPIGetError( RetVal, &ErrBuffer, NULL );
      fprintf( stderr, "Can't get Parameter: %s\n", ErrBuffer );
    }
  else
    {
      printf( "TS = %f, ch0=%f, ch1=%f\n", 
              ValueAuxIn.TimeStamp, 
              ValueAuxIn.Ch0,
              ValueAuxIn.Ch1 );
    }
  
}
