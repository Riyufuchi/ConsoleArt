#ifndef  _CONSOLEUTILITY_H_
#define _CONSOLEUTILITY_H_

#include <string>
#include <iostream>

/* Copyright Header
* Created On: 27.10.2021
* Last Edit: 27.10.2021
* Created By: Riyufuchi
*/

class ConsoleUtility
{
private:

public:
	ConsoleUtility();
  bool repeat();
  void header(std::string);
	~ConsoleUtility();
};
#endif
