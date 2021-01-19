#include "ofApp.h"
#include "waterObj.h"
int pr = 0;
int *d_x1, *d_y1, *l_x1, *l_x2, *l_y1, *l_y2,index_dot=0,index_line=0,num_line=0; //dot,line 전역변수
int r_x = 0;
waterObj Water(100);

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second
    
    // We still want to draw on a black background, so we need to draw
    // the background before we do anything with the brush
    ofBackground(255,255,255);
    ofSetLineWidth(4);
	
	water_flag = 0;//새로 추가함!
    draw_flag = 0;
    load_flag = 0;
    dot_diameter = 20.0f;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (water_flag == 1) {
		if(Water.y1[Water.numy]<ofGetHeight()-50)
		Water.calculate_water(l_x1, l_x2, l_y1, l_y2, index_line, ofGetHeight() - 50);
		
	}

	
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(127,23,31);  // Set the drawing color to brown
    
    // Draw shapes for ceiling and floor
    ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofSetLineWidth(5);
    
    
    ofSetLineWidth(5);
    if( draw_flag ){
		for (int i = 0; i < index_line; i++) {
			ofDrawLine(l_x1[i], l_y1[i], l_x2[i], l_y2[i]);
		}
		ofSetColor(0);
		for (int i = 0; i < index_dot; i++) {
			if(i!=r_x)
			ofDrawCircle(d_x1[i], d_y1[i], 10);

		}
		ofSetColor(255, 0, 0);//red
		ofDrawCircle(d_x1[r_x], d_y1[r_x], 10);
        /* COMSIL1-TODO 3 : Draw the line segment and dot in which water starts to flow in the screen.
         Note that after drawing line segment and dot, you have to make selected water start dot colored in red.
         */

       
        
        // 2nd week portion.
        ofSetLineWidth(2);
		ofSetColor(0, 0, 255);
		if (water_flag==1) {
			for (int i = 0; i < Water.water_index(); i++) {
				ofDrawLine(Water.x1[i],Water.y1[i],Water.x1[i+1],Water.y1[i+1]);
			}
			
			
		}
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'v') {
        // HACK: only needed on windows, when using ofSetAutoBackground(false)
        glReadBuffer(GL_FRONT);
        ofSaveScreen("savedScreenshot_"+ofGetTimestampString()+".png");
    }
    if (key == 'q'){
        // Reset flags
        draw_flag = 0;
        
        // Free the dynamically allocated memory exits.
		free(d_x1);
		free(d_y1);
		free(l_x1);
		free(l_x2);
		free(l_y1);
		free(l_y2);
        cout << "Dynamically allocated memory has been freed." << endl;
        
        _Exit(0);
    }
    if (key == 'd'){
        if( !load_flag) return;
		draw_flag = 1;
        /* COMSIL1-TODO 2: This is draw control part.
        You should draw only after when the key 'd' has been pressed.
        */
    }
    if (key == 's'){
        // 2nd week portion.
		water_flag = 1;
		pr = 0;
		Water.water_init(d_x1[r_x], d_y1[r_x]);
		update();
    }
    if (key == 'e'){
        // 2nd week portion.
		water_flag = 0;
		pr = 1;
		draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if( key == 'l'){
        // Open the Open File Dialog
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a only txt for Waterfall");
        
        // Check whether the user opened a file
        if( openFileResult.bSuccess){
            ofLogVerbose("User selected a file");
            
            // We have a file, so let's check it and process it
            processOpenFileSelection(openFileResult);
            load_flag = 1;
        }
    }
    
    /* COMSIL1-TODO 4: This is selection dot control part.
     You can select dot in which water starts to flow by left, right direction key (<- , ->).
     */
	if (water_flag != 1) {
		if (key == OF_KEY_RIGHT) {
			if (r_x < index_dot - 1) {
				r_x++;

			}
			else {
				r_x = 0;
			}
			draw();
			cout << "Selcted Dot Coordinate is (" << d_x1[r_x] << ", " << d_y1[r_x] << ")" << endl;
		}
		if (key == OF_KEY_LEFT) {
			if (r_x > 0) {
				r_x--;
			}
			else {
				r_x = index_dot - 1;
			}
			draw();
			cout << "Selcted Dot Coordinate is (" << d_x1[r_x] << ", " << d_y1[r_x] << ")" << endl;
		}
	}
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

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) { 
    //Path to the comma delimited file
    //string fileName = "input.txt";
    
    string fileName = openFileResult.getName();
    ofFile file(fileName);
    
    if( !file.exists()) cout << "Target file does not exists." << endl;
    else cout << "We found the target file." << endl;
    
    ofBuffer buffer(file);
    
    /* This variable is for indicating which type of input is being received.
     IF input_type == 0, then work of getting line input is in progress.
     IF input_type == 1, then work of getting dot input is in progress.
     */
    int input_type = 0;
    
    
    /* COMSIL1-TODO 1 : Below code is for getting the number of line and dot, getting coordinates.
     You must maintain those information. But, currently below code is not complete.
     Also, note that all of coordinate should not be out of screen size.
     However, all of coordinate do not always turn out to be the case.
     So, You have to develop some error handling code that can detect whether coordinate is out of screen size.
    */
    
    
    // Read file line by line
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        
        // Split line into strings
        vector<string> words = ofSplitString(line, " ");
        
        if( words.size() == 1){
            if( input_type == 0){ // Input for the number of lines.
                num_of_line = atoi(words[0].c_str());
				l_x1 = (int*)malloc(sizeof(int)*num_of_line);
				l_x2 = (int*)malloc(sizeof(int)*num_of_line);
				l_y1 = (int*)malloc(sizeof(int)*num_of_line);
				l_y2 = (int*)malloc(sizeof(int)*num_of_line);
                cout << "The number of line is: " << num_of_line << endl;
            }
            else{ // Input for the number of dots.
                num_of_dot = atoi(words[0].c_str());
				d_x1 = (int*)malloc(sizeof(int)*num_of_dot);
				d_y1 = (int*)malloc(sizeof(int)*num_of_dot);
                cout << "The number of dot is: " << num_of_dot << endl;
            }
        }
        else if (words.size() >= 2){
            int x1,y1,x2,y2;
            if( input_type == 0){ // Input for actual information of lines
                x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());
                x2 = atoi(words[2].c_str());
                y2 = atoi(words[3].c_str());
				if (x1 <= 1024 && x2 <= 1024 && y1 <= 768 && y2 <= 768) {
					if (x1 >= 0 && x2 >= 0 && y1 >= 0 && y2 >= 0) {//스크린을 넘지 않음
						l_x1[index_line] = x1, l_x2[index_line] = x2;
						l_y1[index_line] = y1, l_y2[index_line] = y2;
						index_line++;
					}
				}
				num_line++;
				if (num_line == num_of_line) {
					input_type = 1;
				}
				

            }
            else{ // Input for actual information of dots.
                x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());
				if (x1 <= 1024&& y1 <= 768) {
					if (x1 >= 0  && y1 >= 0) {//스크린을 넘지 않음
						d_x1[index_dot] = x1;
						d_y1[index_dot] = y1;
						index_dot++;
					}
				}
            }
        } // End of else if.
    } // End of for-loop (Read file line by line).
	int temp_a = 0;
	for (int i = 0; i < index_dot-1; i++) { //후에 화살표로 고르는 것 때문에 버블소트해두기
		for (int j = i; j < index_dot; j++) {
			if (d_x1[i] > d_x1[j]) {
				temp_a = d_x1[i];
				d_x1[i] = d_x1[j];
				d_x1[j] = temp_a;
				temp_a = d_y1[i];
				d_y1[i] = d_y1[j];
				d_y1[j] = temp_a;
			}
		}
	}
    //initializeWaterLines();
}

void ofApp::initializeWaterLines() {
    ;
}

