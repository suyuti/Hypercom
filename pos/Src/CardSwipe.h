unsigned char CardSwipe[] __attribute__ ((aligned (4))) = {
	0x20, 0x00, 0x00, 0x00, // bitmap width
	0x30, 0x00, 0x00, 0x00, // bitmap height
	0x00, 0x00, 0x00, 0x00,
	0x40, 0x00, 0x00, 0x00, // bytes per scan line (row)
	0x10, 0x00, // bits per pixel
	0x01, 0x00, // image planes
// row 000
	0x0F, 0xF8, 0x0F, 0xF8, 0x68, 0x10, 0xDB, 0x51, 0x9F, 0x62, 0x1F, 0x73, 0x9F, 0x83, 0x9F, 0x83, 
	0x9F, 0x83, 0x9F, 0x83, 0x1F, 0x73, 0x9F, 0x62, 0x1F, 0x5A, 0x1F, 0x5A, 0x1F, 0x5A, 0x1F, 0x5A, 
	0x1F, 0x5A, 0x1F, 0x5A, 0x1F, 0x5A, 0x1F, 0x5A, 0x1F, 0x5A, 0x1F, 0x5A, 0x1F, 0x5A, 0x1F, 0x5A, 
	0x1F, 0x5A, 0x1F, 0x5A, 0x1F, 0x5A, 0x1F, 0x5A, 0xBB, 0x49, 0x47, 0x10, 0x01, 0x00, 0xEF, 0x07, 
// row 001
	0x0F, 0xF8, 0x0F, 0xF8, 0x97, 0x41, 0xBD, 0x28, 0x9F, 0x49, 0xFF, 0xC5, 0xFF, 0xE6, 0xFF, 0xE6, 
	0xFF, 0xE6, 0xFF, 0xE6, 0xFF, 0xC5, 0x9F, 0x49, 0x9F, 0x28, 0x9F, 0x28, 0x9F, 0x28, 0x9F, 0x28, 
	0x9F, 0x28, 0x9F, 0x28, 0x54, 0x18, 0x51, 0x18, 0x54, 0x18, 0x9F, 0x28, 0x9F, 0x28, 0x9F, 0x28, 
	0x9F, 0x28, 0x9F, 0x28, 0x9F, 0x28, 0x9F, 0x28, 0x5D, 0x20, 0x37, 0x18, 0x03, 0x00, 0xEF, 0x07, 
// row 002
	0x0F, 0xF8, 0x0F, 0xF8, 0x9B, 0x41, 0x5F, 0x28, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1B, 0x18, 0x06, 0x00, 0xEF, 0x07, 
// row 003
	0x0F, 0xF8, 0x53, 0x31, 0x9D, 0x28, 0x3F, 0x20, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x11, 0x10, 0x14, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1D, 0x18, 0x12, 0x10, 0xEF, 0x07, 
// row 004
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1B, 0x18, 0x14, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 005
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x14, 0x10, 0x18, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 006
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x14, 0x10, 0x11, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 007
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x14, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 008
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x14, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 009
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x11, 0x10, 0x11, 0x10, 0x11, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 010
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x14, 0x10, 0x14, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 011
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1B, 0x18, 0x1B, 0x18, 0x1B, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 012
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x0D, 0x08, 0x0D, 0x08, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x3F, 0x20, 0x7F, 0x28, 0x3F, 0x20, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 013
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x18, 0x18, 0x11, 0x10, 0x11, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 014
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x18, 0x18, 0x14, 0x10, 0x1B, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x3F, 0x20, 
	0xFF, 0xFF, 0xFF, 0x38, 0x1C, 0x52, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 015
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x1F, 0x18, 0x14, 0x10, 0x1F, 0x18, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x15, 0x4A, 0x1D, 0x52, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 016
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x1F, 0x18, 0x14, 0x10, 0xFF, 0xFF, 0x5E, 0x41, 0xAF, 0x39, 
	0xE0, 0xFF, 0x3C, 0x5A, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 017
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1B, 0x18, 0x34, 0x18, 0xFF, 0xFF, 0x5E, 0x41, 0x1D, 0x52, 0x29, 0x29, 
	0xE0, 0xFF, 0x3C, 0x5A, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 018
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x20, 0xFF, 0xFF, 0xFF, 0xFF, 0xCE, 0x41, 0x57, 0x52, 0x1D, 0x52, 0x29, 0x29, 
	0xE0, 0xFF, 0x3C, 0x5A, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 019
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x20, 0xFF, 0xFF, 0xF5, 0x49, 0x2A, 0x29, 0xE0, 0xFF, 0x57, 0x5A, 0x1D, 0x52, 0x29, 0x29, 
	0xE0, 0xFF, 0x3C, 0x5A, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 020
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x5F, 0x20, 
	0xFF, 0xFF, 0x18, 0x52, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0x57, 0x5A, 0x1D, 0x52, 0x29, 0x29, 
	0xE0, 0xFF, 0x3C, 0x5A, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 021
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x20, 0xFF, 0xFF, 0xFF, 0xFF, 
	0x6E, 0x31, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0x57, 0x5A, 0x1D, 0x52, 0x29, 0x29, 
	0xE0, 0xFF, 0x3C, 0x5A, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 022
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x20, 0xFF, 0xFF, 0x1B, 0x52, 0xC7, 0x18, 
	0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0x57, 0x5A, 0x1D, 0x52, 0x29, 0x29, 
	0xE0, 0xFF, 0x3C, 0x5A, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 023
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0xFF, 0xFF, 0x3B, 0x52, 0xE0, 0xFF, 0xE0, 0xFF, 
	0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0x57, 0x5A, 0x1D, 0x52, 0x29, 0x29, 
	0xE0, 0xFF, 0x3C, 0x5A, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 024
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x3F, 0x20, 0xFF, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 
	0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0x57, 0x5A, 0x1D, 0x52, 0x29, 0x29, 
	0xE0, 0xFF, 0x3C, 0x5A, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 025
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x20, 0xDE, 0x30, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0x57, 0x5A, 0x1D, 0x52, 0x29, 0x29, 
	0xE0, 0xFF, 0x3C, 0x5A, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 026
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x20, 0x9E, 0x28, 0xBE, 0x49, 
	0xFF, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0x57, 0x5A, 0x1D, 0x52, 0x29, 0x29, 
	0xE0, 0xFF, 0x3C, 0x5A, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 027
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x5E, 0x28, 
	0x1F, 0x39, 0xFF, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0x57, 0x5A, 0x1D, 0x52, 0x29, 0x29, 
	0xE0, 0xFF, 0x3C, 0x5A, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 028
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x3F, 0x20, 0xDE, 0x30, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xFF, 0x57, 0x5A, 0x1D, 0x52, 0x29, 0x29, 
	0xE0, 0xFF, 0x3C, 0x5A, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 029
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x20, 0x95, 0x20, 0x76, 0x39, 0xFF, 0xFF, 0x57, 0x5A, 0x1D, 0x52, 0x29, 0x29, 
	0xE0, 0xFF, 0x3C, 0x5A, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 030
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1B, 0x18, 0x5B, 0x20, 0xF9, 0x30, 0xFF, 0xFF, 0x1D, 0x52, 0x29, 0x29, 
	0xE0, 0xFF, 0x3C, 0x5A, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 031
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x14, 0x10, 0x14, 0x10, 0x3F, 0x20, 0xFF, 0xFF, 0xAE, 0x39, 
	0xE0, 0xFF, 0x3C, 0x5A, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 032
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x18, 0x18, 0x18, 0x18, 0x1F, 0x18, 0x5E, 0x28, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x1C, 0x52, 0x3C, 0x5A, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 033
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x3F, 0x20, 
	0xDF, 0x30, 0xFF, 0xFF, 0x1C, 0x52, 0xE0, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 034
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x14, 0x10, 0x0D, 0x08, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x20, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 035
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1B, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x3E, 0x20, 0x7E, 0x28, 0x3F, 0x20, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 036
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 037
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x14, 0x10, 0x14, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 038
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x1F, 0x18, 0x14, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 039
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x1F, 0x18, 0x1B, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 040
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x14, 0x10, 0x14, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 041
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x14, 0x10, 0x14, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 042
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x0D, 0x08, 0x14, 0x10, 0x14, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 043
	0x0F, 0xF8, 0x55, 0x39, 0x9F, 0x28, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x11, 0x10, 0x14, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 044
	0x0F, 0xF8, 0x33, 0x31, 0x5D, 0x20, 0x1F, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x18, 0x18, 0x14, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0xEF, 0x07, 
// row 045
	0x0F, 0xF8, 0x0F, 0xF8, 0x39, 0x18, 0x1D, 0x18, 0x9F, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x11, 0x10, 0x14, 0x10, 0x11, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1D, 0x18, 0x12, 0x10, 0xEF, 0x07, 
// row 046
	0x0F, 0xF8, 0x0F, 0xF8, 0x05, 0x00, 0x19, 0x18, 0x9D, 0x49, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x14, 0x10, 0x1F, 0x18, 0x14, 0x10, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1D, 0x18, 0x19, 0x18, 0x04, 0x00, 0xEF, 0x07, 
// row 047
	0x0F, 0xF8, 0x0F, 0xF8, 0x0F, 0xF8, 0x07, 0x08, 0x9B, 0x41, 0x9F, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0xD6, 0x9F, 0x49, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x18, 0x18, 0x14, 0x10, 0x18, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 
	0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x1B, 0x18, 0x07, 0x08, 0x01, 0x00, 0xEF, 0x07, 
};
