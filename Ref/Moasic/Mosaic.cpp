#include <GraphicsMagick/Magick++.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <algorithm>
#include <boost/config.hpp>
#include <boost/regex.hpp>
#include "./Mosaic.h"
#include "./SynchronisedQueue.h"


/*
 * Source:
 * 	Window / sample size
 *
 * Destination:
 * 	Thumbnail size   (set by Destination size)
 *      Destination size (set by Thumbnail size) (width = Thumbnail size * Thumbnail count)
 *
 */
using namespace std;
using namespace Magick;


const boost::regex validfiles(".*\\.(([Jj][Pp][Ee]?|[Pp][Nn])[Gg]|[Gg][Ii][Ff])");

Image Source, Dest;

int    MetricType = 0;
double minMetric  = 0;

unsigned int ActualTileWidth  = 0;
unsigned int ActualTileHeight = 0;

unsigned int SampleTileWidth  = 0;
unsigned int SampleTileHeight = 0;

unsigned long dwidth  = 0;
unsigned long dheight = 0;


SynchronisedQueue<SrcImage_t> WorkerQueue;
//boost::shared_mutex WorkerMutex;

vector<Tiles_t> TilesData;


void LoadThumbnails(string path)
{

        DIR *dir;
        struct dirent *entry;

        if ((dir = opendir(path.c_str())) == NULL) {
                perror("opendir");
        }

        Image Thumbnail;

        unsigned long j = 0;

        while ((entry = readdir(dir)) != NULL) {

                if (entry->d_type != DT_REG || !boost::regex_match(string(entry->d_name), validfiles))
                        continue;

                TilesData.push_back(Tiles_t());
                TilesData[j].Name =  path + entry->d_name;

                Thumbnail.read(TilesData[j].Name);

                TilesData[j].Width  = Thumbnail.columns();
                TilesData[j].Height = Thumbnail.rows();

                unsigned int ThumbnailModulusDepth  = pow(2,Thumbnail.modulusDepth());

                Pixels viewThumbnail(Thumbnail);

                PixelPacket *ThumbnailPixels = viewThumbnail.get(0, 0, TilesData[j].Width, TilesData[j].Height);

                if (ThumbnailPixels == 0) {
                        cout << "ThumbnailPixels == 0";
                        break;
                }

                unsigned long NumberOfPixels = TilesData[j].Width * TilesData[j].Height;

                for (unsigned long i = 0; i < NumberOfPixels; i++) {
                        TilesData[j].MeanRed   = (TilesData[j].MeanRed   + (ThumbnailPixels[i].red   / (double)ThumbnailModulusDepth)) / 2;
                        TilesData[j].MeanGreen = (TilesData[j].MeanGreen + (ThumbnailPixels[i].green / (double)ThumbnailModulusDepth)) / 2;
                        TilesData[j].MeanBlue  = (TilesData[j].MeanBlue  + (ThumbnailPixels[i].blue  / (double)ThumbnailModulusDepth)) / 2;
                }
                j++;
        }

        closedir(dir);
}

void WorkerThread(int tid)
{
        //boost::shared_lock<boost::shared_mutex> lock(WorkerMutex);
        SrcImage_t NextTile;

        Image Thumbnail;

        Geometry ThumbSize = Geometry(ActualTileWidth, ActualTileHeight);
        ThumbSize.aspect(true);

        while(WorkerQueue.Size() != 0) {
                WorkerQueue.TryDequeue(NextTile);

                string BestTile = "";

                double lowestMetric = minMetric;

                for (vector<long>::size_type i = TilesData.size() - 1; i != 0; i--) {

                        double Metric = 0;
                        switch (MetricType) {
                        case 0: // Euclidean
                                Metric = sqrt(
                                              pow(abs(NextTile.MeanRed   - TilesData[i].MeanRed),   2) +
                                              pow(abs(NextTile.MeanGreen - TilesData[i].MeanGreen), 2) +
                                              pow(abs(NextTile.MeanBlue  - TilesData[i].MeanBlue),  2)
                                             );
                                break;
                        case 1: // Manhattan
                                Metric = abs(NextTile.MeanRed   - TilesData[i].MeanRed)   +
                                         abs(NextTile.MeanGreen - TilesData[i].MeanGreen) +
                                         abs(NextTile.MeanBlue  - TilesData[i].MeanBlue);
                                break;
                        case 2: // Max
                                Metric = max({
                                             abs(NextTile.MeanRed   - TilesData[i].MeanRed),
                                             abs(NextTile.MeanGreen - TilesData[i].MeanGreen),
                                             abs(NextTile.MeanBlue  - TilesData[i].MeanBlue)
                                             });
                                break;
                        }

                        if (Metric < lowestMetric) {
                                BestTile = TilesData[i].Name;
                                lowestMetric = Metric;
                        }
                }
                if (BestTile != "") {
                        {
                                //boost::upgrade_lock<boost::shared_mutex> lock(WorkerMutex);
                                //boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

                                //if (self.UniqueTiles) TilesData[i].pop_back(Tiles_t());

                                Thumbnail.read(BestTile);
                                Thumbnail.sample(ThumbSize); //actual tile size

                                Source.composite(Thumbnail, NextTile.x, NextTile.y, OverCompositeOp);
                                //Source.display();
                                //srand(unsigned(time(NULL)));
                                //random_shuffle(TilesData.begin(),TilesData.end());
                        }
                }
        }
        //WorkerQueue.StopQueue();
}


int main(int argc, char **argv)
{
        InitializeMagick(*argv);

        LoadThumbnails(argv[1]);

        MetricType = atoi(argv[2]);
        minMetric  = atof(argv[3]);

        ActualTileWidth  = atol(argv[4]);
        ActualTileHeight = atol(argv[5]);
	
	
	unsigned long ActualTileNumberOfPixels = ActualTileWidth * ActualTileHeight;

        SrcImage_t SrcImageData;

        Source.read("/home/mitch/Pictures/my photos/OCMS 0809 006.jpg");
        //Source.quantizeColorSpace(RGBColorspace);
        //Source.quantizeColors(256);
        //Source.quantize();

        SrcImageData.Width  = Source.columns();
        SrcImageData.Height = Source.rows();

        //unsigned long scolOffset = SrcImageData.Width;
        //unsigned long srowOffset = SrcImageData.Height;

        Geometry SourceSize = Geometry(SrcImageData.Width,SrcImageData.Height);
	
        SourceSize.aspect(true);

        Source.sample(SourceSize);

        unsigned long SourceModulusDepth =  pow(2,Source.modulusDepth());

        Pixels viewSource(Source);

        for (SrcImageData.x = 0; SrcImageData.x < SrcImageData.Width - ActualTileWidth; SrcImageData.x += ActualTileWidth) {
                for (SrcImageData.y = 0; SrcImageData.y < SrcImageData.Height - ActualTileHeight; SrcImageData.y += ActualTileHeight) {

                        PixelPacket *SourcePixels = viewSource.get(SrcImageData.x, SrcImageData.y, ActualTileWidth, ActualTileHeight);

                        if (SourcePixels == 0) {
                                cout << "SourcePixels == 0";
                                continue;
                        }

                        for (unsigned long i = 0; i < ActualTileNumberOfPixels; i++) {
                                SrcImageData.MeanRed   = (SrcImageData.MeanRed   + (SourcePixels[i].red   / (double)SourceModulusDepth)) / 2;
                                SrcImageData.MeanGreen = (SrcImageData.MeanGreen + (SourcePixels[i].green / (double)SourceModulusDepth)) / 2;
                                SrcImageData.MeanBlue  = (SrcImageData.MeanBlue  + (SourcePixels[i].blue  / (double)SourceModulusDepth)) / 2;
                        }

                        WorkerQueue.Enqueue(SrcImageData);
                }
        }

        boost::thread_group ThreadGroup;
        for (unsigned int thread = 0; thread < 400; thread++) {
                boost::thread *th = new boost::thread(WorkerThread, thread);
                ThreadGroup.add_thread(th);
        }
        ThreadGroup.join_all();

        WorkerQueue.StopQueue();
        Source.write("outfff.png");
        return 0;
}
//void GeometryManager();
/*
double* mean(void){

  return RGB;
}
*/