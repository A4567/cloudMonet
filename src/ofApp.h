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
		ofImage img, blackImg, originalImg;
		ofPixels pix, blackPix;
		ofColor colour;

		ofxCvColorImage			colorImg, bgImg;

		ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;

		ofxCvContourFinder 	contourFinder;

		int 				threshold;

		bool				bLearnBakground, b_drawImg;

		//-------------------------------------------------------------------------- GUI 
		ofxPanel			GUI;
		ofxIntSlider		sl_threshold;




};
