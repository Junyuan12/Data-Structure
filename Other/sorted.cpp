#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

//get max value
int getMaxValue(const vector<int> &arr)
{
    int max = 0;
    for (auto val: arr)
    {
        if (val > max)
        {
            max = val;
        }
    }
    return max;
}

//swap two value
void swapValue(int *pa, int *pb)
{
    int tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}

//print vector
void printArr(vector<int> arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << ", ";
    }
    cout << endl;
}

//冒泡排序
//时间复杂度：O(N^2)，稳定性：稳定
void bubbleSort(vector<int> &arr, int bgn, int end)
{
    bool isLoop = true;
    for (int i = end; true == isLoop && i > bgn; --i)
    {
        isLoop = false;
        for (int j = bgn + 1; j < i; ++j)
        {
            if (arr[j] < arr[j - 1])
            {
                swapValue(&arr[j], &arr[j - 1]);
                isLoop = true;
            }
        }
        cout << "tmpRes: ";
        printArr(arr);
    }
    cout << "FinRes: ";
    printArr(arr);
}

//选择排序
//时间复杂度：O(N^2)，稳定性：不稳定
void selectSort(vector<int> &arr, int bgn, int end)
{
    for (int i = bgn; i < end; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < end; ++j)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            swapValue(&arr[i], &arr[minIndex]);
        }
        cout << "tmpRes: ";
        printArr(arr);
    }
    cout << "finRes: ";
    printArr(arr);
}

//快速排序
//时间复杂度：O(NlogN)，稳定性：不稳定
void quickSort(vector<int> &arr, int bgn, int end)
{
    if (bgn >= end - 1)
    {
        return;
    }
    int lindex = bgn;
    int rindex = end - 1;
    int std = arr[lindex];
    while (lindex < rindex)
    {
        while (lindex < rindex)
        {
            if (arr[rindex] < std)
            {
                arr[lindex++] = arr[rindex];
                break;
            }
            --rindex;
        }

        while (lindex < rindex)
        {
            if (arr[lindex] >= std)
            {
                arr[rindex--] = arr[lindex];
                break;
            }
            ++lindex;
        }
        cout << "tmpRes: ";
        printArr(arr);
    }

    arr[lindex] = std;
    quickSort(arr, bgn, lindex);
    quickSort(arr, rindex + 1, end);

    cout << "finRes: ";
    printArr(arr);
}

//插入排序
//时间复杂度：O(N^2)，稳定性：稳定
void insertSort(vector<int> &arr, int bgn, int end)
{
    for (int i = bgn + 1; i < end; ++i)
    {
        int j = i - 1;
        for ( ; j >= bgn; --j)
            if (arr[j] <= arr[i])
                break;

        if (j != i - 1)
        {
            int temp = arr[i];
            for (int k = i; k > j + 1; --k)
            {
                arr[k] = arr[k - 1];
            }
            arr[j + 1] = temp;
        }
    }
    cout << "finRes: ";
    printArr(arr);
}

//希尔排序
//时间复杂度：O(N^(3/2))，稳定性：不稳定
void shellSort(vector<int> &arr, int bgn, int end)
{
    for (int step = (end - bgn) / 2; step > 0; step /= 2)
    {
        for (int i = bgn; i < step; ++i)
        {
            for (int j = i + step; j < end; j += step)
            {
                int k = j - step;
                for ( ; k >= i; k -= step)
                    if (arr[k] <= arr[j])
                        break;
                if (k != j - step)
                {
                    int tmp = arr[j];
                    for (int m = j; m > k + step; m -= step)
                        arr[m] = arr[m - step];
                    arr[k + step] = tmp;
                }
            }
        }
    }
    cout << "finRes: ";
    printArr(arr);
}

//基数排序
//时间复杂度：O(N*x)，稳定性：稳定
void countSort(vector<int> &arr, int exp)
{
    int bucket[10] = { 0 };
    int arrSize = arr.size();
    int *pTemp = new int[arrSize];
    memset(pTemp, 0, arrSize * sizeof(int));

    //统计单位exp各数值计数值
    for (auto const val : arr)
        ++bucket[(val / exp) % 10];

    //计数分层
    for (int i = 1; i < 10; ++i)
        bucket[i] += bucket[i - 1];

    //按exp位大小用数组arr元素填充pTemp
    for (int i = arrSize - 1; i >= 0; --i)
        pTemp[ --bucket[(arr[i] / exp) % 10] ] = arr[i];
/*bugs*/
#if 0
    //bug1: bucket各层次的计数值没遍历一次相应自减1
    for (auto const val : arr)
        pTemp[bucket[(val / exp) % 10] - 1] = val;
    //bug2: arr数组元素每次排序时，下标应从大到小遍历，否则无法实现排序
    for (auto const val : arr)
        pTemp[ --bucket[(val / exp) % 10] ] = val;
#endif

    //pTemp -> arr
    for (int i = 0; i < arrSize; ++i)
        arr[i] = pTemp[i];
    delete []pTemp;
}
//2. 合并各单位计数排序结果
void radixSort(vector<int> &arr)
{
    int max = getMaxValue(arr);
    for (int exp = 1; max / exp != 0; exp *= 10)
        countSort(arr, exp);

    cout << "finRes: ";
    printArr(arr);
}

//归并排序
//时间复杂度：O(NlogN)，稳定性：稳定
void mergeSortInOrder(vector<int> &arr, int bgn, int mid, int end)
{
    int *pBuf = new int[end - bgn];
    int *pTemp = pBuf;
    int lindex = bgn;
    int rindex = mid;

    while ((lindex < mid) && (rindex < end))
        *(pTemp++) = (arr[lindex] < arr[rindex]) ? arr[lindex++] : arr[rindex++];

    while (lindex < mid)
        *pTemp++ = arr[lindex++];
    while (rindex < end)
        *pTemp++ = arr[rindex++];

    //pTemp -> arr
    pTemp = pBuf;
    for (int i = bgn; i < end; i++)
        arr[i] = *pTemp++;

    delete []pBuf;
}
//UpToDown To DownToUp
void mergeSort(vector<int> &arr, int bgn, int end)
{
    //数组arr空or仅有一个元素则退出
    if (bgn >= end - 1)
        return;

    int mid = (bgn + end) / 2;
    mergeSort(arr, bgn, mid);
    mergeSort(arr, mid, end);
    mergeSortInOrder(arr, bgn, mid, end);

    cout << "finRes: ";
    printArr(arr);
}

//堆排序
//时间复杂度：O(NlogN)，稳定性：不稳定
//根节点元素自顶向下移动到合适的位置以构成最大堆
void downToMaxHeap(vector<int> &arr, int bgn, int end)
{
    int child;
    int parent = bgn;

    /*假根节点向下移动至合适的位置 --整个堆排序的核心代码块*/
    while ((child = parent * 2 + 1) < end)
    {
        if ((child < end - 1) && (arr[child] < arr[child + 1]))
            ++child;    //右孩子节点
        if (arr[child] > arr[parent])
            swapValue(&arr[child], &arr[parent]);
        else
            break;
        parent = child;
    }
}
//将数组构造为最大堆
void buildMaxHeap(vector<int> &arr, int bgn, int end)
{
    if (bgn >= end - 1)
        return;

    int parent = end / 2 - 1;
    while (parent >= 0)
    {
        downToMaxHeap(arr, parent, end);
        --parent;
    }
}
//堆排序
void heapSort(vector<int> &arr, int bgn, int end)
{
    //构造最大堆
    buildMaxHeap(arr, bgn, end);

    while (end > 1)
    {
        swapValue(&arr[0], &arr[--end]);
        downToMaxHeap(arr, 0, end);
    }

    cout << "finRes: ";
    printArr(arr);
}

int main()
{
    vector<int> arr = {5, 4, 8, 1, 6, 2, 3, 7};
    //bubbleSort(arr, 0, arr.size());
    //selectSort(arr, 0, arr.size());
    //quickSort(arr, 0, arr.size());
    //insertSort(arr, 0, arr.size());
    //shellSort(arr, 0, arr.size());
    //radixSort(arr);
    //mergeSort(arr, 0, arr.size());
    heapSort(arr, 0, arr.size());

    system("pause");
    return 0;
}