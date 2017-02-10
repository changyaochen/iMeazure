#include <stdlib.h>
#include <stdio.h>

#include "ziAPI.h"

void ProgramCPU( ziConnection Conn,
                 char* Buffer,
                 int Len )
{
  
  ZI_STATUS RetVal;
  char* ErrBuffer;

  if( ( RetVal = ziAPISetValueB( Conn, 
                                 "DEV1046/cpus/0/program", 
                                 Buffer,
                                 Len ) ) != ZI_SUCCESS )
    {
      ziAPIGetError( RetVal, &ErrBuffer, NULL );
      fprintf( stderr, "Can't set Parameter: %s\n", ErrBuffer );
    }

}
