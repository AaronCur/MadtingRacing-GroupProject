#include "AI.h"
#include "BTMath.h"
/// <summary>
/// James Condon
/// c00207200
/// Time Taken 
/// 9:00 - 5:00 16/03/17
/// 9:00 - 5:00 20/03/17
/// 9:00 - 5:00 21/03/17
/// 9:00 - 12:00 23/03/17
/// 
/// This is where all the AI for the game is handled 
/// </summary>
/// <param name="game"></param>
/// <param name="path"></param>
Ai::Ai(Game & game, std::vector<sf::CircleShape> & path, std::vector<sf::CircleShape> & pathTwo,
	std::vector<sf::CircleShape> & pathThree, std::vector<sf::CircleShape> & pathFour) :
	m_game(&game),
	m_nodes(path),
	m_nodesTwo(pathTwo),
	m_nodesThree(pathThree),
	m_nodesFour(pathFour),
	m_steering(0, 0),
	m_steeringTwo(0, 0),
	m_position(1435, 411),
	m_position2(1460, 435),
	m_position3(1445, 465),
	m_position4(1390, 430)
{
	if (!m_aiTexture.loadFromFile("./resources/images/CarSprite.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}

	if (!m_font.loadFromFile("./resources/images/Adventure.otf"))
	{
		std::cout << "problem loading font" << std::endl;
	}

	firstText.setFont(m_font);
	firstText.setColor(sf::Color(0, 0, 0, 0));
	firstText.setStyle(sf::Text::Bold);
	firstText.setCharacterSize(22);

	//sets all the sprite texture rectangles
	m_aiSprite[0].setTexture(m_aiTexture);
	sf::IntRect carOneRect(35, 30, 178, 313);
	m_aiSprite[0].setTextureRect(carOneRect);
	m_aiSprite[0].setOrigin(carOneRect.width *.5, carOneRect.height * .5);
	m_aiSprite[0].setScale(0.13, 0.13);
	m_aiSprite[1].setTexture(m_aiTexture);
	sf::IntRect carTwoRect(399, 30, 176, 316);
	m_aiSprite[1].setTextureRect(carTwoRect);
	m_aiSprite[1].setOrigin(carOneRect.width *.5, carOneRect.height * .5);
	m_aiSprite[1].setScale(0.13, 0.13);
	m_aiSprite[2].setTexture(m_aiTexture);
	sf::IntRect carThreeRect(363, 551, 178, 308);
	m_aiSprite[2].setTextureRect(carThreeRect);
	m_aiSprite[2].setOrigin(carOneRect.width *.5, carOneRect.height * .5);
	m_aiSprite[2].setScale(0.13, 0.13);
	m_aiSprite[3].setTexture(m_aiTexture);
	sf::IntRect carFourRect(35, 30, 178, 313);
	m_aiSprite[3].setTextureRect(carFourRect);
	m_aiSprite[3].setOrigin(carOneRect.width *.5, carOneRect.height * .5);
	m_aiSprite[3].setScale(0.13, 0.13);


	//calls the random float function
	MAX_SPEED = randomFloat(5.0, 6.0);
	MAX_SPEED2 = randomFloat(5.0, 6.0);
	MAX_SPEED3 = randomFloat(5.0, 6.0);
	MAX_SPEED4 = randomFloat(5.0, 6.0);
}
Ai::~Ai()
{
	std::cout << "destructing Help" << std::endl;
}

void Ai::update(sf::Time dt, Xbox360Controller&controller, Player & player)
{
	if (player.restartAi == true)
	{
		m_position = sf::Vector2f(1435, 411);
		m_position2 = sf::Vector2f(1460, 435);
		m_position3 = sf::Vector2f(1445, 465);
		m_position4 = sf::Vector2f(1390, 430);

		m_aiSprite[0].setRotation(270);
		m_aiSprite[1].setRotation(270);
		m_aiSprite[2].setRotation(270);
		m_aiSprite[3].setRotation(270);

		currentNode = 0;
		currentNodeTwo = 0;
		currentNodeThree = 0;
		currentNodeFour = 0;
		player.restartAi = false;
	}
	double time = dt.asSeconds();
	int count = 0;


	//passes back a random float value so the cars will change speed 
	//after a ce4rtain amount of nodes to allow for realism 
	if (currentNode == 20 || currentNode == 30 || currentNode == 40)
	{
		MAX_SPEED = randomFloat(5.0, 6.0);
	}

	if (currentNodeTwo == 20 || currentNodeTwo == 30 || currentNodeTwo == 40)
	{
		MAX_SPEED2 = randomFloat(5.0, 6.0);
	}

	if (currentNodeThree == 20 || currentNodeThree == 30 || currentNodeThree == 40)
	{
		MAX_SPEED3 = randomFloat(5.0, 6.0);
	}

	if (currentNodeFour == 20 || currentNodeFour == 30 || currentNodeFour == 40)
	{
		MAX_SPEED4 = randomFloat(5.0, 6.0);
	}
	if (player.start)
	{
		sf::Vector2f vectorToNode;
		vectorToNode = seek(dt);

		if (thor::length(vectorToNode) != 0)
		{
			m_steering += thor::unitVector(vectorToNode);
		}
		m_steering = Math::truncate(m_steering, MAX_FORCE);
		m_velocity = Math::truncate(m_velocity + m_steering, MAX_SPEED);
		m_position += m_velocity;

		auto dest = atan2(-1 * m_velocity.y, -1 * m_velocity.x) / thor::Pi * 180 + 180;
		auto currentRotation = m_rotation;

		//first car rotation 
		if (std::round(currentRotation - dest) == 0.0)
		{
			m_steering.x = 0;
			m_steering.y = 0;
		}
		else if ((static_cast<int>(std::round(dest - currentRotation + 360))) % 360 < 180)
		{
			// rotate clockwise
			m_rotation = static_cast<int>((m_rotation)+4) % 360;
		}
		else
		{
			// rotate anti-clockwise
			m_rotation -= 4;
		}

		/***************************************************************************************/

		sf::Vector2f vectorToNodeTwo;
		vectorToNodeTwo = seekTwo(dt);

		if (thor::length(vectorToNodeTwo) != 0)
		{
			m_steeringTwo += thor::unitVector(vectorToNodeTwo);
		}
		m_steeringTwo = Math::truncate(m_steeringTwo, MAX_FORCE);
		m_velocityTwo = Math::truncate(m_velocityTwo + m_steeringTwo, MAX_SPEED2);
		m_position2 += m_velocityTwo;

		auto dest2 = atan2(-1.5 * m_velocityTwo.y, -1.5 * m_velocityTwo.x) / thor::Pi * 180 + 180;
		auto currentRotation2 = m_rotation2;

		//second car rotation
		if (std::round(currentRotation2 - dest2) == 0.0)
		{
			m_steeringTwo.x = 0;
			m_steeringTwo.y = 0;
		}
		else if ((static_cast<int>(std::round(dest2 - currentRotation2 + 360))) % 360 < 180)
		{
			// rotate clockwise
			m_rotation2 = static_cast<int>((m_rotation2)+4) % 360;

		}
		else
		{
			// rotate anti-clockwise
			m_rotation2 -= 4;
		}

		/***************************************************************************************/

		sf::Vector2f vectorToNodeThree;
		vectorToNodeThree = seekThree(dt);

		if (thor::length(vectorToNodeThree) != 0)
		{
			m_steeringThree += thor::unitVector(vectorToNodeThree);
		}
		m_steeringThree = Math::truncate(m_steeringThree, MAX_FORCE);
		m_velocityThree = Math::truncate(m_velocityThree + m_steeringThree, MAX_SPEED3);
		m_position3 += m_velocityThree;

		auto dest3 = atan2(-1.5 * m_velocityThree.y, -1.5 * m_velocityThree.x) / thor::Pi * 180 + 180;
		auto currentRotation3 = m_rotation3;

		//second car rotation
		if (std::round(currentRotation3 - dest3) == 0.0)
		{
			m_steeringThree.x = 0;
			m_steeringThree.y = 0;
		}
		else if ((static_cast<int>(std::round(dest3 - currentRotation3 + 360))) % 360 < 180)
		{
			// rotate clockwise
			m_rotation3 = static_cast<int>((m_rotation3)+4) % 360;

		}
		else
		{
			// rotate anti-clockwise
			m_rotation3 -= 4;
		}

		/***************************************************************************************/

		sf::Vector2f vectorToNodeFour;
		vectorToNodeFour = seekFour(dt);

		if (thor::length(vectorToNodeFour) != 0)
		{
			m_steeringFour += thor::unitVector(vectorToNodeFour);
		}
		m_steeringFour = Math::truncate(m_steeringFour, MAX_FORCE);
		m_velocityFour = Math::truncate(m_velocityFour + m_steeringFour, MAX_SPEED4);
		m_position4 += m_velocityFour;

		auto dest4 = atan2(-1.5 * m_velocityFour.y, -1.5 * m_velocityFour.x) / thor::Pi * 180 + 180;
		auto currentRotation4 = m_rotation4;

		//second car rotation
		if (std::round(currentRotation4 - dest4) == 0.0)
		{
			m_steeringFour.x = 0;
			m_steeringFour.y = 0;
		}
		else if ((static_cast<int>(std::round(dest4 - currentRotation4 + 360))) % 360 < 180)
		{
			// rotate clockwise
			m_rotation4 = static_cast<int>((m_rotation4)+4) % 360;

		}
		else
		{
			// rotate anti-clockwise
			m_rotation4 -= 4;
		}
	}

	//sets all cars positions and their rotations 
	m_aiSprite[0].setPosition(m_position);
	m_aiSprite[0].setRotation(m_rotation - 90);

	m_speed = thor::length(m_velocity);
	auto speed = m_speed;

	m_aiSprite[1].setPosition(m_position2);
	m_aiSprite[1].setRotation(m_rotation2 - 90);

	m_speedTwo = thor::length(m_velocityTwo);
	auto speedTwo = m_speedTwo;

	m_aiSprite[2].setPosition(m_position3);
	m_aiSprite[2].setRotation(m_rotation3 - 90);

	m_speedThree = thor::length(m_velocityThree);
	auto speedThree = m_speedThree;

	m_aiSprite[3].setPosition(m_position4);
	m_aiSprite[3].setRotation(m_rotation4 - 90);

	m_speedFour = thor::length(m_velocityFour);
	auto speedFour = m_speedFour;

	/// <summary>
	/// figures out who is currently coming first in the game 
	/// by using a count and checking all the laps against each other 
	/// using the nodes 
	/// </summary>
	/// <param name="dt"></param>
	/// <param name="controller"></param>
	/// <param name="player"></param>
	if (count1 == 1 || count2 == 1 || count3 == 1 || count4 == 1)
	{
		if (player.firstLap < firstlap1 && player.firstLap < firstLap2 && player.firstLap < firstLap3
			&& player.firstLap < firstLap4)
		{
			first = true;
		}
		else
		{
			first = false;
		}
	}
	if (count1 == 2 || count2 == 2 || count3 == 2 || count4 == 2)
	{
		if (player.firstLap + player.secondLap < firstlap1 && player.firstLap + player.secondLap < firstLap2
			&& player.firstLap + player.secondLap < firstLap3 && player.firstLap + player.secondLap < firstLap4)
		{
			first = true;
		}
		else
		{
			first = false;
		}
	}
	if (count1 == 3 || count2 == 3 || count3 == 3 || count4 == 3)
	{
		if (player.firstLap + player.secondLap + player.thirdLap < firstlap1
			&& player.firstLap + player.secondLap + player.thirdLap < firstLap2
			&& player.firstLap + player.secondLap + player.thirdLap < firstLap3
			&& player.firstLap + player.secondLap + player.thirdLap < firstLap4)
		{
			first = true;
		}
		else
		{
			first = false;
		}
	}

}

void Ai::render(sf::RenderWindow &window)
{
	for (int i = 0; i < 4; i++)
	{
		window.draw(m_aiSprite[i]);
	}
	window.draw(firstText);
}
//seek function to increment the nodes 
//the ai can find the most current node move to it
//creating a vector and returning that vector 
sf::Vector2f Ai::seek(sf::Time deltaTime)
{

	firstTime += deltaTime;
	dt1 = firstTime.asSeconds();

	sf::Vector2f target;
	target = m_nodes[currentNode].getPosition();
	if (Math::distance(m_position, target) <= 15)
	{
		currentNode += 1;

		if (currentNode >= m_nodes.size()) {
			currentNode = 0;
			firstlap1 = dt1;
			count1++;
		}

	}

	if (thor::length(target) != 0)
	{
		return target - m_position;
	}
	else
	{
		return sf::Vector2f();
	}

}

//seek function to increment the nodes 
//the ai can find the most current node move to it
//creating a vector and returning that vector 
sf::Vector2f Ai::seekTwo(sf::Time deltaTime)
{
	secondTime += deltaTime;
	dt2 = secondTime.asSeconds();

	sf::Vector2f target;
	target = m_nodesTwo[currentNodeTwo].getPosition();
	if (Math::distance(m_position2, target) <= 15)
	{
		currentNodeTwo += 1;

		if (currentNodeTwo >= m_nodesTwo.size()) {
			currentNodeTwo = 0;
			firstLap2 = dt2;
			count2++;
		}
	}

	if (thor::length(target) != 0)
	{
		return target - m_position2;
	}
	else
	{
		return sf::Vector2f();
	}

}

//seek function to increment the nodes 
//the ai can find the most current node move to it
//creating a vector and returning that vector 
sf::Vector2f Ai::seekThree(sf::Time deltaTime)
{
	thirdTime += deltaTime;
	dt3 = thirdTime.asSeconds();

	sf::Vector2f target;
	target = m_nodesThree[currentNodeThree].getPosition();
	if (Math::distance(m_position3, target) <= 15)
	{
		currentNodeThree += 1;

		if (currentNodeThree >= m_nodesThree.size()) {
			currentNodeThree = 0;
			firstLap3 = dt3;
			count3++;
		}
	}

	if (thor::length(target) != 0)
	{
		return target - m_position3;
	}
	else
	{
		return sf::Vector2f();
	}

}

//seek function to increment the nodes 
//the ai can find the most current node move to it
//creating a vector and returning that vector 
sf::Vector2f Ai::seekFour(sf::Time deltaTime)
{
	fourthTime += deltaTime;
	dt4 = fourthTime.asSeconds();

	sf::Vector2f target;
	target = m_nodesFour[currentNodeFour].getPosition();
	if (Math::distance(m_position4, target) <= 50)
	{
		currentNodeFour += 1;

		if (currentNodeFour >= m_nodesFour.size()) {
			currentNodeFour = 0;
			firstLap4 = dt4;
			count4++;
		}
	}

	if (thor::length(target) != 0)
	{
		return target - m_position4;
	}
	else
	{
		return sf::Vector2f();
	}

}
/// <summary>
/// random float function allows arandom float to 
/// be passed back 
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
float Ai::randomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
