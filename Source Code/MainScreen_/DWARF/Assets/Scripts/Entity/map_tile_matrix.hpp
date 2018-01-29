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
	const int & data_id;
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

		matrix[0][0].texture = (TEXTURES + dir_name_textures + "/" + filename_prefix + file_extention);

		while (std::getline(file, line)) {
			std::vector<std::string> v{ explode(line, ',') };

			for (auto n : v) {
				tile_data & element = matrix[row][col];
				int id = std::atoi(n.c_str());
				if (id == data_id) { element.level = 1; };
				
				element.size = tile_size;
				element.pos = sf::Vector2f(tile_size.x * col, tile_size.y * row);
				element.mid = sf::Vector2f( (element.pos.x + (tile_size.x/2)), (element.pos.y + (tile_size.y / 2)) );

				/*element.texture = (TEXTURES + dir_name_textures + "/" + filename_prefix + file_extention);*/

				++col;
			}
			col = 0;
			++row;
		}

	}



public: 
	map_tile_matrix( 
		const int & data_id,
		const std::string & dir_path_data, 
		const std::string & dir_name_textures, 
		const sf::Vector2i & tile_size,
		const std::string & filename_prefix = std::string(""), 
		const std::string & file_extention = std::string(".png")
	):
		data_id(data_id),
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


