#pragma once
#include "gui/Sprite.h"
#include "main/DesignBlock/DesignsLayout.h"

namespace kubik
{
	namespace config
	{
		typedef std::shared_ptr<class DesignBlock> DesignBlockRef;

		class DesignBlock: public Sprite
		{
		public:	
			static const int OPEN_EVENT = 0;
			static const int OPENED = 1;
			static const int SCREEN_SAVER_STATE = 2;
			static const int SCREEN_SAVER_OPEN_FOLDER = 3;
			static const int CHANGED_DESIGN = 4;
			static const int OPEN_USE_DESIGN_FOLDER = 5;
			static const int HIDE = 6;		
			static const int HIDED = 7;

			DesignBlock(ConfigSettingsRef configSettings, const ci::Vec2i& position);

			void openButtonHandler(EventGUIRef& event);
			void activateListeners();
			void unActivateListeners();
			void screenSaverStateChanged();
			void screenSaverOpenFolder();
			void changedKubikDesign();
			void openUserDesignFolder();
			void hideHandler();
			void showDesigns(const ci::EaseFn& eFunc, float time);
			void animationFinish();
			void hideDesigns(const ci::EaseFn& eFunc, float time);
			void animationHideFinish();
			virtual void drawLayout();
			void setAlpha(float alpha);

			/////////////////////

			bool getScreenSaverValue() const;
			int getDesignID() const;

			void setOpened(bool value);
			bool getOpened() const;

		private:
			ci::gl::Texture icon;
			ci::ColorA iconColor;
			ci::Vec2f designsLayoutPos;
			ci::Anim<ci::Vec2f> animatePosition;
			bool designOpened;

			TextItem			  titleText, subTitleText;			
			SimpleSpriteButtonRef designBtn;
			DesignsLayoutRef	  designsLayout;

			ci::Anim<float> delayTimer;
			bool opened;
		};		
	}
}