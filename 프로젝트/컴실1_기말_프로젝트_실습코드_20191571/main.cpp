#include "ofMain.h"
#include "ofApp.h"
#include "bst.h"
//========================================================================
int main( ){
	ofSetupOpenGL(1250,780,OF_WINDOW);			// <-------- setup the GL context
	//기존의 값에서 조정했다.(그림 크기에 맞춤)
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());//프로그램 실행

}
