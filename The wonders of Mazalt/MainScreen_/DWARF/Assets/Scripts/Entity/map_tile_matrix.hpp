#ifndef MAP_TILE_MATRIX_HPP
#define MAP_TILE_MATRIX_HPP

#include <SFML\System\Vector2.hpp>
#include <Assets\Scripts\ADT\tile_data.hpp>
#include <Settings\folder_paths.hpp>
#include <Library\string_tools.hpp>
#include <array>
#include <string>
#include <fstream>
#include <vector>

template< int ROW, int COL>
class map_tile_matrix {

private:
	std::array< std::array< tile_data, COL>, ROW > matrix;
	const std::string & dir_path_data;
	const std::string & dir_name_textures;
	const sf::Vector2i & tile_size;
	const std::string & filename_prefix;
	const std::string & file_extention;

	void init() {
		std::string path = MODELS + dir_path_data;
		std::ifstream file(path);
		std::string line;
		int row = 0;
		int col = 0;
		
		while (std::getline(file, line)) {
			std::vector<std::string> v{ explode(line, ',') };
			for (auto n : v) {
				tile_data & element = matrix[row][col];
				element.id = std::atoi( n.c_str() );
				element.size = tile_size;
				element.pos = sf::Vector2f(tile_size.x * col, tile_size.y * row);

				if (element.id > -1) {
					element.texture = (TEXTURES + dir_name_textures + "/" + filename_prefix + n + file_extention);
				}
				else {
					element.texture = (TEXTURES + "no_texture_found.png");
				}

				++col;
			}
			col = 0;
			++row;
		}

	}



public: 
	map_tile_matrix( 
		const std::string & dir_path_data, 
		const std::string & dir_name_textures, 
		const sf::Vector2i & tile_size,
		const std::string & filename_prefix = std::string(""), 
		const std::string & file_extention = std::string(".png")
	):
		dir_path_data(dir_path_data),
		dir_name_textures(dir_name_textures),
		tile_size(tile_size),
		filename_prefix(filename_prefix),
		file_extention(file_extention)
	{
		init();
	};

	std::array< std::array< tile_data, COL>, ROW > & get() {
		return matrix;
	}



};




#endif //MAP_TILE_MATRIX_HPP


