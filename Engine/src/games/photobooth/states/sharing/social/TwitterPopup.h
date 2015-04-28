#pragma once
#include "Utils.h"
#include "PhotoboothSettings.h"
#include "gui/Sprite.h"
#include "gui/EventGUI.h"
#include "gui/ImageButtonSprite.h"
#include "VirtualKeyboard.h"
#include "states/sharing/social/Popup.h"
#include "services/social/Twitter.h"

namespace kubik
{
	namespace games
	{
		namespace photobooth
		{
			typedef	std::shared_ptr<class TwitterPopup> TwitterPopupRef;

			class TwitterPopup : public Popup
			{	
				void showAnimComplete() override;
				void initVirtualKeyboard() override;
				void keyTouchHandler();		

				kubik::TwitterRef twitter;

			public:				
				TwitterPopup(kubik::config::PhotoboothSettingsRef settings);

				void show() override;
				void hide(EventGUIRef& event) override;
				void draw() override;				
			};
		}
	}
}