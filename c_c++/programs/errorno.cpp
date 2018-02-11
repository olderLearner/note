#include <errno.h>  
#include <string.h>  
#include <stdio.h>  
#include <sys/time.h>
  
int main()  
{  
    int i;  
    struct timeval tv;
    gettimeofday(&tv,NULL);
    for(i = 0; i < 140; ++i)  
    {  
        errno = i;
gettimeofday(&tv,NULL);
printf("millisecond:%ld\n",tv.tv_sec*1000 + tv.tv_usec/1000);
        printf("errno %d :\t%s\n",i,strerror(errno));  
gettimeofday(&tv,NULL);
printf("millisecond:%ld\n",tv.tv_sec*1000 + tv.tv_usec/1000);
    }  
    return 0;  
}
