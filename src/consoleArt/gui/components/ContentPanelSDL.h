//==============================================================================
// File       : ContentPanelSDL.h
// Author     : riyufuchi
// Created on : Feb 23, 2025
// Last edit  : Feb 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUI_COMPONENTS_CONTENTPANELSDL_H_
#define CONSOLEART_GUI_COMPONENTS_CONTENTPANELSDL_H_

#include <vector>
#include <map>

#include "../abstract/ComponentSDL.h"

namespace ConsoleArt
{
class ContentPanelSDL: public ComponentSDL
{
private:
	std::map<int, std::vector<ComponentSDL*>> components;
	int padding;
public:
	ContentPanelSDL(int x, int y, int width, int height, int padding);
	~ContentPanelSDL();
	virtual void draw(SDL_Renderer* renderer) override;
	void addComponent(int x, int y, ComponentSDL* component);
	void repose();
	void checkHover(int& x, int& y);
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_GUI_COMPONENTS_CONTENTPANELSDL_H_ */
