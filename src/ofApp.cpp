#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	vimg.setup(1280, 960);
	currentImagePath = "clouds3.jpg";
	loadNewImage(currentImagePath);
	



	setupGUI();
	ofFill();
	isCamera = false;

	bTimerReached = false;
	startTime = ofGetElapsedTimeMillis();  // get the start time
	endTime = (int)500; // in milliseconds

	ofSetBackgroundAuto(false);
	

}

//--------------------------------------------------------------
void ofApp::update()
{
	findContours();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	// update the timer this frame
	float timer = ofGetElapsedTimeMillis() - startTime;

	if (tg_timer)
	{
		threshold = (ofGetElapsedTimeMillis() - startTime) / sl_timerSpeed;
		sl_threshold = threshold;

		if (threshold > 255)
		{
			startTime = ofGetElapsedTimeMillis();
			threshold = 0;
		}

		/*threshold = 255 - (ofGetElapsedTimeMillis() / sl_timerSpeed);
		sl_threshold = threshold;

		if (threshold <= 0)
		{
			startTime = 255 - ofGetElapsedTimeMillis();
			threshold = 255;
		}*/
	}



	if (b_drawImg) 
	{
		if (isCamera)
		{
			vimg.draw(0, 0);
		}
		else
		{
			originalImg.draw(0, 0);

		}
	}
		

	
	for (int i = 0; i < contourFinder.nBlobs; i++) 
	{
		//contourFinder.blobs[i].draw(0, 0);
		ofSetColor(0);
		ofSetLineWidth(sl_lineThickness);
		ofPolyline line;


		if (contourFinder.nBlobs > blobColour.size())
		{
			blobColour.push_back(ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
			//blobColour.push_back(ofColor(255, 0, 0 ,130));

		}
		
		if (!tg_lines)
		{
		
			ofSetColor(blobColour[i]);

		}
	

		for (int k = 0; k < contourFinder.blobs[i].pts.size(); k += sl_smoothness)
		{

			line.curveTo(contourFinder.blobs[i].pts[k]);



		}

		line.close();
		line.draw();
		
	
		
		ofBeginShape();
		ofSetColor(blobColour[i]);

		for (int i = 0; i < line.getVertices().size(); i++) 
		{
			ofVertex(line.getVertices().at(i).x, line.getVertices().at(i).y);
		}
		ofEndShape();

		if (tg_eyes)
		{
			if (contourFinder.blobs[i].area > sl_minArea)
			{
				
				ofSetColor(0, 0, 0);
				ofDrawCircle(contourFinder.blobs[i].centroid.x - 30, contourFinder.blobs[i].centroid.y, 20);
				ofDrawCircle(contourFinder.blobs[i].centroid.x + 30, contourFinder.blobs[i].centroid.y, 20);

				ofSetColor(255, 255, 255);
				ofDrawCircle(contourFinder.blobs[i].centroid.x - 30, contourFinder.blobs[i].centroid.y, 15);
				ofDrawCircle(contourFinder.blobs[i].centroid.x + 30, contourFinder.blobs[i].centroid.y, 15);

				ofSetColor(0, 0, 0);

				ofDrawCircle(contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y + 40, 15);

				ofDrawCircle(contourFinder.blobs[i].centroid.x - ofRandom(27, 33), contourFinder.blobs[i].centroid.y, 10);
				ofDrawCircle(contourFinder.blobs[i].centroid.x + ofRandom(27, 33), contourFinder.blobs[i].centroid.y, 10);



			}
		}
		
	}
	
	// finally, a report:
	ofSetHexColor(0xffffff);
	stringstream reportStr;
	reportStr << "bg subtraction and blob detection" << endl
		<< "press ' ' to capture bg" << endl
		<< "threshold " << threshold << " (press: +/-)" << endl
		<< "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate();
	ofDrawBitmapString(reportStr.str(), 20, 600);

	GUI.draw();

	string  info = "FPS:        " + ofToString(ofGetFrameRate(), 0) + "\n";
	info += "Start Time: " + ofToString(startTime, 1) + "\n";
	info += "End Time:   " + ofToString(endTime / 1000.0, 1) + " seconds\n";
	info += "Timer:      " + ofToString(timer / 1000.0, 1) + " seconds\n";
	info += "\nPress ' ' to get a new random end time\n";
	ofDrawBitmapString(info, 20, 400);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key) 
	{
	case ' ':
		bLearnBakground = true;
		b_drawImg = !b_drawImg;
		blobColour.clear();

		break;

	case '=':
		threshold++;
		if (threshold > 255) threshold = 255;
		sl_threshold = threshold;
		break;

	case '-':
		threshold--;
		if (threshold < 0) threshold = 0;
		sl_threshold = threshold;

		break;

	case 't':
		
		isCamera = !isCamera;
		if (isCamera)
		{
			sl_threshold = 40;
			sl_smoothness = 53;
			
		}
		else
		{
			sl_threshold = 200;
			sl_smoothness = 112;
		}
		loadNewImage(currentImagePath);
		
		break;

	case 'l':
		
		if (!isCamera)
		{
			ofFileDialogResult result = ofSystemLoadDialog("Load file");
			if (result.bSuccess)
			{
				currentImagePath = result.getPath();
				loadNewImage(currentImagePath);
				
			}
		}
			
		
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
	img.resize(ofGetWidth(), ofGetHeight());

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//______________________________________________________________ CUSTOM FUNCTIONS

void ofApp::loadNewImage(string newImgPath)
{
	if (!isCamera)
	{
		img.clear();

		img.load(newImgPath);
		img.resize(ofGetWidth(), ofGetHeight());

		pix = img.getPixels();
		blackPix = img.getPixels();
		originalImg.setFromPixels(img.getPixels());

		colorImg.allocate(img.getWidth(), img.getHeight());
		grayImage.allocate(img.getWidth(), img.getHeight());
		grayBg.allocate(img.getWidth(), img.getHeight());
		grayDiff.allocate(img.getWidth(), img.getHeight());
	}
	else
	{
		

		pix = vimg.getPixels();
		blackPix = vimg.getPixels();
		originalImg.setFromPixels(vimg.getPixels());

		colorImg.allocate(vimg.getWidth(), vimg.getHeight());
		grayImage.allocate(vimg.getWidth(), vimg.getHeight());
		grayBg.allocate(vimg.getWidth(), vimg.getHeight());
		grayDiff.allocate(vimg.getWidth(), vimg.getHeight());
	}


	bLearnBakground = true;
	b_drawImg = true;


	for (int i = 0; i < pix.getWidth(); i++) 
	{
		for (int j = 0; j < pix.getHeight(); j++) 
		{
			colour = pix.getColor(i, j);
			ofColor white(200, 200, 200);
			/*
			if ((colour.r < (colour.b - (colour.b / 3))) && (colour.g < (colour.b - (colour.b / 3))) && (colour.b < white.b)) {
				pix.setColor(i, j, ofColor(0, 0, 0));
			}
			

			else 
			{
				//pix.setColor(i, j, ofColor(255, 255, 255));
			}
			*/

			blackPix.setColor(i, j, ofColor(0, 0, 0));
		}
	}

	if (!isCamera)
	{
		img.setFromPixels(pix);
		blackImg.setFromPixels(blackPix);
	}



}

void ofApp::findContours()
{
	threshold = sl_threshold;
	bool bNewFrame = false;


	vimg.update();

	bNewFrame = vimg.isFrameNew();

	if (isCamera)
	{
		if (bNewFrame)
		{

			colorImg.setFromPixels(vimg.getPixels());


			grayImage = colorImg;
			if (bLearnBakground == true) {
				grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
				bLearnBakground = false;
			}

			// take the abs value of the difference between background and incoming and then threshold:
			grayDiff.absDiff(grayBg, grayImage);
			grayDiff.threshold(threshold);

			// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
			// also, find holes is set to true so we will get interior contours as well....
			//contourFinder.findContours(grayDiff, 20, (1280 * 960) / 2, 10, true);	// find holes
		}
			
		
	}
	else
	{
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
		//contourFinder.findContours(grayDiff, 20, (img.getWidth() * img.getHeight()) / 2, 99, true);	// find holes
	}

	contourFinder.findContours(grayDiff, sl_minArea, sl_maxArea, sl_maxBlobs, tg_holes);	// find holes

}

void ofApp::setupGUI()
{
	GUI.setup();
	GUI.add(sl_threshold.setup("Threshold", 70, 0, 255));
	GUI.add(sl_smoothness.setup("Smoothness", 1, 1, 500));
	GUI.add(sl_minArea.setup("Min Area", 20, 0, 10000));
	GUI.add(sl_maxArea.setup("Max Area", 10001, 10001, ofGetWidth() * ofGetHeight()));
	GUI.add(sl_maxBlobs.setup("Max Blobs", 50, 0, 100));
	GUI.add(sl_lineThickness.setup("Line Thickness", 5, 0, 50));
	GUI.add(sl_timerSpeed.setup("Timer Delay (ms)", 250, 1, 250));


	GUI.add(tg_holes.setup("Find Holes?", false));
	GUI.add(tg_lines.setup("Draw Lines?", false));
	GUI.add(tg_eyes.setup("Draw Eyes?", false));
	GUI.add(tg_timer.setup("Use Timer?", false));



}

