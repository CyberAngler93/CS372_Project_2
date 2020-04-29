//  Matt Perry
// Based on Dr. Hartmans CPS2020 example
// Revision for Template design patterns
// CS372 HW assignment 4/28/2020
#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <memory>
#include <initializer_list>
#include <vector>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>


//Enum for handling Angles.
enum class Angle { R90, R180, R270 };

class Shape {
public:
    virtual ~Shape() = default;
    virtual double getHeight() const = 0;
    virtual double getWidth() const = 0;
    virtual std::ostream & genPostScript(std::ostream& os) const = 0;
};

//helper function for printing post script definition in shape.cpp
void printPostScript(std::ostream & os, const std::shared_ptr<Shape> & shape);

//Basic Shapes
std::shared_ptr<Shape> makeCircle(double radius);
std::shared_ptr<Shape> makeRectangle(double width, double height);
std::shared_ptr<Shape> makePolygon(int numSides, double length);
std::shared_ptr<Shape> makeTriangle(double length);
std::shared_ptr<Shape> makeSquare(double length); 
std::shared_ptr<Shape> makeSpacer(double width, double height); 

//Fancy Shapes
std::shared_ptr<Shape> makeRotatedShape(std::shared_ptr<Shape> s, Angle a);
std::shared_ptr<Shape> makeScaledShape(std::shared_ptr<Shape> s, double sx, double sy);
std::shared_ptr<Shape> makeLayeredShape(std::initializer_list<std::shared_ptr<Shape>> i);
std::shared_ptr<Shape> makeVerticalShape(std::initializer_list<std::shared_ptr<Shape>> i);
std::shared_ptr<Shape> makeHorizontalShape(std::initializer_list<std::shared_ptr<Shape>> i);
std::shared_ptr<Shape> makeCustom(double faceRadius, double eyesRadius, double mouthRadius);


class CompositeShapes : public Shape {
public:
    virtual ~CompositeShapes() = default;
    CompositeShapes();
    CompositeShapes(std::initializer_list<std::shared_ptr<Shape>> i);
    std::ostream & genPostScript(std::ostream & os) const override;
    virtual std::ostream & moveToPos(std::ostream & os, size_t) const = 0;
private:
    std::vector<std::shared_ptr<Shape>> _shapeList;
protected:
    virtual std::vector<std::shared_ptr<Shape>> getShapes()const;
};

class Custom : public Shape {
public:
    Custom(double faceRadius, double eyesRadius, double mouthRadius);
    double getHeight() const override;
    double getWidth() const override;
    std::ostream & genPostScript(std::ostream& os) const override;
private:
    double _fRadius;
    double _eRadius;
    double _mRadius;
};


class Circle : public Shape {
public:
    Circle(double radius);
    double getHeight() const override;
    double getWidth() const override;
    std::ostream & genPostScript(std::ostream& os) const override;
private:
    double _radius;
};

class Rectangle : public Shape {
public:
    Rectangle(double width, double height);
    double getHeight() const override;
    double getWidth() const override;
    std::ostream & genPostScript(std::ostream& os) const override;
private:
    double _width;
    double _height;
};

class Polygon : public Shape {
public:
    Polygon(int numSides, double length);
    double getHeight() const override;
    double getWidth() const override;
    std::ostream & genPostScript(std::ostream& os) const override;
private:
    int _numSides;
    double _length;
};

class Triangle : public Shape {
public:
    Triangle(double length);
    double getHeight() const override;
    double getWidth() const override;
    std::ostream & genPostScript(std::ostream& os) const override;
private:
    double _length;
};

class Spacer : public Shape {
public:
    Spacer(double width, double height);
    double getHeight() const override;
    double getWidth() const override;
    std::ostream & genPostScript(std::ostream& os) const override;
private:
    double _width;
    double _height;
};

class RotatedShape : public Shape {
public:
    RotatedShape(std::shared_ptr<Shape> s, Angle a);
    double getHeight() const override;
    double getWidth() const override;
    std::ostream & genPostScript(std::ostream& os) const override;
private:
    std::shared_ptr<Shape> _s;
    int _a;
};

class ScaledShape : public Shape {
public:
    ScaledShape(std::shared_ptr<Shape> s, double xscale, double yscale);
    double getHeight() const override;
    double getWidth() const override;
    std::ostream & genPostScript(std::ostream& os) const override;
private:
    std::shared_ptr<Shape> _s;
    double _xscale;
    double _yscale;
};

class LayeredShape : public CompositeShapes {
public:
    LayeredShape(std::initializer_list<std::shared_ptr<Shape>> i);
    double getHeight() const override;
    double getWidth() const override;
    std::ostream & genPostScript(std::ostream& os) const override;
private:
    std::vector<std::shared_ptr<Shape>> _shapes;
};

class VerticalShape : public CompositeShapes {
public:
    VerticalShape(std::initializer_list<std::shared_ptr<Shape>> i);
    double getHeight() const override;
    double getWidth() const override;
    std::ostream & genPostScript(std::ostream& os) const override;
private:
    std::vector<std::shared_ptr<Shape>> _shapes;
};

class HorizontalShape : public CompositeShapes {
public:
    HorizontalShape(std::initializer_list<std::shared_ptr<Shape>> i);
    double getHeight() const override;
    double getWidth() const override;
    std::ostream & genPostScript(std::ostream& os) const override;
private:
    std::vector<std::shared_ptr<Shape>> _shapes;
};

#endif