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
#include <utility>
#include <unordered_map>

#include "../abstract/ComponentSDL.h"

namespace ConsoleArt
{
class ContentPanelSDL: public ComponentSDL
{
private:
	std::unordered_map<int, std::vector<ComponentSDL*>> componentsAtY;
	std::unordered_map<int, int> widthAtY;
public:
	ContentPanelSDL(int x, int y);
	~ContentPanelSDL();
	virtual void draw(SDL_Renderer* renderer) override;
	void addComponent(int y, ComponentSDL* component);
	void reposeContent();
	void checkHoverOverContent(int& x, int& y);
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUI_COMPONENTS_CONTENTPANELSDL_H_ */
