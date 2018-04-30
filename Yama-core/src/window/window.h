#pragma once

struct GLFWwindow;
class Input;

class Window
{

private:
	int mWidth;
	int mHeight;
	const char* mTitle;
	bool mClosed;

public:
	GLFWwindow* mWindow;
	Input* mInput;

	Window(const char* pName, int pWidth, int pHeight);
	~Window();
	void update();
	void clear();
	bool closed();

	inline int getWidth() const { return mWidth; };
	inline int getHeight() const { return mHeight; };

	Window(const Window&) = delete;
private:

	bool init();

};