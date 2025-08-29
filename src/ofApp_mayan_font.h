#pragma once

#include "ofMain.h"

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
		
		bool bFirst;
		string typeStr;
		
		// Mayan hieroglyph fonts
		ofTrueTypeFont  mayaFont14;
		ofTrueTypeFont	mayaFont30;
		ofTrueTypeFont  mayaFont14A; // aliased version
		
		// Store some common Mayan glyphs/words
		vector<string> mayanGlyphs;
		int currentGlyphIndex;

};
