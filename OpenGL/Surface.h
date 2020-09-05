#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <cassert>

class Surface
{
public:
	class Color
	{
	public:
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a = 1;
	};
public:
	Surface( const std::string& filename )
	{
		std::ifstream file( filename,std::ios::binary );
		assert( file );

		BITMAPFILEHEADER bmFileHeader;
		file.read( reinterpret_cast< char* >( &bmFileHeader ),
			sizeof( bmFileHeader ) );

		BITMAPINFOHEADER bmInfoHeader;
		file.read( reinterpret_cast< char* >( &bmInfoHeader ),
			sizeof( bmInfoHeader ) );

		assert( bmInfoHeader.biBitCount == 24 ||
			bmInfoHeader.biBitCount == 32 );
		assert( bmInfoHeader.biCompression == BI_RGB );

		const bool is32b = bmInfoHeader.biBitCount == 32;

		width = bmInfoHeader.biWidth;

		// Test for reverse row order and
		//  control y loop accordingly.
		int yStart;
		int yEnd;
		int dy;
		if( bmInfoHeader.biHeight < 0 )
		{
			height = -bmInfoHeader.biHeight;
			yStart = 0;
			yEnd = height;
			dy = 1;
		}
		else
		{
			height = bmInfoHeader.biHeight;
			yStart = height - 1;
			yEnd = -1;
			dy = -1;
		}

		pixels.resize( width * height );

		file.seekg( bmFileHeader.bfOffBits );
		// Padding is for 24 bit depth only.
		const int padding = ( 4 - ( width * 3 ) % 4 ) % 4;

		for( int y = yStart; y != yEnd; y += dy )
		{
			for( int x = 0; x < width; ++x )
			{
				typedef unsigned char uchar;
				PutPixel( x,y,Color{ uchar( file.get() ),uchar( file.get() ),uchar( file.get() ) } );

				if( is32b ) file.seekg( 1,std::ios::cur );
			}

			if( !is32b ) file.seekg( padding,std::ios::cur );
		}
	}

	void PutPixel( int x,int y,Color c )
	{
		pixels[y * width + x] = c;
	}

	const std::vector<Color>& GetPixels() const
	{
		return( pixels );
	}
	Color GetPixel( int x,int y ) const
	{
		return( pixels[y * width + x] );
	}
	int GetWidth() const
	{
		return( width );
	}
	int GetHeight() const
	{
		return( height );
	}
private:
	std::vector<Color> pixels;
	int width;
	int height;
};