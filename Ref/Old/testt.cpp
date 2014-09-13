class Mosaic {
  private:
    long SampleTileWidth  = 0, SampleTileHeight  = 0;
    long ActualTileWidth  = 0, ActualTileHeight  = 0;
    long DestinationWidth = 0, DestinationHeight = 0;
    void WorkerThread(void);
  public:
     Mosaic() {};
    ~Mosaic() {};
    void SetSampleTileSize(long width, long height);
    void SetActualTileSize(long width, long height);
    void SetDestinationSize(long width, long height);
    
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
  SampleWidth  = Size.section('x', 0, 0);
  SampleHeight = Size.section('x', 1, 1);
  
  //DestinationWidth  = (ActualTileWidth  / SampleWidth)  * SrcImageData.Width;
  //DestinationHeight = (ActualTileHeight / SampleHeight) * SrcImageData.Height;
}
void Mosaic::SetActualTileSize(const QString & Size){ //destination Tile size (raw, not pre-resized by SampleTileSize (Window) )

  ActualTileWidth  = Size.section('x', 0, 0);
  ActualTileHeight = Size.section('x', 1, 1);
  
  return;
  DestinationWidth  = (ActualTileWidth  / SampleWidth)  * SrcImageData.Width;
  DestinationHeight = (ActualTileHeight / SampleHeight) * SrcImageData.Height;

}
void Mosaic::SetDestinationSize(const QString & Size){
  DestinationWidth  = Size.section('x', 0, 0);
  DestinationHeight = Size.section('x', 1, 1);

  ActualTileWidth   = (DestinationWidth  / SrcImageData.Width)  * SampleTileWidth;
  ActualTileHeight  = (DestinationHeight / SrcImageData.Height) * SampleTileHeight;
}
void Mosaic::WorkerThread(void){
}