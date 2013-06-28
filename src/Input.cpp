#include "Input.h"

vec2i mouseDifference;
vec2i mouseLocation;

vec2i getMouseDifference()
{
	return mouseDifference;
}

vec2i getMousePosition()
{
	return mouseLocation;
}

bool isKeyPressed(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}

bool Input::getKeyStatus(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}

vec2i Input::getMouseDifference()
{
	return mouseDifference;
}

vec2i Input::getLocation()
{
	return mouseLocation;
}

void Input::init(sf::Window* window)
{
	this->window = window;
	mouseLocation = vec2i(sf::Mouse::getPosition());
}

void Input::bindKey(void (*callback)(), sf::Keyboard::Key key)
{
	KeyBinding bind;
	bind.callback = callback;
	bind.key = key;

	keyBindings.push_back(bind);
}

void Input::hookMouse(void (*callback)(vec2i), hookType type)
{
	MouseHook hook;
	hook.callback = callback;
	hook.type = type;

	mouseHooks.push_back(hook);
}

void Input::update()
{
	//check if the user has moved the mouse, if so, call all functions with new coordinates
	vec2i newLocation = vec2i(sf::Mouse::getPosition());
	mouseDifference = newLocation - mouseLocation;
	mouseLocation = newLocation;
	
	sf::Event event;
	while (window->pollEvent(event))
	{
		//has mouse moved?

			/*
			for(int i = 0; i < mouseHooks.size(); i++)
			{
				switch(mouseHooks[i].type)
				{
				case location:
					mouseHooks[i].callback(newLocation);
					break;
				case difference:
					mouseHooks[i].callback(mouseLocation - newLocation);
					break;
				}
			}*/

		//has a key been pressed? (
		if(event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{

			for(unsigned int i = 0; i < keyBindings.size(); i++)
			{
				switch(keyBindings[i].type)
				{
				case press:
					if(!keyBindings[i].wasPressed && sf::Keyboard::isKeyPressed(keyBindings[i].key) == true)//callback and set on
					{
						keyBindings[i].wasPressed = true;
						keyBindings[i].callback();
					}
					else if(keyBindings[i].wasPressed && sf::Keyboard::isKeyPressed(keyBindings[i].key) == false)//set off
					{
						keyBindings[i].wasPressed = false;
					}
					break;

				case release:
					if(keyBindings[i].wasPressed && sf::Keyboard::isKeyPressed(keyBindings[i].key) == false)
					{
						keyBindings[i].wasPressed = false;
						keyBindings[i].callback();
					}	
					else if(!keyBindings[i].wasPressed && sf::Keyboard::isKeyPressed(keyBindings[i].key) == true)
					{
						keyBindings[i].wasPressed = false;
					}
					break;

				case both: // aka toggle
					if((!keyBindings[i].wasPressed && sf::Keyboard::isKeyPressed(keyBindings[i].key) == true)  || 
						(keyBindings[i].wasPressed && sf::Keyboard::isKeyPressed(keyBindings[i].key) == false))
					{
						keyBindings[i].wasPressed = !keyBindings[i].wasPressed;
						keyBindings[i].callback();
					}
					break;
					
				case continuously:
					if(sf::Keyboard::isKeyPressed(keyBindings[i].key))
					{
						keyBindings[i].wasPressed = true;
						keyBindings[i].callback();
					}
					else
					{
						keyBindings[i].wasPressed = false;
					}
					break;

				}
			}
		}
	}
}