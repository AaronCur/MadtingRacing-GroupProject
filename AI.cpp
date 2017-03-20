#include "AI.h"
#include "BTMath.h"
Ai::Ai(Game & game, std::vector<sf::CircleShape> & path) :
	m_game(&game),
	m_nodes(path),
	m_steering(0,0),
	m_rotation(0.0),
	m_position(1400, 430),
	m_position2(1450, 430),
	m_position3(1400, 380),
	m_position4(1450, 380)
{
	if (!m_aiTexture.loadFromFile("./resources/images/CarSprite.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}
	for (int i = 0; i < 4; i++)
	{
		m_aiSprite[i].setTexture(m_aiTexture);
		sf::IntRect carOneRect(15, 13, 73, 129);
		m_aiSprite[i].setTextureRect(carOneRect);
		m_aiSprite[i].setOrigin(carOneRect.width *.5, carOneRect.height * .5);
		m_aiSprite[i].setScale(0.3, 0.3);
	}
	
}
Ai::~Ai()
{
	std::cout << "destructing Help" << std::endl;
}

void Ai::update(sf::Time dt, Xbox360Controller&controller,	Player & player)
{
	sf::Vector2f vectorToNode;
	vectorToNode = seek();
	
	double time = dt.asSeconds();
	
	if (thor::length(vectorToNode) != 0)
	{
		m_steering += thor::unitVector(vectorToNode);
	}
		m_steering = Math::truncate(m_steering, MAX_FORCE);
		m_velocity = Math::truncate(m_velocity + m_steering, MAX_SPEED);
		m_position += m_velocity;
		m_position2 += m_velocity;
		m_position3 += m_velocity;
		m_position4 += m_velocity;

	auto dest = atan2(-1 * m_velocity.y, -1 * m_velocity.x) / thor::Pi * 180 + 180;

	auto currentRotation = m_rotation;
	auto currentRotation2 = m_rotation2;
	auto currentRotation3 = m_rotation3;
	auto currentRotation4 = m_rotation4;

	if (std::round(currentRotation - dest) == 0.0)
	{
		m_steering.x = 0;
		m_steering.y = 0;
	}
	else if ((static_cast<int>(std::round(dest - currentRotation + 360))) % 360 < 180)
	{
		// rotate clockwise
		m_rotation = static_cast<int>((m_rotation)+3) % 360;
	}
	else
	{
		// rotate anti-clockwise
		m_rotation -= 3;
	}
	if (std::round(currentRotation2 - dest) == 0.0)
	{
		m_steering.x = 0;
		m_steering.y = 0;
	}
	else if ((static_cast<int>(std::round(dest - currentRotation2 + 360))) % 360 < 180)
	{
		// rotate clockwise
		m_rotation2 = static_cast<int>((m_rotation2)+1) % 360;
		
	}
	else
	{
		// rotate anti-clockwise
		m_rotation2 -= 1;
	}

	if (std::round(currentRotation3 - dest) == 0.0)
	{
		m_steering.x = 0;
		m_steering.y = 0;
	}
	else if ((static_cast<int>(std::round(dest - currentRotation3 + 360))) % 360 < 180)
	{
		// rotate clockwise
		m_rotation3 = static_cast<int>((m_rotation3)+1) % 360;
	}
	else
	{
		// rotate anti-clockwise
		m_rotation3 -= 1;
	}

	if (std::round(currentRotation4 - dest) == 0.0)
	{
		m_steering.x = 0;
		m_steering.y = 0;
	}
	else if ((static_cast<int>(std::round(dest - currentRotation4 + 360))) % 360 < 180)
	{
		// rotate clockwise
		m_rotation4 = static_cast<int>((m_rotation4) + 1) % 360;
	}
	else
	{
		// rotate anti-clockwise
		m_rotation4 -= 1;
	}
	
	m_speed = thor::length(m_velocity);
	auto speed = m_speed;
	
	m_aiSprite[0].setPosition(m_position);
	m_aiSprite[0].setRotation(m_rotation - 90);
	
	m_aiSprite[1].setPosition(m_position2);
	m_aiSprite[1].setRotation(m_rotation2 - 90);
	
	m_aiSprite[2].setPosition(m_position3);
	m_aiSprite[2].setRotation(m_rotation3 - 90);

	m_aiSprite[3].setPosition(m_position4);
	m_aiSprite[3].setRotation(m_rotation4 - 90);

}

void Ai::render(sf::RenderWindow &window)
{
	for (int i = 0; i < 4; i++)
	{
		window.draw(m_aiSprite[0]);
	}
}
	
sf::Vector2f Ai::seek()
{
	
	sf::Vector2f target;
	target = m_nodes[currentNode].getPosition();
	if (Math::distance(m_position, target) <= 10)
	{
		currentNode += 1;

		if (currentNode >= m_nodes.size()) {
			currentNode = m_nodes.size() - 1;
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