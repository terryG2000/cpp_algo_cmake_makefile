#include <iostream>
#include <utility> // For std::move
#include <vector>

class Widget {
public:
    std::vector<int> dataVector;
    int idata;
    int* data;
    void print(){
        if(data == nullptr) {
            std::cout << "data = " <<" nullptr "<< idata <<std::endl;
            return;
        }
        std::cout << *data <<" - "<< data << " - "<< idata <<std::endl;
    }

    Widget(int a, int b) : data(new int(a)), idata(b){ // Default constructor 默认构造函数
        std::cout << "Default constructor\n";
    }

    Widget(const Widget& w) : data(new int(*w.data)), idata(w.idata) { // Copy constructor 复制构造
        std::cout << "Copy constructor\n";
    }

    Widget& operator=(const Widget& w) { // Copy assignment operator 拷贝赋值运算符
        if (this != &w) {
            *data = *w.data;
            idata = w.idata;// 值复制
        }
        std::cout << "Copy assignment operator\n";
        return *this;
    }

    Widget(Widget&& w) noexcept : data(w.data), idata(w.idata), dataVector(std::move(w.dataVector)) { // Move constructor 移动构造
//        dataVector(std::move(w.dataVector) 这里调用的是移动构造 因为对象内的兑现也是新建的
        w.data = nullptr;
        std::cout << "Move constructor\n";
    }

    Widget& operator=(Widget&& w) noexcept { // Move assignment operator 移动赋值运算符
        if (this != &w) {
            delete data;
            data = w.data;
            idata = w.idata;
            w.data = nullptr;
        }
        std::cout << "Move assignment operator\n";
        return *this;
    }

    ~Widget() { // Destructor
        delete data;
    }
};

int main() {
    Widget w1(1,11); // Default constructor is called
    Widget w2(2,22); // Default constructor is called
    w1.print();
    w2.print();
    std::cout << "-----------------------------" << std::endl;

    std::cout << " 拷贝赋值运算符  w2 = w1  " << std::endl;
    w2 = w1; // Copy assignment operator is called
    w2.print();
    std::cout << "-----------------------------" << std::endl;

    std::cout << "移动构造  Widget w3 = std::move(w1)" << std::endl;
    std::cout << "w1 内存地址" << &w1 << std::endl;
    Widget w3 = std::move(w1); // Move constructor is calleds
    std::cout << "w1 内存地址" << &w1 << std::endl;
    std::cout << "w3 内存地址" << &w3 << std::endl;
    w3.print();
    w1.print();
    std::cout << "-----------------------------" << std::endl;
    // 同下

    std::cout << "移动拷贝赋值  w2 = std::move(w3)" << std::endl;
    w2 = std::move(w3); // Move assignment operator is called
    w2.print();
    std::cout << "-----------------------------" << std::endl;
    /**
    *    std::move(w3)`的作用是将左值`w3`转换为右值引用，这样就能触发移动赋值运算符（如果定义了的话）。
    *这个过程中，`w3`的内部状态（比如它所拥有的资源）会被转移给`w2`。
    *data = w.data;
	*data = nullptr;
    *而`w3`本身会被置于一个有效但未指定的状态，这通常意味着`w3`失去了之前拥有的资源的所有权。此后，使用`w3`应该非常小心，因为它不再拥有之前那些资源了。
    *
    *   关于“并删除`w2`原有的资源”这一点，确实，在移动赋值操作中，`w2`原先持有的资源通常会被释放（或者被交换），以确保资源管理的正确性。具体的行为取决于移动赋值运算符的实现。
    *在这个例子中，移动赋值运算符首先释放了 data
    */

    std::cout << "复制构造 Widget w4 = Widget(w2)" << std::endl;
    Widget w4 = Widget(w2);
    w4.print();
    std::cout << "-----------------------------" << std::endl;

    return 0;
}