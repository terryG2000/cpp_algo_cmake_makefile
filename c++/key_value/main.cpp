//
// Created by terry on 24-3-8.
//
#include <iostream>
#include <map>
#include <string>

int main() {
    // 创建一个map，键类型为string，值类型为int
    std::map<std::string, int> population;

    // 使用键值对插入数据
    population.insert(std::make_pair("New York", 8336817));
    population.insert(std::make_pair("Los Angeles", 3979576));
    population.insert(std::make_pair("Chicago", 2693976));

    // 直接使用下标操作符添加或修改元素
    population["Houston"] = 2320268;

    // 遍历map中的所有元素并打印它们
    std::cout << "City Population:" << std::endl;
    for (const auto& pair : population) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // 访问特定键的值
    std::string city = "New York";
    if (population.find(city) != population.end()) {
        std::cout << "The population of " << city << " is " << population[city] << "." << std::endl;
    } else {
        std::cout << city << " not found in the map." << std::endl;
    }

    return 0;
}
