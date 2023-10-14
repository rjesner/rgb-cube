#include "OpenGLPane.h"

class MyApp: public wxApp {
    virtual bool OnInit();
    wxFrame *frame;
    OpenGLPane * glPane;
public:
};
IMPLEMENT_APP(MyApp)
 
bool MyApp::OnInit() {
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    frame = new wxFrame((wxFrame *)NULL, -1,  wxT("Rotating RGB Cube"), wxPoint(50,50), wxSize(500,500));
    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    glPane = new OpenGLPane( (wxFrame*) frame, args);
    sizer->Add(glPane, 1, wxEXPAND);
    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);
    frame->Show();
    return true;
} 
 
BEGIN_EVENT_TABLE(OpenGLPane, wxGLCanvas)
EVT_PAINT(OpenGLPane::OnRender)
EVT_IDLE(OpenGLPane::OnIdle)
END_EVENT_TABLE()

OpenGLPane::OpenGLPane(wxFrame* parent, int* args) :
    wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE) {
	m_context = new wxGLContext(this);
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}
 
OpenGLPane::~OpenGLPane() {
	delete m_context;
}
 
int OpenGLPane::getWidth() {
    return GetSize().x;
}
 
int OpenGLPane::getHeight() {
    return GetSize().y;
}

void OpenGLPane::OnIdle(wxIdleEvent& e) {   
    Refresh();
    e.Skip();
}

void OpenGLPane::OnRender(wxPaintEvent& evt) {
    if(!IsShown()) return;

    wxLongLong currentTime = wxGetUTCTimeMillis();
    static wxLongLong referenceTime = currentTime;
    if(currentTime - referenceTime > 16) {
        referenceTime = currentTime;
        xRot += 2;
        yRot += 2;
        zRot += 0;
    }

    wxGLCanvas::SetCurrent(*m_context);
    wxPaintDC(this);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    prepare3DViewport(0, 0, getWidth(), getHeight());

    glLoadIdentity();
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int w = getWidth();
    int h = getHeight();
    gluPerspective(60, w / h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        3, 3, 3, 
        0, 0, 0,
        0, 0, 1
    );
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glRotatef(zRot, 0, 0, 1);

    glBegin(GL_QUADS);

    // Draw the cube
    
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glVertex3f(1.0, 1.0,-1.0);
    glVertex3f(-1.0, 1.0,-1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);

    glColor3f(1.0, 0.0, 1.0); // Magenta
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);

    glColor3f(1.0, 1.0, 1.0); // White
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0,-1.0, 1.0);
    glVertex3f(1.0,-1.0, 1.0);

    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);

    glColor3f(0.0, 0.0, 1.0); // Blue
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);

    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);

    glEnd();

    glFlush();
    SwapBuffers();
}

void OpenGLPane::prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_COLOR_MATERIAL);
    glViewport(topleft_x, topleft_y, bottomrigth_x-topleft_x, bottomrigth_y-topleft_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float ratio_w_h = (float)(bottomrigth_x-topleft_x)/(float)(bottomrigth_y-topleft_y);
    gluPerspective(45, ratio_w_h, 0.1, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
/*void OpenGLPane::prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glViewport(topleft_x, topleft_y, bottomrigth_x-topleft_x, bottomrigth_y-topleft_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(topleft_x, bottomrigth_x, bottomrigth_y, topleft_y);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}*/
