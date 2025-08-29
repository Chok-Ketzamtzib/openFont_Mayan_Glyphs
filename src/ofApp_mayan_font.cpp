#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(54, 54, 54, 255);

	// Set DPI for font rendering
	ofTrueTypeFont::setGlobalDpi(72);

	// Load Mayan hieroglyph font (replace "MayaFont.ttf" with your actual font file)
	mayaFont14.load("MayaFont.ttf", 14, true, true);
	mayaFont14.setLineHeight(20.0f);
	mayaFont14.setLetterSpacing(1.2);

	mayaFont30.load("MayaFont.ttf", 30, true, true);
	mayaFont30.setLineHeight(40.0f);
	mayaFont30.setLetterSpacing(1.2);

	mayaFont14A.load("MayaFont.ttf", 14, false); // aliased version
	mayaFont14A.setLineHeight(20.0f);
	mayaFont14A.setLetterSpacing(1.2);

	// Initialize with some example Mayan glyphs/Unicode characters
	// These are example Unicode points for Mayan hieroglyphs (U+15000-U+1507F)
	// Replace with actual characters from your font
	mayanGlyphs.push_back("𕀀𕀁𕀂𕀃𕀄𕀅"); // Example glyphs
	mayanGlyphs.push_back("𕀆𕀇𕀈𕀉𕀊𕀋");
	mayanGlyphs.push_back("𕀌𕀍𕀎𕀏𕀐𕀑");
	
	// If your font doesn't support Unicode, use regular characters that map to glyphs
	// mayanGlyphs.push_back("ABCDEF"); // These would show as Mayan glyphs in the font
	// mayanGlyphs.push_back("GHIJKL");
	// mayanGlyphs.push_back("MNOPQR");

	currentGlyphIndex = 0;
	bFirst = true;
	typeStr = mayanGlyphs[0];
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(225);
	mayaFont14.drawString("Mayan Hieroglyphs Example - press SPACE to cycle glyphs", 30, 35);

	ofSetColor(245, 58, 135);
	mayaFont14.drawString("anti aliased", 155, 92);
	mayaFont14.drawString("anti aliased", 155, 195);
	mayaFont14A.drawString("aliased", 545, 92);

	ofSetColor(225);
	mayaFont14.drawString("Mayan Font 14pt - ", 30, 92);
	mayaFont14.drawString(typeStr, 30, 111);

	mayaFont14A.drawString("Mayan Font 14pt - ", 422, 92);
	ofDrawRectangle(420, 97, 292, 62);
	ofSetColor(54, 54, 54);
	mayaFont14A.drawString(typeStr, 422, 111);

	ofSetColor(29,29,29);
	ofDrawLine(30, 169, ofGetWidth()-4, 169);

	ofSetColor(225);
	mayaFont14.drawString("Mayan Font 30pt - ", 30, 195);
	mayaFont30.drawString(typeStr, 30, 229);

	ofSetColor(29,29,29);
	ofDrawLine(30, 312, ofGetWidth()-4, 312);

	// Rotation example
	ofSetColor(225);
	mayaFont14.drawString("ROTATION", 30, 445);
	mayaFont14.drawString("SCALE", 422, 445);

	ofPushMatrix();
		string rotText = typeStr.substr(0, 3); // First few glyphs
		ofRectangle bounds = mayaFont30.getStringBoundingBox(rotText, 0, 0);

		ofTranslate(110 + bounds.width/2, 500 + bounds.height / 2, 0);
		ofRotateZDeg(ofGetElapsedTimef() * -30.0);

		mayaFont30.drawString(rotText, -bounds.width/2, bounds.height/2 );
	ofPopMatrix();

	// Scale example
	ofPushMatrix();
		string scaleText = typeStr.substr(0, 4);
		bounds = mayaFont14.getStringBoundingBox(scaleText, 0, 0);

		ofTranslate(500 + bounds.width/2, 480 + bounds.height / 2, 0);
		ofScale(2.0 + sin(ofGetElapsedTimef()), 2.0 + sin(ofGetElapsedTimef()), 1.0);

		mayaFont14.drawString(scaleText, -bounds.width/2, bounds.height/2 );
	ofPopMatrix();

	ofPushMatrix();
		string scaleA = typeStr.substr(0, 4);
		bounds = mayaFont14A.getStringBoundingBox(scaleA, 0, 0);

		ofTranslate(500 + bounds.width/2, 530 + bounds.height / 2, 0);
		ofScale(2.0 + cos(ofGetElapsedTimef()), 2.0 + cos(ofGetElapsedTimef()), 1.0);

		mayaFont14A.drawString(scaleA, -bounds.width/2, bounds.height/2 );
	ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if(key == OF_KEY_DEL || key == OF_KEY_BACKSPACE){
		typeStr = typeStr.substr(0, typeStr.length()-1);
	}
	else if(key == OF_KEY_RETURN ){
		typeStr += "\n";
	}
	else if(key == ' '){
		// Cycle through different Mayan glyph sets
		currentGlyphIndex = (currentGlyphIndex + 1) % mayanGlyphs.size();
		typeStr = mayanGlyphs[currentGlyphIndex];
	}
	else{
		if( bFirst ){
			typeStr.clear();
			bFirst = false;
		}
		ofUTF8Append(typeStr, key);
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
