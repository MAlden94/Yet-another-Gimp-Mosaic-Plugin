#!/usr/bin/perl

use strict;
use warnings;

use Image::Magick;
use XML::Simple;
use Data::Dumper;
$| = 1;
my $iX     = 0;
my $X      = 0;
my $Y      = 0;
my $resize = 'scale';
my $formula     = 'Euclidean';
#geometry	=> $geometry
my $uLimit              =    0.3;
my $lLimit               =    0x00_00_40;
my $TileWidth            =  8;
my $TileHeight           =  8;
my $SourceFile           = '/home/mitch/elliott-pano-small.jpg';
my $MosaicBackgroundFile = 'xc:none';
my $MosaicFile           = '/home/mitch/new.png';
my $TileFiles            = '/home/mitch/Pictures/DCIM/103SSCAM/*.JPG';
my $ShuffleTiles         = 1;
my $db                   = {};

$MosaicBackgroundFile = $SourceFile unless ( $MosaicBackgroundFile );
my $Mosaic = new Image::Magick( magick => 'png' );
my $Source = new Image::Magick();
my $Tiles  = new Image::Magick();
$Mosaic->Read($MosaicBackgroundFile);
$Source->Read($SourceFile);

$Mosaic->Quantize( colorspace => 'RGB' );

my ( $SourceWidth, $SourceHeight ) = ( $Source->Ping($SourceFile) )[ 0, 1 ];
#( $SourceWidth, $SourceHeight ) = (500,200);
$Mosaic->Scale( width => $SourceWidth, height =>$SourceHeight );
#$Source->Scale( height =>200, width =>500 );
#$Mosaic->Scale( height =>200 + $TileHeight, width =>500 + $TileWidth );
#$Source->Scale( height =>200 + $TileHeight, width =>500 + $TileWidth );

my @files = glob $TileFiles;
@files = shuffle(@files) if ($ShuffleTiles);
@files = splice(@files,0,300);
foreach (@files) {
     print "$_\n";

    $Tiles->Read($_);
    my @RealTileSize = ( $Tiles->Ping($_) )[ 0, 1 ];
    if ( $resize ne '*' or $resize ne '' ) {
        if ( $RealTileSize[0] != $TileWidth or $RealTileSize[1] != $TileHeight )
        {

            if ( $resize eq 'crop' ) {
                $Tiles->Crop( height => $TileHeight, width => $TileWidth );
            }
            elsif ( $resize eq 'scale' ) {
                $Tiles->Scale( height => $TileHeight, width => $TileWidth );
            }
            elsif ( $resize eq 'resize' ) {
                $Tiles->AdaptiveResize(
                    height => $TileHeight,
                    width  => $TileWidth
                );
            }
        }
    }
    else {
        if ( $resize ne '' ) {
            ( $TileWidth, $TileHeight ) = @RealTileSize;
        }
    }
    my @TilePixels = (
       meanColor($Tiles->GetPixels(
            'map'       => 'R',
            'normalize' => 'true',
            height      => $TileHeight,
            width       => $TileWidth
        )),
        meanColor($Tiles->GetPixels(
            'map'       => 'G',
            'normalize' => 'true',
            height      => $TileHeight,
            width       => $TileWidth
        )),
        meanColor($Tiles->GetPixels(
            'map'       => 'B',
            'normalize' => 'true',
            height      => $TileHeight,
            width       => $TileWidth
        ))
    );

    $db->{$_ }= {
            'pixels' => \@TilePixels,
            'width'  => $TileWidth,
            'height' => $TileHeight
        };

    @$Tiles = ();
}
my $XMLobj =
  new XML::Simple( RootName => 'config', AttrIndent => 1, NoAttr => 1 );

#print $XMLobj->XMLout( \%db );
DRAWLOOP: while (1) {

    #print "$iX] ($Y += $TileHeight) <= $SourceHeight | ($X += $TileWidth) <= $SourceWidth\n";

  PICKLOOP: for my $keys ( each %$db ) {#keys 

        $TileHeight            = $db->{$keys}->{'height'} // warn "SKIP\n",  next PICKLOOP;
        $TileWidth             = $db->{$keys}->{'width'}   // warn "SKIP\n",  next PICKLOOP;

	print <<DAT
        ($Y += $TileHeight) <= $SourceHeight | ($X += $TileWidth) <= $SourceWidth
	-->@{[shorten($keys)]}
DAT
;

        my @H_W_X_Y = (
            x      => $X,
            y      => $Y,
            height => $TileHeight,
            width  => $TileWidth
        );
        my @SourcePixels = (
            meanColor(
                $Source->GetPixels(
                    'map'       => 'R',
                    'normalize' => 'true',
                    @H_W_X_Y
                )
            ),
            meanColor(
                $Source->GetPixels(
                    'map'       => 'G',
                    'normalize' => 'true',
                    @H_W_X_Y
                )
            ),
            meanColor(
                $Source->GetPixels(
                    'map'       => 'B',
                    'normalize' => 'true',
                    @H_W_X_Y
                )
            )
        );

        if (match($db->{$keys}->{'pixels'},\@SourcePixels)){
	    $Tiles->Read($keys);
            $Mosaic->Composite(
                image   => $Tiles,
                compose => 'Over',
                @H_W_X_Y
            );
            @$Tiles = ();
	    print "last PICKLOOP\n";
            last PICKLOOP;
        }
        #@$Tiles = ();
    }

    #unless ( $X = ( $iX += $TileWidth ) % $SourceWidth ) {
    #    $Y += $TileHeight;
    #}
    if (($X += $TileWidth) >= $SourceWidth){
     $X = 0;
     $Y += $TileHeight;
     }
    last DRAWLOOP if ( $Y >= $SourceHeight );

}
$Mosaic->Write( filename => $MosaicFile );
undef $Mosaic;

#-------------------------------------------------------------------------------------------------------------------------------
#     Usage : &meanColor( @COLORS );
#   Purpose : Computes the mean 8-bit channel color.
# Arguments : @COLORS = list of normalized channel intensities to be averaged.
# Externals : $Verbose
#      Subs : None.
#   Remarks : None.
#   History : v1.0.0 - January 23, 2008 - Original release.
#   Website: http://www.webpraxis.ab.ca/photo_mosaic/img2photomosaic.shtml
sub meanColor {
    #eval {
    my $mean;    # mean 8-bit color value
    $mean += $_ for @_;    # sum all the normalized color values
    $mean = 256 * $mean / scalar @_;    # compute the mean 8-bit value
    #printf "%5.1f ", $mean; #if $Verbose;                                             # report if requested
    return $mean;                       # return the mean
    #};
}

sub match {
    my ( $obj1, $obj2 ) = @_;
    my $TotalDelta;
    #print Dumper( $obj1, $obj2 ),"\n";
    #print "$obj1->[0] * $obj1->[1] * $obj1->[2]\n";
    my @Deltas = (
    $obj1->[0] - $obj2->[0],
    $obj1->[1] - $obj2->[1],
    $obj1->[2] - $obj2->[2]
    );
if ($formula eq 'Euclidean'){
    $TotalDelta  = sqrt(
      $Deltas[0] ** 2 
    + $Deltas[1] ** 2 
    + $Deltas[2] ** 2
    );
    } else {
    $TotalDelta = $Deltas[0]+ $Deltas[1] + $Deltas[2];                         #     Manhattan
    }
    
   # my $Delta2     = $obj2->[0] ** 2 $obj2->[1] ** 2 $obj2->[2];
   #my $TotalDelta = $Delta1 - $Delta2;
    #printf "\%06X - \%06X = \%06X\n", $Delta1, $Delta2, $TotalDelta;
    printf "\%f < \%f\n",$TotalDelta,$uLimit;
    
    if ($TotalDelta < $uLimit ){
	    $uLimit = $TotalDelta;
	    return 1;
    }
    return 0;
}
sub shorten {
	(my $s = shift) =~ s#(.*?)([a-zA-Z0-9]{6,})(\1)#$1...$3#o;
	 return $s;
}
sub shuffle {
my (@array) = @_;
my @shuff;
push( @shuff, splice( @array,  int rand( $#array + 1 ), 1 ) )  foreach ( 0 .. $#array );
return @shuff;
}
