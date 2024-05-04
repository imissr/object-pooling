#include <stack>
#include <memory>
#include <iostream>

template <typename T>
class ObjectPool {
public:
    ObjectPool(size_t initialSize) {
        for (size_t i = 0; i < initialSize; ++i) {
            pool.push(std::make_unique<T>());
        }
    }

    std::unique_ptr<T> acquire() {
        if (pool.empty()) {
            return nullptr; // No available objects
        } else {
            auto obj = std::move(pool.top());
            pool.pop();
            return obj;
        }
    }

    void release(std::unique_ptr<T> obj) { //return the object to the stack
        pool.push(std::move(obj));
    }

private:
    std::stack<std::unique_ptr<T>> pool; // The pool of reusable objects
};

class MyObject {
public:
    MyObject() {
        std::cout << "MyObject created\n";
    }

    void doSomething() {
        std::cout << "Doing something with MyObject\n";
    }
};

int main() {
    ObjectPool<MyObject> objectPool(3); // Create a pool with 3 objects

    auto obj1 = objectPool.acquire(); // Acquire an object from the pool
    obj1->doSomething();

    objectPool.release(std::move(obj1)); // Release the object back to the pool

    auto obj2 = objectPool.acquire(); // Acquire another object
    obj2->doSomething();

    return 0;
}