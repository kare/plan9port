/* Copyright (c) 1994-1996 David Hogan, see README for licence details */
#include <stdio.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/shape.h>
#include "dat.h"
#include "fns.h"

typedef struct Cursordata Cursordata;
struct Cursordata {
	int		width;
	int		hot[2];
	unsigned char	mask[64];
	unsigned char	fore[64];
};

Cursordata bigarrow = {
	16,
	{0, 0},
	{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0x3F,
	  0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0x1F, 0xFF, 0x3F,
	  0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0x3F,
	  0xCF, 0x1F, 0x8F, 0x0F, 0x07, 0x07, 0x03, 0x02,
	},
	{ 0x00, 0x00, 0xFE, 0x7F, 0xFE, 0x3F, 0xFE, 0x0F,
	  0xFE, 0x07, 0xFE, 0x07, 0xFE, 0x0F, 0xFE, 0x1F,
	  0xFE, 0x3F, 0xFE, 0x7F, 0xFE, 0x3F, 0xCE, 0x1F,
	  0x86, 0x0F, 0x06, 0x07, 0x02, 0x02, 0x00, 0x00,
	}
};

Cursordata sweep0data = {
	16,
	{7, 7},
	{0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03,
	 0xC0, 0x03, 0xC0, 0x03, 0xFF, 0xFF, 0xFF, 0xFF,
	 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x03, 0xC0, 0x03,
	 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03},
	{0x00, 0x00, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01,
	 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0xFE, 0x7F,
	 0xFE, 0x7F, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01,
	 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x00, 0x00}
};

Cursordata boxcursdata = {
	16,
	{7, 7},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	 0xFF, 0xFF, 0x1F, 0xF8, 0x1F, 0xF8, 0x1F, 0xF8,
	 0x1F, 0xF8, 0x1F, 0xF8, 0x1F, 0xF8, 0xFF, 0xFF,
	 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{0x00, 0x00, 0xFE, 0x7F, 0xFE, 0x7F, 0xFE, 0x7F,
	 0x0E, 0x70, 0x0E, 0x70, 0x0E, 0x70, 0x0E, 0x70,
	 0x0E, 0x70, 0x0E, 0x70, 0x0E, 0x70, 0x0E, 0x70,
	 0xFE, 0x7F, 0xFE, 0x7F, 0xFE, 0x7F, 0x00, 0x00}
};

Cursordata sightdata = {
	16,
	{7, 7},
	{0xF8, 0x1F, 0xFC, 0x3F, 0xFE, 0x7F, 0xDF, 0xFB,
	 0xCF, 0xF3, 0xC7, 0xE3, 0xFF, 0xFF, 0xFF, 0xFF,
	 0xFF, 0xFF, 0xFF, 0xFF, 0xC7, 0xE3, 0xCF, 0xF3,
	 0xDF, 0x7B, 0xFE, 0x7F, 0xFC, 0x3F, 0xF8, 0x1F,},
	{0x00, 0x00, 0xF0, 0x0F, 0x8C, 0x31, 0x84, 0x21,
	 0x82, 0x41, 0x82, 0x41, 0x82, 0x41, 0xFE, 0x7F,
	 0xFE, 0x7F, 0x82, 0x41, 0x82, 0x41, 0x82, 0x41,
	 0x84, 0x21, 0x8C, 0x31, 0xF0, 0x0F, 0x00, 0x00,}
};

Cursordata arrowdata = {
	16,
	{1, 1},
	{0xFF, 0x07, 0xFF, 0x07, 0xFF, 0x03, 0xFF, 0x00,
	 0xFF, 0x00, 0xFF, 0x01, 0xFF, 0x03, 0xFF, 0x07,
	 0xE7, 0x0F, 0xC7, 0x1F, 0x83, 0x3F, 0x00, 0x7F,
	 0x00, 0xFE, 0x00, 0x7C, 0x00, 0x38, 0x00, 0x10,},
	{0x00, 0x00, 0xFE, 0x03, 0xFE, 0x00, 0x3E, 0x00,
	 0x7E, 0x00, 0xFE, 0x00, 0xF6, 0x01, 0xE6, 0x03,
	 0xC2, 0x07, 0x82, 0x0F, 0x00, 0x1F, 0x00, 0x3E,
	 0x00, 0x7C, 0x00, 0x38, 0x00, 0x10, 0x00, 0x00,}
};

Cursordata whitearrow = {
	16,
	{0, 0},
	{0xFF, 0x07, 0xFF, 0x07, 0xFF, 0x03, 0xFF, 0x00,
	 0xFF, 0x00, 0xFF, 0x01, 0xFF, 0x03, 0xFF, 0x07,
	 0xE7, 0x0F, 0xC7, 0x1F, 0x83, 0x3F, 0x00, 0x7F,
	 0x00, 0xFE, 0x00, 0x7C, 0x00, 0x38, 0x00, 0x10,},
	{0xFF, 0x07, 0xFF, 0x07, 0x83, 0x03, 0xC3, 0x00,
	 0xC3, 0x00, 0x83, 0x01, 0x1B, 0x03, 0x3F, 0x06,
	 0x67, 0x0C, 0xC7, 0x18, 0x83, 0x31, 0x00, 0x63,
	 0x00, 0xC6, 0x00, 0x6C, 0x00, 0x38, 0x00, 0x10,}
};

Cursordata blittarget = {
	18,
	{8, 8},
	{0xe0, 0x1f, 0x00, 0xf0, 0x3f, 0x00, 0xf8, 0x7f, 0x00,
	 0xfc, 0xff, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xff, 0x03,
	 0xff, 0xff, 0x03, 0xff, 0xff, 0x03, 0xff, 0xff, 0x03,
	 0xff, 0xff, 0x03, 0xff, 0xff, 0x03, 0xff, 0xff, 0x03,
	 0xff, 0xff, 0x03, 0xfe, 0xff, 0x01, 0xfc, 0xff, 0x00,
	 0xf8, 0x7f, 0x00, 0xf0, 0x3f, 0x00, 0xe0, 0x1f, 0x00},
	{0x00, 0x00, 0x00, 0xc0, 0x0f, 0x00, 0xf0, 0x3f, 0x00,
	 0x38, 0x73, 0x00, 0x8c, 0xc7, 0x00, 0xec, 0xdf, 0x00,
	 0x66, 0x9b, 0x01, 0x36, 0xb3, 0x01, 0xfe, 0xff, 0x01,
	 0xfe, 0xff, 0x01, 0x36, 0xb3, 0x01, 0x66, 0x9b, 0x01,
	 0xec, 0xdf, 0x00, 0x8c, 0xc7, 0x00, 0x38, 0x73, 0x00,
	 0xf0, 0x3f, 0x00, 0xc0, 0x0f, 0x00, 0x00, 0x00, 0x00}
};

Cursordata blitarrow = {
	18,
	{1, 1},
	{0xff, 0x0f, 0x00, 0xff, 0x07, 0x00, 0xff, 0x03, 0x00,
	 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x01, 0x00,
	 0xff, 0x03, 0x00, 0xff, 0x07, 0x00, 0xe7, 0x0f, 0x00,
	 0xc7, 0x1f, 0x00, 0x87, 0x3f, 0x00, 0x03, 0x7f, 0x00,
	 0x01, 0xfe, 0x00, 0x00, 0xfc, 0x01, 0x00, 0xf8, 0x03,
	 0x00, 0xf0, 0x01, 0x00, 0xe0, 0x00, 0x00, 0x40, 0x00},
	{0x00, 0x00, 0x00, 0xfe, 0x03, 0x00, 0xfe, 0x00, 0x00,
	 0x3e, 0x00, 0x00, 0x7e, 0x00, 0x00, 0xfe, 0x00, 0x00,
	 0xf6, 0x01, 0x00, 0xe6, 0x03, 0x00, 0xc2, 0x07, 0x00,
	 0x82, 0x0f, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x3e, 0x00,
	 0x00, 0x7c, 0x00, 0x00, 0xf8, 0x00, 0x00, 0xf0, 0x01,
	 0x00, 0xe0, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00}
};

Cursordata blitsweep = {
	18,
	{8, 8},
	{0xc4, 0xff, 0x03, 0xce, 0xff, 0x03, 0xdf, 0xff, 0x03,
	 0x3e, 0x80, 0x03, 0x7c, 0x83, 0x03, 0xf8, 0x83, 0x03,
	 0xf7, 0x83, 0x03, 0xe7, 0x83, 0x03, 0xf7, 0x83, 0x03,
	 0xf7, 0x83, 0x03, 0x07, 0x80, 0x03, 0x07, 0x80, 0x03,
	 0x07, 0x80, 0x03, 0x07, 0x80, 0x03, 0x07, 0x80, 0x03,
	 0xff, 0xff, 0x03, 0xff, 0xff, 0x03, 0xff, 0xff, 0x03},
	{0x00, 0x00, 0x00, 0x84, 0xff, 0x01, 0x0e, 0x00, 0x01,
	 0x1c, 0x00, 0x01, 0x38, 0x00, 0x01, 0x70, 0x01, 0x01,
	 0xe0, 0x01, 0x01, 0xc2, 0x01, 0x01, 0xe2, 0x01, 0x01,
	 0x02, 0x00, 0x01, 0x02, 0x00, 0x01, 0x02, 0x00, 0x01,
	 0x02, 0x00, 0x01, 0x02, 0x00, 0x01, 0x02, 0x00, 0x01,
	 0x02, 0x00, 0x01, 0xfe, 0xff, 0x01, 0x00, 0x00, 0x00}
};

/*
 *	Grey tile pattern for root background
 */

#define grey_width 4
#define grey_height 2
static char grey_bits[] = {
	0x01, 0x04
};

static XColor	bl, wh;

Cursor
getcursor(Cursordata *c, ScreenInfo *s)
{
	Pixmap f, m;

	f = XCreatePixmapFromBitmapData(dpy, s->root, (char *)c->fore,
		c->width, c->width, 1, 0, 1);
	m = XCreatePixmapFromBitmapData(dpy, s->root, (char *)c->mask,
		c->width, c->width, 1, 0, 1);
	return XCreatePixmapCursor(dpy, f, m, &bl, &wh,
			c->hot[0], c->hot[1]);
}

void
initcurs(ScreenInfo *s)
{
	XColor dummy;

	XAllocNamedColor(dpy, DefaultColormap(dpy, s->num),
			"black", &bl, &dummy);
	XAllocNamedColor(dpy, DefaultColormap(dpy, s->num),
			"white", &wh, &dummy);

	if(nostalgia){
		s->arrow = getcursor(&blitarrow, s);
		s->target = getcursor(&blittarget, s);
		s->sweep0 = getcursor(&blitsweep, s);
		s->boxcurs = getcursor(&blitsweep, s);
	}
	else {
		s->arrow = getcursor(&bigarrow, s);
		s->target = getcursor(&sightdata, s);
		s->sweep0 = getcursor(&sweep0data, s);
		s->boxcurs = getcursor(&boxcursdata, s);
	}

	s->root_pixmap = XCreatePixmapFromBitmapData(dpy,
		s->root, grey_bits, grey_width, grey_height,
		s->black, s->white, s->depth);

	s->bordcurs[BorderN] = XCreateFontCursor(dpy, 138);
	s->bordcurs[BorderNNE] = XCreateFontCursor(dpy, 136);
	s->bordcurs[BorderENE] = s->bordcurs[BorderNNE] ;
	s->bordcurs[BorderE] = XCreateFontCursor(dpy, 96);
	s->bordcurs[BorderESE] = XCreateFontCursor(dpy, 14);
	s->bordcurs[BorderSSE] = s->bordcurs[BorderESE];
	s->bordcurs[BorderS] = XCreateFontCursor(dpy, 16);
	s->bordcurs[BorderSSW] = XCreateFontCursor(dpy, 12);
	s->bordcurs[BorderWSW] = s->bordcurs[BorderSSW];
	s->bordcurs[BorderW] = XCreateFontCursor(dpy, 70);
	s->bordcurs[BorderWNW] = XCreateFontCursor(dpy, 134);
	s->bordcurs[BorderNNW] = s->bordcurs[BorderWNW];
}


/* RIO

Cursor crosscursor = {
	{-7, -7},
	{0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0,
	 0x03, 0xC0, 0x03, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF,
	 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0xC0, 0x03, 0xC0,
	 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, },
	{0x00, 0x00, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80,
	 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x7F, 0xFE,
	 0x7F, 0xFE, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80,
	 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, }
};

Cursor boxcursor = {
	{-7, -7},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	 0xFF, 0xFF, 0xF8, 0x1F, 0xF8, 0x1F, 0xF8, 0x1F,
	 0xF8, 0x1F, 0xF8, 0x1F, 0xF8, 0x1F, 0xFF, 0xFF,
	 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, },
	{0x00, 0x00, 0x7F, 0xFE, 0x7F, 0xFE, 0x7F, 0xFE,
	 0x70, 0x0E, 0x70, 0x0E, 0x70, 0x0E, 0x70, 0x0E,
	 0x70, 0x0E, 0x70, 0x0E, 0x70, 0x0E, 0x70, 0x0E,
	 0x7F, 0xFE, 0x7F, 0xFE, 0x7F, 0xFE, 0x00, 0x00, }
};

Cursor sightcursor = {
	{-7, -7},
	{0x1F, 0xF8, 0x3F, 0xFC, 0x7F, 0xFE, 0xFB, 0xDF,
	 0xF3, 0xCF, 0xE3, 0xC7, 0xFF, 0xFF, 0xFF, 0xFF,
	 0xFF, 0xFF, 0xFF, 0xFF, 0xE3, 0xC7, 0xF3, 0xCF,
	 0x7B, 0xDF, 0x7F, 0xFE, 0x3F, 0xFC, 0x1F, 0xF8, },
	{0x00, 0x00, 0x0F, 0xF0, 0x31, 0x8C, 0x21, 0x84,
	 0x41, 0x82, 0x41, 0x82, 0x41, 0x82, 0x7F, 0xFE,
	 0x7F, 0xFE, 0x41, 0x82, 0x41, 0x82, 0x41, 0x82,
	 0x21, 0x84, 0x31, 0x8C, 0x0F, 0xF0, 0x00, 0x00, }
};

Cursor whitearrow = {
	{0, 0},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFC,
	 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xF8, 0xFF, 0xFC,
	 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFC,
	 0xF3, 0xF8, 0xF1, 0xF0, 0xE0, 0xE0, 0xC0, 0x40, },
	{0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x06, 0xC0, 0x1C,
	 0xC0, 0x30, 0xC0, 0x30, 0xC0, 0x38, 0xC0, 0x1C,
	 0xC0, 0x0E, 0xC0, 0x07, 0xCE, 0x0E, 0xDF, 0x1C,
	 0xD3, 0xB8, 0xF1, 0xF0, 0xE0, 0xE0, 0xC0, 0x40, }
};

Cursor query = {
	{-7,-7},
	{0x0f, 0xf0, 0x1f, 0xf8, 0x3f, 0xfc, 0x7f, 0xfe,
	 0x7c, 0x7e, 0x78, 0x7e, 0x00, 0xfc, 0x01, 0xf8,
	 0x03, 0xf0, 0x07, 0xe0, 0x07, 0xc0, 0x07, 0xc0,
	 0x07, 0xc0, 0x07, 0xc0, 0x07, 0xc0, 0x07, 0xc0, },
	{0x00, 0x00, 0x0f, 0xf0, 0x1f, 0xf8, 0x3c, 0x3c,
	 0x38, 0x1c, 0x00, 0x3c, 0x00, 0x78, 0x00, 0xf0,
	 0x01, 0xe0, 0x03, 0xc0, 0x03, 0x80, 0x03, 0x80,
	 0x00, 0x00, 0x03, 0x80, 0x03, 0x80, 0x00, 0x00, }
};

Cursor tl = {
	{-4, -4},
	{0xfe, 0x00, 0x82, 0x00, 0x8c, 0x00, 0x87, 0xff,
	 0xa0, 0x01, 0xb0, 0x01, 0xd0, 0x01, 0x11, 0xff,
	 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00,
	 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x1f, 0x00, },
	{0x00, 0x00, 0x7c, 0x00, 0x70, 0x00, 0x78, 0x00,
	 0x5f, 0xfe, 0x4f, 0xfe, 0x0f, 0xfe, 0x0e, 0x00,
	 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00,
	 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x00, 0x00, }
};

Cursor t = {
	{-7, -8},
	{0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x06, 0xc0,
	 0x1c, 0x70, 0x10, 0x10, 0x0c, 0x60, 0xfc, 0x7f,
	 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0xff, 0xff,
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, },
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
	 0x03, 0x80, 0x0f, 0xe0, 0x03, 0x80, 0x03, 0x80,
	 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x00, 0x00,
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }
};

Cursor tr = {
	{-11, -4},
	{0x00, 0x7f, 0x00, 0x41, 0x00, 0x31, 0xff, 0xe1,
	 0x80, 0x05, 0x80, 0x0d, 0x80, 0x0b, 0xff, 0x88,
	 0x00, 0x88, 0x0, 0x88, 0x00, 0x88, 0x00, 0x88,
	 0x00, 0x88, 0x00, 0x88, 0x00, 0x88, 0x00, 0xf8, },
	{0x00, 0x00, 0x00, 0x3e, 0x00, 0x0e, 0x00, 0x1e,
	 0x7f, 0xfa, 0x7f, 0xf2, 0x7f, 0xf0, 0x00, 0x70,
	 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70,
	 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x00, }
};

Cursor r = {
	{-8, -7},
	{0x07, 0xc0, 0x04, 0x40, 0x04, 0x40, 0x04, 0x58,
	 0x04, 0x68, 0x04, 0x6c, 0x04, 0x06, 0x04, 0x02,
	 0x04, 0x06, 0x04, 0x6c, 0x04, 0x68, 0x04, 0x58,
	 0x04, 0x40, 0x04, 0x40, 0x04, 0x40, 0x07, 0xc0, },
	{0x00, 0x00, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80,
	 0x03, 0x90, 0x03, 0x90, 0x03, 0xf8, 0x03, 0xfc,
	 0x03, 0xf8, 0x03, 0x90, 0x03, 0x90, 0x03, 0x80,
	 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x00, 0x00, }
};

Cursor br = {
	{-11, -11},
	{0x00, 0xf8, 0x00, 0x88, 0x00, 0x88, 0x00, 0x88,
	 0x00, 0x88, 0x00, 0x88, 0x00, 0x88, 0x00, 0x88,
	 0xff, 0x88, 0x80, 0x0b, 0x80, 0x0d, 0x80, 0x05,
	 0xff, 0xe1, 0x00, 0x31, 0x00, 0x41, 0x00, 0x7f, },
	{0x00, 0x00, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70,
	 0x0, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70,
	 0x00, 0x70, 0x7f, 0xf0, 0x7f, 0xf2, 0x7f, 0xfa,
	 0x00, 0x1e, 0x00, 0x0e, 0x00, 0x3e, 0x00, 0x00, }
};

Cursor b = {
	{-7, -7},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	 0xff, 0xff, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01,
	 0xfc, 0x7f, 0x0c, 0x60, 0x10, 0x10, 0x1c, 0x70,
	 0x06, 0xc0, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, },
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	 0x00, 0x00, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe,
	 0x03, 0x80, 0x03, 0x80, 0x0f, 0xe0, 0x03, 0x80,
	 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }
};

Cursor bl = {
	{-4, -11},
	{0x1f, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00,
	 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00,
	 0x11, 0xff, 0xd0, 0x01, 0xb0, 0x01, 0xa0, 0x01,
	 0x87, 0xff, 0x8c, 0x00, 0x82, 0x00, 0xfe, 0x00, },
	{0x00, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00,
	 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00,
	 0x0e, 0x00, 0x0f, 0xfe, 0x4f, 0xfe, 0x5f, 0xfe,
	 0x78, 0x00, 0x70, 0x00, 0x7c, 0x00, 0x00, 0x0, }
};

Cursor l = {
	{-7, -7},
	{0x03, 0xe0, 0x02, 0x20, 0x02, 0x20, 0x1a, 0x20,
	 0x16, 0x20, 0x36, 0x20, 0x60, 0x20, 0x40, 0x20,
	 0x60, 0x20, 0x36, 0x20, 0x16, 0x20, 0x1a, 0x20,
	 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x03, 0xe0, },
	{0x00, 0x00, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0,
	 0x09, 0xc0, 0x09, 0xc0, 0x1f, 0xc0, 0x3f, 0xc0,
	 0x1f, 0xc0, 0x09, 0xc0, 0x09, 0xc0, 0x01, 0xc0,
	 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x00, 0x00, }
};

Cursor *corners[9] = {
	&tl,	&t,	&tr,
	&l,	nil,	&r,
	&bl,	&b,	&br
};

*/
