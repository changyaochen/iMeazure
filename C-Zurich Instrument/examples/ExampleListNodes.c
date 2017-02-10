#include <stdio.h>

#include "ziAPI.h"

void PrintChildren( ziConnection Conn, 
                    char* Path )
{

  ZI_STATUS RetVal;
  char* ErrBuffer;

  char NodesBuffer[ 8192 ];
  
  if( ( RetVal = ziAPIListNodes( Conn, 
                                 Path, 
                                 NodesBuffer, 
                                 8192, 
                                 ZI_LIST_NONE ) ) != ZI_SUCCESS )
    {
      ziAPIGetError( RetVal, &ErrBuffer, NULL );
      fprintf( stderr, "Can't List Nodes: %s\n", ErrBuffer );
    }
  else
    {

      char* Ptr = NodesBuffer;
      char* LastPtr = Ptr;
      
      //print out each node on a separate line with dash as prefix
      for( ; *Ptr != 0; Ptr++ )
	{

	  if( *Ptr == '\n' )
	    {
	      *Ptr = 0;
	      printf("- %s\n", LastPtr);
	      LastPtr = Ptr + 1;
	    }
	  
	}

      //print out the last node
      if( Ptr != LastPtr )
        printf("- %s\n", LastPtr);

    }
  
}
