#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	img.load("cloud3.jpg");
vimg.setup(1280, 960);

	pix = img.getPixels();
	blackPix = img.getPixels();
	
	originalImg.setFromPixels(img.getPixels());
	

	colorImg.allocate(img.getWidth(), img.getHeight());
	grayImage.allocate(img.getWidth(), img.getHeight());
	grayBg.allocate(img.getWidth(), img.getHeight());
	grayDiff.allocate(img.getWidth(), img.getHeight());
	
	bLearnBakground = true;
	threshold = 200;
	b_drawImg = true;


for (int i = 0; i < pix.getWidth(); i++) {
		for (int j = 0; j < pix.getHeight(); j++) {
			colour = pix.getColor(i, j);
			ofColor white(200, 200, 200);
			if ((colour.r < (colour.b - (colour.b / 3))) && (colour.g < (colour.b - (colour.b / 3))) && (colour.b < white.b)) {
				pix.setColor(i, j, ofColor(0, 0, 0));
			}
			else {
				//pix.setColor(i, j, ofColor(255, 255, 255));
			}
			blackPix.setColor(i, j, ofColor(0, 0, 0));
		}
	}
	img.setFromPixels(pix);
	blackImg.setFromPixels(blackPix);

}

//--------------------------------------------------------------
void ofApp::update(){
	

	bool bNewFrame = false;


	vimg.update();
	bNewFrame = vimg.isFrameNew();
	//if (bNewFrame) {


		colorImg.setFromPixels(img.getPixels());
		bgImg.setFromPixels(blackImg.getPixels());

		grayImage = colorImg;
		if (bLearnBakground == true) {
			grayImage = bgImg;
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (img.getWidth() * img.getHeight()) / 2, 99, true);	// find holes
	//}
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (b_drawImg) {
originalImg.draw(0, 0);
	}
	
	

	for (int i = 0; i < contourFinder.nBlobs; i++) {
		//contourFinder.blobs[i].draw(0, 0);
		ofSetColor(0);
		ofSetLineWidth(5);
		ofPolyline line;
		for (int k = 0; k < contourFinder.blobs[i].pts.size(); k++) {
			line.curveTo(contourFinder.blobs[i].pts[k]);
		}
		line.close();
	line.draw();
	}
	
	// finally, a report:
	ofSetHexColor(0xffffff);
	stringstream reportStr;
	reportStr << "bg subtraction and blob detection" << endl
		<< "press ' ' to capture bg" << endl
		<< "threshold " << threshold << " (press: +/-)" << endl
		<< "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate();
	ofDrawBitmapString(reportStr.str(), 20, 600);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case ' ':
		bLearnBakground = true;
		b_drawImg = !b_drawImg;
		break;
	case '=':
		threshold++;
		if (threshold > 255) threshold = 255;
		break;
	case '-':
		threshold--;
		if (threshold < 0) threshold = 0;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
