#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(54, 54, 54, 255);

	//old OF default is 96 - but this results in fonts looking larger than in other programs.
	ofTrueTypeFont::setGlobalDpi(79);

	verdana14.load("verdana.ttf", 14, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);

	verdana30.load("verdana.ttf", 30, true, true);
	verdana30.setLineHeight(34.0f);
	verdana30.setLetterSpacing(1.035);

	// Setup Mayan glyph names (common Mayan day signs and numbers)
	glyphNames = {"Ahau", "Kan", "Muluk", "Ok", "Chuen", "Eb", "Ben", "Ix", "Men", "Cib", "Caban", "Etznab", "Cauac", "Imix"};
	
	// Try to load real Mayan glyph images, fall back to patterns if not found
	mayanGlyphs.resize(glyphNames.size());
	
	for(int i = 0; i < glyphNames.size(); i++){
		string filename = "mayan_glyphs/" + ofToLower(glyphNames[i]) + ".jpeg";
		
		// Try to load the real Mayan glyph image
		if(mayanGlyphs[i].load(filename)){
			ofLogNotice() << "Loaded real Mayan glyph: " << filename;
		} else {
			// Fall back to creating beautiful geometric patterns
			ofLogNotice() << "Creating pattern for: " << glyphNames[i] << " (image not found: " << filename << ")";
			
			// Create a colored glyph image
			mayanGlyphs[i].allocate(64, 64, OF_IMAGE_COLOR);
			
			// Fill with different colors for each glyph
			ofColor glyphColor;
			glyphColor.setHsb((i * 25) % 255, 200, 255);
			
			ofPixels& pixels = mayanGlyphs[i].getPixels();
			for(int y = 0; y < 64; y++){
				for(int x = 0; x < 64; x++){
					// Create unique geometric patterns inspired by Mayan art
					bool isPattern = ((x + y + i*10) % 20 < 10) || ((x - y + i*5) % 15 < 7);
					if(isPattern){
						pixels.setColor(x, y, glyphColor);
					} else {
						pixels.setColor(x, y, ofColor::black);
					}
				}
			}
			mayanGlyphs[i].update();
		}
	}

	currentGlyphIndex = 0;
	bFirst = true;
	typeStr = "Press SPACE to see Mayan glyphs";
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(225);
	verdana14.drawString("Mayan Hieroglyphs Example - press SPACE to cycle glyphs", 30, 35);

	ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate()), 10, 10);

	verdana14.drawString("Current glyph: " + glyphNames[currentGlyphIndex], 30, 55);

	// Draw current glyph at different sizes
	ofSetColor(255);
	
	// Small glyph
	mayanGlyphs[currentGlyphIndex].draw(30, 90, 32, 32);
	verdana14.drawString("32x32", 70, 135);
	
	// Medium glyph  
	mayanGlyphs[currentGlyphIndex].draw(150, 90, 64, 64);
	verdana14.drawString("64x64", 190, 170);
	
	// Large glyph
	mayanGlyphs[currentGlyphIndex].draw(300, 90, 128, 128);
	verdana14.drawString("128x128", 340, 235);

	ofSetColor(29,29,29);
	ofDrawLine(30, 250, ofGetWidth()-4, 250);

	// Draw all glyphs in a grid
	ofSetColor(225);
	verdana14.drawString("All Mayan Day Signs:", 30, 275);
	
	int cols = 7;
	for(int i = 0; i < mayanGlyphs.size(); i++){
		int x = 30 + (i % cols) * 80;
		int y = 300 + (i / cols) * 100;
		
		ofSetColor(255);
		mayanGlyphs[i].draw(x, y, 48, 48);
		
		ofSetColor(180);
		verdana14.drawString(glyphNames[i], x, y + 65);
	}

	ofSetColor(29,29,29);
	ofDrawLine(30, 450, ofGetWidth()-4, 450);

	// Animation examples
	ofSetColor(225);
	verdana14.drawString("ROTATION", 30, 475);
	verdana14.drawString("SCALE", 300, 475);

	// Rotating glyph
	ofPushMatrix();
		ofTranslate(110, 520);
		ofRotateZDeg(ofGetElapsedTimef() * -30.0);
		ofSetColor(255, 200, 100);
		mayanGlyphs[currentGlyphIndex].draw(-32, -32, 64, 64);
	ofPopMatrix();

	// Scaling glyph
	ofPushMatrix();
		ofTranslate(380, 520);
		float scale = 1.0 + 0.5 * sin(ofGetElapsedTimef() * 2.0);
		ofScale(scale, scale);
		ofSetColor(100, 255, 200);
		mayanGlyphs[currentGlyphIndex].draw(-32, -32, 64, 64);
	ofPopMatrix();

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if(key == ' '){
		// Cycle through Mayan glyphs
		currentGlyphIndex = (currentGlyphIndex + 1) % mayanGlyphs.size();
	}
	else if(key == OF_KEY_RIGHT){
		currentGlyphIndex = (currentGlyphIndex + 1) % mayanGlyphs.size();
	}
	else if(key == OF_KEY_LEFT){
		currentGlyphIndex = (currentGlyphIndex - 1 + mayanGlyphs.size()) % mayanGlyphs.size();
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
