#include <rs232.h>
#include <gpib.h>
#include <utility.h>
#include <ansi_c.h>	   

int main()
{
int n,i;
char buf[100]="--------------------------";
int handle;
double db;
/*OpenComConfig (1, "", 9600, 0,7, 2, 512, 512);
//ComWrt (1, "@2H1\r", 5);
ComWrt (1, "@2X\r", 4);
ComRd(1,buf,11);
printf(buf);
printf("\n***********\n");
ComWrt (1, "@2R7\r", 5);
n=ComRdTerm(1,buf,11,13);
printf("%s%i%s%s","ReadBytes:\n",n,"\n***\n:",buf);


*/
//ibonl(0,1);
handle=ibdev (0, 25, NO_SAD, T1s, 0, 1037);
Delay(0.1);
//ibclr (handle);
//ibtrg (handle);		
//ibwrt(handle,"X\r",2);
//n=ibrd(handle,buf,100);
//ibwrt (handle, "V\r",2);
ibwrt (handle, "R7\r",3);
n=ibrd(handle,buf,100);
printf("%s%i%s%i%s%i%s%i","\n read:",n," CNT:",ibcntl," IBSTA:",ibsta," ERR:",iberr);
buf[ibcntl]=0;
printf("%f",atof(buf));
//Delay(10);
//buf[n]=0;
//buf[0]=13;
//printf(buf);
printf("\n");

for(i=0;i<20;i++){printf("%i%s%c%s",i,"=",buf[i],"\n");}
//buf[0]=1;
//db=atof(buf);
//printf("%s%f","\n***:",db);
//printf("%x",ibsta);
Delay(10);
		  }
