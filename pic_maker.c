#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int test(int x, int y, int r){
  int xcor = x-250;
  int ycor = y-250;
  int radius = r;
  if( ( (xcor*xcor) + (ycor*ycor) ) <= (radius*radius) ){
    return 0;
  }
  return -1;
}

int color_picker(int r){
  int val = r%3;
  //printf("%d\n",val);
  return val;
}

void print_pixes(){
  int fd, bn;
  fd = open("my_pic.ppm",O_CREAT|O_RDWR,0666);
  char* h = "P3 500 500 255\n";
  bn = write(fd,h,strlen(h));
  if(bn==-1){
    perror("writing head failed");
  }

  int x = 0;
  int y = 0;
  for(y=0; y<500; y = y+1){
    for(x=0; x<500; x = x+1){
      //char* p = "0 255 255 ";
      char* p;
      char* pp;

      int c=-1;
      int r=0;
      for(r=0; r<250; r+=50){
        if(test(x,y,r)==0){
	  if(color_picker(r)==0){
	    c=0;
	    pp = "0 0 255 ";
	    sprintf(p,pp);
	    bn = write(fd,p,strlen(pp));
	    if(bn==-1){
	      perror("writing pix failed");
	    }
	  }else if(color_picker(r)==1){
	    c=0;
	    pp = "0 0 100 ";
	    sprintf(p,pp);
	    bn = write(fd,p,strlen(pp));
	    if(bn==-1){
	      perror("writing pix failed");
	    }
	  }else{
	    c=0;
	    if(y<100){
	      //pp = "255 196 0 ";
	      pp = "236 167 28 ";
	    }else{
	      pp = "39 0 131 ";
	    }
	    sprintf(p,pp);
	    bn = write(fd,p,strlen(pp));
	    if(bn==-1){
	      perror("writing pix failed");
	    }
	  }
	}
      }
      if(c==-1){
	if(y>=100){
	  pp = "43 91 144 ";
	}else{
	  //pp = "0 175 255 ";
	   pp = "164 90 35 ";
	}
	sprintf(p,pp);
	bn = write(fd,p,strlen(pp));
	if(bn==-1){
	  perror("writing pix failed");
	}
      }

    }
    char* sp = "\n\n";
    bn = write(fd,sp,2);
  }

  int c;
  c = close(fd);
}

int main(){
  print_pixes();
  return 0;
}
