#include <iostream>
#include <vector>
#define PI 3.14159265358979323846


class Circle {
public:
    Circle(double radius) : radius_(radius) {}

    double CalculateArea() const {
        return PI * radius_ * radius_;
    }

private:
    double radius_;
};

// 定义Person类，用于存储个人的身高、体重和三围数据
class Person {
public:

    Person(double height, double weight, double chest, double waist, double hips) {
        height_ = height;
        weight_ = weight;
        measurements_.push_back(chest);
        measurements_.push_back(waist);
        measurements_.push_back(hips);
    }
    //Person(double height, double weight, double chest, double waist, double hips)
    //    : height_(height), weight_(weight), measurements_{ chest, waist, hips } {}
    
    
    // 获取身高的成员函数
    double getHeight() const { return height_; }
    // 获取体重的成员函数
    double getWeight() const { return weight_; }
    // 获取三围数据的成员函数，返回一个包含三围数据的向量
    std::vector<double> getMeasurements() const { return measurements_; }

private:
    double height_;
    double weight_;
    std::vector<double> measurements_;  // 存储三围数据，使用向量来存储胸围、腰围和臀围
};

// 定义Group类，用于存储多个Person对象，并计算他们的平均身高、体重和三围
class Group {
public:
    // 添加人物
    void addPerson(const Person & p) {
        group.push_back(p);
    }
    double averageWeight() {
        double sum = 0;
        for (const Person & person : group) {
            sum += person.getWeight();
        }
        return sum / group.size();
    }
    double averageHeight() {
        double sum = 0;
        for (const Person& person : group) {
            sum += person.getHeight();
        }
        return sum / group.size();
    }
    // 计算平均三围的成员函数，返回一个包含平均胸围、腰围和臀围的向量
    std::vector<double> averageMeasurements() const {
        double totalChest = 0, totalWaist = 0, totalHips = 0;

        for (const Person & person : group) {
            auto measurements = person.getMeasurements();
            totalChest += measurements[0];
            totalWaist += measurements[1];
            totalHips += measurements[2];
        }
        int count = group.size();

        return { totalChest / count, totalWaist / count, totalHips / count };
    }

private:
    std::vector<Person> group;
};


int main() {

    Circle circle(5);  // 创建一个半径为5的圆
    std::cout << "Circle area: " << circle.CalculateArea() << std::endl;//预期输出：Circle area: 78.5398

    Group group;
    // 添加测试数据
    group.addPerson(Person(170, 60, 90, 60, 90)); 
    group.addPerson(Person(160, 55, 85, 65, 85)); 
    group.addPerson(Person(175, 70, 95, 70, 95)); // 第三个人的数据

    // 打印测试结果
    std::cout << "Average height: " << group.averageHeight() << std::endl;  // 预期输出：Average height: 168.333
    std::cout << "Average weight: " << group.averageWeight() << std::endl;  // 预期输出：Average weight: 61.6667
    auto averageMeasurements = group.averageMeasurements();
    std::cout << "Average measurements: Chest: " << averageMeasurements[0]
        << ", Waist: " << averageMeasurements[1]
        << ", Hips: " << averageMeasurements[2] << std::endl;  // 预期输出：Average measurements: Chest: 90, Waist: 65, Hips: 90

    return 0;

}
