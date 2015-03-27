#pragma once

#include "IScreen.h"
#include "IGame.h"
#include "ServicePopup.h"
#include "preloader/Preloader.h"
#include "gui/Sprite.h"

namespace kubik
{
	class ApplicationView
	{
	public:

		ApplicationView();

		void startLocation(IScreenRef screen);
		void draw();
		void clearLayers();
		void addLayer(SpriteRef layer);
		void removeLayer(SpriteRef layer);

		////////////////////////////////////////////////////////////////////////////
		//
		//				PRELOADER
		//
		////////////////////////////////////////////////////////////////////////////

		void showPreloader();

		////////////////////////////////////////////////////////////////////////////
		//
		//					SERVICE POPUP
		//
		////////////////////////////////////////////////////////////////////////////

		void showServicePopup(KubikException exc);

	private:	
		IScreenRef location;
		ServicePopupRef servicePopup;
		PreloaderRef preloader;	

		std::list<SpriteRef> layers;
	};
}