////////////////////////////////////////////////////////////////////////////////
// 	ADT_joystick.h
// 	Mario Chirinos Colunga
// 	Aurea Desarrollo Tecnológico.
//	16 de Diciembre del 2010
//------------------------------------------------------------------------------
// Notes:
//	c++ Joystick API
//
////////////////////////////////////////////////////////////////////////////////

#ifndef ADT_JOYSTICK_H
#define ADT_JOYSTICK_H
//------------------------------------------------------------------------------
#include <glib.h>
#include <linux/joystick.h>
#include <vector>
using namespace std;
typedef void (*jsPt2Function)(unsigned int number, int value, void *userdata);
//------------------------------------------------------------------------------
class JsData
{
 public:
	char name[80];
	int nAxis;
	int nButtons;
	JsData();
};
//------------------------------------------------------------------------------
class ADT_joystick
{
 private:
	vector<JsData> jsList;
	GIOChannel* channel;
	char *devName;
	char name[80];
	int fd;
	int version;
	int nAxis;
	int nButtons;
	int *vAxis;
	bool *vButton;

	jsPt2Function axisCallback;
	jsPt2Function buttonCallback;
	static int jscallback(GIOChannel *source, GIOCondition condition, void *data);
 public:
	int enumJoysticks();
	int connect(const char *filename);
	int readJs();
	void setAxisCallback(jsPt2Function _fpt);
	void unsetAxisCallback();
	void setButtonCallback(jsPt2Function _fpt);
	void unsetButtonCallback();

	vector<JsData> getList() const;
	const char* getDevName() const;
	const char* getName() const;
	unsigned int getAxisCount() const;
	unsigned int getButtonCount() const;
	int getAxis(unsigned int i) const;
	bool getButton(unsigned int i) const;

	ADT_joystick();
	~ADT_joystick();
};
//------------------------------------------------------------------------------
#endif
