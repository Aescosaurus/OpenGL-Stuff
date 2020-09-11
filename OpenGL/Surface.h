#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <cassert>

class Surface
{
private:
	typedef unsigned char uchar;
public:
	class Color
	{
	public:
		uchar r;
		uchar g;
		uchar b;
		// unsigned char a = 1;
	};
public:
	Surface( int width,int height )
		:
		width( width ),
		height( height ),
		pixels( width * height )
	{}
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
				Color col{ uchar( file.get() ),uchar( file.get() ),uchar( file.get() ) };
				std::swap( col.r,col.b );
				PutPixel( x,y,col );

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
	// Generates a 1x1 surface of color c.
	static Surface FromColor( int r,int g,int b )
	{
		Surface temp{ 1,1 };
		temp.PutPixel( 0,0,Color{ uchar( r ),uchar( g ),uchar( b ) } );
		return( temp );
	}
private:
	std::vector<Color> pixels;
	int width;
	int height;
};