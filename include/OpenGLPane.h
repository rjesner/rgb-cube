#ifndef _OPENGLPANE_
#define _OPENGLPANE_
 
#include "wx/wx.h"
#include "wx/glcanvas.h"
#include "wx/sizer.h"
#include "wx/time.h"

#include "GL/freeglut.h"
 
class OpenGLPane : public wxGLCanvas
{
	wxGLContext*	m_context;
	double xRot = 0; 
	double yRot = 0;
	double zRot = 0;
public:
	OpenGLPane(wxFrame* parent, int* args);
	virtual ~OpenGLPane();
	int getWidth();
	int getHeight();
	void OnIdle(wxIdleEvent& e);
	void OnRender(wxPaintEvent& evt);
	//void prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
	void prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
    
	DECLARE_EVENT_TABLE()
};

#endif
