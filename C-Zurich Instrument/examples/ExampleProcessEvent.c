#include <stdio.h>

#include "ziAPI.h"

void ProcessEvent( ziEvent* Event )
{

  int j;

  switch( Event->Type )
    {
      
    case ZI_DATA_DOUBLE:

      printf( "%u elements of double data %s\n", 
              Event->Count, 
              Event->Path );

      for( j = 0; j < Event->Count; j++ )
	printf( "%f\n", Event->Val.Double[j]);

      break;
      
    case ZI_DATA_INTEGER:

      printf( "%u elements of integer data %s\n", 
              Event->Count, 
              Event->Path );

      for( j = 0; j < Event->Count; j++ )
	printf( "%lld\n", Event->Val.Integer[j] );

      break;
      
    case ZI_DATA_DEMODSAMPLE:

      printf( "%u elements of sample data %s\n", 
              Event->Count, 
              Event->Path );

      for( j = 0; j < Event->Count; j++ )
	printf( "TS=%f, X=%f, Y=%f\n", 
                Event->Val.SampleDemod[j].TimeStamp, 
                Event->Val.SampleDemod[j].X, 
                Event->Val.SampleDemod[j].Y );

      break;
      
    case ZI_DATA_TREE_CHANGED:

      printf( "%u elements of tree-changed data %s\n", 
              Event->Count, 
              Event->Path );

      for( j = 0; j < Event->Count; j++ ){
        
        switch( Event->Val.Tree[j].Action )
          {
          case TREE_ACTION_REMOVE:
            printf( "Tree removed: %s\n", 
                    Event->Val.Tree[j].Name );
            break;

          case TREE_ACTION_ADD:
            printf( "Tree added: %s\n", 
                    Event->Val.Tree[j].Name );
            break;

          case TREE_ACTION_CHANGE:
            printf( "Tree changed: %s\n", 
                    Event->Val.Tree[j].Name );
            break;
          }

      }

      break;
      
    }
  
}
