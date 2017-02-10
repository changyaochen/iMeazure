#include <stdlib.h>
#include <stdio.h>

#include "ziAPI.h"

void UpdateValue( ziConnection Conn )
{
  
  ZI_STATUS RetVal;
  char* ErrBuffer;
  ziIntegerType ValueI;

  if( ( RetVal = ziAPISetValueD( Conn, 
                                 "DEV1046/demods/*/rate", 
                                 5.53 ) ) != ZI_SUCCESS )
    {
      ziAPIGetError( RetVal, &ErrBuffer, NULL );
      fprintf( stderr, "Can't set Parameter: %s\n", ErrBuffer );
    }
  
  if( ( RetVal = ziAPIGetValueI( Conn, 
                                 "DEV1046/demods/0/rate", 
                                 &ValueI ) ) != ZI_SUCCESS )
    {
      ziAPIGetError( RetVal, &ErrBuffer, NULL );
      fprintf( stderr, "Can't get Parameter: %s\n", ErrBuffer );
    }
  else
    {
      printf( "Value = %lld\n", ValueI );
    }

}
