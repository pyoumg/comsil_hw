#include "Array.h"
template <typename T>
class GrowableArray: public Array<T>{
	public:
		GrowableArray(int);
		~GrowableArray();
		T& operator[](int);
		T operator[] (int)const;
		

};


template <typename T>
GrowableArray<T>::GrowableArray(int size):Array<T>(size) {
	if (size <= 0) {
		cout << "Array size error!" << endl;
	}
	else
	{
		this->data = new T[size];
		this->len = size;
	}


}
template <typename T>
GrowableArray<T>::~GrowableArray() {


}

template <typename T>
T& GrowableArray<T>::operator[](int i) {

	if (i >= 0 && i < this->len) {
		return this->data[i];
	}
	else {
		int l = (this->len) * 2;
		T* n_data = new T[l];
		for (int j = 0; j < this->len; j++) {
			n_data[j] = this->data[j];

		}

		for (int j = this->len; j < l; j++) {
			n_data[j] = 0;


		}
		T* del = this->data;
		this->len = l;
		this->data = n_data;
		delete[] del;
		return this->data[i];


	}
}



