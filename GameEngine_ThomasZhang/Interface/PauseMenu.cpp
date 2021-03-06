#include "PauseMenu.h"
#include "States.h"

PauseMenu::PauseMenu()
{
}

PauseMenu::PauseMenu(sf::RenderWindow* Window)
{
	States::SetPausedState(false);
	initButton();
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Update(sf::Event event, float deltatime, sf::RenderWindow* Window)
{

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			States::SetPausedState(!States::GetPausedState());
		}
	}

	ButtonMap::GetMap()["RESUME"]->update(event, deltatime);
	ButtonMap::GetMap()["LOAD"]->update(event, deltatime);
	ButtonMap::GetMap()["SAVE"]->update(event, deltatime);
	ButtonMap::GetMap()["QUIT"]->update(event, deltatime);

	if (ButtonMap::GetMap()["RESUME"]->bClicked)
	{
		States::SetPausedState(false);
		ButtonMap::GetMap()["RESUME"]->bClicked = false;
	}
	if (ButtonMap::GetMap()["QUIT"]->bClicked)
	{
		quit(Window);
		ButtonMap::GetMap()["QUIT"]->bClicked = false;
	}
}

void PauseMenu::Render(sf::RenderWindow* Window, float deltatime, sf::Vector2f resumePosition)
{
	sf::Font font;
	font.loadFromFile("../Debug/Fonts/arial.ttf");

	sf::Vector2f sizeOffset = sf::Vector2f(
		ButtonMap::GetMap()["RESUME"]->buttonBG.getSize().x / 2,
		ButtonMap::GetMap()["RESUME"]->buttonBG.getSize().y / 2
	);

	ButtonMap::GetMap()["RESUME"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, -80) - sizeOffset);
	ButtonMap::GetMap()["RESUME"]->buttonText.setFont(font);
	ButtonMap::GetMap()["RESUME"]->buttonText.setPosition(ButtonMap::GetMap()["RESUME"]->buttonBG.getPosition());
	ButtonMap::GetMap()["RESUME"]->highlight(Window);
	ButtonMap::GetMap()["RESUME"]->render(Window, deltatime);

	ButtonMap::GetMap()["LOAD"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, -40) - sizeOffset);
	ButtonMap::GetMap()["LOAD"]->buttonText.setFont(font);
	ButtonMap::GetMap()["LOAD"]->buttonText.setPosition(ButtonMap::GetMap()["LOAD"]->buttonBG.getPosition());
	ButtonMap::GetMap()["LOAD"]->highlight(Window);
	ButtonMap::GetMap()["LOAD"]->render(Window, deltatime);

	ButtonMap::GetMap()["SAVE"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, 0) - sizeOffset);
	ButtonMap::GetMap()["SAVE"]->buttonText.setFont(font);
	ButtonMap::GetMap()["SAVE"]->buttonText.setPosition(ButtonMap::GetMap()["SAVE"]->buttonBG.getPosition());
	ButtonMap::GetMap()["SAVE"]->highlight(Window);
	ButtonMap::GetMap()["SAVE"]->render(Window, deltatime);

	ButtonMap::GetMap()["QUIT"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, 40) - sizeOffset);
	ButtonMap::GetMap()["QUIT"]->buttonText.setFont(font);
	ButtonMap::GetMap()["QUIT"]->buttonText.setPosition(ButtonMap::GetMap()["QUIT"]->buttonBG.getPosition());
	ButtonMap::GetMap()["QUIT"]->highlight(Window);
	ButtonMap::GetMap()["QUIT"]->render(Window, deltatime);

	Window->display();
}

void PauseMenu::initButton()
{
	sf::Vector2f size = sf::Vector2f(125, 30);

	ButtonMap::GetMap().insert({
		"RESUME", new Button(size, sf::Color(125, 125, 125), "RESUME GAME")
	});
	ButtonMap::GetMap().insert({
		"LOAD", new Button(size, sf::Color(125, 125, 125), "LOAD TILEMAP")
	});
	ButtonMap::GetMap().insert({
		"SAVE", new Button(size, sf::Color(125, 125, 125), "SAVE TILEMAP")
	});
	ButtonMap::GetMap().insert({
		"QUIT", new Button(size, sf::Color(125, 125, 125), "QUIT GAME")
	});
}

void PauseMenu::quit(sf::Window* Window)
{
	Window->close();

}
