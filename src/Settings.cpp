#include "settings.h"
#include <iostream>
using namespace std;

Settings* Settings::_pInstance = nullptr;

Settings::Settings() {}

Settings * Settings::getInstance()
{
	if (!_pInstance) {
		_pInstance = new Settings();
	}

	return _pInstance;
}