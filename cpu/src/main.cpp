#include"bitmap24.h"
#include"bitmap24_filter.h"
#include<stdlib.h>
#include<stdio.h>
#include<iostream>

int main(int argc, char *argv[])
{
  if(argc != 3){
    std::cout << stderr << " Usage: ./main <inputfile> <outputfile>\n" << std::endl;
    exit(1);
  }

  Samurai::CV::Bitmap24::Image *colorimg;
  Samurai::CV::Bitmap24::Image *colorimg_;

  // 1. Read bitmap image
  if((colorimg = Samurai::CV::Bitmap24::read_image(argv[1])) == NULL){
    exit(1);
  }

  // 2. Filtering bitmap  image
  colorimg_ = Samurai::CV::Bitmap24::channel_masking(colorimg, false, true, true); // red, green, blue

  // 3. Write bitmap image
  if(Samurai::CV::Bitmap24::write_bmp(argv[2], colorimg_)){
    exit(1);
  }

  Samurai::CV::Bitmap24::free_image(colorimg);
  Samurai::CV::Bitmap24::free_image(colorimg_);

  return 0;
}

