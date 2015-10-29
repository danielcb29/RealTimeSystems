#include <time.h>
#define MINUS(dst, src1, src2) \
  { \
    if ((src2)->tv_nsec > (src1)->tv_nsec) { \
      (dst)->tv_sec = (src1)->tv_sec - (src2)->tv_sec - 1; \
      (dst)->tv_nsec = ((src1)->tv_nsec - (src2)->tv_nsec) + 1000000000; \
    } \
    else { \
      (dst)->tv_sec = (src1)->tv_sec - (src2)->tv_sec; \
      (dst)->tv_nsec = (src1)->tv_nsec - (src2)->tv_nsec; \
    } \
  }
#define ADD(dst, src1, src2) \
  { \
    if (  (src2)->tv_nsec + (src1)->tv_nsec > 1000000000 ) { \
      (dst)->tv_sec = (src1)->tv_sec + (src2)->tv_sec + 1; \
      (dst)->tv_nsec =  (src2)->tv_nsec + (src1)->tv_nsec - 1000000000; \
    } \
    else { \
      (dst)->tv_nsec =  (src2)->tv_nsec + (src1)->tv_nsec;  \
      (dst)->tv_sec  = (src1)->tv_sec + (src2)->tv_sec; \
    } \
  }
#define ACUM(dst, src1 ) \
  { \
    if (  (dst)->tv_nsec + (src1)->tv_nsec > 1000000000 ) { \
      (dst)->tv_sec = (dst)->tv_sec + (src1)->tv_sec + 1; \
      (dst)->tv_nsec =  (dst)->tv_nsec + (src1)->tv_nsec - 1000000000; \
    } \
    else { \
      (dst)->tv_nsec = (dst)->tv_nsec + (src1)->tv_nsec;  \
      (dst)->tv_sec  = (dst)->tv_sec  + (src1)->tv_sec; \
    } \
  }
#define DIV(dst, pruebas) \
  { \
		if ( ((dst)->tv_sec % (pruebas))!=0) { \
			(dst)->tv_nsec= (dst)->tv_nsec + ((dst)->tv_sec % (pruebas))*1000000000/(pruebas); \
			(dst)->tv_sec = (dst)->tv_sec / (pruebas); \
			if ( (dst)->tv_nsec > 1000000000) { \
				(dst)->tv_nsec-=1000000000; \
				(dst)->tv_sec++; \
	    } \
    } \
    else { \
			(dst)->tv_sec = (dst)->tv_sec / (pruebas); \
    } \
  }
#define CLEAR(time) \
  { \
      (time)->tv_sec = (time)->tv_nsec = 0; \
  }
#define COPY(dst, src) \
  { \
      (dst)->tv_sec  = (src)->tv_sec ; \
      (dst)->tv_nsec = (src)->tv_nsec ; \
  }
#define PRINT(dst) \
  { \
      printf("Sec:  %ld\n", (dst)->tv_sec ); \
      printf("nSec: %ld\n", (dst)->tv_nsec ); \
  }