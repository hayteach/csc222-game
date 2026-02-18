#include <iostream>
#include "arrayQueue.h"

int main() {
    arrayQueue<int> q(10);

    std::cout << "Test: add 1..6 to queue\n";
    for (int i = 1; i <= 6; ++i) q.addQueue(i);

    std::cout << "front=" << q.front() << " rear=" << q.rear() << " size=" << q.size() << "\n";

    std::cout << "remove(0) (no-op)\n";
    q.remove(0);
    std::cout << "front=" << q.front() << " rear=" << q.rear() << " size=" << q.size() << "\n";

    std::cout << "remove(1) -> removes 1\n";
    q.remove(1);
    std::cout << "front=" << q.front() << " rear=" << q.rear() << " size=" << q.size() << "\n";

    std::cout << "remove(3) -> removes next 3 (should remove 2,3,4)\n";
    q.remove(3);
    std::cout << "front=" << q.front() << " rear=" << q.rear() << " size=" << q.size() << "\n";

    std::cout << "remove(100) -> should empty the queue\n";
    q.remove(100);
    std::cout << "isEmpty=" << std::boolalpha << q.isEmptyQueue() << " size=" << q.size() << "\n";

    std::cout << "Re-add 7,8 and test deleteQueue/front/rear\n";
    q.addQueue(7);
    q.addQueue(8);
    std::cout << "front=" << q.front() << " rear=" << q.rear() << " size=" << q.size() << "\n";

    std::cout << "deleteQueue() -> removes 7\n";
    q.deleteQueue();
    std::cout << "front=" << q.front() << " rear=" << q.rear() << " size=" << q.size() << "\n";

    std::cout << "All tests completed.\n";
    return 0;
}
