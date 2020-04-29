//  Matt Perry, Tailon Russell, Chenyi Ling, McKade Sorensen

#include "shape.hpp"

using std::initializer_list;
using std::vector;
using std::shared_ptr;

std::shared_ptr<Shape> makeCircle(double radius)
{
	return std::make_shared<Circle>(radius);
}

std::shared_ptr<Shape> makeCustom(double faceRadius, double eyesRadius, double mouthRadius)
{
	return std::make_shared<Custom>(faceRadius, eyesRadius, mouthRadius);
}

std::shared_ptr<Shape> makePolygon(int numSides, double length)
{
	return std::make_shared<Polygon>(numSides, length);
}

std::shared_ptr<Shape> makeRectangle(double width, double height)
{
	return std::make_shared<Rectangle>(width,height);
}

std::shared_ptr<Shape> makeSpacer(double width, double height)
{
	return std::make_shared<Spacer>(width, height);
}

std::shared_ptr<Shape> makeSquare(double length)
{
	return std::make_shared<Rectangle>(length,length);
}

std::shared_ptr<Shape> makeTriangle(double length)
{
	return std::make_shared<Triangle>(length);
}

std::shared_ptr<Shape> makeRotatedShape(std::shared_ptr<Shape> s, Angle a)
{
	return std::make_shared<RotatedShape>(s,a);
}

std::shared_ptr<Shape> makeScaledShape(std::shared_ptr<Shape> s, double sx, double sy)
{
	return std::make_shared<ScaledShape>(s, sx, sy);
}

std::shared_ptr<Shape> makeLayeredShape(std::initializer_list<std::shared_ptr<Shape>> i)
{
	return std::make_shared<LayeredShape>(i);
}

std::shared_ptr<Shape> makeVerticalShape(std::initializer_list<std::shared_ptr<Shape>> i)
{
	return std::make_shared<VerticalShape>(i);
}

std::shared_ptr<Shape> makeHorizontalShape(std::initializer_list<std::shared_ptr<Shape>> i)
{
	return std::make_shared<HorizontalShape>(i);
}

Custom::Custom(double faceRadius, double eyeRadius, double mouthRadius): _fRadius(faceRadius),
	 _eRadius(eyeRadius), _mRadius(mouthRadius){}

double Custom::getHeight() const
{
	return (2 * _fRadius);
}

double Custom::getWidth() const
{
	return (2 * _fRadius);
}

std::ostream & Custom::genPostScript(std::ostream& os) const 
{
	os << "gsave\n0 0 "<< _fRadius << " 0 360 arc\nstroke\n";
	os << "0 0 " << _mRadius << " 210 330 arc closepath\nstroke\n";
	os << "-"<< 2*_eRadius << " " << _eRadius << " " << _eRadius << " 0 360 arc\nstroke\n";
	os << 2*_eRadius << " " << _eRadius << " " << _eRadius << " 0 360 arc\nstroke\ngrestore\n";
}

Circle::Circle(double radius): _radius(radius){}

double Circle::getHeight() const
{
	return (2 * _radius);
}

double Circle::getWidth() const
{
	return (2 * _radius);
}

std::ostream & Circle::genPostScript(std::ostream& os) const 
{
	os << "gsave\n0 0 " << _radius << " 0 360 arc\nstroke\ngrestore\n";
}

Polygon::Polygon(int numSides, double length): _numSides(numSides), _length(length){}

double Polygon::getHeight() const
{
	if (_numSides % 2 == 1)
		return (_length * (1 + std::cos(M_PI / _numSides))/(2 * std::sin(M_PI / _numSides)));
	if (_numSides % 4 == 0)
		return (_length * (std::cos(M_PI / _numSides)) / std::sin(M_PI / _numSides));
	if (_numSides % 2 == 0)
		return (_length * (std::cos(M_PI / _numSides)) / std::sin(M_PI / _numSides));
	
	return 0.0;
}

double Polygon::getWidth() const
{
	if (_numSides % 2 == 1)
		return ((_length * std::sin(M_PI * (_numSides - 1.0) / (2.0 * _numSides))) / std::sin(M_PI / _numSides));
	if (_numSides % 4 == 0)
		return ((_length * std::cos(M_PI / _numSides)) / std::sin(M_PI / _numSides));
	if (_numSides % 2 == 0)
		return (_length / std::sin(M_PI / _numSides));

	return 0.0;
}

std::ostream & Polygon::genPostScript(std::ostream& os) const
{
	os << "gsave\n";
	double degree = 180 - (double)((180 * (_numSides - 2)) / _numSides);
	os << "newpath\n" << _length << " 0 moveto\n";
	for (int i = 0; i < _numSides - 1; ++i)
		os << degree << " rotate " << _length << " 0 lineto\n";
	os << "closepath\nstroke\ngrestore\n";
}


Rectangle::Rectangle(double width, double height): _width(width), _height(height){}

double Rectangle::getHeight() const
{
	return _height;
}

double Rectangle::getWidth() const
{
	return _width;
}


std::ostream & Rectangle::genPostScript(std::ostream& os) const
{
	os << "gsave\n-" << _width/2 << " -" << _height/2 << " translate\nnewpath\n0 0 moveto\n"; 
	os << _width << " 0 lineto\n" << _width << " " << _height << " lineto\n 0 " << _height << " lineto\n";
	os << "closepath\nstroke\ngrestore\n";	
}



Spacer::Spacer(double width, double height): _width(width), _height(height){}

double Spacer::getHeight() const
{
	return _height;
}

double Spacer::getWidth() const
{
	return _width;
}


std::ostream & Spacer::genPostScript(std::ostream& os) const
{
	os << "1 setgray\n";
	os << "gsave\n-" << _width/2 << " -" << _height/2 << " translate\nnewpath\n0 0 moveto\n"; 
	os << _width << " 0 lineto\n" << _width << " " << _height << " lineto\n 0 " << _height << " lineto\n";
	os << "closepath\nstroke\ngrestore\n";	
}


Triangle::Triangle(double length): _length(length){}

double Triangle::getHeight() const
{
	return Polygon(3, _length).getHeight();
}

double Triangle::getWidth() const
{
	return Polygon(3, _length).getWidth();
}


std::ostream & Triangle::genPostScript(std::ostream& os) const
{
	os << "gsave\n -" << _length / 2 << " -" << (_length / 2) * (sqrt(3.0)) << " tanslate\nnewpath\n0 0 moveto\n" << _length;
	os << " 0 lineto\n" << _length / 2 << " " << (_length / 2) * (sqrt(3.0)) << " lineto\nclosepath\nstroke\ngrestore\n";
	
}


RotatedShape::RotatedShape(std::shared_ptr<Shape> s, Angle a)
{
	_s = s;
	switch (a) {
	case Angle::R90:
		_a = 90;
		break;
	case Angle::R180:
		_a = 180;
		break;
	case Angle::R270:
		_a = 270;
		break;
	}
}

double RotatedShape::getHeight() const
{
	if (_a == 90 || _a == 270)
		return _s->getWidth();
	if (_a == 180)
		return _s->getHeight();

	return 0.0;
}

double RotatedShape::getWidth() const
{
	if (_a == 90 || _a == 270)
		return _s->getHeight();
	if (_a == 180)
		return _s->getWidth();

	return 0.0;
}


std::ostream & RotatedShape::genPostScript(std::ostream& os) const
{
	os << "gsave\n";
	os << _a << " rotate \n";
	_s->genPostScript(os);
	os << "grestore\n";
}


ScaledShape::ScaledShape(std::shared_ptr<Shape> s, double xscale, double yscale): _s(s), _xscale(xscale), _yscale(yscale){}

double ScaledShape::getHeight() const
{
	return (_s->getHeight() * _yscale);
}

double ScaledShape::getWidth() const
{
	return (_s->getWidth() * _xscale);
}


std::ostream & ScaledShape::genPostScript(std::ostream& os) const
{
	os << _xscale << " " << _yscale <<" scale\n"; 
	_s->genPostScript(os);
}

CompositeShapes::CompositeShapes(initializer_list<shared_ptr<Shape>> i) 
{
	vector<shared_ptr<Shape>> temp(i.begin(), i.end());
	_shapeList = temp;
}

std::ostream& CompositeShapes::genPostScript(std::ostream& os) const
{
	for (auto i = 0l; i < getShapes().size(); ++i) {
		moveToPos(os, i);
		getShapes()[i]->genPostScript(os);
	}
	return os;
}

std::vector<std::shared_ptr<Shape>> CompositeShapes::getShapes() const
{
	return _shapeList;
}

LayeredShape::LayeredShape(initializer_list<shared_ptr<Shape>> i): CompositeShapes(i)
{}

double LayeredShape::getHeight() const
{
	return 0.0;
}

double LayeredShape::getWidth() const
{
	return 0.0;
}


std::ostream& LayeredShape::moveToPos(std::ostream& os, size_t distance) const
{
	return os;
}

VerticalShape::VerticalShape(initializer_list<shared_ptr<Shape>> i) : CompositeShapes(i)
{}

double VerticalShape::getHeight() const
{
	return 0.0;
}

double VerticalShape::getWidth() const
{
	return 0.0;
}

std::ostream& VerticalShape::moveToPos(std::ostream& os, size_t index) const
{
	os << "0 " << getShapes()[index]->getHeight() << " translate\n";
	return os;
}


HorizontalShape::HorizontalShape(initializer_list<shared_ptr<Shape>> i) : CompositeShapes(i)
{}

double HorizontalShape::getHeight() const
{
	return 0.0;
}

double HorizontalShape::getWidth() const
{
	return 0.0;
}

std::ostream& HorizontalShape::moveToPos(std::ostream& os, size_t index) const
{
	os << getShapes()[index]->getWidth() << " 0 translate\n";
	return os;
}

//helper function to print ps
void printPostScript(std::ostream & os, const std::shared_ptr<Shape> & shape){
    std::cout << "306 396 translate\n";
    shape->genPostScript(std::cout);
    std::cout << "showpage\n";
    std::cout << "\n";
}