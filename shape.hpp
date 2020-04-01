//  Matt Perry, Tailon Russell, Chenyi Ling, McKade Sorensen

#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>


class Shape {
public:
    virtual ~Shape() = default;
    virtual double getHeight() const = 0;
    virtual double getWidth() const = 0;
    virtual void generatePostScript(std::ostream& os) const = 0;
};

class Circle : public Shape {
public:
    Circle(double radius);
    double getHeight() const override;
    double getWidth() const override;
    void generatePostScript(std::ostream& os) const override;
private:
    double _radius;
};


#endif