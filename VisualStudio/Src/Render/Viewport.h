#pragma once

class Viewport
{
public:
	Viewport(int w, int h);
	~Viewport();

	void set();

	void setSize(int w, int h);
	void setPos(int x, int y);

	inline int getX() const { return _x; };
	inline int getY() const { return _y; };
	inline int getW() const { return _w; };
	inline int getH() const { return _h; };
	inline float getAspect() const { return _aspect; }

protected:
	int _x = 0, _y = 0, _w = 0, _h = 0;
	float _aspect = 1.0f;
};