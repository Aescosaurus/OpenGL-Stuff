#include "MapGenerator.h"

int MapGenerator::width = 0;
int MapGenerator::height = 0;

void MapGenerator::SetDims( int widthIn,int heightIn,int quality )
{
	width = widthIn / quality;
	height = heightIn / quality;
}
