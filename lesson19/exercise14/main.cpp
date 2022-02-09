#include "Wampus.h"
#include "Simple_window.h"
#include <Windows.h>
#include <winuser.h>

using namespace Wampus_game;

int main()
try {
	int x_center{ 0 };
	int y_center{ 0 };

	DEVMODEW dispsett;
	dispsett.dmSize = sizeof(DEVMODE);
	dispsett.dmDriverExtra = 0;
	if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dispsett))
	{
		x_center = dispsett.dmPelsWidth / 2;
		y_center = dispsett.dmPelsHeight / 2;
	}

	Main_menu menu({ x_center, y_center });

	return gui_main();
}
catch (shut_off& off) {
	return 1;
}