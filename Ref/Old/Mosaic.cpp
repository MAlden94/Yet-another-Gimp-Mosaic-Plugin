#include <GraphicsMagick/Magick++.h>
#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <boost/config.hpp>
#include <boost/regex.hpp>
#include <thread>

//g++ Mosaic.cpp $(GraphicsMagick++-config --cppflags --cxxflags --ldflags --libs)  -lboost_regex -g -O0 -std=gnu++11

// shit I need to finish this
// and add threads
// and qt load ui file

using namespace std;
using namespace Magick;

void Tiler(void);
bool match(double rl, double gl, double bl, double rr, double gr, double br);

float uLimit = 0.01;
unsigned char formula = 0;

unsigned long twidth  = 18;
unsigned long theight = 18;

vector < string > Thumbnails;
string SourceFiles = "";
const boost::regex validfiles(".*\\.[Jj][Pp][Gg]");

/*
struct Tiles {
  string Name;
  long   Width;
  long   Height;
  double MeanR;
  double MeanG;
  double MeanB;
} *TilesData [];
*/

int main(int argc, char **argv)
{
    argv[1] = "/home/mitch/Pictures/my photos/photos/";
    argv[2] = "./out.jpg";
    InitializeMagick(*argv);
    //if (!argv[1] || !argv[2]){
     // cout << "2\n";
     // exit(1);
    //}
    SourceFiles = argv[2];


    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(argv[1])) == NULL) {
	perror("opendir");
    }

    while ((entry = readdir(dir)) != NULL) {
	if (entry->d_type != DT_REG)
	    continue;

	if (boost::regex_match(string(entry->d_name), validfiles)) {
	    Thumbnails.push_back(string(argv[1]) + string(entry->d_name));
	}
    }

    closedir(dir);


    cout << "run\n";
    Tiler();

    return 0;
}

bool match(double rl, double gl, double bl, double rr, double gr, double br)
{
    float TotalDelta = 0;
    switch (formula) {
    case 0:			// Euclidean
	TotalDelta = sqrt(pow(abs(rl - rr), 2) + pow(abs(gl - gr), 2) + pow(abs(bl - br), 2));
	break;
    case 1:			// Manhattan
	TotalDelta = abs(rl - rr) + abs(gl - gr) + abs(bl - br);
	break;
    case 2:                     // Max (NIY!!!)
	TotalDelta = 0;
    }

    if (TotalDelta < uLimit && TotalDelta > 0) {
	cout << TotalDelta << " ~ " << uLimit << " true\n";
        uLimit = TotalDelta;
	return true;
    }
    //cout << TotalDelta << " ~ " << uLimit << " false\n";
    return false;
}

void Tiler(void)
{

    Image Source, Thumbnail;

    PixelPacket *SourcePixels, *ThumbnailPixels;

    Source.read(SourceFiles);
    Pixels viewSource(Source);

    Geometry Size = Geometry(twidth, theight);

    Size.aspect(true);

    unsigned long scol = Source.columns();
    unsigned long srow = Source.rows();

    if ( scol <= 0 || srow <= 0) return;

    unsigned int  ThumbnailModulusDepth;
    unsigned int  SourceModulusDepth =  pow(2,Source.modulusDepth());

    unsigned long srowOffset =  srow - theight;
    unsigned long scolOffset =  scol - twidth;

    unsigned long x, y;

    for (y = 0; y < srowOffset; y += theight) {
	for (x = 0; x < scolOffset ; x += twidth) {

	    SourcePixels = viewSource.get(x, y, twidth, theight);

	    //srand(unsigned(time(NULL)));
	    //random_shuffle(Thumbnails.begin(), Thumbnails.end());
	    
	    for(vector<long>::size_type iThumbnails = Thumbnails.size() - 1; iThumbnails != 0; iThumbnails--) {

		Thumbnail.read(Thumbnails.at(iThumbnails));
		//Thumbnail.sample(Size);

		ThumbnailModulusDepth  = pow(2,Thumbnail.modulusDepth());

		Pixels viewThumbnail(Thumbnail);
		ThumbnailPixels = viewThumbnail.get(0, 0, twidth, theight);

		if (ThumbnailPixels == 0 || SourcePixels == 0){
		  cout << "ThumbnailPixels + SourcePixels == 0";
		  exit(255);
		}

		double sred = 0, sgreen = 0, sblue = 0, tred = 0, tgreen = 0, tblue = 0;
		unsigned long i;
		unsigned long NumberOfPixels = twidth * theight;

		for (i = 0; i < NumberOfPixels; i++) {
		  tred   = (tred   + (ThumbnailPixels[i].red   / (double)ThumbnailModulusDepth)) / 2;
		  tgreen = (tgreen + (ThumbnailPixels[i].green / (double)ThumbnailModulusDepth)) / 2;
		  tblue  = (tblue  + (ThumbnailPixels[i].blue  / (double)ThumbnailModulusDepth)) / 2;
		  //if (i)  << " " << Thumbnails.at(iThumbnails) << " "  << tred << " " << tgreen << " " << tblue << endl; 
		    sred   = (sred   + (SourcePixels[i].red      / SourceModulusDepth))    / 2;
		    sgreen = (sgreen + (SourcePixels[i].green    / SourceModulusDepth))    / 2;
		    sblue  = (sblue  + (SourcePixels[i].blue     / SourceModulusDepth))    / 2;
		}
		cout << Thumbnails.at(iThumbnails) << " " << twidth << " " << theight << " "  << tred << " " << tgreen << " " << tblue << endl; 
		
/*
		if (match(sred, sgreen, sblue, tred, tgreen, tblue)) {
		    //if (true) Thumbnails.pop_back();
		    //*SourcePixels = *ThumbnailPixels;
		    //Source.composite(Thumbnail, x, y, OverCompositeOp);
		    //Source.syncPixels();
		    //Source.write("out.jpg");
		    break;
		}
*/
	    }
	    break;
	}
	break;
    }
    //Source.write("out.jpg");
}
