#include <stdint.h>
#include <stdlib.h>
#include "gba.h"
#include "font.h"

// A blank tile.
// See the palette below for what the colour numbers mean.
const uint8_t blank_tile[64] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};

// A red box as a tile.
// (If you're making a game with lots of these, it's easier to convert
// them from graphics files than to write them out by hand like this!)
const uint8_t red_box_tile[64] = {
	1, 1, 1, 1, 1, 1, 1, 2,
	1, 3, 3, 3, 3, 3, 3, 2,
	1, 3, 3, 3, 3, 3, 3, 2,
	1, 3, 3, 3, 3, 3, 3, 2,
	1, 3, 3, 3, 3, 3, 3, 2,
	1, 3, 3, 3, 3, 3, 3, 2,
	1, 3, 3, 3, 3, 3, 3, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
};

// A smiley face.
const uint8_t smiley_tile[64] = {
	0, 0, 3, 3, 3, 3, 0, 0,
	0, 3, 3, 3, 3, 3, 3, 0,
	3, 3, 1, 3, 3, 1, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 1, 3, 3, 3, 3, 1, 3,
	0, 3, 1, 1, 1, 1, 3, 0,
	0, 0, 3, 3, 3, 3, 0, 0,
};

// An upward-facing arrow (top left tile).
const uint8_t arrow0_tile[64] = {
	0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 1, 2,
	0, 0, 0, 0, 0, 1, 2, 2,
	0, 0, 0, 0, 1, 2, 2, 2,
	0, 0, 0, 1, 2, 2, 2, 2,
	0, 0, 1, 2, 2, 2, 2, 2,
	0, 1, 2, 2, 2, 2, 2, 2,
	1, 2, 2, 2, 2, 2, 2, 2,
};

// An upward-facing arrow (top right tile).
const uint8_t arrow1_tile[64] = {
	1, 0, 0, 0, 0, 0, 0, 0,
	2, 1, 0, 0, 0, 0, 0, 0,
	2, 2, 1, 0, 0, 0, 0, 0,
	2, 2, 2, 1, 0, 0, 0, 0,
	2, 2, 2, 2, 1, 0, 0, 0,
	2, 2, 2, 2, 2, 1, 0, 0,
	2, 2, 2, 2, 2, 2, 1, 0,
	2, 2, 2, 2, 2, 2, 2, 1,
};

// An upward-facing arrow (bottom left tile).
const uint8_t arrow2_tile[64] = {
	1, 1, 1, 1, 2, 2, 2, 2,
	0, 0, 0, 1, 2, 2, 2, 2,
	0, 0, 0, 1, 2, 2, 2, 2,
	0, 0, 0, 1, 2, 2, 2, 2,
	0, 0, 0, 1, 2, 2, 2, 2,
	0, 0, 0, 1, 2, 2, 2, 2,
	0, 0, 0, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0,
};

// An upward-facing arrow (bottom right tile).
const uint8_t arrow3_tile[64] = {
	2, 2, 2, 2, 1, 1, 1, 1,
	2, 2, 2, 2, 1, 0, 0, 0,
	2, 2, 2, 2, 1, 0, 0, 0,
	2, 2, 2, 2, 1, 0, 0, 0,
	2, 2, 2, 2, 1, 0, 0, 0,
	2, 2, 2, 2, 1, 0, 0, 0,
	1, 1, 1, 1, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};

int main()
{
	// Set display options.
	// DCNT_MODE0 sets mode 0, which provides four tiled backgrounds.
	//   (But we've not actually turned any of them on... yet.)
	// DCNT_OBJ enables objects.
	// DCNT_OBJ_1D make object tiles mapped in 1D (which makes life easier).
	REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D;
	
	// Set up the object palette.
	SetPaletteObj(0, RGB(0, 0, 0)); // black (but actually transparent)
	SetPaletteObj(1, RGB(0, 0, 0)); // black
	SetPaletteObj(2, RGB(31, 31, 31)); // white
	SetPaletteObj(3, RGB(31, 31, 0)); // yellow
	SetPaletteObj(4, RGB(31, 0, 0)); // red

	// Load the tiles for the objects into charblock 4.
	// (Charblocks 4 and 5 are for object tiles;
	// 8bpp tiles 0-255 are in CB 4, tiles 256-511 in CB 5.)
	LoadTile8(4, 1, smiley_tile);
	LoadTile8(4, 10, arrow0_tile);
	LoadTile8(4, 11, arrow1_tile);
	LoadTile8(4, 12, arrow2_tile);
	LoadTile8(4, 13, arrow3_tile);
	
	ClearObjects();

	// Set up object 0 as a smiley face in the middle of the screen.
	SetObject(0,
	          ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(76),
			  ATTR1_SIZE(0) | ATTR1_X(116),
			  ATTR2_ID8(1));
			  
	SetObject(1,
	          ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(76),
			  ATTR1_SIZE(1) | ATTR1_X(116) | ATTR1_VFLIP,
			  ATTR2_ID8(10));
int xpos = 0;
int ypos = 0;
	while (true)
	{
		// ... do more interesting things here
	SetObjectX( 0, xpos);
		SetObjectY( 0, ypos);
		WaitVSync();
		UpdateObjects();
		if(xpos <= SCREEN_WIDTH) xpos++;
		if(xpos <= SCREEN_HEIGHT) ypos++;
		
	}

	return 0;
}
