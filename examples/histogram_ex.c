/* $Id: histogram_ex.c,v 1.6 2003/11/30 22:10:18 tom Exp $ */

#include <cdk.h>

#ifdef HAVE_XCURSES
char *XCursesProgramName = "histogram_ex";
#endif

int main(int argc, char **argv)
{
   /* Declare vars. */
   CDKSCREEN *cdkscreen = 0;
   CDKHISTOGRAM *volume = 0;
   CDKHISTOGRAM *bass	= 0;
   CDKHISTOGRAM *treble = 0;
   WINDOW *cursesWin	= 0;
   char *volumeTitle	= "<C></5>Volume<!5>";
   char *bassTitle	= "<C></5>Bass  <!5>";
   char *trebleTitle	= "<C></5>Treble<!5>";

   CDK_PARAMS params;
   boolean Box;

   CDKparseParams(argc, argv, &params, CDK_CLI_PARAMS);
   Box = CDKparamValue(&params, 'N', TRUE);

   /* Set up CDK. */
   cursesWin = initscr();
   cdkscreen = initCDKScreen (cursesWin);

   /* Start CDK Color. */
   initCDKColor();

   /* Create the histogram objects. */
   volume = newCDKHistogram (cdkscreen,
			     CDKparamValue(&params, 'X', 10),
			     CDKparamValue(&params, 'Y', 10),
			     CDKparamValue(&params, 'H', 1),
			     CDKparamValue(&params, 'W', -2),
			     HORIZONTAL, volumeTitle,
			     Box,
			     CDKparamValue(&params, 'S', FALSE));
   if (volume == 0)
   {
      /* Exit CDK. */
      destroyCDKScreen (cdkscreen);
      endCDK();

      /* Print out a message and exit. */
      printf ("Oops. Can not make volume histogram. Is the window big enough??\n");
      exit (1);
   }

   bass = newCDKHistogram (cdkscreen,
			   CDKparamValue(&params, 'X', 10),
			   CDKparamValue(&params, 'Y', 14),
			   CDKparamValue(&params, 'H', 1),
			   CDKparamValue(&params, 'W', -2),
			   HORIZONTAL, bassTitle,
			   Box,
			   CDKparamValue(&params, 'S', FALSE));
   if (bass == 0)
   {
      /* Exit CDK. */
      destroyCDKHistogram (volume);
      destroyCDKScreen (cdkscreen);
      endCDK();

      /* Print out a message and exit. */
      printf ("Oops. Can not make bass histogram. Is the window big enough??\n");
      exit (1);
   }

   treble = newCDKHistogram (cdkscreen,
			     CDKparamValue(&params, 'X', 10),
			     CDKparamValue(&params, 'Y', 18),
			     CDKparamValue(&params, 'H', 1),
			     CDKparamValue(&params, 'W', -2),
			     HORIZONTAL, trebleTitle,
			     Box,
			     CDKparamValue(&params, 'S', FALSE));
   if (treble == 0)
   {
      /* Exit CDK. */
      destroyCDKHistogram (volume);
      destroyCDKHistogram (bass);
      destroyCDKScreen (cdkscreen);
      endCDK();

      /* Print out a message and exit. */
      printf ("Oops. Can not make treble histogram. Is the window big enough??\n");
      exit (1);
   }

#define BAR(a,b,c) A_BOLD, a, b, c, ' '|A_REVERSE|COLOR_PAIR(3), Box

   /* Set the histogram values. */
   setCDKHistogram (volume, vPERCENT, CENTER, BAR(0, 10, 6));
   setCDKHistogram (bass  , vPERCENT, CENTER, BAR(0, 10, 3));
   setCDKHistogram (treble, vPERCENT, CENTER, BAR(0, 10, 7));
   refreshCDKScreen (cdkscreen);
   sleep (4);

   /* Set the histogram values. */
   setCDKHistogram (volume, vPERCENT, CENTER, BAR(0, 10, 8));
   setCDKHistogram (bass  , vPERCENT, CENTER, BAR(0, 10, 1));
   setCDKHistogram (treble, vPERCENT, CENTER, BAR(0, 10, 9));
   refreshCDKScreen (cdkscreen);
   sleep (4);

   /* Set the histogram values. */
   setCDKHistogram (volume, vPERCENT, CENTER, BAR(0, 10, 10));
   setCDKHistogram (bass  , vPERCENT, CENTER, BAR(0, 10, 7));
   setCDKHistogram (treble, vPERCENT, CENTER, BAR(0, 10, 10));
   refreshCDKScreen (cdkscreen);
   sleep (4);

   /* Set the histogram values. */
   setCDKHistogram (volume, vPERCENT, CENTER, BAR(0, 10, 1));
   setCDKHistogram (bass  , vPERCENT, CENTER, BAR(0, 10, 8));
   setCDKHistogram (treble, vPERCENT, CENTER, BAR(0, 10, 3));
   refreshCDKScreen (cdkscreen);
   sleep (4);

   /* Set the histogram values. */
   setCDKHistogram (volume, vPERCENT, CENTER, BAR(0, 10, 3));
   setCDKHistogram (bass  , vPERCENT, CENTER, BAR(0, 10, 3));
   setCDKHistogram (treble, vPERCENT, CENTER, BAR(0, 10, 3));
   refreshCDKScreen (cdkscreen);
   sleep (4);

   /* Set the histogram values. */
   setCDKHistogram (volume, vPERCENT, CENTER, BAR(0, 10, 10));
   setCDKHistogram (bass  , vPERCENT, CENTER, BAR(0, 10, 10));
   setCDKHistogram (treble, vPERCENT, CENTER, BAR(0, 10, 10));
   refreshCDKScreen (cdkscreen);
   sleep (4);

   /* Clean up. */
   destroyCDKHistogram (volume);
   destroyCDKHistogram (bass);
   destroyCDKHistogram (treble);
   destroyCDKScreen (cdkscreen);
   delwin (cursesWin);
   endCDK();
   exit (0);
}
