#pragma once
#include <functional>
#include <list>

//*��Ч�����㷨
//ϣ������
template<typename T>
void ShellSort(T data[], int arrSize) {
	register int i, j, hCnt, h;
	int increments[20], k;
	//ȷ������ֵ
	for (h = 1, i = 0; h < arrSize; ++i) {
		increments[i] = h;
		h = 3 * h + 1;
	}
	//��ht+2>=nʱ����Ӧ��ֹͣ��ht;
	//�����forѭ��������һ����
	for (i-=2; i >= 0; --i) {
		h = increments[i];
		for (hCnt = h; hCnt < 2 * h; ++hCnt) {
			for(j = hCnt; j < arrSize;) {
				T tmp = data[j];
				k = j;
				while (k - h >= 0 && tmp < data[k - h]) {
					data[k] = data[k - h];
					k -= h;
				}
				data[k] = tmp; 
				j += h;
			}
		}
	}
}
//������
template<typename T>
void moveDown(T data[], int parent, int size) {//��data[parent]Ϊ����������
	int child = 2 * parent + 1;
	while (child <= size) {
		if (child<size&&data[child] < data[child + 1])
			++child;
		if (data[parent] < data[child ]) {
			std::swap(data[parent], data[child]);
			parent = child;
			child = 2 *parent + 1;
		}
	else	child= size + 1;
	}
}
template<typename T>
void heapsort(T data[], int size) {
	int i = 0;
	for (i = size / 2 - 1; i >= 0; --i)//����һ����
		moveDown(data, i, size - 1);
	for (i = size - 1; i >= 1; --i) {
		std::swap(data[0], data[i]);//��������ŵ�data[i]
		moveDown(data, 0, i - 1);//����ʣ�µ����ؽ��ɶ�
	}
}
//��������
template<typename T>
void quicksort(T data[], int first, int last) {          //ʵ�ַ���һ
	int lower = first + 1, upper = last;
	std::swap(data[first], data[(first + last) / 2]);    //�������м�����ŵ���ǰ
	T bound = data[first];                                       //��������Ϊ�߽�
	while (lower <= upper) {
		while (data[lower] < bound)                        //�ҳ���߱ȱ߽���
			++lower;
		while (bound < data[upper])                        //�ҳ��ұ߱ȱ߽�С��
			--upper;
		if (lower < upper)
			std::swap(data[lower + +], data[upper--]);//�������С��λ�öԻ�
		else
			++lower;
	}
	std::swap(data[upper], data[first]);
	if (first < upper - 1)
		quicksort(data, first, upper - 1);                    //�ݹ���������
	if (upper + 1 < last)
		quicksort(data, upper + 1, last);                    //�ݹ���������
}
template<typename T>
void quicksort(T data[], int n) {        //ʵ�ַ�����
	int i, max;
	if (n < 2)
		return;
	for (i = 1, max = 0; i < n; i++)      //�ҵ�����Ԫ�ز��������������
		if (data[max] < data[i])
			max = i;
	std::swap(data[n - 1], data[max]);//������������������
	quicksort(data, 0, n - 2);               //��ȥ�������ʣ�µ����������ݹ�
}
//�鲢����
template<typename T>
void merge(T array1[], T temp[], int first, int last) {
	int mid = (first + last) / 2;
	int i1 = 0, i2 = first, i3 = mid + 1;
	while (i2 <= mid && i3 <= last)
		if (array1[i2] < array1[i3])
			temp[i1++] = array1[i2++];
		else temp[i1++] = array1[i3++];//����С������temp[]��������δ���������н�С��
		while (i2 <= mid)                    
			temp[i1++] = array1[i2++];   //��ʣ�µ�װ��ȥ
		while (i3 <= last)
			temp[i1++] = array1[i3++];
		for (i1 = 0, i2 = first; i2 <= last; array1[i2++] = temp[i1++]);//��temp����array
		return;
}
template<typename T>
void mergesort(T data[], T temp[], int first, int last) {
	if (first < last) {//�ݹ�����
		int mid = (first + last) / 2;
		mergesort(data, temp, first, mid);
		mergesort(data, temp, mid + 1, last);
		merge(data, temp, first, last);
	}
	return;//���������������ݹ�
}
template<typename T>
void mergesort(T data[], const int n) {
	T *temp = new T[n];
	mergesort(data, temp, 0, n - 1);
	return;
}
//��������
const int radix = 10;           //����
const int digits = 10;          //���ֵ����λ��
void radixsort(long data[], int n) {
	register int i, j, k, factor;//i��λ��ѭ��������j������Ԫ��ѭ��������k������������λ�õ������±꣬factor�Ǳ���������ȡԪ��ÿ��λ���ϵ�ֵ
	std::list<long> queues[10];
	for (i = 0, factor = 1;i< 10; factor *=10, ++i) {
		for (j = 0; j < n; ++j)
			queues[(data[j] / factor) % 10].push_back(data[j]);
		for (j = k = 0; j <10; ++j)
			while(!queues[j].empty()){
				data[k++] = queues[j].front();
				queues[j].pop_front();
			}
	}
}
//��������̫�����������������
const int bits = 31;                                                                //��������λ��
void bitRadixsort(long data[], const int n, int b) {               //�����ַ�����鳤�ȣ������������λ��
	int pow2b = 1; 
	pow2b <<= b;                                                                   //�����������
	int i, j, k, pos = 0, mask = pow2b - 1;                               //0-b-1λȫ��1��bλ��0
	int last = (bits % b == 0) ? (bits / b) : (bits / b + 1);          //ѭ��������Ϊʲô
	std::list<long> *queues = new std::list<long>[pow2b];   //queueָ�򳤶�Ϊpow2b��Ԫ������Ϊlist<list>������
	for (i = 0; i < last; i++) {
		for (j = 0; j < n; j++)
			queues[data[j] & mask>> pos].push_front(data[j]);//queues�±����Ԫ�ر���
		mask <<= b;                                                                 //������ʹ˳��Ӵ�С��
		pos = pos + b;                                                              //��û��pos�����һ��
		for (j = k = 0; j < pow2b; j++)
			while (!queues[j].empty()){
				data[k++] = queues[j].front();
				queues[j].pop_front();
			}			
	}
}
//����������
void inline clear(long& q) {q = -1;}
int inline isEmpty(long q) {return q == -1;}//����0��1��
template<typename T>
class RadixSortNode {
public:
	T * arr;
	RadixSortNode *next;
};
void radixsort2(long data[], const int n) {
	register int d, j, k, factor, where;
	RadixSortNode<long> n1, n2, *p1, *p2;
	n1.arr = data;
	n2.arr = new long[n];
	for (j = 0; j < n; ++j)
		n2.arr[j] = data[j];                                                                          //n2=n1=data[]?
	long* queue = new long[n], queueHeads[radix], queueTails[radix];//const int radix=10;����
	p1 = n2.next = &n1;
	p2 = n1.next = &n2;                                                                           //n1,n2��β����
	for (d = 0, factor = 1; d < digits; factor *= radix, d++) {                  //const int digits = 10;���ʮλ��
		for (j = 0; j < radix; j++)
			clear(queueHeads[j]);                                                                //��queueHeads[j]��λ
		for (j = 0; j < n; j++) {
			where = (p1->arr[j] / factor) % radix;                                       //��ȡdata[j]ĳλ�ϵ�ֵx
			//std::cout <<where<<' '<< p1->arr[j]<<'\t';
			if (isEmpty(queueHeads[where]))                                            //queueHeads[i]�Ƿ�Ϊ��
				queueTails[where] = queueHeads[where] = j;                     //Ϊ�գ�queueTails[x] = queueHeads[x] �ǵ�һ��ĳ��λΪx��Ԫ���±�
			else {                                           
				queue[queueTails[where]] = j;                                             //��Ϊ�գ�queue�����ĳ��λͬΪx��������һ��Ԫ���±�
				queueTails[where] = j;                                                         //��queueTails��������һ��ĳ��λΪx��Ԫ�ص��±�
			}                                                                                 
		}//std::cout <<std::endl;                                         
		for (j = 0; j < radix; j++)                                                    
			if (!(isEmpty(queueHeads[j])))                                               //�������ĳ��λΪj ����
				clear(queue[queueTails[j]]);                                               //��queue[j]�����һ�������λ;
		for (j = k = 0; j < radix; j++)
			while (!(isEmpty(queueHeads[j]))) {
				p2->arr[k++] = p1->arr[queueHeads[j]];                           //����queueHeads[j]��ĳ��λֵΪj��dataԪ�ص��±� n                
				queueHeads[j] = queue[queueHeads[j]];                           //������queue�е��ظ�ֵqueue[j']=j����queueHeads[j]
				//queue[queueHeads]�Ὣ��һ���±괫��queueHeads,�Ӷ���ɵ���
			}
		p2 = p2->next;
		p1 = p1->next;
		//std::cout << std::endl;
	}
	if (digits % 2 != 0)                                                                         //���digits������;
		for (d = 0; d < n; d++)
			data[d] = p1->arr[d];
}
//����������
class RadixsortNode {
public:
	long *arr;
	RadixsortNode *next;
	RadixsortNode() {next = 0;}
	RadixsortNode(long *a, int n) {
		arr = new long[n];
		for (int i = 0; i < n; i++)
			arr[i] = a[i];
		next = 0;
	}
	RadixsortNode(int n) {
		arr = new long[n];
		next = 0;
	}
};
void bitRadixsort2(long data[], const int n, int b) {
	int pow2b = 1;
	pow2b <<= b;
	int d, j, k, where, pos = 0, mask = pow2b - 1;
	int last = (bits % b == 0) ? (bits / b) : (bits / b + 1);
	long *queues = new long[n], *queueHeads = new long[pow2b];
	long *queueTails = new long[pow2b];
	RadixsortNode *n2 = new RadixsortNode(data, n), *n1 = new RadixsortNode(n);
	n1->arr = data;
	n2->next = n1;
	n1->next = n2;
	for (d = 0; d < last; d++) {
		for (j = 0; j < pow2b; j++)
			clear(queueHeads[j]);
		for (j = 0; j < n; j++) {
			where = (n1->arr[j] & mask) >> pos;
			if (isEmpty(queueHeads[where]))
				queueTails[where] = queueHeads[where] = j;
			else {
				queues[queueTails[where]] = j;
				queueTails[where] = j;
			}
		}
		mask <<= b;
		pos = pos + b;
		for (j = 0; j < pow2b; j++)
			if (!(isEmpty(queueHeads[j])))
				clear(queues[queueTails[j]]);
		for (j = k = 0; j < pow2b; j++)
			while (!(isEmpty(queueHeads[j]))) {
				n2->arr[k++] = n1->arr[queueHeads[j]];
				queueHeads[j] = queues[queueHeads[j]];
			}
		n2 = n2->next;
		n1 = n1->next;
	}
	if (last % 2 != 0) //���         
		for (d = 0; d < n; d++)
			data[d] = n1->arr[d];
}
//��������
void countsort(long data[], const long n) {
	long i;
	long largest = data[0];
	long *tmp = new long[n];
	for (i = 1; i < n; ++i)                        //�ҵ������
		if (largest < data[i])                     //���ҽ���������λ
			largest = data[i];
	unsigned long *count = new unsigned long[largest + 1];
	for (i = 0; i <= largest; ++i)             //��¼data[]�е�Ԫ��
		count[i] = 0;
	for (i = 0; i < n; ++i)                       //���ֵĴ���
		++count[data[i]];                         
	for (i = 1; i <= largest; ++i)             //С��i ��Ԫ�ظ�������ʵ��tmp�����±�
		count[i] = count[i - 1] + count[i];
	for (i = n - 1; i >= 0; --i) {               //��Ԫ�ذ�˳�����tmp
		tmp[count[data[i]] - 1] = data[i];
		--count[data[i]];
	}
	for (i = 0; i < n; ++i)                       //��tmp��ԭ��data[]
		data[i] = tmp[i];
}
