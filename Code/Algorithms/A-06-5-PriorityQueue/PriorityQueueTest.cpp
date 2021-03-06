// Copyright [2017] <MaoMao>

#include "PriorityQueueTest.h"
#include "Utils.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <time.h>
#include <stdint.h>

using namespace std;

// insert `x` to priority queue
extern void Insert(int* array, int& length, int x);

// get the Maximum key in priority queue
extern int  Maximum(int* array, int& length);

// extract Maximum key from priority queue
extern int  ExtractMax(int* array, int& length);

// increase the key value of array[i] to `key`
extern void IncreaseKey(int* array, int& length, int i, int key);

extern void quick_sort(int* array, int start, int end);

PriorityQueueTest::PriorityQueueTest()
{
    m_info.id = "A-6-5";
    m_info.name = "PriorityQueue";

    m_size = 0;
    m_length = 0;
    m_array = NULL;
}

PriorityQueueTest::~PriorityQueueTest()
{
    if (m_array != NULL)
    {
        delete []m_array;
        m_array = NULL;
    }
}

void PriorityQueueTest::m_BuildInput()
{
    printf("Please input array size:\n");

    std::cin >> m_size;
    assert(m_size > 0);

    m_array = new int[m_size];

    for (int i = 0; i < m_size; i++)
        m_array[i] = 0;
}

void PriorityQueueTest::m_Execute()
{
    int choice = -1;
    do
    {
        printf("1. Insert.\n");
        printf("2. Maximum.\n");
        printf("3. ExtractMax.\n");
        printf("4. IncreaseKey.\n");
        printf("5. Print.\n");
        printf("-1. Exit.\n");
        std::cin >> choice;
        switch (choice)
        {
            case 1:
            {
                printf("Input num to insert :\n");
                int key;
                std::cin >> key;
                Insert(m_array, m_length, key);
                break;
            }
            case 2:
            {
                int max = Maximum(m_array, m_length);
                printf("Maximum value=%d\n", max);
                break;
            }
            case 3:
            {
                int max = ExtractMax(m_array, m_length);
                printf("Extract Maximum value=%d\n", max);
                break;
            }
            case 4:
            {
                int i, x;
                printf("Increase array[i] value to x, please input i and x:\n");
                std::cin >> i >> x;
                IncreaseKey(m_array, m_length, i, x);
                break;
            }
            case 5:
            {
                Print(m_array, m_length);
                break;
            }
        }
    }while(choice > 0);
}

void PriorityQueueTest::Print(int* array, int& length)
{
    for (int i = 0; i < length; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}


bool PriorityQueueTest::CheckHeap(int* array, int& length)
{
    for (int i = 0; i < length; i++)
    {
        int left = i*2 + 1;
        int right = i*2 + 2;
        if (left < length && array[i] < array[left])
        {
            printf("array[%d]=%d < left child array[%d]=%d \n", i, array[i], left, array[left]);
            return false;
        }
        if (right < length && array[i] < array[right])
        {
            printf("array[%d]=%d < right child array[%d]=%d \n", i, array[i], right, array[right]);
            return false;
        }
    }
    return true;
}

#define TEST_SIZE 1024*1024

bool PriorityQueueTest::m_CheckOutput()
{
    bool bRet = true;
    int length = 0;
    int* array_input = new int[TEST_SIZE];
    int* array_sorted = new int[TEST_SIZE];
    int* array_queue = new int[TEST_SIZE];
    int* array_output = new int[TEST_SIZE];

    srand(time(NULL));
    for (int i = 0; i < TEST_SIZE; i++)
    {
        array_input[i] = rand();
        array_sorted[i] = array_input[i];
    }
    quick_sort(array_sorted, 0, TEST_SIZE-1);

    // time check
    clock_t c1, c2;
    c1 = clock();

    for (int i = 0; i < TEST_SIZE; i++)
    {
        Insert(array_queue, length, array_input[i]);
    }
    for (int i = 0; i < TEST_SIZE; i++)
    {
        array_output[TEST_SIZE-i-1] = ExtractMax(array_queue, length);
    }

    c2 = clock();
    printf("Time used %lds %ldms\n", (c2 - c1) / CLOCKS_PER_SEC, (c2 - c1) % CLOCKS_PER_SEC);

    // Check
    bRet = CheckHeap(array_queue, length);
    if (!bRet)
        return bRet;

    for (int i = 0 ; i < TEST_SIZE; i++)
    {
        if (array_output[i] != array_sorted[i])
            return bRet = false;
    }

    return bRet;
}
