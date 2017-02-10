#include <stdlib.h>
#include <stdio.h>

#include "ziAPI.h"

void GetSample( ziConnection Conn )
{
  
  ZI_STATUS RetVal;
  char* ErrBuffer;

  DIOSample ValueDIO;

  if( ( RetVal = ziAPIGetValueDIO( Conn, 
                                   "DEV1046/dios/0/output", 
                                   &ValueDIO ) ) != ZI_SUCCESS )
    {
      ziAPIGetError( RetVal, &ErrBuffer, NULL );
      fprintf( stderr, "Can't get Parameter: %s\n", ErrBuffer );
    }
  else
    {
      printf( "TS = %f, bits=%08x\n", 
              ValueDIO.TimeStamp, 
              ValueDIO.Bits );
    }

}
