#include "string1.h"
#include <iostream>
#include <string.h>
using namespace std;

Str::Str(int leng) {
	if (leng < 0) {
		cout << "length error" << endl;
	}
	else {
		str = new char[leng + 1];
		len = leng;
		
	}
}
Str::Str(char *neyong) {
	if (neyong == NULL){
		cout << "neyong is NULL" << endl;
		len = 0;
		str = new char[1];
		str[0] = '\0';
	}
	else {
		str = new char[strlen(neyong) + 1];
		len = strlen(neyong);
		strcpy(str, neyong);
		
	}
}
Str::~Str() {
	delete[]str;
}
int Str::length(void) {
	return len;
}
char* Str::contents()
{
	return str;
}
int Str::compare(class Str& a) {
	return strcmp(str, a.contents());
}
int Str::compare(char* a) {
	return strcmp(str, a);
}
void Str::operator=(char *a) {
if (a == NULL) {
	len = 0;
	delete str;
	str = new char[1];
	str[0] = '\0';
	}
else {
	delete[] str;
	str = new char[strlen(a) + 1];
	len = strlen(a);
	strcpy(str, a);
}
}
void Str::operator=(class Str& a) {
	delete[] str;
	str = new char[a.length() + 1];
	len = a.length();
	strcpy(str, a.contents());
}

