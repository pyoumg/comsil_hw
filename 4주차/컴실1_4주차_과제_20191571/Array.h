#ifndef __ARRAY__
#define __ARRAY__
#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T>
class Array{
	protected:
		T *data;
		int len;
	public:
			
			Array(int size);
			~Array();
				
			int length() const;

			T& operator[](int i);
			T operator[](int i)const;

			void print();

};


template <typename T>
Array<T>::Array(int size)
{
	//����� Ȯ���ϰ� ����̸� new�� ����Ͽ� �迭 data�� �Ҵ�, len�� �ʱ�ȭ
	if (size < 0)
	{
		cout << "Array size error!" << endl;
	}
	else
	{
		data = new T[size];
		len = size;
	}
}
template <typename T>
Array<T>::~Array()
{
	delete[] data; // �Ҹ���; �Ҵ�� �޸� ����

}
template <typename T>
int Array<T>::length() const
{
	return len;
	// �迭�� ũ�� ����
}


// �迭�� ���Ҹ� �����ϰų� ���� ��ȯ�ϴ� �κ����� []�������� �����ε��̴�
template <typename T>
T& Array<T>::operator[](int i) // �迭�� ���� ����
{
	static T tmp;

	// �迭�� �ε����� ���� ���� ������ �� ����, �׷��� ������ �����޼��� ����ϰ� tmp����
	if (i >= 0 && i < len)
	{
		return data[i];
	}
	else
	{
		cout << "Array bound error!" << endl;
		return tmp;
	}
}
template <typename T>
T Array<T>::operator[](int i) const // �迭�� ���Ұ� ��ȯ
{
	//�迭�� �ε����� ���� ���� ������ ���� ����, �׷��� ������ �����޼��� ����ϰ� 0�� ����
	if (i >= 0 && i < len)
	{
		return data[i];
	}
	else
	{
		cout << "Array bound error!" << endl;
		return 0;
	}
}
template <typename T>
void Array<T>::print() //�迭�� ��� ������ ������ִ� �Լ�
{
	int i;
	cout << "[";
	for (i = 0; i < len; i++) {
		cout << data[i];
		if (i != len - 1)
			cout << ' ';
	}


	cout << "]" << endl;
}


#endif
