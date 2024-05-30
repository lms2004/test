#include <set>
#include <string>
#include <iostream>
#include <memory>
// 智能指针无法实现
class User {
public:
    // 构造函数
    User() = default;
    User(std::string name) : name(std::move(name)) {}

    // 移动构造函数
    User(User && other) noexcept {
        if (this != &other) {
            name = std::move(other.name);
            friends = std::move(other.friends);
            std::cout<<"移动"<<std::endl;
        }
    }
    // 移动赋值操作符
    User& operator=(User&& other) noexcept {
        if (this != &other) {
            name = std::move(other.name);
            friends = std::move(other.friends);
        }
        std::cout<<"移动赋值"<<std::endl;
        return *this;
    }

    // 禁用复制构造函数
    User(const User&) = delete;

    // 禁用复制赋值操作符
    User& operator=(const User&) = delete;

    // getter functions
    std::string getName() const { return name; }
    const std::set<std::shared_ptr<User>>& getFriends() const { return friends; }

    // setter functions
    void setName(std::string newName) { name = std::move(newName); }

    // 比较符，用于std::set
    bool operator<(const std::shared_ptr<User>& other) const { return name < other->name; }

    // 朋友操作符，用于建立朋友关系
    friend User&& operator+(User& lhs, User& rhs);

private:
    std::string name;
    std::set<std::shared_ptr<User>> friends; // 使用指针来存储朋友
};

User&& operator+(User& lhs, User& rhs) {
    // Since we are disabling copy operations, consider changing this logic
    // to avoid creating new User instances. You might need a different approach
    // to link existing users without copying them.
    auto rhsName=rhs.name;
    auto lhsName=lhs.name;
    auto lhsPtr = std::make_shared<User>(std::move(lhs)); // This approach is problematic with the copy disabled
    auto rhsPtr = std::make_shared<User>(std::move(rhs)); // Same issue as above
    rhs.friends.insert(lhsPtr);
    lhs.friends.insert(rhsPtr);
    rhs.name=rhsName;
    lhs.name=lhsName;
    return std::move(lhs);
}

void printFriends(const User& user) {
    std::cout<<user.getName()<<std::endl;
    for (const auto& friendUser : user.getFriends()) {
        std::cout <<" friends:"<< (*friendUser).getName() << std::endl;
    }
}

int main() {


    User alice("Alice");
    User bob("Bob");
    User charlie("Charlie");
    User dave("Dave");
    // // This will not work as intended because of the deleted copy operations.
    // // Need to rethink the logic for adding friends.
    alice = alice + bob;
    alice = alice + charlie;
    dave = dave + bob;
    charlie = charlie + dave;

    printFriends(alice);
    printFriends(bob);
    printFriends(charlie);
    printFriends(dave);

    return 0;
}
