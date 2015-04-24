/* GIMP Plug-in Template
 * Copyright (C) 2000  Michael Natterer <mitch@gimp.org> (the "Author").
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the Author of the
 * Software shall not be used in advertising or otherwise to promote the
 * sale, use or other dealings in this Software without prior written
 * authorization from the Author.
 */

#include "config.h"

#include <gtk-2.0/gtk/gtk.h>

#include <gimp-2.0/libgimp/gimp.h>

#include "main.h"
#include "render.h"

#include "plugin-intl.h"


/*  Public functions  */

void
render (gint32              image_ID,
	GimpDrawable       *drawable,
	PlugInVals         *vals,
	PlugInImageVals    *image_vals,
	PlugInDrawableVals *drawable_vals)
{
  
  /* substitute pixel vales */
  gimp_pixel_rgn_init (
    &image_ID, drawable,
    0, 0,
    vals->SourceWidth,
    vals->SourceHeight,
    FALSE,
    FALSE
  );
  gimp_pixel_rgn_init (
    &dest_rgn, drawable,
    0, 0,
    vals->DestinationWidth,
    vals->DestinationHeight,
    TRUE,
    TRUE
  );
  
  for (pr = gimp_pixel_rgns_register(2, &src_rgn, &dest_rgn);
       pr != NULL;
       pr = gimp_pixel_rgns_process(pr))
       {
	 src  = src_rgn.data;
	 dest = dest_rgn.data;
	 
	 for (y = 0; y < src_rgn.h; y++)
	 {
	   s = src;
	   d = dest;
	   
	   for (x = 0; x < src_rgn.w; x++)
	   {
	     d[0] = (src_rgn.x + x + src_rgn.y + y) % 256;
	     d[1] = s[1];
	     d[2] = (- src_rgn.x - x + src_rgn.y + y) % 256;
	     if (has_alpha)
	       d[alpha] = s[alpha];
	     
	     s += src_rgn.bpp;
	     d += dest_rgn.bpp;
	   }
	   
	   src += src_rgn.rowstride;
	   dest += dest_rgn.rowstride;
	 }
	 
	 /* Update progress */
	 progress += src_rgn.w * src_rgn.h;
	 
	 gimp_progress_update ((double) progress / (double) max_progress);
       }
       

  g_message (_("This plug-in is just a dummy. "
               "It has now finished doing nothing."));
}
