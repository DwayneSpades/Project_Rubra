#pragma once

struct GLFWwindow;

class window_settings 
{
public:
	//Big Four
	window_settings() = default;
	window_settings(window_settings& ptr) = default;
	window_settings& operator = (window_settings& ptr) = default;
	~window_settings() = default;

	window_settings(float width, float height, const char* name);

	//set
	void setWindowName(const char*  string);
	//get
	GLFWwindow* getWindow() const;
	const char* getWindowName(); 	
	float getWidth();
	float getHeight();

private:
	GLFWwindow* _window = nullptr;
	const char* _windowName = nullptr;
	float _width = 0;
	float _height = 0;

};