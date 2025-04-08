/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-02-13 ����3:38
@description:
*/
// �����㷨.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#if 1
/*
�Ӽ�������
*/
void func(int arr[], int i, int length, int x[])
{
	if (i == length)   // �ݹ���������� StackOverFlow
	{
		for (int j = 0; j < length; ++j)
		{
			if (x[j] == 1)
			{
				cout << arr[j] << " ";   // 1 2 3
			}
		}
		cout << endl;
	}
	else
	{
		x[i] = 1;   // ѡ��i�ڵ�
		func(arr, i + 1, length, x); // ����i������

		x[i] = 0;  // ��ѡ��i�ڵ�
		func(arr, i + 1, length, x); // ����i���Һ���
	}
}
int main()
{
	int arr[] = { 1,2,3 };   // 1 2 3 12 13 23 ...
	int length = sizeof(arr) / sizeof(arr[0]);
	int x[3] = { 0 };
	func(arr, 0, length, x);
	return 0;
}
#endif

#if 0
/*
����ѡ�����⣺����һ����������������ѡ��һ����������ѡ��������ĺͣ���ʣ�µ������ĺ͵Ĳ���С
*/
int arr[] = { 12,6,7,11,16,3,8 };
const int length = sizeof(arr) / sizeof(arr[0]);
//int x[length] = { 0 };  // �Ӽ�����������  ��¼�ڵ��������ӻ����Һ��ӣ�����i�ڵ㱻ѡ��&δ��ѡ��
//int bestx[length] = { 0 }; // ��¼���Ž�
vector<int> x;
vector<int> bestx;
unsigned int mymin = 0xFFFFFFFF; // ��¼��С�Ĳ�ֵ
int sum = 0; // ��¼��ѡ�Ӽ����ֵ��ܺ�
int r = 0; // ��¼δѡ�����ֵĺ�

// �����Ӽ���
void func(int i)
{
	if (i == length)  // ���ʵ����Ӽ�����һ��Ҷ�ӽڵ�
	{
		// sum
		int result = abs(sum - r);
		if (result < mymin)
		{
			mymin = result;
			// ��Ҫ��¼һ�²�ֵ��С���Ӽ�
			bestx = x;
		}
	}
	else
	{
		r -= arr[i];
		sum += arr[i];
		x.push_back(arr[i]);
		func(i + 1); // ѡ��i�ڵ�
		sum -= arr[i];
		r += arr[i];

		x.pop_back();
		func(i + 1); // ��ѡ��i�ڵ�
	}
}
/*
// �����Ӽ���
void func(int i)
{
	if (i == length)  // ���ʵ����Ӽ�����һ��Ҷ�ӽڵ�
	{
		// sum
		int result = abs(sum - r);
		if (result < min)
		{
			min = result;
			// ��Ҫ��¼һ�²�ֵ��С���Ӽ�
			for (int j = 0; j < length; ++j)
			{
				bestx[j] = x[j];
			}
		}
	}
	else
	{
		r -= arr[i];
		sum += arr[i];
		x[i] = 1;
		func(i + 1); // ѡ��i�ڵ�
		sum -= arr[i];
		r += arr[i];

		x[i] = 0;
		func(i + 1); // ��ѡ��i�ڵ�
	}
}
*/
int main()
{
	for (int v : arr)
	{
		r += v;
	}
	func(0);
	/*for (int i = 0; i < length; ++i)
	{
		if (bestx[i] == 1)
		{
			cout << arr[i] << " ";
		}
	}*/
	for (int v : bestx)
	{
		cout << v << " ";
	}
	cout << endl;
	cout << "min:" << min << endl;
	return 0;
}
#endif

#if 0
/*
����ѡ�����⣺����2n����������������ѡ��n����������ѡ��������ĺͣ���ʣ�µ������ĺ͵Ĳ���С
*/
int arr[] = { 12,6,7,11,16,3,8,4 };
const int length = sizeof(arr) / sizeof(arr[0]);
vector<int> x;  // ��¼�Ӽ���ѡ���Ԫ��
vector<int> bestx; // ��¼���Ž�
int sum = 0; // ��¼�Ӽ�����ѡ���ֵĺ�
int r = 0; // ��¼δѡ�����ֵĺ�
unsigned int minval = 0xFFFFFFFF; // ��¼��С��ֵ
int leftcnt = length; // ��¼δ��������ֵĸ���
int cnt = 0; // ��¼�������Ӽ��ĸ��������ڲ���

void func(int i)
{
	if (i == length)
	{
		// cnt++;
		// �õ��Ӽ�����һ���⣬��Ӧһ��Ҷ�ӽڵ�
		if (x.size() != length / 2)
		{
			return;
		}

		int result = abs(sum - r);
		if (result < minval)
		{
			minval = result;
			bestx = x;
		}
	}
	else
	{
		leftcnt--;   // ��ʾ����i�ڵ㣬��ʾʣ���δ�����Ԫ�صĸ���
		if (x.size() < length / 2) // ������֦������㷨Ч�ʡ�ѡ�����ֵ�ǰ�᣺��δѡ��n������
		{
			sum += arr[i];
			r -= arr[i];
			x.push_back(arr[i]);
			func(i + 1); // ����i�����ӣ���ʾѡ��i��λԪ��
			sum -= arr[i];
			r += arr[i];
			x.pop_back();
		}

		// ��������֦�ɲ����Լ�֦�أ� ��ѡ������ֵĸ��� + δ����ѡ������е����ֵĸ���(i+1,i+2....n) >= n��Ԫ��
		if (x.size() + leftcnt >= length / 2)
		{
			func(i + 1); // ����i���Һ��ӣ���ʾ��ѡ��i��λԪ��
		}

		// ��ǰi�ڵ��Ѵ�����ɣ����ݵ��丸�ڵ���
		leftcnt++;
	}
}
int main()
{
	for (int v : arr)
	{
		r += v;
	}
	func(0);
	for (int v : bestx)
	{
		cout << v << " ";
	}
	cout << endl;
	cout << "min:" << minval << endl;
	cout << "cnt:" << cnt << endl;
	return 0;
}
#endif

#if 0
/*
��ѡ���֣���һ������������ѡ��һ�����֣������ǵĺ͵���ָ����ֵ�����ڽ��ӡ�������ڴ�ӡ
*/
int arr[] = { 4,8,12,16,7,9,3 };
const int length = sizeof(arr) / sizeof(arr[0]);
int number = 18;
vector<int> x; // ��¼ѡ�������
int sum = 0; // ��¼��ѡ�����ֵĺ�
int r = 0; // ��¼δ��������ֵĺ�                            ��Ҫ����δ�����δѡ��
void func(int i)
{
	if (i == length)
	{
		if (sum != number)
		{
			return;
		}
		for (int v : x)
		{
			cout << v << " ";
		}
		cout << endl;
	}
	else
	{
		r -= arr[i]; // ����ǰi�ڵ�
		if (sum + arr[i] <= number)  // ������֦   ��ѡ������ֵĺ�+����Ҫѡ�������
		{
			sum += arr[i];
			x.push_back(arr[i]);
			func(i + 1);
			sum -= arr[i];
			x.pop_back();
		}

		if (sum + r >= number) // ������֦   ��ѡ������ֵĺ�+ʣ��Ŀ��Ա�ѡ������ֵĺ�(i+1,i+2....n)
		{
			func(i + 1);
		}
		r += arr[i];
	}
}
int main()
{
	for (int v : arr)
	{
		r += v;
	}
	func(0);
	return 0;
}
#endif

#if 0
/*
��ѡ���֣���һ������������ѡ��һ�����֣������ǵĺ͵���ָ����ֵ�����ڽ��ӡ�������ڴ�ӡ
*/
int arr[] = { 4,8,12,16,7,9,3,3 };
const int length = sizeof(arr) / sizeof(arr[0]);
int number = 18;
vector<int> vec; // ���ѡ�������
void func(int i, int number)
{
	if (number == 0)
	{
		for (int v : vec)
		{
			cout << v << " ";
		}
		cout << endl;
	}
	else
	{
		// �Ե�ǰ�ڵ㿪ʼ����ʣ��Ԫ�صĺ��ӽڵ�����
		for (int k = i; k < length; ++k)
		{
			if (number >= arr[k]) // ʣ���Ԫ��С��number������ɵ�Ԫ��ֵ��
			{
				vec.push_back(arr[k]);
				// ��ǰ���������һ���ʱ��   arr[k] != arr[k-1]
				// �������ظ�ѡ��Ԫ��
				func(k + 1, number - arr[k]); // �������ӽڵ㣬arr[k]�ĺ��ӽڵ�
				// �����ظ�ѡ��Ԫ��
				//func(k, number - arr[k]);
				vec.pop_back();
			}
		}
	}
}
int main()
{
	func(0, number);
	return 0;
}
#endif

#if 0
/*
0-1�������⣺��һ����Ʒ���������ֱ���:w1,w2,...wn�����ֵ�ֱ���v1,v2,...,vn��������һ����������������C��
����ô����Ʒװ�뱳�����ܹ�ʹ�����ļ�ֵ��󻯣�
*/
int w[] = { 12,5,8,9,6 };  // ��Ʒ������
int v[] = { 9,2,4,7,8 };  // ��Ʒ�ļ�ֵ
const int length = sizeof(w) / sizeof(w[0]);
vector<int> x; // ѡ�����Ʒ
vector<int> bestx; // ��¼����ѡ�����Ʒ
int c = 20; // ����������
int cw = 0; // ��ѡ����Ʒ������
int cv = 0; // ��ѡ����Ʒ�ļ�ֵ
int bestv = 0; // ��¼װ�뱳������Ʒ����ֵ
int r = 0; // δ������Ʒ���ܼ�ֵ

void func(int i)
{
	if (i == length)
	{
		if (bestv < cv)
		{
			bestv = cv;
			bestx = x;
		}
	}
	else
	{
		r -= v[i];
		if (cw + w[i] <= c) // ��ѡ����Ʒ������ + ����ѡ��ĵ�i����Ʒ������
		{
			cw += w[i];
			cv += v[i];
			x.push_back(w[i]);
			func(i + 1);
			cw -= w[i];
			cv -= v[i];
			x.pop_back();
		}

		// bestv   cv + [i+1,i+2.....n]�ܼ�ֵ > bestv
		if (cv + r > bestv)
		{
			func(i + 1);
		}
		r += v[i];
	}
}
int main()
{
	for (int val : v)
	{
		r += val;
	}
	func(0);
	for (int w : bestx)
	{
		cout << w << " ";
	}
	cout << endl;
	cout << "bestv:" << bestv << endl;
	return 0;
}
#endif

#if 0
/*
��ռ�-����������
*/
void swap(int arr[], int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}
void func(int arr[], int i, int length)
{
	if (i == length)
	{
		for (int j = 0; j < length; ++j)
		{
			cout << arr[j] << " ";
		}
		cout << endl;
	}
	else
	{
		// ����i�ڵ�����к��ӽڵ�
		for (int k = i; k < length; ++k)
		{
			swap(arr, i, k);
			func(arr, i + 1, length);
			swap(arr, i, k); // һ��Ҫ�ٽ�������
		}
	}
}
int main()
{
	int arr[] = { 1,2,3,4 };
	int length = sizeof(arr) / sizeof(arr[0]);
	func(arr, 0, length);

	return 0;
}
#endif

#if 0
int cnt = 0; // ͳ��8�ʺ�����д���
void swap(int arr[], int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}
bool judge(int ar[], int i)  // i��ʾ��ǰ���ûʺ����ӵ�λ��
{
	for (int j = 0; j < i; ++j)
	{
		if (i == j || ar[i] == ar[j] || abs(i - j) == abs(ar[i] - ar[j]))
		{
			return false;
		}
	}
	return true;
}
void func(int ar[], int i, int length)
{
	if (i == length)
	{
		cnt++;
		for (int j = 0; j < length; ++j)
		{
			cout << ar[j] << " ";
		}
		cout << endl;
	}
	else
	{
		for (int k = i; k < length; ++k)
		{
			swap(ar, i, k);
			if (judge(ar, i)) // �жϵ�i��λ�õ�Ԫ�أ��Ƿ�����8�ʺ������   0 - i-1
				func(ar, i + 1, length);  // ���ɺ��ӽڵ㣬Ҳ����˵������һϵ�е����з�ʽ
			swap(ar, i, k);
		}
	}
}
int main()
{
	// ��ar������±굱���У��±��Ӧ��Ԫ�ص�ֵ������
	int ar[] = { 1,2,3,4,5,6,7,8 };
	int n = 8;
	func(ar, 0, n);
	cout << "cnt:" << cnt << endl;
	return 0;
}
#endif

#if 0
// ��һ��ʵ��ȫ���еĴ���   ����leetcodeˢ���������
int ar[] = { 1,2,3 };
const int N = 3;
bool state[N]; // ��¼����Ԫ���Ƿ�ѡ���״̬  true��ѡ����  false��δѡ��
vector<int> vec;
void func(int i)
{
	if (i == N)
	{
		for (int v : vec)
		{
			cout << v << " ";
		}
		cout << endl;
	}
	else
	{
		for (int k = 0; k < N; ++k)
		{
			if (!state[k])
			{
				state[k] = true;
				vec.push_back(ar[k]);
				func(i + 1);  // k����ʾ���ǿ�ѡ���Ԫ�ص���ʼ�±�     i����ʾ����
				vec.pop_back();
				state[k] = false;
			}
		}
	}
}
int main()
{
	func(0);
	return 0;
}
#endif