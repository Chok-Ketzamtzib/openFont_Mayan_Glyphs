#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(54, 54, 54, 255);

	// Load UI font
	uiFont.load("verdana.ttf", 14, true, true);

	// Create vector-based Mayan glyphs
	createMayanGlyphs();

	currentGlyphIndex = 0;
	rotationAngle = 0.0f;
	scaleAmount = 1.0f;
}

//--------------------------------------------------------------
void ofApp::createMayanGlyphs(){
	glyphNames = {"Circular", "Square", "Triangle", "Cross", "Diamond", "Star", "Spiral", "Wave"};
	
	mayanGlyphs.clear();
	mayanGlyphs.resize(glyphNames.size());
	
	// Create sample geometric patterns inspired by Mayan art
	for(int i = 0; i < glyphNames.size(); i++){
		mayanGlyphs[i] = createSampleGlyph(i);
	}
}

//--------------------------------------------------------------
ofPath ofApp::createSampleGlyph(int type){
	ofPath path;
	path.setFilled(true);
	path.setStrokeWidth(2);
	
	switch(type){
		case 0: // Circular glyph
			path.circle(0, 0, 30);
			path.circle(0, 0, 15);
			path.setFillMode(OF_POLY_WINDING_NONZERO);
			break;
			
		case 1: // Square glyph
			path.rectangle(-25, -25, 50, 50);
			path.rectangle(-15, -15, 30, 30);
			path.setFillMode(OF_POLY_WINDING_NONZERO);
			break;
			
		case 2: // Triangle glyph
			path.triangle(0, -30, -25, 20, 25, 20);
			path.triangle(0, -15, -12, 10, 12, 10);
			path.setFillMode(OF_POLY_WINDING_NONZERO);
			break;
			
		case 3: // Cross glyph
			path.rectangle(-30, -5, 60, 10);
			path.rectangle(-5, -30, 10, 60);
			break;
			
		case 4: // Diamond glyph
			path.moveTo(0, -30);
			path.lineTo(30, 0);
			path.lineTo(0, 30);
			path.lineTo(-30, 0);
			path.close();
			
			path.moveTo(0, -15);
			path.lineTo(15, 0);
			path.lineTo(0, 15);
			path.lineTo(-15, 0);
			path.close();
			path.setFillMode(OF_POLY_WINDING_NONZERO);
			break;
			
		case 5: // Star glyph
			{
				int numPoints = 8;
				float outerRadius = 30;
				float innerRadius = 15;
				
				for(int i = 0; i < numPoints * 2; i++){
					float angle = (i * PI) / numPoints;
					float radius = (i % 2 == 0) ? outerRadius : innerRadius;
					float x = cos(angle) * radius;
					float y = sin(angle) * radius;
					
					if(i == 0) path.moveTo(x, y);
					else path.lineTo(x, y);
				}
				path.close();
			}
			break;
			
		case 6: // Spiral glyph
			{
				float maxRadius = 25;
				int numTurns = 3;
				int numPoints = 50;
				
				for(int i = 0; i < numPoints; i++){
					float t = (float)i / (numPoints - 1);
					float angle = t * numTurns * TWO_PI;
					float radius = t * maxRadius;
					float x = cos(angle) * radius;
					float y = sin(angle) * radius;
					
					if(i == 0) path.moveTo(x, y);
					else path.lineTo(x, y);
				}
			}
			break;
			
		case 7: // Wave glyph
			{
				int numWaves = 3;
				int numPoints = 30;
				float amplitude = 15;
				float width = 50;
				
				for(int i = 0; i < numPoints; i++){
					float t = (float)i / (numPoints - 1);
					float x = (t - 0.5) * width;
					float y = sin(t * numWaves * TWO_PI) * amplitude;
					
					if(i == 0) path.moveTo(x, y);
					else path.lineTo(x, y);
				}
			}
			break;
	}
	
	return path;
}

//--------------------------------------------------------------
void ofApp::update(){
	rotationAngle = ofGetElapsedTimef() * 45.0f;
	scaleAmount = 1.0f + 0.3f * sin(ofGetElapsedTimef() * 2.0f);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(225);
	uiFont.drawString("Mayan Vector Glyphs Example - press SPACE to cycle", 30, 35);
	uiFont.drawString("Current glyph: " + glyphNames[currentGlyphIndex], 30, 55);

	if(currentGlyphIndex < mayanGlyphs.size()){
		// Draw static glyph
		ofPushMatrix();
			ofTranslate(100, 150);
			ofSetColor(255);
			mayanGlyphs[currentGlyphIndex].draw();
		ofPopMatrix();
		
		// Draw filled vs outline versions
		ofPushMatrix();
			ofTranslate(250, 150);
			ofSetColor(200, 100, 100);
			ofFill();
			mayanGlyphs[currentGlyphIndex].draw();
		ofPopMatrix();
		
		ofPushMatrix();
			ofTranslate(400, 150);
			ofSetColor(100, 200, 100);
			ofNoFill();
			ofSetLineWidth(2);
			mayanGlyphs[currentGlyphIndex].draw();
		ofPopMatrix();
		
		// Draw rotating glyph
		ofPushMatrix();
			ofTranslate(100, 300);
			ofRotateZDeg(rotationAngle);
			ofSetColor(100, 100, 255);
			ofFill();
			mayanGlyphs[currentGlyphIndex].draw();
		ofPopMatrix();
		
		// Draw scaling glyph
		ofPushMatrix();
			ofTranslate(250, 300);
			ofScale(scaleAmount, scaleAmount);
			ofSetColor(255, 200, 100);
			ofFill();
			mayanGlyphs[currentGlyphIndex].draw();
		ofPopMatrix();
		
		// Draw multiple colors
		ofPushMatrix();
			ofTranslate(400, 300);
			for(int i = 0; i < 3; i++){
				ofPushMatrix();
					ofTranslate(i * 15, i * 15);
					ofSetColor(255 - i * 50, 100 + i * 50, 150 + i * 30, 150);
					ofFill();
					mayanGlyphs[currentGlyphIndex].draw();
				ofPopMatrix();
			}
		ofPopMatrix();
		
		// Draw all glyphs in a row
		ofSetColor(255);
		for(int i = 0; i < mayanGlyphs.size(); i++){
			ofPushMatrix();
				ofTranslate(50 + i * 80, 450);
				ofScale(0.7, 0.7);
				ofFill();
				mayanGlyphs[i].draw();
			ofPopMatrix();
			
			// Draw glyph name
			ofSetColor(180);
			uiFont.drawString(glyphNames[i], 30 + i * 80, 480);
			ofSetColor(255);
		}
	}

	// Instructions
	ofSetColor(225);
	uiFont.drawString("Press SPACE to cycle through glyphs", 30, 520);
	uiFont.drawString("Arrow keys to navigate glyphs", 30, 540);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	if(key == ' '){
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
