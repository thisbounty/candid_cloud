/* 

   Mask word cloud generator

   Copyright Salva Espana Boquera sespana@dsic.upv.es

   mostly made for fun (it could be greatly improved)
   
   in debian/ubuntu install first libcairomm-1.0-dev

   LICENSE: LGPL v3
*/

#include "mask_word_cloud.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <random>
#include <unistd.h> // getopt

void usage(const char *programname) {
  std::cerr <<
    "Usage: " << programname << " \\\n"
    "\t[-h] \\ (show this help)\n"
    "\t[-r red_background] \\   (RGB of background, default 255 255 255 black\n"
    "\t[-g green_background] \\  color components in scale 0-255)\n"
    "\t[-b blue_background] \\\n"
    "\t[-m mask_file] \\ (determines also the size of image)\n"
    "\t[-c color_file] \\ (must have the same size of mask, words colors are picked from here)\n"
    "\t[-f font_name] \\  (e.g. Sans)\n"
    "\t[-M min_font_size] \\ (default value 10)\n"
    "\t[-o output_prefix] \\ (default \"output\" generate \"output.png\") \n"
    "\t[-d words_margin] \\ (default value is 2)\n"
    "\t[-v vertical_preference] \\ (value between 0 and 100, default is 50)\n"
    "\twords.txt (an ordered list of pairs word initial_size)\n";
}

std::istream& safeGetline(std::istream& is, std::string& t)
{
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if(sb->sgetc() == '\n')
                sb->sbumpc();
            return is;
        case EOF:
            // Also handle the case when the last line has no line ending
            if(t.empty())
                is.setstate(std::ios::eofbit);
            return is;
        default:
            t += (char)c;
        }
    }
}

int main (int argc, char **argv) {
  const char *maskfilename       = "mask.png";
  const char *colorimagefilename = "";
  const char *fontname           = "Sans";
  const char *outputfilename  = "output";
  clock_t start = clock();

  double r = 255;
  double g = 255;
  double b = 255;
  int    R = 0;
  int    G = 0;
  int    B = 0;
  int vertical_preference=50;
  int font_step=2;
  int mini_font_size=10;
  int words_margin=2;
  int opt;
  while ((opt = getopt(argc, argv, "hr:g:b:m:c:f:M:o:d:v:")) != -1) {
    switch (opt) 
      {
      case 'h':
	usage(argv[0]);
	exit(EXIT_SUCCESS);
      case 'r':
	r = atof(optarg)/255.0;
	break;
      case 'g':
	g = atof(optarg)/255.0;
	break;
      case 'b':
	b = atof(optarg)/255.0;
	break;
      case 'm':
	maskfilename = optarg;
	break;
      case 'c':
	colorimagefilename = optarg;
	break;
      case 'f':
	fontname = optarg;
	break;
      case 'M':
	mini_font_size = atoi(optarg);
	break;
      case 'o':
	outputfilename = optarg;
	break;
      case 'd':
	words_margin = atoi(optarg);
	break;
      case 'v':
	vertical_preference = atoi(optarg);
	break;
      default: /* '?' */
	usage(argv[0]);
	exit(EXIT_FAILURE);
      }
  }
  
  if (optind >= argc) {
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }
  const char *termsfilename = argv[optind];

  std::string output_prefix(outputfilename);
  std::string png_outputfilename = output_prefix + ".png";
  
  MaskWordCloud mwc(maskfilename,
		    colorimagefilename,
		    fontname,
		    r,g,b,
		    R,G,B,
		    vertical_preference,
		    words_margin,
		    mini_font_size);
  
  std::ifstream fs;
  fs.open(termsfilename);
  std::string word;
  std::mt19937 rd;
  std::vector <std::pair<std::string,int> > wordsList;
  int biggestDimention = mwc.width > mwc.height ? mwc.width : mwc.height;
  int biggestSize = biggestDimention/8 > 200 ? biggestDimention/8 : 200;
  std::uniform_int_distribution<int> d(50, biggestSize);
  while (!safeGetline(fs, word).eof()) {
    wordsList.push_back(std::make_pair(word, d(rd)));
  }
  bool goon=true;
  while (goon) {
    std::uniform_int_distribution<int> d(0, wordsList.size()-1);
    int i = d(rd);
    goon = mwc.paintWord(wordsList[i].first.c_str(), wordsList[i].second);
  }
  mwc.writeImage(png_outputfilename.c_str());
  printf("Took: %f", double(clock() - start) / CLOCKS_PER_SEC);
  return 0;
}

