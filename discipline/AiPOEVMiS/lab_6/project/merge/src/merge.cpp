#include <Magick++.h> 
#include <iostream>
#include <sstream>
#include <algorithm>
#include <new>

#include <cstdlib>
#include <getopt.h>

#define SIZE_RGBA 4

using namespace std; 
using namespace Magick;

extern "C" void merge_raw_pixels(unsigned char * raw_pixels_a, unsigned char * raw_pixels_b,
                                 unsigned char * raw_pixels_res, size_t num_pixels);
extern "C" void end_MMX();

struct Args {
  string path_src_1;   // source image path 1
  string path_src_2;   // source image path 2
  string path_dst;   // destination image path
};

void
print_usage(char * program_name, int exit_code) {
  cout << "Usage: " << program_name << " -o dst_image src_image_1 src_image_2\n"
       << "  -o  --output out_image         Specify output image path.\n"
       << "  -h  --help                     Display this usage message." << endl;
  exit(exit_code);
}

// parse cmdline arguments
Args
parse_args(int argc, char **argv) {
  Args args;

  const char *const short_opts = "o:h";
  const struct option long_opts[] = {
    { "output",   1, NULL, 'o'  },
    { "help",     0, NULL, 'h'  },
    { NULL,       0, NULL,  0   }
  };
  
  int next_opt;
  do {
    next_opt = getopt_long(argc, argv, short_opts,
                           long_opts, NULL);
    switch (next_opt) {

    case 'h':
      print_usage(argv[0], 0);
      break;
      
    case 'o':
      args.path_dst = string(optarg);
      
    case '?':
    case -1:
      break;
      
    default:
      print_usage(argv[0], 1);
      break;
    }
  }
  while (next_opt != -1);

  // destination path is not set
  if (args.path_dst == "") {
    cout << "Please, specify output image path." << endl;
    print_usage(argv[0], 1);
  }

  // sorce paths are not provided
  if ((argc - optind) < 2) {
    cout << "Please, specify input image paths." << endl;
    print_usage(argv[0], 1);
  }

  args.path_src_1 = string(argv[optind]);
  args.path_src_2 = string(argv[optind+1]);
  
  return args;
}

// merge images into one file
void
merge_images(string path_src_1, string path_src_2, string path_dst) {
  Image image_a, image_b;

  // Read a file into image object 
  image_a.read(path_src_1);
  image_a.type(TrueColorType);
    
  image_b.read(path_src_2);
  image_b.type(TrueColorType);
    
  // Determine size of result image
  size_t rows = min(image_a.rows(), image_b.rows());
  size_t columns = min(image_a.columns(), image_b.columns());

  // Create result image
  Image image_res(Geometry(rows, columns), Color("white"));
  image_res.type(TrueColorType);

  // Write raw pixels of a
  unsigned char * raw_pixels_a = (unsigned char *) calloc(columns*rows, SIZE_RGBA);
  if (!raw_pixels_a) {
    cout << "Error: cannot allocate memory." << endl;
    throw bad_alloc();
  }
    
  image_a.write(0, 0, columns, rows, "RGBA", CharPixel, raw_pixels_a);

  // Write raw pixels of b
  unsigned char * raw_pixels_b = (unsigned char *) calloc(columns*rows, SIZE_RGBA);
  if (!raw_pixels_b) {
    cout << "Error: cannot allocate memory." << endl;
    free(raw_pixels_a);
    throw bad_alloc();
  }

  image_b.write(0, 0, columns, rows, "RGBA", CharPixel, raw_pixels_b);
    
  // Allocate raw pixels of res
  unsigned char * raw_pixels_res = (unsigned char *) calloc(columns*rows, SIZE_RGBA);
  if (!raw_pixels_res) {
    cout << "Error: cannot allocate memory." << endl;
    free(raw_pixels_a);
    free(raw_pixels_b);
    throw bad_alloc();
  }

  // call ASM
  merge_raw_pixels(raw_pixels_a, raw_pixels_b, raw_pixels_res, rows*columns);
  end_MMX();
    
  // Write chages to result image
  image_res.read(columns, rows, "RGBA", CharPixel, raw_pixels_res);
    
  // Write result image to file 
  image_res.write(path_dst);

  // free acquired memory
  free(raw_pixels_a);
  free(raw_pixels_b);
  free(raw_pixels_res);
}

int main(int argc, char **argv) 
{
  Args args = parse_args(argc, argv);
  try { 
    InitializeMagick(*argv);    
    merge_images(args.path_src_1, args.path_src_2, args.path_dst);
  } 
  catch( Exception &error_ ) { 
    cout << "Caught exception: " << error_.what() << endl;
    return 1; 
  }
  return 0; 
}
