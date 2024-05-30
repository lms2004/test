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

// ����Person�࣬���ڴ洢���˵���ߡ����غ���Χ����
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
    
    
    // ��ȡ��ߵĳ�Ա����
    double getHeight() const { return height_; }
    // ��ȡ���صĳ�Ա����
    double getWeight() const { return weight_; }
    // ��ȡ��Χ���ݵĳ�Ա����������һ��������Χ���ݵ�����
    std::vector<double> getMeasurements() const { return measurements_; }

private:
    double height_;
    double weight_;
    std::vector<double> measurements_;  // �洢��Χ���ݣ�ʹ���������洢��Χ����Χ����Χ
};

// ����Group�࣬���ڴ洢���Person���󣬲��������ǵ�ƽ����ߡ����غ���Χ
class Group {
public:
    // �������
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
    // ����ƽ����Χ�ĳ�Ա����������һ������ƽ����Χ����Χ����Χ������
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

    Circle circle(5);  // ����һ���뾶Ϊ5��Բ
    std::cout << "Circle area: " << circle.CalculateArea() << std::endl;//Ԥ�������Circle area: 78.5398

    Group group;
    // ��Ӳ�������
    group.addPerson(Person(170, 60, 90, 60, 90)); 
    group.addPerson(Person(160, 55, 85, 65, 85)); 
    group.addPerson(Person(175, 70, 95, 70, 95)); // �������˵�����

    // ��ӡ���Խ��
    std::cout << "Average height: " << group.averageHeight() << std::endl;  // Ԥ�������Average height: 168.333
    std::cout << "Average weight: " << group.averageWeight() << std::endl;  // Ԥ�������Average weight: 61.6667
    auto averageMeasurements = group.averageMeasurements();
    std::cout << "Average measurements: Chest: " << averageMeasurements[0]
        << ", Waist: " << averageMeasurements[1]
        << ", Hips: " << averageMeasurements[2] << std::endl;  // Ԥ�������Average measurements: Chest: 90, Waist: 65, Hips: 90

    return 0;

}
