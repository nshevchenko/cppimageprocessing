
class BasicApplication : public wxApp {
 public:
    virtual bool OnInit();
};


class MyFrame : public wxFrame {
 protected:
    wxMenuBar  *menuBar;//main menu bar
    wxMenu     *fileMenu;//file menu
    wxBitmap *back_bitmap; // offscreen memory buffer for drawing
    wxToolBar *toolbar;//tollbar not necessary to use
    int oldWidth, oldHeight; // save old dimensions

    wxBitmap bitmap;  //structure for the edited image
    wxImage *loadedImage; // image loaded from file
    int imgWidth, imgHeight; // image dimensions
    int stuffToDraw;

   /* declear message handler */
    void AddSaltPepperFilter(wxCommandEvent & event);
    void MinFiltering(wxCommandEvent & event); //---> To be modified!
    void MaxFiltering(wxCommandEvent & event); //---> To be modified!
    void MidPointFiltering(wxCommandEvent & event); //---> To be modified!
    void OnSaveImage(wxCommandEvent & event);

 public:
    MyFrame(const wxString title, int xpos, int ypos, int width, int height);
    virtual ~MyFrame();

    void OnExit(wxCommandEvent & event);
    void OnOpenFile(wxCommandEvent & event);
    void OnPaint(wxPaintEvent & event);

    DECLARE_EVENT_TABLE()

};

enum { NOTHING = 0,
       ORIGINAL_IMG,
};

enum { EXIT_ID = wxID_HIGHEST + 1,
       LOAD_FILE_ID,
       ALGORITHM_ONE,
       ALGORITHM_TWO,
       SAVE_IMAGE_ID,
       ALGORITHM_THREE, //--->To be modified!
};
