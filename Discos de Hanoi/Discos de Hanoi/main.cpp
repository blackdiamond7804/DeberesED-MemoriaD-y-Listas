#include <iostream>
#include <vector>
#include <string>

class Tower {
public:
    Tower(std::string name) : name(name) {}

    void addDisk(int disk) {
        disks.push_back(disk);
    }

    void moveTopTo(Tower& destination) {
        int top = disks.back();
        disks.pop_back();
        destination.addDisk(top);
        std::cout << "Move disk " << top << " from " << name << " to " << destination.getName() << std::endl;
    }

    void moveDisks(int n, Tower& destination, Tower& buffer) {
        if (n > 0) {
            // Move top n-1 disks from this tower to buffer, using destination as a buffer
            moveDisks(n - 1, buffer, destination);
            // Move the nth disk to destination
            moveTopTo(destination);
            // Move the n-1 disks from buffer to destination, using this tower as a buffer
            buffer.moveDisks(n - 1, destination, *this);
        }
    }

    std::string getName() const {
        return name;
    }

private:
    std::string name;
    std::vector<int> disks;
};

class Hanoi {
public:
    Hanoi(int numDisks) : numDisks(numDisks), source("A"), destination("C"), buffer("B") {
        for (int i = numDisks; i >= 1; --i) {
            source.addDisk(i);
        }
    }

    void solve() {
        source.moveDisks(numDisks, destination, buffer);
    }

private:
    int numDisks;
    Tower source;
    Tower destination;
    Tower buffer;
};

int main() {
    int numDisks;
    std::cout << "Enter the number of disks: ";
    std::cin >> numDisks;

    Hanoi hanoi(numDisks);
    hanoi.solve();

    return 0;
}