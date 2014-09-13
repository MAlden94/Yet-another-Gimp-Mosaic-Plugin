/* GIMP Plug-in Template
 * Copyright (C) 2000-2004  Michael Natterer <mitch@gimp.org> (the "Author").
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

#include <gimp-2.0/libgimp/gimp.h>
#include <gimp-2.0/libgimp/gimpui.h>

#include "main.h"
#include "interface.h"

#include "plugin-intl.h"


/*  Constants  */

#define SCALE_WIDTH        180
#define SPIN_BUTTON_WIDTH   75
#define RANDOM_SEED_WIDTH  100


  /*
  // Sample Tile size being set
  DestinationWidth  = (ActualTileWidth  / SampleTileWidth)  * SrcImageData.Width;
  DestinationHeight = (ActualTileHeight / SampleTileHeight) * SrcImageData.Height;
  // Actual Tile size being set
  DestinationWidth  = (ActualTileWidth  / SampleTileWidth)  * SrcImageData.Width;
  DestinationHeight = (ActualTileHeight / SampleTileHeight) * SrcImageData.Height;

 // Dest size being set
  ActualTileWidth   = (DestinationWidth  / SrcImageData.Width)  * SampleTileWidth;
  ActualTileHeight  = (DestinationHeight / SrcImageData.Height) * SampleTileHeight;
*/


/*  Local function prototypes  */

static gboolean   dialog_image_constraint_func (gint32    image_id,
                                                gpointer  data);


/*  Local variables  */

static PlugInUIVals *ui_state = NULL;


/*  Public functions  */

gboolean
dialog (gint32              image_ID,
	GimpDrawable       *drawable,
	PlugInVals         *vals,
	PlugInImageVals    *image_vals,
	PlugInDrawableVals *drawable_vals,
	PlugInUIVals       *ui_vals)
{
  GtkWidget *dlg;
  GtkWidget *main_vbox;
  GtkWidget *frame;
  GtkWidget *table;
  GtkWidget *hbox;
  GtkWidget *hbox2;
  GtkWidget *coordinates;
  GtkWidget *combo;
  GtkObject *adj;
  gint       row;
  gboolean   run = FALSE;
  GimpUnit   unit;
  gdouble    xres, yres;
  
  if (vals->DestinationWidth  == 0)
      vals->DestinationWidth = drawable->width;
  if (vals->DestinationHeight == 0)
      vals->DestinationHeight = drawable->height;
  
  if (vals->SourceWidth  == 0)
      vals->SourceWidth = drawable->width;
  if (vals->SourceHeight == 0)
      vals->SourceHeight= drawable->height;
  

  ui_state = ui_vals;

  gimp_ui_init (PLUGIN_NAME, TRUE);

  dlg = gimp_dialog_new (_("Mosaic Maker"), PLUGIN_NAME,
                         NULL, 0,
			 gimp_standard_help_func, "plug-in-template",

			 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			 GTK_STOCK_OK,     GTK_RESPONSE_OK,

			 NULL);

  main_vbox = gtk_vbox_new (FALSE, 12);
  gtk_container_set_border_width (GTK_CONTAINER (main_vbox), 12);
  gtk_container_add (GTK_CONTAINER (GTK_DIALOG (dlg)->vbox), main_vbox);

  frame = gimp_frame_new (_("Mosaic Maker"));
  gtk_box_pack_start (GTK_BOX (main_vbox), frame, FALSE, FALSE, 0);
  gtk_widget_show (frame);

  table = gtk_table_new (3, 3, FALSE);
  gtk_table_set_col_spacings (GTK_TABLE (table), 6);
  gtk_table_set_row_spacings (GTK_TABLE (table), 2);
  gtk_container_add (GTK_CONTAINER (frame), table);
  gtk_widget_show (table);

  row = 0;

  unit = gimp_image_get_unit (image_ID);
  gimp_image_get_resolution (image_ID, &xres, &yres);

  frame = gimp_frame_new (_("Source Image"));
  gtk_box_pack_start (GTK_BOX (main_vbox), frame, FALSE, FALSE, 0);
  gtk_widget_show (frame);

  
  hbox = gtk_hbox_new (FALSE, 4);
  gtk_container_set_border_width (GTK_CONTAINER (hbox), 4);
  gtk_container_add (GTK_CONTAINER (frame), hbox);
  gtk_widget_show (hbox);

  table = gtk_table_new (3, 2, FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (table), 4);
  gtk_table_set_col_spacings (GTK_TABLE (table), 4);
  gtk_table_set_row_spacings (GTK_TABLE (table), 2);
  gtk_container_add (GTK_CONTAINER (hbox), table);
  gtk_widget_show (table);
  
  
  row = 0;
  
  combo = gimp_layer_combo_box_new (NULL, NULL);
  gimp_int_combo_box_connect (GIMP_INT_COMBO_BOX (combo), drawable->drawable_id,
			      G_CALLBACK (gimp_int_combo_box_get_active),
			      &drawable_vals->drawable_id);

  gimp_table_attach_aligned (GTK_TABLE (table), 0, row++,
			     _("Layer:"), 0.0, 0.5, combo, 1, FALSE);

  coordinates = gimp_coordinates_new (unit, "%p", TRUE, TRUE, SPIN_BUTTON_WIDTH,
				      GIMP_SIZE_ENTRY_UPDATE_SIZE,

				      ui_vals->chain_active, TRUE,

				      _("Width:"), vals->SourceWidth, xres,
				      1, GIMP_MAX_IMAGE_SIZE,
				      0, drawable->width,

				      _("Height:"), vals->SourceHeight, yres,
				      1, GIMP_MAX_IMAGE_SIZE,
				      0, drawable->height);
  gtk_box_pack_start (GTK_BOX (hbox), coordinates, FALSE, FALSE, 0);
  gtk_widget_show (coordinates);
  
  frame = gimp_frame_new (_("Destination Image"));
  gtk_box_pack_start (GTK_BOX (main_vbox), frame, FALSE, FALSE, 0);
  gtk_widget_show (frame);
  
  
  hbox = gtk_hbox_new (FALSE, 4);
  gtk_container_set_border_width (GTK_CONTAINER (hbox), 4);
  gtk_container_add (GTK_CONTAINER (frame), hbox);
  gtk_widget_show (hbox);
  
  table = gtk_table_new (3, 2, FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (table), 4);
  gtk_table_set_col_spacings (GTK_TABLE (table), 4);
  gtk_table_set_row_spacings (GTK_TABLE (table), 2);
  gtk_container_add (GTK_CONTAINER (hbox), table);
  gtk_widget_show (table);
  
  
  row = 0;
  
  combo = gimp_layer_combo_box_new (NULL, NULL);
  gimp_int_combo_box_connect (GIMP_INT_COMBO_BOX (combo), drawable->drawable_id,
			      G_CALLBACK (gimp_int_combo_box_get_active),
			      &drawable_vals->drawable_id);
  
  gimp_table_attach_aligned (GTK_TABLE (table), 0, row++,
			     _("Layer:"), 0.0, 0.5, combo, 1, FALSE);

  coordinates = gimp_coordinates_new (unit, "%p", TRUE, TRUE, SPIN_BUTTON_WIDTH,
				      GIMP_SIZE_ENTRY_UPDATE_SIZE,
				      
				      ui_vals->chain_active, TRUE,
				      
				      _("Width:"), vals->DestinationWidth, xres,
				      1, GIMP_MAX_IMAGE_SIZE,
				      0, drawable->width,
				      
				      _("Height:"), vals->DestinationHeight, yres,
				      1, GIMP_MAX_IMAGE_SIZE,
				      0, drawable->height);
  gtk_box_pack_start (GTK_BOX (hbox), coordinates, FALSE, FALSE, 0);
  gtk_widget_show (coordinates);

  
  frame = gimp_frame_new (_("Sampling Window Resolution"));
  gtk_box_pack_start (GTK_BOX (main_vbox), frame, FALSE, FALSE, 0);
  gtk_widget_show (frame);
  
  hbox = gtk_hbox_new (FALSE, 4);
  gtk_container_set_border_width (GTK_CONTAINER (hbox), 4);
  gtk_container_add (GTK_CONTAINER (frame), hbox);
  gtk_widget_show (hbox);
  
  coordinates = gimp_coordinates_new (unit, "%p", TRUE, TRUE, SPIN_BUTTON_WIDTH,
				      GIMP_SIZE_ENTRY_UPDATE_SIZE,
				      
				      ui_vals->chain_active, TRUE,
				      _("Width:"),
				      vals->SampleTileWidth, xres,
				      1, GIMP_MAX_IMAGE_SIZE,
				      0, drawable->width,
				      
				      _("Height:"), vals->SampleTileHeight, yres,
				      1, GIMP_MAX_IMAGE_SIZE,
				      0, drawable->height);
  gtk_box_pack_start (GTK_BOX (hbox), coordinates, FALSE, FALSE, 0);
  gtk_widget_show (coordinates);
  
  
  frame = gimp_frame_new (_("Actual Tile Resolution"));
  gtk_box_pack_start (GTK_BOX (main_vbox), frame, FALSE, FALSE, 0);
  gtk_widget_show (frame);

  hbox = gtk_hbox_new (FALSE, 4);
  gtk_container_set_border_width (GTK_CONTAINER (hbox), 4);
  gtk_container_add (GTK_CONTAINER (frame), hbox);
  gtk_widget_show (hbox);
  
  coordinates = gimp_coordinates_new (unit, "%p", TRUE, TRUE, SPIN_BUTTON_WIDTH,
				      GIMP_SIZE_ENTRY_UPDATE_SIZE,
				      
				      ui_vals->chain_active, TRUE,
				      
				      _("Width:"),
				      vals->ActualTileWidth, xres,
				      1, GIMP_MAX_IMAGE_SIZE,
				      0, drawable->width,
				      
				      _("Height:"),
				      vals->ActualTileHeight, yres,
				      1, GIMP_MAX_IMAGE_SIZE,
				      0, drawable->height);
  gtk_box_pack_start (GTK_BOX (hbox), coordinates, FALSE, FALSE, 0);
  gtk_widget_show (coordinates);

  /*  Image and drawable menus  */



  //combo = gimp_image_combo_box_new (dialog_image_constraint_func, NULL);
  //gimp_int_combo_box_connect (GIMP_INT_COMBO_BOX (combo), image_ID,
  //                            G_CALLBACK (gimp_int_combo_box_get_active),
  //                            &image_vals->image_id);

  //gimp_table_attach_aligned (GTK_TABLE (table), 0, row++,
//			     _(":"), 0.0, 0.5, combo, 1, FALSE);

  /*  Show the main containers  */

  gtk_widget_show (main_vbox);
  gtk_widget_show (dlg);

  run = (gimp_dialog_run (GIMP_DIALOG (dlg)) == GTK_RESPONSE_OK);

  if (run)
    {
      /*  Save ui values  */
      ui_state->chain_active =
        gimp_chain_button_get_active (GIMP_COORDINATES_CHAINBUTTON (coordinates));
    }

  gtk_widget_destroy (dlg);

  return run;
}


/*  Private functions  */

static gboolean
dialog_image_constraint_func (gint32    image_id,
                              gpointer  data)
{
  return (gimp_image_base_type (image_id) == GIMP_RGB);
}
