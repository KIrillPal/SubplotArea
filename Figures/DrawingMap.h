#include "FloatMap.h"
typedef struct Box
{
	float x, y, width, height;
	Box(float x, float y, float w, float h)
		: x(x), y(y), height(h), width(w) {};
};
class DrawingMap
{
public:
	DrawingMap(uint16_t width, uint16_t height, char* programName);
    DrawingMap() {};
	~DrawingMap();
	sf::RenderWindow* getWindow();
	sf::RenderWindow *window;
	void updateGraph(Box real_window, Box mind_window, double (*af)(double x), double (*bf)(double x), double (*cf)(double x));
private:
	uint16_t currentWidth, currentHeight;
	void DrawingMap::setPixel(uint16_t x, uint16_t y, size_t width, size_t height, sf::Color c);
	void DrawingMap::drawLines(float x, float y, sf::Vector2f lw, Box real_window,
		Box mind_window, sf::Color c, sf::Vector2f step, sf::Vector2f scale);
	void DrawingMap::drawNumbers(float x, float y, Box real_window, Box mind_window,
		sf::Vector2f step, sf::Vector2f scale, bool axis);
    void DrawingMap::drawLine(double (*f)(double x), sf::Color clr, Box real_window, Box mind_window, sf::Vector2f scale, sf::Vector2f from);
};

