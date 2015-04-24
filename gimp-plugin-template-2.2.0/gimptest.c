#include <gimp-2.0/libgimp/gimp.h>


/* Declare local functions.
 */
static void      query  (void);
static void      run    (gchar      *name,
                         gint        nparams,
                         GimpParam  *param,
                         gint       *nreturn_vals,
                         GimpParam **return_vals);

static void      stripes_demo         (GimpDrawable *drawable);

GimpPlugInInfo PLUG_IN_INFO =
{
  NULL,  /* init_proc  */
  NULL,  /* quit_proc  */
  query, /* query_proc */
  run,   /* run_proc   */
};


MAIN ()

static void
query (void)
{
  static GimpParamDef args[] =
  {
    { GIMP_PDB_INT32, "run_mode", "Interactive, non-interactive" },
    { GIMP_PDB_IMAGE, "image", "Input image" },
    { GIMP_PDB_DRAWABLE, "drawable", "Input drawable" }
  };
  static gint nargs = sizeof (args) / sizeof (args[0]);

  gimp_install_procedure ("plug_in_stripes_demo",
                          "Demonstration plug-in - creates stripes",
                          "This simple plug-in creates diagonal stripes.",
                          "Simon Budig  <simon@gimp.org>",
                          "Simon Budig",
                          "2001",
                          "<Image>/Filters/Colors/Stripes Demo",
                          "RGB*",
                          GIMP_PLUGIN,
                          nargs, 0,
                          args, NULL);
}

static void
run (gchar      *name,
     gint        nparams,
     GimpParam  *param,
     gint       *nreturn_vals,
     GimpParam **return_vals)
{
  static GimpParam values[1];
  GimpDrawable *drawable;
  GimpRunModeType run_mode;
  GimpPDBStatusType status = GIMP_PDB_SUCCESS;

  gint32 image_ID;

  run_mode = param[0].data.d_int32;

  /*  Get the specified drawable  */
  drawable = gimp_drawable_get (param[2].data.d_drawable);
  image_ID = param[1].data.d_image;

  /*  Make sure that the drawable is RGB color  */
  if (gimp_drawable_is_rgb (drawable->id))
    {
      gimp_progress_init ("Creating Stripes...");
      gimp_tile_cache_ntiles (2 * (drawable->width / gimp_tile_width () + 1));
      stripes_demo (drawable);

      if (run_mode != GIMP_RUN_NONINTERACTIVE)
        gimp_displays_flush ();
    }
  else
    {
      status = GIMP_PDB_EXECUTION_ERROR;
    }

  *nreturn_vals = 1;
  *return_vals = values;

  values[0].type = GIMP_PDB_STATUS;
  values[0].data.d_status = status;

  gimp_drawable_detach (drawable);
}


static void
stripes_demo (GimpDrawable *drawable)
{
  GimpPixelRgn src_rgn, dest_rgn;
  guchar *src, *s;
  guchar *dest, *d;
  gint    progress, max_progress;
  gint    has_alpha, red, green, blue, alpha;
  gint    x1, y1, x2, y2;
  gint    x, y;
  gpointer pr;

  /* Get selection area */
  gimp_drawable_mask_bounds (drawable->id, &x1, &y1, &x2, &y2);
  has_alpha = gimp_drawable_has_alpha (drawable->id);

  red = 0; green = 1; blue = 2;

  alpha = (has_alpha) ? drawable->bpp - 1 : drawable->bpp;

  /* Initialize progress */
  progress = 0;
  max_progress = (x2 - x1) * (y2 - y1);

  /* substitute pixel vales */
  gimp_pixel_rgn_init (&src_rgn, drawable,
                       x1, y1, (x2 - x1), (y2 - y1), FALSE, FALSE);
  gimp_pixel_rgn_init (&dest_rgn, drawable,
                       x1, y1, (x2 - x1), (y2 - y1), TRUE, TRUE);

  for (pr = gimp_pixel_rgns_register (2, &src_rgn, &dest_rgn);
       pr != NULL;
       pr = gimp_pixel_rgns_process (pr))
    {
      src = src_rgn.data;
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

  /*  update the region  */
  gimp_drawable_flush (drawable);
  gimp_drawable_merge_shadow (drawable->id, TRUE);
  gimp_drawable_update (drawable->id, x1, y1, (x2 - x1), (y2 - y1));
}