#include <iostream>

#include <stack.h>
#include <queue.h>

using namespace std;

int main() {
    Stack<char>
        s;
    Queue<char>
        q;
    string
        str;

    cout << "Enter a line: ";
    getline(cin,str);

    for (char ch : str) {
        s.push(ch);
        q.enqueue(ch);
    }

    cout << "Stack: ";
    while (!s.isEmpty())
        cout << s.pop();
    cout << endl;
    cout << "Queue: ";
    while (!q.isEmpty())
        cout << q.dequeue();
    cout << endl;

    return 0;
}
