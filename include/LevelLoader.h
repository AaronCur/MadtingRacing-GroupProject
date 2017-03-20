#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"

struct ObstacleData
{
  std::string m_type;
  sf::Vector2f m_position;
  double m_rotation;
};

struct PathData
{
	std::string m_type;
	sf::Vector2f m_position;
	double m_rotation;
};

struct BackgroundData
{
   std::string m_fileName;
   
};


struct LevelData
{
   BackgroundData m_background;
   std::vector<PathData> m_paths;
   std::vector<ObstacleData> m_obstacles;
   PathData send(PathData data);
   sf::Vector2f current;
};

class LevelLoader
{
public:

   LevelLoader();
   
   static bool load(int nr, LevelData& level);
};
