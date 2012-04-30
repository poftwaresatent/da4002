#include <png.h>
#include <stdexcept>
#include <errno.h>

using namespace std;


static void png2txt(std::string const & filename) throw(std::runtime_error);
static void png2txt(FILE * fp) throw(std::runtime_error);


void png2txt(std::string const & filename) throw(std::runtime_error)
{
  FILE * fp(fopen(filename.c_str(), "rb"));
  if (0 == fp) {
    throw runtime_error("png2txt(" + filename + "): " + strerror(errno));
  }
  png2txt(fp);
  fclose(fp);
}
  
  
void 
png2txt(FILE * fp) throw(std::runtime_error)
{
  png_structp read_;
  png_infop read_info_, read_info_end_;
  png_uint_32 width_, height_;
  png_bytepp row_p_;
  
  width_ = 0;
  height_ = 0;
  row_p_ = 0;
  
  read_ = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  if ( ! read_) {
    throw runtime_error("png2txt(): png_create_read_struct() failed");
  }
  read_info_ = png_create_info_struct(read_);
  if ( ! read_info_) {
    throw runtime_error("png2txt(): png_create_info_struct() failed");
  }
  read_info_end_ = png_create_info_struct(read_);
  if ( ! read_info_end_) {
    throw runtime_error("png2txt(): png_create_info_struct() failed");
  }
  
  png_init_io(read_, fp);
  png_read_png(read_, read_info_, PNG_TRANSFORM_IDENTITY, 0);
  int bit_depth, color_type, interlace_type, compression_type, filter_type;
  png_get_IHDR(read_, read_info_, &width_, &height_, &bit_depth, &color_type,
	       &interlace_type, &compression_type, &filter_type);
  if (PNG_COLOR_TYPE_GRAY != color_type) {
    throw runtime_error("png2txt(): input is not grayscale");
  }
  if (8 != bit_depth) {
    throw runtime_error("png2txt(): input is not 8-bit");
  }
    
  row_p_ = png_get_rows(read_, read_info_);
  if ( ! row_p_) {
    throw runtime_error("png2txt(): png_get_rows() failed");
  }
    
  for (png_uint_32 irow(0); irow < height_; ++irow) {
    png_bytep row(row_p_[irow]);
    for (png_uint_32 icol(0); icol < width_; ++icol) {
      if (0 == row[icol]) {
	fprintf(stdout, "  # ");
      }
      else {
	fprintf(stdout, "%3d ", (int) 256 - row[icol]);
      }
    }
    fprintf(stdout, "\n");
  }
  
  png_destroy_read_struct(&read_, &read_info_, &read_info_end_);
  png_destroy_info_struct(read_, &read_info_);
  png_destroy_info_struct(read_, &read_info_end_);
}


int main(int argc, char ** argv)
{
  if (2 > argc) {
    png2txt(stdin);
  }
  else {
    png2txt(argv[1]);
  }
}
