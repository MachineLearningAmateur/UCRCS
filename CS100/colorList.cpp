#include <list>
#include <utility> //for pair class
#include <cmath> //for sin 
#include <iostream>


struct Hue {
    double data;
};

struct Point {
    int x;
    double y;
};

int main() {
    std::list<std::pair<Hue, Point>> colorList;
    for (int i = 0; i < 25; i++) {
        Hue arg1;
        arg1.data = static_cast<double>(i)/25; 
        Point arg2;
        arg2.x = i;
        arg2.y = std::sin(i);
        std::pair<Hue, Point> temp(arg1, arg2);
        // std::cout << "colorList[" << i << "]: " << temp.first.data << ", " << temp.second.x << ", " << temp.second.y << std::endl;
        colorList.push_back(temp);
    }
    int i = 0;
    for (std::list<std::pair<Hue, Point>>::iterator it = colorList.begin(); it != colorList.end(); it++) { //if you need to iterate through the list 
        std::cout << "colorList[" << i <<  "]: " << (*it).first.data << ", " << (*it).second.x << ", " << (*it).second.y << std::endl;
        i++;
    }

    return 0;
}