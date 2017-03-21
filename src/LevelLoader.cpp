#include "LevelLoader.h"
#include <time.h>
void operator >> (const YAML::Node& obstacleNode, ObstacleData& obstacle)
{
   obstacle.m_type = obstacleNode["type"].as<std::string>();
   obstacle.m_position.x = obstacleNode["position"]["x"].as<float>();
   obstacle.m_position.y = obstacleNode["position"]["y"].as<float>();
   obstacle.m_rotation = obstacleNode["rotation"].as<double>();
}
void operator >> (const YAML::Node& pathNode, PathData& path)
{
	path.m_type = pathNode["type"].as<std::string>();
	path.m_position.x = pathNode["position"]["x"].as<float>();
	path.m_position.y = pathNode["position"]["y"].as<float>();

}
void operator >> (const YAML::Node& backgroundNode, BackgroundData& background)
{
   background.m_fileName = backgroundNode["file"].as<std::string>();
}

void operator >> (const YAML::Node& levelNode, LevelData& level)
{
	levelNode["background"] >> level.m_background;

	const YAML::Node& obstaclesNode = levelNode["obstacles"].as<YAML::Node>();
	for (unsigned i = 0; i < obstaclesNode.size(); ++i)
	{

		ObstacleData obstacle;
		obstaclesNode[i] >> obstacle;
		level.m_obstacles.push_back(obstacle);
	}
	
	const YAML::Node& pathNode = levelNode["paths"].as<YAML::Node>();
	for (unsigned i = 0; i < pathNode.size(); ++i)
	{

		PathData path;
		pathNode[i] >> path;
		level.m_paths.push_back(path);
		level.send(path);
		level.current = path.m_position;
	}
	
	const YAML::Node& pathNodeTwo = levelNode["pathsTwo"].as<YAML::Node>();
	for (unsigned i = 0; i < pathNodeTwo.size(); ++i)
	{

		PathData path;
		pathNodeTwo[i] >> path;
		level.m_pathsTwo.push_back(path);
		level.send(path);
		level.current = path.m_position;
	}

	const YAML::Node& pathNodeThree = levelNode["pathsThree"].as<YAML::Node>();
	for (unsigned i = 0; i < pathNodeThree.size(); ++i)
	{

		PathData path;
		pathNodeThree[i] >> path;
		level.m_pathsThree.push_back(path);
		level.send(path);
		level.current = path.m_position;
	}

	const YAML::Node& pathNodeFour = levelNode["pathsFour"].as<YAML::Node>();
	for (unsigned i = 0; i < pathNodeFour.size(); ++i)
	{

		PathData path;
		pathNodeFour[i] >> path;
		level.m_pathsFour.push_back(path);
		level.send(path);
		level.current = path.m_position;
	}
}
LevelLoader::LevelLoader()	
{
}

bool LevelLoader::load(int nr, LevelData& level)
{
	std::stringstream ss;
	ss << "./resources/levels/level";
	ss << nr;
	ss << ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(ss.str());
		if (baseNode.IsNull())
		{
			std::string message("file: " + ss.str() + " not found");
			throw std::exception(message.c_str());
		}
		baseNode >> level;
	}
	catch (YAML::ParserException& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	return true;
}

PathData LevelData::send(PathData data)
{
	return data;
}