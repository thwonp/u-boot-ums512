/*
 * plorpOS boot logo (plorpos-3yv.49.1): the wordmark on the launcher's
 * background, "plorp" in the plorpOS purple and "OS" in the launcher's text
 * color, centered. Drawn upright for the way the device is held: open as the
 * panel's own orientation, closed turned the way the launcher turns (sway's
 * transform 90 - the panel's right edge becomes the top).
 *
 * Self-contained so it can be compiled on a host and checked against the
 * rendered artwork.
 */
#include "plorpos_logo_draw.h"
#include "plorpos_logo.h"

#define BG	0x07080cu	/* launcher background (UI_BG_*) */
#define FG_L	0x8a5cd6u	/* plorpOS purple */
#define FG_R	0xededf2u	/* launcher text (UI_TEXT) */

static unsigned int mix(unsigned int fg, unsigned int a)
{
	unsigned int r = ((fg >> 16 & 0xff) * a + (BG >> 16 & 0xff) * (255 - a)) / 255;
	unsigned int g = ((fg >> 8 & 0xff) * a + (BG >> 8 & 0xff) * (255 - a)) / 255;
	unsigned int b = ((fg & 0xff) * a + (BG & 0xff) * (255 - a)) / 255;

	return 0xff000000u | r << 16 | g << 8 | b;
}

void plorpos_logo_draw(unsigned int *fb, int w, int h, int closed)
{
	const unsigned char *p = plorpos_logo_rle;
	const unsigned char *end = p + sizeof(plorpos_logo_rle);
	int x0 = (w - PLORPOS_LOGO_W) / 2, y0 = (h - PLORPOS_LOGO_H) / 2;
	int i, n = w * h, k = 0;

	for (i = 0; i < n; i++)
		fb[i] = 0xff000000u | BG;

	while (p < end && k < PLORPOS_LOGO_W * PLORPOS_LOGO_H) {
		int run = 1;
		unsigned int a = *p++;

		if (!a)
			run = *p++;
		for (; run; run--, k++) {
			int u, v, x, y;

			if (!a)
				continue;
			u = x0 + k % PLORPOS_LOGO_W;	/* viewer coordinates */
			v = y0 + k / PLORPOS_LOGO_W;
			x = closed ? w - 1 - v : u;	/* panel coordinates */
			y = closed ? u : v;
			fb[y * w + x] = mix(k % PLORPOS_LOGO_W < PLORPOS_LOGO_SPLIT ?
					    FG_L : FG_R, a);
		}
	}
}
