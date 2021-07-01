#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


		////-------------------------------------------------------------------------- CUSTOM FUNCTIONS START

		void setupGUI();
		
		void loadNewImage(string newImgPath);
		void findContours();
		
		////-------------------------------------------------------------------------- CUSTOM FUNCTIONS END


		//ofPolyline line;

		ofVideoGrabber vimg;
		ofImage img, blackImg, originalImg, eyes;
		ofPixels pix, blackPix;
		ofColor colour;

		ofxCvColorImage			colorImg, bgImg;

		ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;

		ofxCvContourFinder 	contourFinder;

		int 				threshold;
		bool				bLearnBakground, b_drawImg;
		bool				isCamera;
		string				currentImagePath;
		std::vector<ofColor>			blobColour;

		float startTime; // store when we start time timer
		float endTime; // when do want to stop the timer

		bool  bTimerReached; // used as a trigger when we hit the timer

		//-------------------------------------------------------------------------- GUI 
		ofxPanel			GUI;

		ofxIntSlider		sl_threshold;
		ofxIntSlider		sl_smoothness;
		ofxIntSlider		sl_minArea;
		ofxIntSlider		sl_maxArea;
		ofxIntSlider		sl_maxBlobs;
		ofxIntSlider		sl_lineThickness;
		ofxIntSlider		sl_timerSpeed;

		ofxToggle			tg_holes;
		ofxToggle			tg_lines;
		ofxToggle			tg_eyes;
		ofxToggle			tg_timer;







};
