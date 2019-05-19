#include"bitmap24.h"

namespace Samurai{
namespace CV{
namespace Bitmap24{

Samurai::CV::Bitmap24::Image *read_image(char *filename)
{
/*

  Flow chart:
    1. Read header file
    2. Check height and width of image
    3. Read data of image

  Data structure of Bitmap which have 24 bit:
    [0:1] File type
    [2:5] File size (byte unit)
    [6:7] Reservation, 0
    [8:9] Reservation, 0
    [10:13] Start byte address of data, 54
    [14:17] Size of header, 40
    [18:21] Width of image
    [22:25] Height of image
    [26:27] Number of plane, 1
    [28:29] What number of bit is this bitmap file?
    [30:33] Comppressed image?, 0
    [34:37] Size of image, width * height * 3
    [38:41] Resolution of horizontal, 0
    [42:45] Resolution of vertical, 0
    [46:49] Number of pallet, 0
    [50:53] Index of important pallet, 0
    [54:xx] Data of image

*/

  int real_width; // number of byte in data
  unsigned int width, height; // Number of pixels
  unsigned int color; // Type of bitmap file
  FILE *fp;
  unsigned char header_buf[HEADERSIZE]; // Header file
  unsigned char *bmp_line_data;  // a line data of image
  Samurai::CV::Bitmap24::Image *img;

  if((fp = fopen(filename, "rb")) == NULL){
    std::cout << stderr << " Error: " << filename << " could not read." << std::endl;
    return NULL;
  }

  // 1. Read header file
  fread(header_buf, sizeof(unsigned char), HEADERSIZE, fp);
  if(strncmp((const char*)header_buf, "BM", 2)){
    std::cout << stderr << "Error: " << filename << " is not Image file." << std::endl;
    return NULL;
  }

  // 2. Check height and width of image
  memcpy(&width, header_buf + 18, sizeof(width));
  memcpy(&height, header_buf + 22, sizeof(height));
  memcpy(&color, header_buf + 28, sizeof(unsigned int));
  if(color != 24){
    std::cout << stderr << " Error: " << filename << " is not 24bit color image" << std::endl;
    return NULL;
  }

  // RGB data must be multiple of 4 byte
  real_width = width*3 + width%4;

  // Buffer a line data of image
  if((bmp_line_data = (unsigned char *)malloc(sizeof(unsigned char)*real_width)) == NULL){
    std::cout << stderr << " Error: Allocation error." << std::endl;
    return NULL;
  }
  if((img = create_image(width, height)) == NULL){
    free(bmp_line_data);
    fclose(fp);
    return NULL;
  }

  // 3. Read data of image
  for(unsigned int i=0; i<height; i++){
    fread(bmp_line_data, 1, real_width, fp);
    for(unsigned int j=0; j<width; j++){
      img->data[(height-i-1)*width + j].b = bmp_line_data[j*3];
      img->data[(height-i-1)*width + j].g = bmp_line_data[j*3 + 1];
      img->data[(height-i-1)*width + j].r = bmp_line_data[j*3 + 2];
    }
  }

  free(bmp_line_data);
  fclose(fp);

  return img;
}


int write_bmp(char *filename, Samurai::CV::Bitmap24::Image *img)
{
/*

  Flow chart:
    1. Read header file
    2. Check height and width of image
    3. Read data of image

  Data structure of Bitmap which have 24 bit:
    [0:1] File type
    [2:5] File size (byte unit)
    [6:7] Reservation, 0
    [8:9] Reservation, 0
    [10:13] Start byte address of data, 54
    [14:17] Size of header, 40
    [18:21] Width of image
    [22:25] Height of image
    [26:27] Number of plane, 1
    [28:29] What number of bit is this bitmap file?
    [30:33] Comppressed image?, 0
    [34:37] Size of image, width * height * 3
    [38:41] Resolution of horizontal, 0
    [42:45] Resolution of vertical, 0
    [46:49] Number of pallet, 0
    [50:53] Index of important pallet, 0
    [54:xx] Data of image

*/

  FILE *fp;
  unsigned int real_width;
  unsigned char *bmp_line_data; // a line data of image
  unsigned char header_buf[HEADERSIZE]; // Header file
  unsigned int file_size;
  unsigned int offset_to_data;
  unsigned long info_header_size;
  unsigned int planes;
  unsigned int color;
  unsigned long compress;
  unsigned long data_size;
  long xppm;
  long yppm;

  if((fp = fopen(filename, "wb")) == NULL){
    fprintf(stderr, "Error: %s could not open.", filename);
    return 1;
  }

  real_width = img->width*3 + img->width%4;

  // Create headerfile
  file_size = img->height * real_width + HEADERSIZE;
  offset_to_data = HEADERSIZE;
  info_header_size = INFOHEADERSIZE;
  planes = 1;
  color = 24;
  compress = 0;
  data_size = img->height * real_width;
  xppm = 1;
  yppm = 1;
  
  header_buf[0] = 'B';
  header_buf[1] = 'M';
  memcpy(header_buf + 2, &file_size, sizeof(file_size));
  header_buf[6] = 0;
  header_buf[7] = 0;
  header_buf[8] = 0;
  header_buf[9] = 0;
  memcpy(header_buf + 10, &offset_to_data, sizeof(file_size));
  header_buf[11] = 0;
  header_buf[12] = 0;
  header_buf[13] = 0;

  memcpy(header_buf + 14, &info_header_size, sizeof(info_header_size));
  header_buf[15] = 0;
  header_buf[16] = 0;
  header_buf[17] = 0;
  memcpy(header_buf + 18, &img->width, sizeof(img->width));
  memcpy(header_buf + 22, &img->height, sizeof(img->height));
  memcpy(header_buf + 26, &planes, sizeof(planes));
  memcpy(header_buf + 28, &color, sizeof(color));
  memcpy(header_buf + 30, &compress, sizeof(compress));
  memcpy(header_buf + 34, &data_size, sizeof(data_size));
  memcpy(header_buf + 38, &xppm, sizeof(xppm));
  memcpy(header_buf + 42, &yppm, sizeof(yppm));
  header_buf[46] = 0;
  header_buf[47] = 0;
  header_buf[48] = 0;
  header_buf[49] = 0;
  header_buf[50] = 0;
  header_buf[51] = 0;
  header_buf[52] = 0;
  header_buf[53] = 0;

  // Write header file
  fwrite(header_buf, sizeof(unsigned char), HEADERSIZE, fp);
  
  if((bmp_line_data = (unsigned char *)malloc(sizeof(unsigned char)*real_width)) == NULL){
    std::cout << stderr << "Error: Allocation error." << std::endl;
    fclose(fp);
    return 1;
  }

  // Write RGB data
  for(unsigned int i=0; i<img->height; i++){
    for(unsigned int j=0; j<img->width; j++){
      bmp_line_data[j*3]      =  img->data[(img->height - i - 1)*img->width + j].b;
      bmp_line_data[j*3 + 1]  =  img->data[(img->height - i - 1)*img->width + j].g;
      bmp_line_data[j*3 + 2]  =  img->data[(img->height - i - 1)*img->width + j].r;
    }
    // RGB data must be multiple of 4 byte
    for(unsigned int j=img->width*3; j<real_width; j++){
      bmp_line_data[j] = 0;
    }
    fwrite(bmp_line_data, sizeof(unsigned char), real_width, fp);
  }

  free(bmp_line_data);

  fclose(fp);

  return 0;
}


Samurai::CV::Bitmap24::Image *create_image(int width, int height)
{
  Samurai::CV::Bitmap24::Image *img;

  if((img = (Samurai::CV::Bitmap24::Image *)malloc(sizeof(Samurai::CV::Bitmap24::Image))) == NULL){
    std::cout << stderr << " Allocation error" << std::endl;
    return NULL;
  }

  if((img->data = (Samurai::CV::Bitmap24::Rgb*)malloc(sizeof(Samurai::CV::Bitmap24::Rgb)*width*height)) == NULL){
    std::cout << stderr << " Allocation error" << std::endl;
    free(img);
    return NULL;
  }

  img->width = width;
  img->height = height;

  return img;
}


void free_image(Samurai::CV::Bitmap24::Image *img)
{
  free(img->data);
  free(img);
}

} // Bitmap24
} // CV
} // Samurai


