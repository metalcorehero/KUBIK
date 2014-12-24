#pragma once
#include "cinder/app/AppNative.h"
#include "ApplicationModel.h"
#include "MenuButton.h"
#include "Graphics.h"
#include "IGame.h"
#include "Button.h"
#include "PhotoboothSettings.h"
#include "states/PhotoInstruction.h"
#include "states/PhotoFilter.h"
#include "states/PhotoTimer.h"
#include "states/PhotoShooting.h"
#include "states/PhotoSharing.h"
#include "states/PhotoChoosing.h"
#include "states/PhotoTemplate.h"
#include "states/PhotoProcessing.h"
#include "model/PhotoStorage.h"
#include "CameraAdapter.h"

using namespace std;
using namespace ci;
using namespace ci::app;

namespace kubik
{
	class Photobooth:public IGame
	{
	public:	
		Photobooth(ISettingsRef config);
		~Photobooth();

		void update();	
		void draw();	
		void start();
		void create();
		void reset(ISettingsRef config) override;		
		void init(ISettingsRef config) override;

		void addMouseUpListener();
		void removeMouseUpListener();

		connection updateSignal;

	private:		
		ButtonRef closeBtn;

		void setTextures();
		void mouseUp(MouseEvent& event);
		void mouseUpHandler(Button& button);

		connection mouseUpListener, closeBtnListener;	

		PhotoInstructionRef photoInstruction;
		PhotoFilterRef		photoFilter;
		PhotoTimerRef		photoTimer;
		PhotoShootingRef	photoShooting;
		PhotoProcessingRef	photoProcessing;		
		PhotoChoosingRef	photoChoosing;
		PhotoTemplateRef	photoTemplate;
		PhotoSharingRef		photoSharing;

		list<IPhotoboothLocationRef>  locations;
		list<IPhotoboothLocationRef>::iterator currentLocation;

		void nextLocationHandler();
		void initLocations();

		PhotoboothSettingsRef settings;
		PhotoStorageRef photoStorage;
	};
}