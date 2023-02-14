#include <iostream>
using namespace std;
#define n 50

class queue
{
    int *arr;
    int front;
    int back;

public:
    queue()
    {
        arr = new int[n];
        front = -1;
        back = -1;
    }

    void push(int val)
    {
        if (back == n - 1)
        {
            cout << "Queue Overflow" << endl;
        }
        else
        {
            arr[++back] = val;
        }
        if (front == -1)
        {
            front++;
        }
    }
    void pop()
    {
        if (front == -1 || front > back)
        {
            cout << "Queue is empty" << endl;
        }
        front++;
    }
    int peek()
    {
        if (front == -1 || front > back)
        {
            cout << "Queue is empty" << endl;
            return -1;
        }
        return arr[front];
    }void Display()
	{
		int t = front;
		cout << "Stack: ";
		while (t <= back)
		{
			cout << arr[t]<< " ";
			t++;
		}
		cout << "\n";
	}

    bool isEmpty()
    {
        Display();
        if (front == -1 || front > back)
        {
            return true;
        }
        return false;
    }
};

int main()
{
    queue q;
    q.push(2);
    // cout << q.peek() << endl;
    q.push(1);
    // cout << q.peek() << endl;
    q.push(3);
    // cout << q.peek() << endl;
    // q.pop();
    // cout << q.peek() << endl;

    // q.pop();
    // q.pop();


    cout << q.peek() << endl;
    cout << q.isEmpty() << endl;

    return 0;
}