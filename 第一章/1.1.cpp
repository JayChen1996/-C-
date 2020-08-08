#include "stdc++.h"
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

void randomvector(vector<int>& data, int N, int min, int max)
{
	random_device rd;
	while (N--) {
		data.push_back(rd() % (max - min) + min);
	}
}

void qssort(vector<int>& data, int l, int r)
{	// 从大到小排序
	if (l < r) {
		int i = l, j = r, t = data[r];
		while (i < j) {
			while (i < j && data[i] > t)	// 从左往右数
				i++;
			if (i < j)
			{
				data[j] = data[i];
				j--;
			}
			while (i < j && data[j]<t)
				j--;
			if (i < j) {
				data[i] = data[j];
				i++;
			}
		}
		data[i] = t;
		qssort(data, l, i - 1);
		qssort(data, i + 1, r);
	}
}

int qsfind(vector<int>& data, int l, int r, int k)
{
	if (l < r) {
		int i = l, j = r, t = data[r];
		while (i < j) {
			while (i < j && data[i] > t)	// 从左往右数
				i++;
			if (i < j)
			{
				data[j] = data[i];
				j--;
			}
			while (i < j && data[j] < t)	// 从右往左数
				j--;
			if (i < j) {
				data[i] = data[j];
				i++;
			}
		}
		data[i] = t;	// t是第i+1大的数
		if (i+1 == k)
			return t;
		if (i+1 < k)	// 说明k在右边
			return qsfind(data, i + 1, r,k-i-1); // 
		else
			return qsfind(data, l, i - 1, k);
	}
	else {
		return data[l];
	}
}

unsigned int m_sort(vector<int> &data)
{
	milliseconds time;
	auto start = steady_clock::now();
	qssort(data, 0, data.size() - 1);
	auto end = steady_clock::now();
	time = duration_cast<milliseconds>(end - start);
	return time.count();
}

unsigned int m_find(vector<int>& data, int k)
{
	milliseconds time;
	auto start = steady_clock::now();
	int numK = qsfind(data, 0, data.size() - 1, k+1);
	auto end = steady_clock::now();
	time = duration_cast<milliseconds>(end - start);
	return time.count();
}


int main()
{
	random_device rd;
	vector<int> tst;
	// 生成N个随机数

	for (unsigned int i = 1;i <= 10000000;i = i * 10) {
		randomvector(tst, i, 0, 100);

		unsigned int time;
		int k = tst.size() / 2;
		time = m_find(tst, k);
		cout <<"N="<<i<<" "<<"查找时间:" <<time/1000.0<<"秒" << endl;
		tst.clear();
	}

	return 0;
}
