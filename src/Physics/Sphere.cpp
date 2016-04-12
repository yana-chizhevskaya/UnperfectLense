
#include "Sphere.h"

const sf::Color COLOR(255, 255, 255, 50);

  Sphere::Sphere(double r1, double r2, Vector2 center1, Vector2 center2,double n) {
	
	this->c1.r = r1;
	this->c2.r = r2;
	this->c1.center = center1;
	this->c2.center = center2;
	this->n = n;
}
double* Sphere::getParam(double r1, double r2, double h) {
	double a = (r1*r1 - r2*r2 + h*h) / (2 * h);
	double* param =new double[2];
	param[0] = acos(a / r1);
	param[1] = acos((h - a) / r2);
	return param;
}

void Sphere::fillVertex() {
	static const float pi = 3.141592654f;
	double dist = c2.center.x - c1.center.x;
	
	double* param = getParam(c1.r,c2.r, dist);
	double t = -param[0];
	double x = std::cos(t) * c1.r;
	double y = std::sin(t) * c1.r;

	for (t = -param[0] + 0.001; t <param[0]; t += 0.001) {
		
		circle1.push_back(sf::Vertex(sf::Vector2f(c1.center.x + x, 250 + y)));
		x = std::cos(t) *  c1.r;
		y = std::sin(t) *  c1.r;
		circle1.push_back(sf::Vertex(sf::Vector2f(c1.center.x + x, 250 + y)));
	}
	
	t = -param[1] + pi;
	x = std::cos(t) * c2.r;
	y = std::sin(t) * c2.r;
	for (t = -param[1] + pi + 0.001; t <param[1] + pi; t += 0.001) {
		circle2.push_back(sf::Vertex(sf::Vector2f(c2.center.x + x, 250 + y)));
		x = std::cos(t) * c2.r;
		y = std::sin(t) * c2.r;
		circle2.push_back(sf::Vertex(sf::Vector2f(c2.center.x + x, 250 + y)));
	
	}

}

void Sphere::DrawLense(sf::RenderWindow *window) {
	fillVertex();
	
		
		window->draw(&circle1[0], circle1.size(), sf::Lines);
		//cout << "I AM HERE" << endl;
		window->draw(&circle2[0], circle2.size(), sf::Lines);
	
	
}

Vector2 Sphere::Intersect(StraightLine line, Vector2 center, double r,char sign) {
	
	//cout << "LINE   " << line.a << sign <<endl;
	double *x = Quadratic((1 + line.a*line.a), 2 * line.a*(line.b - center.y) - 
		2 * center.x, (line.b - center.y)*(line.b - center.y) - r*r + center.x*center.x);
	if (x == NULL) {
		cout << "!!!" << endl;
		exit(1);
	}
	double* y = new double[2];
	y[0] = line.a*x[0] + line.b;
	y[1] = line.a*x[1] + line.b;
/*	cout << x[0] << " " << y[0] << endl;
	cout << x[1] << " " << y[1] << endl;*/
	Vector2 points[] =
	{
		Vector2(x[0],y[0]),
		Vector2(x[1],y[1]),
	};
	if (sign == '-')
	{
		if ((points[0].x) <= (points[1].x))
			return points[0];
		else
			return points[1];
	}
	if (sign == '+')
	{
		
	//	cout << x[1] << " " << y[1] << endl;
		if ((points[0].x) >= (points[1].x))
			return points[0];
		else
			return points[1];
	}

}

Circle Sphere::getFirstCircle()
{
	return c1;
}

Circle Sphere::getSecondCircle()
{
	return c2;
}

StraightLine Sphere::Normal(Vector2 p0, int circ)
{
	StraightLine normal;
	double der_y;
	if (circ == 1) {
		der_y = -(p0.x - c1.center.x) / (p0.y - c1.center.y);
		normal.b = c1.center.y + c1.center.x / der_y;
		normal.a = -1 / der_y;
	}
	if (circ == 2) {
		der_y = -(p0.x - c2.center.x) / (p0.y - c2.center.y);
		normal.b = c2.center.y + c2.center.x / der_y;
		normal.a = -1 / der_y;
	}
	
	return normal;
}

double Sphere::sinAngle(StraightLine normal, StraightLine line)
{
	double a1 = -normal.a;
	double a2 = -line.a;
	double cos = (a1*a2 + 1) / (sqrt(a1*a1 + 1)*sqrt(a2*a2 + 1));
	double sin = sqrt(1 - cos*cos);
	return sin;
}
void Sphere::DrawRays(Ray ray, sf::RenderWindow *window) {
//	sf::Vertex way[4];
	StraightLine line = ray.Equation();
	Vector2 p = Intersect(line, c2.center, c2.r, '-');
	way[0] = sf::Vertex(sf::Vector2f(ray.getBegin().x, ray.getBegin().y), COLOR);
	way[1] = sf::Vertex(sf::Vector2f(p.x, p.y), COLOR);
	StraightLine normal = Normal(p, 2);
	StraightLine refrline;
//	drawNormal(p, normal, window);
	double sin = sinAngle(normal, line);
	double refr_sin = sin / n;
	if (refr_sin > 1 || refr_sin < -1) { // external reflection
		cout << "I AM HERE" << endl;
		refrline = external_reflection(normal, sin, p, line.a);
		
		double x =  - refrline.b / refrline.a;
		//double y = refrline.a * 500 + refrline.b;
		way[2] = sf::Vertex(sf::Vector2f(x, 0));
		
	}
	else{
		 refrline = refr_line(normal, refr_sin, p, line.a);
		cout << "REFRSIN" << refr_sin<< endl;
		p = Intersect(refrline, c1.center, c1.r, '+');

		way[2] = sf::Vertex(sf::Vector2f(p.x,p.y), COLOR);
		normal = Normal(p, 1);
	}
	sin = sinAngle(normal, refrline);
	refr_sin = n*sin;
//cout << refr_sin << endl;
	if (refr_sin > 1 || refr_sin < -1) { // external reflection
		
		cout << "REFRSIN" << refr_sin << endl;
		refrline = external_reflection(normal, sin, p, refrline.a);
		double x = (250 - refrline.b) / refrline.a;
		//double y = refrline.a * 500 + refrline.b;
		way[3] = sf::Vertex(sf::Vector2f(x,250), COLOR);
		window->draw(way, 4, sf::LinesStrip);
	}
	else {
		refrline = refr_line(normal, refr_sin, p, refrline.a);
		//double x = (250 - refrline.b) / refrline.a;
		//way[3] = sf::Vertex(sf::Vector2f(x, 250));
		double y = refrline.a * 500 + refrline.b;
		way[3] = sf::Vertex(sf::Vector2f(500, y), COLOR);
		window->draw(way, 4, sf::LinesStrip);
	}
}
void Sphere::DiscreteSource(sf::RenderWindow * window)
{
	double dist = c2.center.x - c1.center.x;

	double* param = getParam(c1.r, c2.r, dist);

	Ray* ray = new Ray[200];
	double x, y, t;
	int i = 0;
	double step = 2 * param[0] /10;
//	cout <<"step"<< step << "param"<<param[0]<< "   "<<param[1] << endl;
	/*t = -param[0]+0.1;
	 x = std::cos(t) * c1.r;
	 y = std::sin(t) * c1.r;
	ray[i] = Ray(Vector2(70, 250), Vector2(c1.center.x + x, 250 + y));
	
	DrawRays(ray[i], window);*/
	for (t = -param[0]; t <= param[0]; t += 0.02) {
		cout << "step" << step <<"    "<< "t" << t << endl;
		 x = std::cos(t) * c1.r;
		 y = std::sin(t) * c1.r;
		ray[i]= Ray(Vector2(0,250), Vector2(c1.center.x + x, 250 + y));
	//	ray[i].print();
		DrawRays(ray[i], window);
		i++;
		cout << i << endl;
	}
	
}
void Sphere::drawNormal(Vector2 p,StraightLine normal, sf::RenderWindow * window)
{
	sf::Vertex norm[2];
	double x1 = -normal.b/normal.a;
	double x2 =(250 -normal.b) / normal.a;
	norm[0] = sf::Vertex(sf::Vector2f(x1, 0));
	norm[1] = sf::Vertex(sf::Vector2f(x2, 250));
	window->draw(norm, 2, sf::LinesStrip);
}
/*
void Sphere::DrawRays(Ray ray, sf::RenderWindow *window)

{
	sf::Vertex way[4];
	StraightLine line = ray.Equation();
	Vector2 p = Intersect(line, c2.center, c2.r, '-');


	way[0] = sf::Vertex(sf::Vector2f(ray.getBegin().x, ray.getBegin().y));
	way[1] = sf::Vertex(sf::Vector2f(p.x, p.y));
	double focus = (n - 1)*((1 /c2.r) + (1 / c1.r));
	cout << "I AM HERE" << endl;
	double len = p.x - ray.getBegin().x;//длина луча до преломления
	double r_len = n / ((1 / len) - (1 - n) / c2.r);//длина луча после преломления
	Vector2 new_end(r_len + len, 250);
	Ray refr_ray(Vector2(p.x,p.y), new_end);
	refr_ray.print();
	cout << "I AM HERE" << endl;
	p = Intersect(refr_ray.Equation(), c1.center, c1.r, '+');//точка пересечения внутри линзы
	
	way[2] = sf::Vertex(sf::Vector2f(p.x, p.y));
	
	double res_len = 1 / (focus + (1 / 275));

	way[3] = sf::Vertex(sf::Vector2f(275 + res_len, 250));
	window->draw(way, 4, sf::LinesStrip);
	
}
*/


StraightLine Sphere::refr_line(StraightLine normal, double sin,Vector2 p,double dir)
{
	StraightLine refrline;
	double a = normal.a;
	double cos = sqrt(1 - sin*sin);
	double* k = Quadratic(cos*cos - a*a*sin*sin, -2 * a, a*a*cos*cos - sin*sin);
	cout << "DIRECTIONS           " << k[0] << " " << k[1] << endl;
	cout << "NORMAL           " << a << endl;
	//cout << k[0] << " kkk" << k[1] << endl;
	//cout << normal.a << " normal" <<  endl;
	if (dir > 0) {
		if (k[0]>normal.a)
			refrline.a = k[0];
		else refrline.a = k[1];
	}
	else {
		if (k[1] < normal.a)
			refrline.a = k[1];
		else refrline.a = k[0];
	}
	refrline.b = p.y - refrline.a*p.x;
	return refrline;
}

StraightLine Sphere::external_reflection(StraightLine normal, double sin, Vector2 p, double dir)
{
	StraightLine refrline;
	double a = normal.a;
	double cos = sqrt(1 - sin*sin);
	double* k = Quadratic(cos*cos - a*a*sin*sin, -2 * a, a*a*cos*cos - sin*sin);
	cout << "ROOTS       "<<dir<< "   " << k[0] << "   " << k[1] << endl;
	if (fabs(dir - k[1]) > fabs(dir - k[0])) {
		cout << " I am in IF" << endl;
		refrline.a = k[1];
	}
			
	else refrline.a = k[0];

	refrline.b = p.y - refrline.a*p.x;
	cout << "DIR       " << dir << "   " << refrline.a << endl;
	return refrline;
}
