#include <stdlib.h>
#include <stdio.h>

#include "ziAPI.h"

void PrintVersion( ziConnection Conn )
{
  
  ZI_STATUS RetVal;
  char* ErrBuffer;
  
  char* Path = "ZI/ABOUT/VERSION";
  unsigned char Buffer[ 0xff ];
  unsigned int Length;
  
  if( ( RetVal = ziAPIGetValueB( Conn, 
                                 Path, 
                                 Buffer, 
                                 &Length, 
                                 sizeof(Buffer) - 1 ) ) != ZI_SUCCESS )
    {
      ziAPIGetError( RetVal, &ErrBuffer, NULL );
      fprintf( stderr, "Can't get value: %s\n", ErrBuffer );
    }
  else
    {
      Buffer[ Length ] = 0;
      printf( "%s=\"%s\"\n", Path, Buffer );
    }
  
}
