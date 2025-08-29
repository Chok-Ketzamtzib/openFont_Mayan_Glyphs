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
		
		// Keep original fonts for UI text
		ofTrueTypeFont	verdana14;
		ofTrueTypeFont	verdana30;
		
		// Since we don't have a TTF Mayan font, we'll use images instead
		vector<ofImage> mayanGlyphs;
		vector<string> glyphNames;
		int currentGlyphIndex;

};

