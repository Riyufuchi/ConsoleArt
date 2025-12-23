//==============================================================================
// File       : IMultiPage.hpp
// Author     : riyufuchi
// Created on : Nov 16, 2025
// Last edit  : Nov 16, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef IMAGES_IMULTIPAGE_HPP_
#define IMAGES_IMULTIPAGE_HPP_

#include <iostream>

namespace consoleartlib
{
class IMultiPage
{
public:
	IMultiPage() = default;
	virtual ~IMultiPage() = default;
	virtual void selectPage(size_t index) = 0;
	virtual size_t getSelectedPageIndex() const = 0;
	virtual size_t getPageCount() const = 0;
};
}

#endif /* IMAGES_IMULTIPAGE_HPP_ */
