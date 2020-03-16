#pragma once

class Viewport
{
public:
	Viewport(int w, int h);
	~Viewport();

	void set();

	void setSize(int w, int h);
	void setPos(int x, int y);

	inline int getX() const { return x_; };
	inline int getY() const { return y_; };
	inline int getW() const { return w_; };
	inline int getH() const { return h_; };
	inline float getAspect() const { return aspect_; }

protected:
	int x_ = 0, y_ = 0, w_ = 0, h_ = 0;
	float aspect_ = 1.0f;
};