#include <wx/wx.h>
#include "window.h"
#include <wx/image.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/dc.h>
#include <iostream>
#include <map>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

using namespace std;

static const wxChar *FILETYPES = _T("All files (*.*)|*.*");

IMPLEMENT_APP(BasicApplication)

bool BasicApplication::OnInit(){
  wxInitAllImageHandlers();
  MyFrame *frame = new MyFrame(_("Basic Frame"), 50, 50, 700, 400);
  frame->Show(TRUE);
  SetTopWindow(frame);
  return TRUE;
}

MyFrame::MyFrame(const wxString title, int xpos, int ypos, int width, int height): wxFrame((wxFrame *) NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height)){
  fileMenu = new wxMenu;
  fileMenu->Append(LOAD_FILE_ID, _T("&Open file"));
  fileMenu->AppendSeparator();

  fileMenu->Append(ALGORITHM_ONE, _T("&Alg 1"));
  fileMenu->Append(ALGORITHM_TWO, _T("&Alg 2"));
  fileMenu->Append(ALGORITHM_THREE, _T("&Alg 3")); //--->To be modified!
  fileMenu->Append(ALGORITHM_FOUR, _T("&Alg 4")); //--->To be modified!

  fileMenu->AppendSeparator();
  fileMenu->Append(SAVE_IMAGE_ID, _T("&Save image"));
  fileMenu->Append(EXIT_ID, _T("E&xit"));

  menuBar = new wxMenuBar;
  menuBar->Append(fileMenu, _T("&File"));

  SetMenuBar(menuBar);
  CreateStatusBar(3);
  oldWidth = 0;
  oldHeight = 0;
  loadedImage = 0;

  /* initialise the variables that we added */
  imgWidth = imgHeight = 0;
  stuffToDraw = 0;

}

MyFrame::~MyFrame(){
  /* release resources */
  if(loadedImage){
    loadedImage->Destroy();
    loadedImage = 0;
  }

}

void MyFrame::OnOpenFile(wxCommandEvent & event){
  wxFileDialog *openFileDialog = new wxFileDialog ( this, _T("Open file"), _T(""), _T(""), FILETYPES, wxFD_OPEN, wxDefaultPosition);
  if(openFileDialog->ShowModal() == wxID_OK){
    wxString filename = openFileDialog->GetFilename();
    wxString path = openFileDialog->GetPath();
    printf("Loading image form file...");
    loadedImage = new wxImage(path); //Image Loaded form file
    if(loadedImage->Ok()){
      stuffToDraw = ORIGINAL_IMG;    // set the display flag
      printf("Done! \n");
    }
    else {
      printf("error:...");
      loadedImage->Destroy();
      loadedImage = 0;
    }
    Refresh();
  }
}


//###########################################################//
//-----------------------------------------------------------//
//---------- DO NOT MODIFY THE CODE ABOVE--------------------//
//-----------------------------------------------------------//
//###########################################################//

void MyFrame::NegativeLinear(wxCommandEvent & event){

    printf("Negative Linear...");
        free(loadedImage);
        loadedImage = new wxImage(bitmap.ConvertToImage());

        for( int i=0;i<imgWidth;i++)
           for(int j=0;j<imgHeight;j++){
     	loadedImage->SetRGB(i,j,255-loadedImage->GetRed(i,j),
    				255-loadedImage->GetGreen(i,j),
    				255-loadedImage->GetBlue(i,j));
        }

        printf(" Finished inverting.\n");
        Refresh();
}


//IMAGE min filtering
void MyFrame::LogaritmicFun(wxCommandEvent & event){
    printf("Logarithmic function...");
        free(loadedImage);
        loadedImage = new wxImage(bitmap.ConvertToImage());
        float L = log(255);
        for( int i=0;i<imgWidth;i++)
           for(int j=0;j<imgHeight;j++) {
        //    printf("sk(%d,%d) [r = %d ] \n",i,j,loadedImage->GetRed(i,j));
               double r = loadedImage->GetRed(i,j);
               double g = loadedImage->GetGreen(i,j);
               double b = loadedImage->GetBlue(i,j);
               //  log (values 1-255) / log(255) map to (0-1) * 255
               r =  (log(r+1)/L)*255.0;
               g =  (log(g+1)/L)*255.0;
               b =  (log(b+1)/L)*255.0;
            //    printf("sk(%d,%d) [r = %f ] \n",i,j,r);

               loadedImage->SetRGB(i,j,(int)r,(int)g,(int)b);
            }
        // printf(" Finished inverting.\n");
        Refresh();
}


//IMAGE SCALEING
void MyFrame::PowerLawFun(wxCommandEvent & event){

    printf("Power Law function...");
        free(loadedImage);
        loadedImage = new wxImage(bitmap.ConvertToImage());

        for( int i=0;i<imgWidth;i++)
           for(int j=0;j<imgHeight;j++) {
               float r = loadedImage->GetRed(i,j) /255.0f;
               float g = loadedImage->GetGreen(i,j) /255.0f;
               float b = loadedImage->GetBlue(i,j) /255.0f;
               printf("sk(%d,%d) [r = %f ] \n",i,j,r);
               int c = 1;
               r = pow(r,0.6f);

               r = r * 255.0f;
            //    printf("sk(%d,%d) [r = %f ] \n",i,j,r);

               loadedImage->SetRGB(i,j,(int)r,(int)r,(int)r);
            }

        printf(" Finished power law.\n");
        Refresh();
}


map<int,int> create_map()
{
  map<int,int> m;
  m[0] = 1;
  m[1] = 1;
  m[2] = 1;
  m[3] = 1;
  m[4] = 2;
  m[5] = 4;
  m[6] = 6;
  m[7] = 8;
  m[8] = 10;
  m[9] = 10;
  m[10] = 10;
  return m;
}

//My Function ---> To be modified!
void MyFrame::RandomLookUp(wxCommandEvent & event){

    printf("My function...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());
    map<int, int> table = create_map();
    //  {
    //
    // };

    for( int i=0;i<imgWidth;i++)
       for(int j=0;j<imgHeight;j++) {
           float r = loadedImage->GetRed(i,j) /255.0f;
           float g = loadedImage->GetGreen(i,j) /255.0f;
           float b = loadedImage->GetBlue(i,j) /255.0f;

           // look up table mapped from 0 - 10
           r = table[(int)(r*10)]/10.0f * 255.0f;
           g = table[(int)(g*10)]/10.0f * 255.0f;
           b = table[(int)(b*10)]/10.0f * 255.0f;

        //    printf("sk(%d,%d) [r = %f ] \n",i,j,r);

           loadedImage->SetRGB(i,j,(int)r,(int)g,(int)b);
        }

    printf(" Finished My function.\n");
    Refresh();
}


//###########################################################//
//-----------------------------------------------------------//
//---------- DO NOT MODIFY THE CODE BELOW--------------------//
//-----------------------------------------------------------//
//###########################################################//


//IMAGE SAVING
void MyFrame::OnSaveImage(wxCommandEvent & event){

    printf("Saving image...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());

    loadedImage->SaveFile(wxT("Saved_Image.bmp"), wxBITMAP_TYPE_BMP);

    printf("Finished Saving.\n");
}


void MyFrame::OnExit (wxCommandEvent & event){
  Close(TRUE);
}


void MyFrame::OnPaint(wxPaintEvent & event){
  wxPaintDC dc(this);
  int cWidth, cHeight;
  GetSize(&cWidth, &cHeight);
  // if ((back_bitmap == NULL) || (oldWidth != cWidth) || (oldHeight != cHeight)) {
  //   if (back_bitmap != NULL)
  //     delete back_bitmap;
  //   back_bitmap = new wxBitmap(cWidth, cHeight);
  //   oldWidth = cWidth;
  //   oldHeight = cHeight;
  // }
  // wxMemoryDC *temp_dc = new wxMemoryDC(&dc);
  // temp_dc->SelectObject(*back_bitmap);
  // // We can now draw into the offscreen DC...
  // temp_dc->Clear();
  if(loadedImage)
    dc.DrawBitmap(wxBitmap(*loadedImage), 0, 0, false);//given bitmap xcoord y coord and transparency

  switch(stuffToDraw){
     case NOTHING:
        break;
     case ORIGINAL_IMG:
      bitmap.CleanUpHandlers(); // clean the actual image header
       bitmap = wxBitmap(*loadedImage); // Update the edited/loaded image
       break;
  }

// update image size
imgWidth  = (bitmap.ConvertToImage()).GetWidth();
imgHeight = (bitmap.ConvertToImage()).GetHeight();



 // temp_dc->SelectObject(bitmap);//given bitmap

  //end draw all the things
  // Copy from this DC to another DC.
  // dc.Blit(0, 0, cWidth, cHeight, temp_dc, 0, 0);
  // delete temp_dc; // get rid of the memory DC
}

BEGIN_EVENT_TABLE (MyFrame, wxFrame)
  EVT_MENU ( LOAD_FILE_ID,  MyFrame::OnOpenFile)
  EVT_MENU ( EXIT_ID,  MyFrame::OnExit)

//###########################################################//
//----------------------START MY EVENTS ---------------------//
//###########################################################//

  EVT_MENU ( ALGORITHM_ONE,  MyFrame::NegativeLinear)
  EVT_MENU ( ALGORITHM_TWO,  MyFrame::LogaritmicFun)
  EVT_MENU ( SAVE_IMAGE_ID,  MyFrame::OnSaveImage)
  EVT_MENU ( ALGORITHM_THREE,  MyFrame::PowerLawFun)//--->To be modified!

//###########################################################//
//----------------------END MY EVENTS -----------------------//
//###########################################################//

  EVT_PAINT (MyFrame::OnPaint)
END_EVENT_TABLE()
