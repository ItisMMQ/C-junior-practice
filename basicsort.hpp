#pragma once
#include <functional>
//*ª˘±æ≈≈–ÚÀ„∑®
//≤Â»Î≈≈–Ú
template <typename T>
void insertionsort(T data[], int n) {
	for (int i = 1, j; i < n; i++) {
		T tmp = data[i];
		for (j = i; j > 0 && tmp < data[j - 1]; j--)
			data[j] = data[j - 1];
		data[j] = tmp;
	}
}
//—°‘Ò≈≈–Ú
template<typename T>
void selection(T data[], int n) {
	for (int i = 0, j, least; i < n - 1; ++i) {
		for (j = i + 1, least = i; j < n; ++j)
			if (data[j] < data[least])
				least = j;
		if (i != least)
			std::swap(data[least], data[i]);
	}
}
//√∞≈›≈≈–Ú
template<typename T>
void bubblesort(T data[], int n) {
	for (int i = 0; i < n - 1; ++i) 
		for (int j = n - 1; j > i; --j)
			if (data[j] < data[j - 1])
				std::swap(data[j], data[j - 1]);
}
//∏ƒΩ¯µƒ√∞≈›≈≈–Ú
template<typename T>
void bubblesort2(T data[], int n) {
	bool again = true;
	for (int i = 0; i < n - 1&&again; ++i)
		for (int j = n - 1,again=false; j > i; --j)
			if (data[j] < data[j - 1]){
				std::swap(data[j], data[j - 1]);
				again = true;
			}	
}
// ·≈≈–Ú
template<typename T>
void combsort(T data[], const int n) {
	int step = n, j, k;
	while((step=int(step/1.3))>1)
		for (j = n - 1; j >= step; --j) {
			k = j - step;
			if (data[j] < data[k])
				swap(data[j], data[k]);
		}
	bool again = true;
	for (int i = 0; i < n - 1 && again; ++i)
		for (int j = n - 1, again = false; j > i; --j)
			if (data[j] < data[j - 1]) {
				std::swap(data[j], data[j - 1]);
				again = true;
			}
}