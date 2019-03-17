#pragma once
#include <functional>
#include <list>

//*高效排序算法
//希尔排序
template<typename T>
void ShellSort(T data[], int arrSize) {
	register int i, j, hCnt, h;
	int increments[20], k;
	//确定增量值
	for (h = 1, i = 0; h < arrSize; ++i) {
		increments[i] = h;
		h = 3 * h + 1;
	}
	//当ht+2>=n时，就应该停止得ht;
	//上面的for循环多算了一步。
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
//堆排序
template<typename T>
void moveDown(T data[], int parent, int size) {//以data[parent]为树根的子树
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
	for (i = size / 2 - 1; i >= 0; --i)//创建一个堆
		moveDown(data, i, size - 1);
	for (i = size - 1; i >= 1; --i) {
		std::swap(data[0], data[i]);//将最大数放到data[i]
		moveDown(data, 0, i - 1);//并将剩下的数重建成堆
	}
}
//快速排序
template<typename T>
void quicksort(T data[], int first, int last) {          //实现方法一
	int lower = first + 1, upper = last;
	std::swap(data[first], data[(first + last) / 2]);    //将数组中间的数放到最前
	T bound = data[first];                                       //并将其设为边界
	while (lower <= upper) {
		while (data[lower] < bound)                        //找出左边比边界大的
			++lower;
		while (bound < data[upper])                        //找出右边比边界小的
			--upper;
		if (lower < upper)
			std::swap(data[lower + +], data[upper--]);//将左大右小的位置对换
		else
			++lower;
	}
	std::swap(data[upper], data[first]);
	if (first < upper - 1)
		quicksort(data, first, upper - 1);                    //递归左子数组
	if (upper + 1 < last)
		quicksort(data, upper + 1, last);                    //递归右子数组
}
template<typename T>
void quicksort(T data[], int n) {        //实现方法二
	int i, max;
	if (n < 2)
		return;
	for (i = 1, max = 0; i < n; i++)      //找到最大的元素并放置在数组最后
		if (data[max] < data[i])
			max = i;
	std::swap(data[n - 1], data[max]);//现在最大数在数组最后
	quicksort(data, 0, n - 2);               //除去最大数，剩下的子数组进入递归
}
//归并排序
template<typename T>
void merge(T array1[], T temp[], int first, int last) {
	int mid = (first + last) / 2;
	int i1 = 0, i2 = first, i3 = mid + 1;
	while (i2 <= mid && i3 <= last)
		if (array1[i2] < array1[i3])
			temp[i1++] = array1[i2++];
		else temp[i1++] = array1[i3++];//将较小数放入temp[]，无序且未必是数组中较小数
		while (i2 <= mid)                    
			temp[i1++] = array1[i2++];   //把剩下的装进去
		while (i3 <= last)
			temp[i1++] = array1[i3++];
		for (i1 = 0, i2 = first; i2 <= last; array1[i2++] = temp[i1++]);//将temp还给array
		return;
}
template<typename T>
void mergesort(T data[], T temp[], int first, int last) {
	if (first < last) {//递归条件
		int mid = (first + last) / 2;
		mergesort(data, temp, first, mid);
		mergesort(data, temp, mid + 1, last);
		merge(data, temp, first, last);
	}
	return;//条件不符，结束递归
}
template<typename T>
void mergesort(T data[], const int n) {
	T *temp = new T[n];
	mergesort(data, temp, 0, n - 1);
	return;
}
//基数排序
const int radix = 10;           //基数
const int digits = 10;          //数字的最大位数
void radixsort(long data[], int n) {
	register int i, j, k, factor;//i是位数循环辅助，j是数组元素循环辅助，k是排序结果插入位置的数组下标，factor是被除数用于取元素每个位数上的值
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
//！！！不太懂！！！基数排序二
const int bits = 31;                                                                //最大可容纳位数
void bitRadixsort(long data[], const int n, int b) {               //数组地址，数组长度，最大数二进制位数
	int pow2b = 1; 
	pow2b <<= b;                                                                   //所需队列数量
	int i, j, k, pos = 0, mask = pow2b - 1;                               //0-b-1位全置1，b位置0
	int last = (bits % b == 0) ? (bits / b) : (bits / b + 1);          //循环次数？为什么
	std::list<long> *queues = new std::list<long>[pow2b];   //queue指向长度为pow2b，元素类型为list<list>的数组
	for (i = 0; i < last; i++) {
		for (j = 0; j < n; j++)
			queues[data[j] & mask>> pos].push_front(data[j]);//queues下标就是元素本身啊
		mask <<= b;                                                                 //这两句使顺序从大到小排
		pos = pos + b;                                                              //有没有pos结果都一样
		for (j = k = 0; j < pow2b; j++)
			while (!queues[j].empty()){
				data[k++] = queues[j].front();
				queues[j].pop_front();
			}			
	}
}
//基数排序三
void inline clear(long& q) {q = -1;}
int inline isEmpty(long q) {return q == -1;}//返回0或1；
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
	long* queue = new long[n], queueHeads[radix], queueTails[radix];//const int radix=10;基数
	p1 = n2.next = &n1;
	p2 = n1.next = &n2;                                                                           //n1,n2首尾相连
	for (d = 0, factor = 1; d < digits; factor *= radix, d++) {                  //const int digits = 10;最大十位数
		for (j = 0; j < radix; j++)
			clear(queueHeads[j]);                                                                //将queueHeads[j]置位
		for (j = 0; j < n; j++) {
			where = (p1->arr[j] / factor) % radix;                                       //提取data[j]某位上的值x
			//std::cout <<where<<' '<< p1->arr[j]<<'\t';
			if (isEmpty(queueHeads[where]))                                            //queueHeads[i]是否为空
				queueTails[where] = queueHeads[where] = j;                     //为空，queueTails[x] = queueHeads[x] 是第一个某数位为x的元素下标
			else {                                           
				queue[queueTails[where]] = j;                                             //不为空，queue存的是某数位同为x的所有下一个元素下标
				queueTails[where] = j;                                                         //且queueTails存的是最后一个某数位为x的元素的下标
			}                                                                                 
		}//std::cout <<std::endl;                                         
		for (j = 0; j < radix; j++)                                                    
			if (!(isEmpty(queueHeads[j])))                                               //如果存在某数位为j 的数
				clear(queue[queueTails[j]]);                                               //将queue[j]中最后一个清空置位;
		for (j = k = 0; j < radix; j++)
			while (!(isEmpty(queueHeads[j]))) {
				p2->arr[k++] = p1->arr[queueHeads[j]];                           //排序，queueHeads[j]是某数位值为j的data元素的下标 n                
				queueHeads[j] = queue[queueHeads[j]];                           //将存入queue中的重复值queue[j']=j存入queueHeads[j]
				//queue[queueHeads]会将下一个下标传给queueHeads,从而完成递推
			}
		p2 = p2->next;
		p1 = p1->next;
		//std::cout << std::endl;
	}
	if (digits % 2 != 0)                                                                         //如果digits是奇数;
		for (d = 0; d < n; d++)
			data[d] = p1->arr[d];
}
//基数排序四
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
	if (last % 2 != 0) //如果         
		for (d = 0; d < n; d++)
			data[d] = n1->arr[d];
}
//计数排序
void countsort(long data[], const long n) {
	long i;
	long largest = data[0];
	long *tmp = new long[n];
	for (i = 1; i < n; ++i)                        //找到最大数
		if (largest < data[i])                     //并且将计数器置位
			largest = data[i];
	unsigned long *count = new unsigned long[largest + 1];
	for (i = 0; i <= largest; ++i)             //记录data[]中的元素
		count[i] = 0;
	for (i = 0; i < n; ++i)                       //出现的次数
		++count[data[i]];                         
	for (i = 1; i <= largest; ++i)             //小于i 的元素个数，其实是tmp数组下标
		count[i] = count[i - 1] + count[i];
	for (i = n - 1; i >= 0; --i) {               //将元素按顺序放入tmp
		tmp[count[data[i]] - 1] = data[i];
		--count[data[i]];
	}
	for (i = 0; i < n; ++i)                       //将tmp还原成data[]
		data[i] = tmp[i];
}
