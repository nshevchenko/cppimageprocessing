// author implementation NIK from the given template

enum { EXIT_ID = wxID_HIGHEST + 1,
       LOAD_FILE_ID,
       ALGORITHM_ONE,
       ALGORITHM_TWO,
       SAVE_IMAGE_ID,
       ALGORITHM_THREE,
       UNDO_ID,
       ALGORITHM_FIVE,
       ALGORITHM_FOUR, //--->To be modified!
};

enum ROI_CONFIG {
       NOTHING = 0,
       ORIGINAL_IMG = 1,
       ROI_IMG = 2

};


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
    wxImage *loadedImagePrevious; // image loaded from file
    wxImage *ROIImage; // image loaded from file

    ROI_CONFIG ROIConfig;
    int imgWidth, imgHeight; // image dimensions
    int stuffToDraw;
    int coordinatesROI[4]; // topleft(x,y), rightbotton(x,y)
    bool selectingROI; // is currently selecting a new ROI

   /* declear message handler */
    void MeanAndStandartDeviation(wxCommandEvent & event);
    void SimleThresholding(wxCommandEvent & event); //---> To be modified!
    void AutomatedThresholding(wxCommandEvent & event); //---> To be modified!
    void OnConvolutionImage(wxCommandEvent & event); //---> To be modified!
    void HistogramEqualisation(wxCommandEvent & event); //---> To be modified!
    void OnSaveImage(wxCommandEvent & event);
    void OnUndoPressed(wxCommandEvent & event);
    bool isRoiCoordinates(int i, int j);

 public:
    MyFrame(const wxString title, int xpos, int ypos, int width, int height);
    virtual ~MyFrame();

    void OnExit(wxCommandEvent & event);
    void OnOpenFile(wxCommandEvent & event);
    void OnPaint(wxPaintEvent & event);
    void OnMouseDown(wxMouseEvent& event);
    void OnMouseUp(wxMouseEvent& event);
    void OnRightDown(wxMouseEvent& event);
    DECLARE_EVENT_TABLE()

};
