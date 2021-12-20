#include "random.h"

static long rntb[32] = {
           3,
  0x9a319039,
  0x32d9c024,
  0x9b663182,
  0x5da1f342, 
  0xde3b81e0,
  0xdf0a6fb5,
  0xf103bc02,
  0x48f340fb,
  0x7449e56b,
  0xbeb1dbb0, 0xab5c5918, 0x946554fd, 0x8c2e680f, 0xeb3d799f,
  0xb11ee0b7, 0x2d436b86, 0xda672e2a, 0x1588ca88, 0xe369735d,
  0x904f35f7, 0xd7158fd6, 0x6fa6f051, 0x616e6b96, 0xac94efdc, 
  0x36413f93, 0xc622c298, 0xf5a42ab8, 0x8a88d77b, 0xf5ad9d0e,
  0x8999220b, 0x27fb47b9
};

static long* fptr=&rntb[4];
static long* rptr=&rntb[1];
static long* state=&rntb[1];
static long* end_ptr=&rntb[32];

static long rrandom(void)
{
  *fptr+=*rptr;
  long i=(*fptr >> 1) & 0x7fffffff;
  if (++fptr>=end_ptr) {
    fptr=state;
    ++rptr;
  } else {
    if (++rptr>=end_ptr) {
      rptr=state;
    }
  }
  return i;
}

int get_rand(int x, int y)
{
    int r, t;
    long lr;

    if (x > y)
	{
        t = y;
        y = x;
        x = t;
    }
    lr = rrandom();
    lr &= (long) 0x00007fff;
    r = (int) lr;
    r = (r % ((y - x) + 1)) + x;
    return(r);
}

int rand_percent(int percentage)
{
  return(get_rand(1,100)<=percentage);
}

int coin_toss(void)
{
  return (((rrandom()&01) ? 1:0));
}
