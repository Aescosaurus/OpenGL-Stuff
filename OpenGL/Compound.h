#pragma once

#include "Model.h"
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include "Cube.h"

class Compound
{
public:
	// File looks like: x y z xscale yscale zscale
	Compound( const std::string& fileName )
	{
		const auto try_emplace = []( const std::string& curFloat,
			std::vector<std::vector<float>>& modelData )
		{
			try
			{
				modelData.back().emplace_back( std::stof( curFloat ) );
			}
			catch( ... )
			{
				// In case stof fails ignore object.
				modelData.pop_back();
			}
		};

		std::ifstream in{ fileName };
		std::vector<std::vector<float>> modelData;
		while( in.good() )
		{
			std::string line;
			std::getline( in,line );
			modelData.emplace_back();
			std::string curFloat = "";
			for( char c : line )
			{
				if( c == ' ' )
				{
					try_emplace( curFloat,modelData );
					curFloat = "";
				}
				else curFloat += c;
			}

			try_emplace( curFloat,modelData );
		}

		for( const auto& obj : modelData )
		{
			std::unique_ptr<Cube> curModel = std::make_unique<Cube>( glm::vec3{ obj[3],obj[4],obj[5] } );
			curModel->xform.pos = glm::vec3{ obj[0],obj[1],obj[2] };
			components.emplace_back( std::move( curModel ) );
		}
	}

	void Draw( Shader& shader ) const
	{
		for( const auto& comp : components )
		{
			shader.Update( comp->xform );
			comp->mesh.Draw();
		}
	}
public:
	// Transform xform;
private:
	// Unique ptr allows multiple model types, as well as avoid copy ctor.  Nice!
	std::vector<std::unique_ptr<Model>> components;
};