#include <wx/wx.h>
#include "window.h"
#include <wx/image.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/dc.h>
#include <iostream>

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

void MyFrame::OnShiftImage(wxCommandEvent & event){

    printf("On shifting...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());

    int shift = 20;

    for( int i = 0; i < imgWidth; i++)
       for(int j = 0; j < imgHeight; j++) {
          int r = (int) loadedImage->GetRed(i,j);   // red pixel value
          int g = (int) loadedImage->GetGreen(i,j); // green pixel value
          int b = (int) loadedImage->GetBlue(i,j); // blue pixel value
          // apply shifting
          r += shift;
          g += shift;
          b += shift;
          // check for max
          if(r > 255)
            r = 255;
          if(g > 255)
            g = 255;
          if(b > 255)
            b = 255;
          loadedImage->SetRGB(i,j,r, g, b);
    }

    printf(" Finished shifting.\n");
    Refresh();
}



//IMAGE SCALEING
void MyFrame::OnConvolutionImage(wxCommandEvent & event){

    printf("`Convoluting`...");
    free(loadedImage);

    // greyscale
    float const blur_kernel[3][3] = {
      {0, 1, 0},
      {1, 4, 1},
      {0, 1, 0},
    };
    float const sharpen_kernel[3][3] = {
      {-1, -1, -1},
      {-1,  9, -1},
      {-1, -1, -1},
    };

    loadedImage = new wxImage(bitmap.ConvertToImage());
    int intensity = 0;

    for( int i = 1; i < imgWidth; i++)
       for(int j = 1; j < imgHeight; j++){
          int newI = 0;
          int sumK = 0;
          for( int ik = -1; ik <= 1; ik++){
             for(int jk = -1; jk <= 1; jk++){
               if(sharpen_kernel[ik+1][jk+1] > 0){
                 intensity = (int) (loadedImage->GetRed(i+ik,j+jk));   // get pixel value (any of the rgb)
                 sumK += sharpen_kernel[ik+1][jk+1];
                 newI += intensity * sharpen_kernel[ik+1][jk+1];
               }
             }
           }
           newI = (int)(newI/sumK);
           printf("(%d,%d) [r = %d  | sumK = %x | b = %x] \n",i,j,newI,sumK,newI);
           loadedImage->SetRGB(i,j,newI,newI,newI);
    }
    printf(" Finished convoluting.\n");

    Refresh();
}


//My Function ---> To be modified!
void MyFrame::OnMyFunctionImage(wxCommandEvent & event){

    printf("My function...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());

    unsigned char r,g,b;

    for( int i=0;i<imgWidth;i++)
       for(int j=0;j<imgHeight;j++){
	// GET THE RGB VALUES
        r = loadedImage->GetRed(i,j);   // red pixel value
        g = loadedImage->GetGreen(i,j); // green pixel value
	b = loadedImage->GetBlue(i,j); // blue pixel value

	printf("(%d,%d) [r = %x  | g = %x | b = %x] \n",i,j,r,g,b);

	// SAVE THE RGB VALUES
	loadedImage->SetRGB(i,j,r,g,b);
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

  EVT_MENU ( ALGORITHM_ONE,  MyFrame::OnShiftImage)
  EVT_MENU ( ALGORITHM_TWO,  MyFrame::OnConvolutionImage)
  EVT_MENU ( SAVE_IMAGE_ID,  MyFrame::OnSaveImage)
  EVT_MENU ( ALGORITHM_THREE,  MyFrame::OnMyFunctionImage)//--->To be modified!

//###########################################################//
//----------------------END MY EVENTS -----------------------//
//###########################################################//

  EVT_PAINT (MyFrame::OnPaint)
END_EVENT_TABLE()
