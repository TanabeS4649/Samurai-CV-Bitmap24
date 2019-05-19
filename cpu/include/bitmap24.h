#ifndef __BITMAP24_H_INCLUDED__
#define __BITMAP24_H_INCLUDED__

#define FILEHEADERSIZE 14
#define INFOHEADERSIZE 40
#define HEADERSIZE (FILEHEADERSIZE+INFOHEADERSIZE)

#include<stdio.h>
#include<string.h>
#include<iostream>
#include<math.h>
#include<cstdlib>

namespace Samurai{
namespace CV{
namespace Bitmap24{

typedef struct{
  unsigned char b;
  unsigned char g;
  unsigned char r;
}Rgb;

typedef struct{
  unsigned int height;
  unsigned int width;
  Samurai::CV::Bitmap24::Rgb *data;
}Image;

Samurai::CV::Bitmap24::Image *read_image(char *filename);
int write_bmp(char *filename, Samurai::CV::Bitmap24::Image *img);
Samurai::CV::Bitmap24::Image *create_image(int width, int height);
void free_image(Samurai::CV::Bitmap24::Image *img);

} // Bitmap24
} // CV
} // Samurai

#endif /*__BITMAP24_H_INCLUDED__*/

