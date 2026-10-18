#ifndef PLORPOS_LOGO_DRAW_H
#define PLORPOS_LOGO_DRAW_H
/* Fill a w x h 32bpp (ARGB8888) framebuffer with the plorpOS boot logo;
 * closed: the swivel is closed, draw turned to match the launcher. */
void plorpos_logo_draw(unsigned int *fb, int w, int h, int closed);
#endif
