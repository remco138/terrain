#ifndef INPUT_H
#define INPUT_H

#include <SFML/Window/Event.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include "shapes/vec.h"


enum bindType//Keyboard
{
	press,
	release,
	both, //aka toggle
	continuously
};

enum hookType
{
	location,
	difference
};


struct KeyBinding
{
	void (*callback)();
	sf::Keyboard::Key key;
	bindType type;
	bool wasPressed;
};

struct MouseHook
{
	void (*callback)(vec2i);
	hookType type;
	//more to come
};


vec2i getMouseDifference();
vec2i getMousePosition();

bool isKeyPressed(sf::Keyboard::Key key);

class Input
{
public:
	vec2i getLocation();

	void bindKey(void (*callback)(), sf::Keyboard::Key key);
	void Input::hookMouse(void (*callback)(vec2i), hookType type);
	//more binding options?

	bool getKeyStatus(sf::Keyboard::Key key);
	vec2i getMouseDifference();

	Input() {}

	void init(sf::Window* window);
	void update();
protected:
	std::vector<KeyBinding> keyBindings; 
	std::vector<MouseHook> mouseHooks;
	//vec2i mouseLocation;
	//vec2i mouseDifference;

	sf::Window* window;
};

#endif
