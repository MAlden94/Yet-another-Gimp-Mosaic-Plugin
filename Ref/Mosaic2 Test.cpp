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


#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

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

int main(int argc, char **argv)
{
  InitializeMagick(*argv);
  return 0;
}

class Mosaic {
  
  private:
    SynchronisedQueue<SrcImage_t> WorkerQueue;
    vector<Tiles_t> TilesData;

    Image Source, Destination;

    string SourceFile      = "";
    string DestinationFile = "";
    string ThumbnailsDir   = "";

    long   WorkerThreads  = 400;
    int    MetricType     = 0;
    double minMetric      = 0;
    long SampleTileWidth  = 0, SampleTileHeight  = 0;
    long ActualTileWidth  = 0, ActualTileHeight  = 0;
    long DestinationWidth = 0, DestinationHeight = 0;
    void WorkerThread(void);
    void CreateMoasic(void);
  public:
     Mosaic() {};
    ~Mosaic() {};
    void SetSampleTileSize(long width, long height);
    void SetActualTileSize(long width, long height);
    void SetDestinationSize(long width,long height);
    
};


/*
 * Source:
 * 	Window / sample size
 * 	
 * Destination:
 * 	Thumbnail size   (set by Destination size)
 *      Destination size (set by Thumbnail size) (width = Thumbnail size * Thumbnail count)
 * 	
 */
/*
 * Src:         1024x768
 * Sample Tile: 20x20
 * Actual Tile: 40x40
 * Output: (2x) 2048x1536
*/

void Mosaic::SetSampleTileSize(const QString & Size){
  SampleTileWidth  = Size.section('x', 0, 0);
  SampleTileHeight = Size.section('x', 1, 1);
  
  //DestinationWidth  = (ActualTileWidth  / SampleTileWidth)  * SrcImageData.Width;
  //DestinationHeight = (ActualTileHeight / SampleTileHeight) * SrcImageData.Height;
}
void Mosaic::SetActualTileSize(const QString & Size){ //destination Tile size (raw, not pre-resized by SampleTileSize (Window) )

  ActualTileWidth  = Size.section('x', 0, 0);
  ActualTileHeight = Size.section('x', 1, 1);
  
  return;
  DestinationWidth  = (ActualTileWidth  / SampleTileWidth)  * SrcImageData.Width;
  DestinationHeight = (ActualTileHeight / SampleTileHeight) * SrcImageData.Height;

}
void Mosaic::SetDestinationSize(const QString & Size){
  DestinationWidth  = Size.section('x', 0, 0);
  DestinationHeight = Size.section('x', 1, 1);

  ActualTileWidth   = (DestinationWidth  / SrcImageData.Width)  * SampleTileWidth;
  ActualTileHeight  = (DestinationHeight / SrcImageData.Height) * SampleTileHeight;
}

void Mosaic::SetNumberOfThreads(const QString & Number){
  DestinationWidth  = Size.section('x', 0, 0);
  DestinationHeight = Size.section('x', 1, 1);

  ActualTileWidth   = (DestinationWidth  / SrcImageData.Width)  * SampleTileWidth;
  ActualTileHeight  = (DestinationHeight / SrcImageData.Height) * SampleTileHeight;
}

void Mosaic::LoadThumbnails(const QString & Path){

  DIR *dir;
  struct dirent *entry;
  
  if ((dir = opendir(Path.c_str())) == NULL) {
    perror("opendir");
  }
  
  Image Thumbnail;
  
  unsigned long j = 0;
  
  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type != DT_REG || !boost::regex_match(string(entry->d_name), validfiles))
      continue;

    TilesData.push_back(Tiles_t());

    TilesData[j].Name =  Path + entry->d_name;

    Thumbnail.read(TilesData[j].Name);
    
    TilesData[j].Width  = Thumbnail.columns();
    TilesData[j].Height = Thumbnail.rows();
    
    unsigned int ThumbnailModulusDepth  = pow(2,Thumbnail.modulusDepth());
    
    Pixels viewThumbnail(Thumbnail);
    
    PixelPacket *ThumbnailPixels = viewThumbnail.get(0, 0, TilesData[j].Width, TilesData[j].Height);
    
    if (ThumbnailPixels == 0){
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

void Mosaic::WorkerThread(void){
  SrcImage_t NextTile;

  Image Thumbnail;

  Geometry ThumbSize = Geometry(ActualTileWidth, ActualTileHeight);
  ThumbSize.aspect(true);

  while(WorkerQueue.Size() != 0)
  {
    WorkerQueue.TryDequeue(NextTile);

    string BestTile = "";

    double lowestMetric = minMetric;
    
    for (vector<long>::size_type i = TilesData.size() - 1; i != 0; i--) {
      double Metric = 0;
      switch (MetricType) {
	case 0: // Euclidean
	  Metric = sqrt(
	    pow(abs(NextTile.MeanRed   - TilesData[i].MeanRed),     2) +
	    pow(abs(NextTile.MeanGreen - TilesData[i].MeanGreen),   2) +
	    pow(abs(NextTile.MeanBlue  - TilesData[i].MeanBlue),    2)
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
    
    if (BestTile != ""){
      {
        Thumbnail.read(BestTile);
        Thumbnail.sample(ThumbSize);
        Source.composite(Thumbnail, NextTile.x, NextTile.y, OverCompositeOp);
      }
    }
  }
}
void CreateMoasic(void){
  
  LoadThumbnails(ThumbnailsDir);

  SrcImage_t SrcImageData;

  Source.read(SourceFile);

  SrcImageData.Width  = Source.columns();
  SrcImageData.Height = Source.rows();

  unsigned long SourceModulusDepth =  pow(2,Source.modulusDepth());

  Pixels viewSource(Source);
  
  for (SrcImageData.x = 0; SrcImageData.x < SrcImageData.Width    - SampleTileWidth;  SrcImageData.x += SampleTileWidth ) {
    for (SrcImageData.y = 0; SrcImageData.y < SrcImageData.Height - SampleTileHeight; SrcImageData.y += SampleTileHeight) {

      PixelPacket *SourcePixels = viewSource.get(SrcImageData.x, SrcImageData.y, SampleTileWidth, SampleTileHeight);
      
      cout << "(" << SrcImageData.y << ", " << SrcImageData.x << ") == (" << SrcImageData.Height << ", " << SrcImageData.Width << ")" << endl;
      if (SourcePixels == 0){
	cout << "(" << SrcImageData.y << ", " << SrcImageData.x << ") == (" << SrcImageData.Height << ", " << SrcImageData.Width << ")  SourcePixels == 0" << endl;
	continue;
      }
 
      unsigned long NumberOfPixels = SampleTileWidth * SampleTileHeight;
      for (unsigned long i = 0; i < NumberOfPixels; i++) {
	SrcImageData.MeanRed   = (SrcImageData.MeanRed   + (SourcePixels[i].red   / (double)SourceModulusDepth)) / 2;
	SrcImageData.MeanGreen = (SrcImageData.MeanGreen + (SourcePixels[i].green / (double)SourceModulusDepth)) / 2;
	SrcImageData.MeanBlue  = (SrcImageData.MeanBlue  + (SourcePixels[i].blue  / (double)SourceModulusDepth)) / 2;
      }

      WorkerQueue.Enqueue(SrcImageData);
    } 
  }

  boost::thread_group ThreadGroup;
  for (unsigned int thread = 0; thread < WorkerThreads; thread++) {
    boost::thread *th = new boost::thread(WorkerThread, thread);
    ThreadGroup.add_thread(th);
  }
  ThreadGroup.join_all();

  WorkerQueue.StopQueue();

  Source.write(DestinationFile);
}