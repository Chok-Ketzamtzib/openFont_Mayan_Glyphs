#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(54, 54, 54, 255);

	// Load UI font
	uiFont.load("verdana.ttf", 14, true, true);

	// Load Mayan hieroglyph images
	// Place your Mayan glyph PNG files in bin/data/mayan_glyphs/
	glyphNames = {"ahau", "kan", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib"};
	
	mayanGlyphs.resize(glyphNames.size());
	
	for(int i = 0; i < glyphNames.size(); i++){
		string imagePath = "mayan_glyphs/" + glyphNames[i] + ".png";
		if(mayanGlyphs[i].load(imagePath)){
			ofLogNotice() << "Loaded glyph: " << imagePath;
		} else {
			ofLogError() << "Failed to load glyph: " << imagePath;
			// Create a placeholder rectangle if image fails to load
			mayanGlyphs[i].allocate(64, 64, OF_IMAGE_COLOR);
			mayanGlyphs[i].setColor(ofColor::white);
		}
	}

	currentGlyphIndex = 0;
	glyphSize = 1.0f;
	rotationAngle = 0.0f;
}

//--------------------------------------------------------------
void ofApp::update(){
	rotationAngle = ofGetElapsedTimef() * 30.0f;
	glyphSize = 1.0f + 0.5f * sin(ofGetElapsedTimef() * 2.0f);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(225);
	uiFont.drawString("Mayan Hieroglyphs Example - press SPACE to cycle glyphs", 30, 35);
	uiFont.drawString("Current glyph: " + glyphNames[currentGlyphIndex], 30, 55);

	// Draw multiple sizes of the current glyph
	if(currentGlyphIndex < mayanGlyphs.size()){
		ofImage& currentGlyph = mayanGlyphs[currentGlyphIndex];
		
		// Small size
		ofSetColor(255);
		currentGlyph.draw(30, 100, 32, 32);
		uiFont.drawString("32x32", 70, 120);
		
		// Medium size
		currentGlyph.draw(30, 150, 64, 64);
		uiFont.drawString("64x64", 100, 190);
		
		// Large size
		currentGlyph.draw(30, 230, 128, 128);
		uiFont.drawString("128x128", 170, 290);
		
		// Draw a row of different glyphs
		ofSetColor(255);
		for(int i = 0; i < min(8, (int)mayanGlyphs.size()); i++){
			float x = 300 + i * 70;
			mayanGlyphs[i].draw(x, 100, 48, 48);
			
			// Draw glyph name below
			ofSetColor(180);
			uiFont.drawString(glyphNames[i], x, 160);
			ofSetColor(255);
		}
		
		// Rotating glyph
		ofPushMatrix();
			ofTranslate(400, 250);
			ofRotateZDeg(rotationAngle);
			ofSetColor(255, 200, 100);
			currentGlyph.draw(-32, -32, 64, 64);
		ofPopMatrix();
		
		// Scaling glyph
		ofPushMatrix();
			ofTranslate(550, 250);
			ofScale(glyphSize, glyphSize);
			ofSetColor(100, 255, 200);
			currentGlyph.draw(-32, -32, 64, 64);
		ofPopMatrix();
		
		// Tinted glyphs in different colors
		float y = 350;
		ofColor colors[] = {ofColor::red, ofColor::green, ofColor::blue, ofColor::yellow, ofColor::magenta};
		for(int i = 0; i < 5; i++){
			ofSetColor(colors[i]);
			currentGlyph.draw(30 + i * 80, y, 48, 48);
		}
		
		// Instructions
		ofSetColor(225);
		uiFont.drawString("Press SPACE to cycle through glyphs", 30, y + 80);
		uiFont.drawString("Arrow keys to change current glyph", 30, y + 100);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	if(key == ' '){
		// Cycle through glyphs
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
