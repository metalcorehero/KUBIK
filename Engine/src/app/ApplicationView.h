#pragma once
#include "cinder/app/AppNative.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "TuneUpScreen.h"
#include "IScreen.h"
#include "Preloader.h"
#include "ScreenSaver.h"

using namespace std;
using namespace ci;
using namespace ci::app;

namespace kubik
{
	class ApplicationView
	{
	public:

		void draw();
		void startLocation(IScreen* screen);

	private:	
		IScreen *location;	
	};
}