#pragma once

#include <iostream>
#include "clsLoginScreen.h"

using namespace std;

class clsStartBank
{

public:

	static void startBank() {

		while (true) {

			if (!clsLoginScreen::ShowLoginScreen() ) {

				break;
			}

		}
	}

};

