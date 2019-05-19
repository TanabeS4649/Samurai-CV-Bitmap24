#ifndef __BITMAP24_FILTER_H_INCLUDED__
#define __BITMAP24_FILTER_H_INCLUDED__
#include"bitmap24.h"

namespace Samurai{
namespace CV{
namespace Bitmap24{

Samurai::CV::Bitmap24::Image *channel_masking(Samurai::CV::Bitmap24::Image *img, bool red, bool green, bool blue);

} // Bitmap24
} // CV
} // Samurai

#endif /*__BITMAP24_FILTER_H_INCLUDED__*/

