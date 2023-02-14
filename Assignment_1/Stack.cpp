// #include <iostream>
// using namespace std;
// int stack[100], n = 100, top = -1;
// void push(int val)
// {
//     if (top >= n - 1)
//         cout << "Stack Overflow" << endl;
//     else
//     {
//         top++;
//         stack[top] = val;
//     }
// }
// void pop()
// {
//     if (top <= -1)
//         cout << "Stack Underflow" << endl;
//     else
//     {
//         cout << "The popped element is " << stack[top] << endl;
//         top--;
//     }
// }
// void display()
// {
//     if (top >= 0)
//     {
//         cout << "Stack elements are:";
//         for (int i = top; i >= 0; i--)
//             cout << stack[i] << " ";
//         cout << endl;
//     }
//     else
//         cout << "Stack is empty";
// }
// int main()
// {
//     int ch, val;
//     cout << "1) Push in stack" << endl;
//     cout << "2) Pop from stack" << endl;
//     cout << "3) Display stack" << endl;
//     cout << "4) Exit" << endl;
//     do
//     {
//         cout << "Enter choice: " << endl;
//         cin >> ch;
//         switch (ch)
//         {
//         case 1:
//         {
//             cout << "Enter value to be pushed:" << endl;
//             cin >> val;
//             push(val);
//             break;
//         }
//         case 2:
//         {
//             pop();
//             break;
//         }
//         case 3:
//         {
//             display();
//             break;
//         }
//         case 4:
//         {
//             cout << "Exit" << endl;
//             break;
//         }
//         default:
//         {
//             cout << "Invalid Choice" << endl;
//         }
//         }
//     } while (ch != 4);
//     return 0;
// }

#include <iostream>
using namespace std;
#define n 100

class Stack
{
    int *arr;
    int top;

public:
    Stack()
    {
        arr = new int[n];
        top = -1;
    }
    void push(int val)
    {
        if (top >= n - 1)
        {

            cout << "Stack Overflow" << endl;
            return;
        }
        else
        {
            top++;
            arr[top] = val;
        }
    }
    void pop()
    {
        if (top <= -1)
        {
            cout << "Stack is empty" << endl;
            return;
        }
        else
        {
            top--;
        }
    }

    int Top()
    {
        if (top <= -1)
        {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return arr[top];
    }
    bool isEmpty()
    {

        return top == -1;
    }
};

int main()
{
    Stack st;
    st.push(2);
cout<<st.Top()<<endl;
st.pop();
cout<<st.Top()<<endl;

    return 0;
}