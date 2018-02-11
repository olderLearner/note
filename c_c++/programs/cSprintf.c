#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct stCmd{
    int iCmdSize;                   /* Command Size */
    unsigned char cCmdData[256];    /* Command Data : 1024byte */
}_stCmd;

static struct stCmd stCmdData;

static int generateCmdData(unsigned char* speed, struct stCmd* pstCmdData);

int main() {
  int i = 500;
  //printf("%x\n", i);
  char r[4] = {0};
  sprintf(r, "%x", i);
  //for (int k=0; k<strlen(r); k++) {
  //  printf("r[%d]:0x%x\t", k, r[k]);
  //}
  //printf("\n");
  //printf("%s\n", r);

  //unsigned char s[4] = {0};
  //s[0] = i & 0xf;
  //s[1] = (i & 0xf0) >> 4;
  //s[2] = (i & 0xf00) >> 8;
  //s[3] = (i & 0xf000) >> 12;
/**
  unsigned char q[2] = {0};
  q[0] = i & 0xff;
  q[1] = (i & 0xff00) >> 8;

  for (int l=0; l<2; l++) {
  	printf("q[%d]:0x%x\t", l, q[l]);
  }
  printf("\n");
**/
  float v = 0.0;
  unsigned char speed[2] = {0};

  for (i=0; i< 60; i++ ) {
  	if (i <=20) {
  		v = 3 * 0.5 * i;
  	} else if (i >= 40) {
  		v += -3 * 0.5;
  	}

  	printf("v:%0.1f ", v);
  	int data = v / 0.00391;
  	printf("data:%d ", data);
  	speed[0] = data & 0xff;
  	speed[1] = (data & 0xff00) >> 8;
  	for (int l=0; l<2; l++) {
  		printf("speed[%d]:0x%x\t", l, speed[l]);
  	}
    memset( &stCmdData, '\0', sizeof(struct stCmd));
  	generateCmdData(speed, &stCmdData);
  	//printf("%0.1f\n", (data * 0.00391 + 0)/1.0);
  	usleep(500000);
  }
  return 0;
}


static int generateCmdData(unsigned char* speed, struct stCmd* pstCmdData) {
    
    unsigned char dataLen = 0x05;
    pstCmdData->iCmdSize = 10;
    if (speed[1] != 0x00) {
        dataLen = 0x06;
        pstCmdData->iCmdSize = 11;
    }
    printf("cmddata size:%d \n", pstCmdData->iCmdSize);
    pstCmdData->cCmdData[0] = 0x02;
    
    pstCmdData->cCmdData[1] = 0x00;
    pstCmdData->cCmdData[2] = dataLen;
    pstCmdData->cCmdData[3] = 0xff;
    pstCmdData->cCmdData[4] = ~dataLen;

    pstCmdData->cCmdData[5] = 0xa9;
    pstCmdData->cCmdData[6] = 0x85;

    pstCmdData->cCmdData[7] = 0xcb;

    if (dataLen == 0x05) {
    	pstCmdData->cCmdData[8] = speed[0];
    	pstCmdData->cCmdData[9] = 0x03;
    } else if (dataLen == 0x06) {
	    pstCmdData->cCmdData[8] = speed[0];
    	pstCmdData->cCmdData[9] = speed[1];
    	pstCmdData->cCmdData[10] = 0x03;
    } else {
    	printf("error!\n");
    }

    for (int i=0; i< pstCmdData->iCmdSize; i++) {
    	printf("cmdData[%d]:0x%x\t", i, pstCmdData->cCmdData[i]);
    }
    printf("\n");

}