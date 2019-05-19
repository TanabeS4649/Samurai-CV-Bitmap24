#include"bitmap24_filter.h"

namespace Samurai{
namespace CV{
namespace Bitmap24{

Samurai::CV::Bitmap24::Image *channel_masking(Samurai::CV::Bitmap24::Image *img, bool red, bool green, bool blue)
{

  unsigned int width = img->width;
  unsigned int height = img->height;
  Samurai::CV::Bitmap24::Image *img_;

  img_ = img;

  for(unsigned int i=0; i<height; i++){
    for(unsigned int j=0; j<width; j++){

      if(blue == true ){
        img_->data[(height-i-1)*width + j].b = (unsigned char)0;
      } else {
        img_->data[(height-i-1)*width + j].b = img->data[(height-i-1)*width + j].b;
      }

      if(green == true){
        img_->data[(height-i-1)*width + j].g = (unsigned char)0;
      } else {
        img_->data[(height-i-1)*width + j].g = img->data[(height-i-1)*width + j].g;
      }

      if(red == true){
        img_->data[(height-i-1)*width + j].r = (unsigned char)0;
      } else {
        img_->data[(height-i-1)*width + j].r = img->data[(height-i-1)*width + j].r;
      }
    }
  }

  return img_;

}

} // Bitmap24
} // CV
} // Samurai


