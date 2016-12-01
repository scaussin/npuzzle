#ifndef MAP_HPP
# define MAP_HPP

class MapLine;

class Map {

	public :
		Map(int **map, int mapSize);
		~Map();

		int **map;
		MapLine *mapLine;
		int mapSize;
		int nMax;
		bool isSolvable();
		void print();

	private :
		class MapLine
		{
			public:
				MapLine();
				~MapLine();
				int *line;
				int *getCase(int find);
				bool isSolved();
				void print();
			private:
		};
};

#endif