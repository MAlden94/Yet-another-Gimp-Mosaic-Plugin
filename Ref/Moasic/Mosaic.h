
struct Tiles_t {
  std::string Name = "";
  unsigned long   Width     = 0;
  unsigned long   Height    = 0;
  double MeanRed   = 0;
  double MeanGreen = 0;
  double MeanBlue  = 0;
};

struct SrcImage_t {
  unsigned long Width  = 0;
  unsigned long Height = 0;
  unsigned long x      = 0;
  unsigned long y      = 0;
  double MeanRed       = 0;
  double MeanGreen     = 0;
  double MeanBlue      = 0;
};

extern std::vector<Tiles_t> TilesData;
extern SrcImage_t SrcImageData;