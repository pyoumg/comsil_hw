/*

	ofxWinMenu basic example - ofApp.cpp

	Example of using ofxWinMenu addon to create a menu for a Microsoft Windows application.
	
	Copyright (C) 2016-2017 Lynn Jarvis.

	https://github.com/leadedge

	http://www.spout.zeal.co

    =========================================================================
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    =========================================================================

	03.11.16 - minor comment cleanup
	21.02.17 - rebuild for OF 0.9.8

*/
#include "ofApp.h"
#include <iostream>
using namespace std;
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("Maze Example"); // Set the app name on the title bar
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);
	// Get the window size for image loading
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	isdfs = false;
	isOpen = 0;
	// Centre on the screen
	ofSetWindowPosition((ofGetScreenWidth()-windowWidth)/2, (ofGetScreenHeight()-windowHeight)/2);

	// Load a font rather than the default
	myFont.loadFont("verdana.ttf", 12, true, true);

	// Load an image for the example
	//myImage.loadImage("lighthouse.jpg");

	// Window handle used for topmost function
	hWnd = WindowFromDC(wglGetCurrentDC());

	// Disable escape key exit so we can exit fullscreen with Escape (see keyPressed)
	ofSetEscapeQuitsApp(false);

	//
	// Create a menu using ofxWinMenu
	//

	// A new menu object with a pointer to this class
	menu = new ofxWinMenu(this, hWnd);

	// Register an ofApp function that is called when a menu item is selected.
	// The function can be called anything but must exist. 
	// See the example "appMenuFunction".
	menu->CreateMenuFunction(&ofApp::appMenuFunction);

	// Create a window menu
	HMENU hMenu = menu->CreateWindowMenu();

	//
	// Create a "File" popup menu
	//
	HMENU hPopup = menu->AddPopupMenu(hMenu, "File");

	//
	// Add popup items to the File menu
	//

	// Open an maze file
	menu->AddPopupItem(hPopup, "Open", false, false); // Not checked and not auto-checked
	
	// Final File popup menu item is "Exit" - add a separator before it
	menu->AddPopupSeparator(hPopup);
	menu->AddPopupItem(hPopup, "Exit", false, false);

	//
	// View popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "View");

	bShowInfo = true;  // screen info display on
	menu->AddPopupItem(hPopup, "Show DFS",false,false); // Checked
	bTopmost = false; // app is topmost
	menu->AddPopupItem(hPopup, "Show BFS"); // Not checked (default)
	bFullscreen = false; // not fullscreen yet
	menu->AddPopupItem(hPopup, "Full screen", false, false); // Not checked and not auto-check

	//
	// Help popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "Help");
	menu->AddPopupItem(hPopup, "About", false, false); // No auto check

	// Set the menu to the window
	menu->SetWindowMenu();

} // end Setup


//
// Menu function
//
// This function is called by ofxWinMenu when an item is selected.
// The the title and state can be checked for required action.
// 
void ofApp::appMenuFunction(string title, bool bChecked) {

	ofFileDialogResult result;
	string filePath;
	size_t pos;

	//
	// File menu
	//
	if(title == "Open") {
		readFile();
	}
	if(title == "Exit") {
		ofExit(); // Quit the application
	}

	//
	// Window menu
	//
	if(title == "Show DFS") {
		//doTopmost(bChecked); // Use the checked value directly
		  // Flag is used elsewhere in Draw()
		if (isOpen)
		{
			if (DFS()) {
				isdfs = true;
				isbfs = false;
			}
			
			
			bShowInfo = bChecked;
		}
		else
			cout << "you must open file first" << endl;
		
	}

	if(title == "Show BFS") {
		
		

	}

	if(title == "Full screen") {
		bFullscreen = !bFullscreen; // Not auto-checked and also used in the keyPressed function
		doFullScreen(bFullscreen); // But als take action immediately
	}

	//
	// Help menu
	//
	if(title == "About") {
		ofSystemAlertDialog("ofxWinMenu\nbasic example\n\nhttp://spout.zeal.co");
	}

} // end appMenuFunction


//--------------------------------------------------------------
void ofApp::update() {

}


//--------------------------------------------------------------
void ofApp::draw() {

	char str[256];
	//ofBackground(0, 0, 0, 0);
	ofSetColor(100);
	ofSetLineWidth(5);
	int i, j;
	
	// TO DO : DRAW MAZE; 
	// 저장된 자료구조를 이용해 미로를 그린다.
	// add code here
	ofDrawLine(0, 0, (WIDTH-1) * 20, 0);
	ofDrawLine(0, 0, 0, (HEIGHT-1) * 20);
	ofDrawLine(0, (HEIGHT-1) * 20, (WIDTH-1) * 20, (HEIGHT-1) * 20);
	ofDrawLine((WIDTH-1) * 20, 0, (WIDTH-1) * 20, (HEIGHT-1) * 20);//테두리 그리기
	for (int i = 1; i < HEIGHT - 1; i++) {//테두리 제외하고 그리기
		for (int j = 1; j < WIDTH - 1; j++) {//테두리 제외하고 그리기
			if (input[i][j]=='|') {
				
					ofDrawLine(j * 20, (i - 1) * 20, j * 20, (i+1) * 20);
			}
			else if(input[i][j]=='-'){
					ofDrawLine((j-1) * 20, i * 20, (j+1) * 20, i * 20);
			}
			
		}
	}
	if (isdfs)
	{
		ofSetColor(50);
		ofSetLineWidth(5);
		if (isOpen)
			dfsdraw();
		else
			cout << "You must open file first" << endl;
	}
	if (isbfs) {
	
	}
	if(bShowInfo) {
		// Show keyboard duplicates of menu functions
		sprintf(str, " comsil project");
		myFont.drawString(str, 15, ofGetHeight()-20);
	}

} // end Draw


void ofApp::doFullScreen(bool bFull)
{
	// Enter full screen
	if(bFull) {
		// Remove the menu but don't destroy it
		menu->RemoveWindowMenu();
		// hide the cursor
		ofHideCursor();
		// Set full screen
		ofSetFullscreen(true);
	}
	else { 
		// return from full screen
		ofSetFullscreen(false);
		// Restore the menu
		menu->SetWindowMenu();
		// Restore the window size allowing for the menu
		ofSetWindowShape(windowWidth, windowHeight + GetSystemMetrics(SM_CYMENU)); 
		// Centre on the screen
		ofSetWindowPosition((ofGetScreenWidth()-ofGetWidth())/2, (ofGetScreenHeight()-ofGetHeight())/2);
		// Show the cursor again
		ofShowCursor();
		// Restore topmost state
		if(bTopmost) doTopmost(true);
	}

} // end doFullScreen


void ofApp::doTopmost(bool bTop)
{
	if(bTop) {
		// get the current top window for return
		hWndForeground = GetForegroundWindow();
		// Set this window topmost
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
		ShowWindow(hWnd, SW_SHOW);
	}
	else {
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(hWnd, SW_SHOW);
		// Reset the window that was topmost before
		if(GetWindowLong(hWndForeground, GWL_EXSTYLE) & WS_EX_TOPMOST)
			SetWindowPos(hWndForeground, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
		else
			SetWindowPos(hWndForeground, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
	}
} // end doTopmost


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	// Escape key exit has been disabled but it can be checked here
	if(key == VK_ESCAPE) {
		// Disable fullscreen set, otherwise quit the application as usual
		if(bFullscreen) {
			bFullscreen = false;
			doFullScreen(false);
		}
		else {
			ofExit();
		}
	}

	// Remove or show screen info
	if(key == ' ') {
		bShowInfo = !bShowInfo;
		// Update the menu check mark because the item state has been changed here
		menu->SetPopupItem("Show DFS", bShowInfo);
	}

	if(key == 'f') {
		bFullscreen = !bFullscreen;	
		doFullScreen(bFullscreen);
		// Do not check this menu item
		// If there is no menu when you call the SetPopupItem function it will crash
	}

} // end keyPressed

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
bool ofApp::readFile()
{
	node_pointer pNew;
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select .maz file");
	string filePath;
	size_t pos;
	// Check whether the user opened a file
	if (openFileResult.bSuccess) {
		ofLogVerbose("User selected a file");

		//We have a file, check it and process it
		string fileName = openFileResult.getName();
		//string fileName = "maze0.maz";
		printf("file name is %s\n", fileName.c_str());
		filePath = openFileResult.getPath();
		printf("Open\n");
		pos = filePath.find_last_of(".");
		if (pos != string::npos && pos != 0 && filePath.substr(pos + 1) == "maz") {

			ofFile file(fileName);

			if (!file.exists()) {
				cout << "Target file does not exists." << endl;
				return false;
			}
			else {
				cout << "We found the target file." << endl;
				isOpen = 1;
			}

			ofBuffer buffer(file);

			// Input_flag is a variable for indication the type of input.
			// If input_flag is zero, then work of line input is progress.
			// If input_flag is one, then work of dot input is progress.
			int input_flag = 0;

			// Idx is a variable for index of array.
			int idx = 0;

			// Read file line by line
			int cnt = 0;
			
		
			// TO DO
			// .maz 파일을 input으로 받아서 적절히 자료구조에 넣는다
			
			WIDTH = 0, HEIGHT = 0;//초기화
			input = (char**)malloc(sizeof(char*)*MAX_SIZE);//MAX_SIZE:500
			  // Read file line by line
			for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
				string line = *it; //한줄씩 받음
				if (WIDTH == 0) {
					WIDTH = line.size();
				}
				input[HEIGHT] = (char*)malloc(sizeof(char)*WIDTH);
				for (int i = 0; i < WIDTH; i++) {
					input[HEIGHT][i] = line[i];//input에 입력받은것을 저장
				}

				HEIGHT++;
					
			}
			/*이 부분부터 인접리스트로 표현한 그래프 구현*/
			maze_col = (HEIGHT - 1) / 2, maze_row = (WIDTH - 1) / 2;
			graph =(node_pointer*)malloc(sizeof(node)*maze_col*maze_row);
			visited = (int*)malloc(sizeof(int)*maze_col*maze_row);
			init();
			for (int i = 1; i < HEIGHT-1; i++) {
				for (int j = 1; j < WIDTH-1; j++) {
					if (i % 2 == 1 && j % 2 == 0 && input[i][j] == ' ') {
						temp = graph[((i - 1) / 2 )*maze_row+ ((j - 1) / 2)];
						while (temp->link != NULL)
							temp = temp->link;//인접리스트에 연결된 마지막 노드를 찾는다
						pNew =(node_pointer) malloc(sizeof(node));
						temp->link = pNew;
						pNew->link = NULL;
						pNew->vertex = ((i - 1) / 2)*maze_row + ((j - 1) / 2+1);//왼쪽에 있는 노드에 오른쪽에 있는 노드를 연결
						//그 오른쪽에 있는 노드도 연결해야함
						temp = graph[((i - 1) / 2)*maze_row + ((j - 1) / 2)+1];
						while (temp->link != NULL)
							temp = temp->link;//인접리스트에 연결된 마지막 노드를 찾는다
						pNew = (node_pointer)malloc(sizeof(node));
						temp->link = pNew;
						pNew->link = NULL;
						pNew->vertex = ((i - 1) / 2)*maze_row + ((j - 1) / 2);//오른쪽에 있는 노드에 왼쪽에 있는 노드를 연결

					}
					else if (i % 2 == 0 && j % 2 == 1 && input[i][j] == ' ') {
						temp = graph[((i - 1) / 2)*maze_row + ((j - 1) / 2)];
						while (temp->link != NULL)
							temp = temp->link;//인접리스트에 연결된 마지막 노드를 찾는다
						pNew = (node_pointer)malloc(sizeof(node));
						temp->link = pNew;
						pNew->link = NULL;
						pNew->vertex = ((i - 1) / 2+1 )*maze_row + ((j - 1) / 2);//위쪽에 있는 노드에 아래쪽에 있는 노드를 연결
						//그 오른쪽에 있는 노드도 연결해야함
						temp = graph[((i - 1) / 2+1)*maze_row + ((j - 1) / 2)];
						while (temp->link != NULL)
							temp = temp->link;//인접리스트에 연결된 마지막 노드를 찾는다
						pNew = (node_pointer)malloc(sizeof(node));
						temp->link = pNew;
						pNew->link = NULL;
						pNew->vertex = ((i - 1) / 2)*maze_row + ((j - 1) / 2);//아래쪽에 있는 노드에 위쪽에 있는 노드를 연결

					}
				}
			}
		}
		else {
			printf("  Needs a '.maz' extension\n");
			return false;
		}
	}
}
void ofApp::freeMemory() {
	for (int i = 0; i < WIDTH; i++) {
		free(input[i]);
	}
	free(input);

	free(visited);
	for (int i = 0; i < maze_row*maze_col; i++)
		free(graph[i]);
	free(graph);
	free(arraydfs);
	//TO DO
	// malloc한 memory를 free해주는 함수
}

bool ofApp::DFS()//DFS탐색을 하는 함수
{
	_top = NULL;
	//0에서 시작해서 maze_row*maze_col-1을 찾는다
	int target = maze_row * maze_col - 1;
	for (int i = 0; i < maze_row*maze_col; i++) {
		visited[i] = 0;
	}
	//TO DO
	//DFS탐색을 하는 함수 ( 3주차)
	push(0);
	visited[0] = 1;
	k = 0;
	while (_top != NULL) {
		if (_top->vertex == target) {
			return true;
		}
		temp = graph[_top->vertex];
		k = 0;
		for (temp; temp; temp=temp->link) {
			if (visited[temp->vertex] == 0) {
				push(temp->vertex);
				visited[temp->vertex]=1;
				k = 1;
			}
		
		}

		if (k == 0) {
			pop();
		}
		
	}


	return false;
}
void ofApp::dfsdraw()
{
	node_pointer temp2;
	int temp_num = 0;
	temp = _top;
	ofSetColor(0, 100, 0);
	while (temp->link != NULL) {

		if (temp->link->vertex == temp->vertex + maze_row || temp->link->vertex == temp->vertex - maze_row || temp->link->vertex == temp->vertex + 1 || temp->link->vertex == temp->vertex - 1||temp->vertex==temp->link->vertex)
			ofDrawLine(temp->vertex % maze_row * 40 + 20, temp->vertex / maze_row * 40 + 20, temp->link->vertex  % maze_row * 40 + 20, temp->link->vertex / maze_row * 40 + 20);
		else {
			temp2 = temp->link->link;
			temp_num = temp->vertex;
			while (temp2 != NULL&&temp2->vertex!=temp_num+1&&temp2->vertex!=temp_num-1&&temp2->vertex!=temp_num+maze_row&&temp2->vertex!=temp_num-maze_row) {
				temp2 = temp2->link;
			}
			ofDrawLine(temp->vertex % maze_row * 40 + 20, temp->vertex / maze_row * 40 + 20, temp2->vertex  % maze_row * 40 + 20, temp2->vertex / maze_row * 40 + 20);
		}
		temp = temp->link;
	}

	if (iscalculatedfs == 0) {
		
		temp = _top;
		arraydfs = (int*)malloc(sizeof(int)*maze_row*maze_col);
		arraydfs[0] = maze_row * maze_col - 1;
		numdfs++;
	
	while (temp->link != NULL) {
		
		if (temp->link->vertex == temp->vertex + maze_row || temp->link->vertex == temp->vertex - maze_row || temp->link->vertex == temp->vertex + 1 || temp->link->vertex == temp->vertex - 1)
		{
			arraydfs[numdfs] = temp->link->vertex;
			numdfs++;
		}

		temp = temp->link;
	}
	iscalculatedfs = 1;
	}

	ofSetColor(100,0,0);
	for (int i = 0; i < numdfs-1; i++) {
		ofDrawLine(arraydfs[i] % maze_row * 40 + 20, arraydfs[i] / maze_row * 40 + 20, arraydfs[i + 1] % maze_row * 40 + 20, arraydfs[i + 1] / maze_row * 40 + 20);
	}
	//TO DO 
	//DFS를 수행한 결과를 그린다. (3주차 내용)
}


void ofApp::init() {
	for (int i = 0; i < maze_col*maze_row; i++) {
		graph[i] = (node*)malloc(sizeof(node));
		graph[i]->vertex = i;
		graph[i]->link = NULL;
		visited[i] = 0;
	}
}
void ofApp::push(int u) {
	node_pointer pNew = (node_pointer)malloc(sizeof(node));
	pNew->vertex = u;
	if (_top == NULL) {
		_top = pNew;
		pNew->link = NULL;
	}
	else {
		pNew->link = _top;
		_top = pNew;
	}
	
	
}
void ofApp::pop() {
	node_pointer pNew = _top;
	if (_top == NULL) {
		printf("error\n");
		return;
	}
	else {
		_top = _top->link;
	}
	free(pNew);
}
void ofApp::addq(int data) {
	temp = (node_pointer)malloc(sizeof(node));
	temp->vertex = data;
	if (front == NULL) {
		front = temp;
		rear = temp;
		front->link = NULL;
	}
	else {
		temp->link = NULL;
		rear->link = temp;
		rear = temp;
	}
}
int ofApp::deleteq() {
	int data;
	if (front == NULL) {
		printf("Node is NULL\n");
		return 0;
	}
	else {
		temp = front;
		front = front->link;
		data = temp->vertex;
		free(temp);
		return data;
	}
}