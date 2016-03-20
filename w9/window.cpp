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
  ROIConfig = ORIGINAL_IMG;
  fileMenu->Append(ALGORITHM_ONE, _T("&Mean and standart dev"));
  fileMenu->Append(ALGORITHM_TWO, _T("&Simple Thresholding"));
  fileMenu->Append(ALGORITHM_THREE, _T("&Automated Thresholding")); //--->To be modified!
  fileMenu->Append(ALGORITHM_FOUR, _T("&Convolution Blur")); //--->To be modified!
  fileMenu->Append(ALGORITHM_FIVE, _T("&Histogram Equalisation")); //--->To be modified!

  fileMenu->AppendSeparator();
  fileMenu->Append(SAVE_IMAGE_ID, _T("&Save image"));
  fileMenu->Append(UNDO_ID, _T("UNDO"));
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

// HISTOGRAM HELPERS

// FIND PR (rk)
void findPrRkValues(float PrRk[], int histogram[], int size){
    for(int i = 0; i < 256; i++){
       PrRk[i] = (double)histogram[i] / size;
    }
}
// find maximum value of histogram
void findMaxHistoValue(int histogram[], int max){
    for(int i = 0; i < 256; i++)
        if(max < histogram[i])
            max = histogram[i];
}
// find accumulative histogram values
void cumulativeHist(int cumhist[], int histogram[]){
    cumhist[0] = histogram[0];
    for(int i = 1; i < 256; i++)
        cumhist[i] = histogram[i] + cumhist[i-1];

}


//Image processing main algorithms
void MyFrame::MeanAndStandartDeviation(wxCommandEvent & event){
    printf("Mean and standar deviation...");
    free(loadedImage);
    loadedImagePrevious = new wxImage(bitmap.ConvertToImage());
    int L = 256;
    loadedImage = new wxImage(bitmap.ConvertToImage());
    int histogram[L];
    for(int i = 0; i < L; i++)
        histogram[i] = 0;

    int sizePic = loadedImage->GetWidth() * loadedImage->GetHeight();
    float scalar = 255.0/sizePic;

    // add up intensities of gray
    for( int i=0;i<imgWidth;i++)
       for(int j=0;j<imgHeight;j++) {
           int r = loadedImage->GetRed(i,j);
           histogram[r]++;
       }
    printf("histo[50] = %d ] \n",histogram[50]);

    float PrRk[L];
    findPrRkValues(PrRk, histogram, sizePic);

    int mean=0;
    for(int i = 0; i < L; i++)
        mean += i * PrRk[i];
    mean = mean;
    printf("mean = %d ] \n", mean);

    int variance = 0;
    for (int i = 0; i < L; i++){
        PrRk[i] = ((PrRk[i] - mean) * (PrRk[i] - mean)) * PrRk[i];
        variance += PrRk[i];
    }
    printf(" Finished standard deviation %d \n", variance);
    Refresh();
}

void MyFrame::SimleThresholding(wxCommandEvent & event){
    printf("Starting simple thresholding..");
    // load image
    free(loadedImage);
    loadedImagePrevious = new wxImage(bitmap.ConvertToImage());
    int L = 256;
    loadedImage = new wxImage(bitmap.ConvertToImage());

    // init histogram to 0
    int histogram[L];
    for(int i = 0; i < L; i++)
        histogram[i] = 0;

    int sizePic = loadedImage->GetWidth() * loadedImage->GetHeight();
    float scalar = 255.0/sizePic;

    // add up intensities of gray
    for( int i=0;i<imgWidth;i++)
       for(int j=0;j<imgHeight;j++) {
           int r = loadedImage->GetRed(i,j);
           histogram[r]++;
       }

    // find best delta (biggest delta)
    int maxDelta = 0;
    int thresholdBestGuess = 0;
    for(int i = 1; i < L; i++)
        if(histogram[i] - histogram[i-1] > maxDelta){
            maxDelta = histogram[i] - histogram[i-1];
            thresholdBestGuess  = i;
        }
    // add up intensities of gray
    for( int i=0;i<imgWidth;i++)
        for(int j=0;j<imgHeight;j++) {
            if(ROIConfig == ROI_IMG){
                if(!isRoiCoordinates(i,j))
                    continue;
            }
            cout << "inside " << isRoiCoordinates(i,j);
            int r = loadedImage->GetRed(i,j);
            if(r > thresholdBestGuess)
                 r = 255;
             else
                 r = 0;
            loadedImage->SetRGB(i,j,(int)r,(int)r,(int)r);
        }

    printf(" Finished simple thresholding.\n");
    Refresh();
}

void MyFrame::AutomatedThresholding(wxCommandEvent & event){
    printf("Starting Automated Thresholding..");
    // load image
    free(loadedImage);
    loadedImagePrevious = new wxImage(bitmap.ConvertToImage());
    int L = 256;
    loadedImage = new wxImage(bitmap.ConvertToImage());

    // init histogram to 0
    int histogram[L];
    for(int i = 0; i < L; i++)
        histogram[i] = 0;

    int sizePic = loadedImage->GetWidth() * loadedImage->GetHeight();
    float scalar = 255.0/sizePic;

    // add up intensities of gray
    for( int i=0;i<imgWidth;i++)
       for(int j=0;j<imgHeight;j++) {
           int r = loadedImage->GetRed(i,j);
           histogram[r]++;
       }

    // find best delta (biggest delta)
    int maxDelta = 0;
    int thresholdBestGuess = 0;
    for(int i = 1; i < L; i++)
        if(histogram[i] - histogram[i-1] > maxDelta){
            maxDelta = histogram[i] - histogram[i-1];
            thresholdBestGuess  = i;
        }
    // add up intensities of gray
    for( int i=0;i<imgWidth;i++)
        for(int j=0;j<imgHeight;j++) {
            if(ROIConfig == ROI_IMG){
                if(!isRoiCoordinates(i,j))
                    continue;
            }
            int r = loadedImage->GetRed(i,j);
            if(r > thresholdBestGuess)
                 r = 255;
             else
                 r = 0;
             loadedImage->SetRGB(i,j,(int)r,(int)r,(int)r);
         }

    printf(" Finished Automated Thresholding.\n");
    Refresh();
}

void MyFrame::HistogramEqualisation(wxCommandEvent & event){
    printf("Histogram equi function...");
    // load image
    free(loadedImage);
    loadedImagePrevious = new wxImage(bitmap.ConvertToImage());
    int L = 256;
    loadedImage = new wxImage(bitmap.ConvertToImage());

    // init histogram to 0
    int histogram[L];
    for(int i = 0; i < L; i++)
        histogram[i] = 0;

    int sizePic = loadedImage->GetWidth() * loadedImage->GetHeight();
    float scalar = 255.0/sizePic;

    // add up intensities of gray
    for( int i=0;i<imgWidth;i++)
       for(int j=0;j<imgHeight;j++) {
           int r = loadedImage->GetRed(i,j);
           histogram[r]++;
       }
    printf("histo[50] = %d ] \n",histogram[50]);

    float PrRk[L];
    findPrRkValues(PrRk, histogram, sizePic);
    printf("PrRk[50] = %f ] \n", PrRk[50]);

    // max intensity from histogram
    int max = histogram[0];
    findMaxHistoValue(histogram, max);
    printf("max = %d ] \n", max);

    // calculate cumulative histogram
    int cumHist[L];
    cumulativeHist(cumHist, histogram);

    int Sk[L];
    for(int i = 0; i < L; i++)
        Sk[i] = (int)(scalar * cumHist[i]);


    // add up intensities of gray
    for( int i=0;i<imgWidth;i++)
       for(int j=0;j<imgHeight;j++) {
           if(ROIConfig == ROI_IMG){
               if(!isRoiCoordinates(i,j))
                   continue;
           }
           int r = loadedImage->GetRed(i,j);
           int res = Sk[r];
           r = res;
           loadedImage->SetRGB(i,j,(int)r,(int)r,(int)r);
       }

    printf(" Finished histogram equi.\n");
    Refresh();
}

void MyFrame::OnConvolutionImage(wxCommandEvent & event){

    printf("`Convoluting`...");
    free(loadedImage);
    loadedImagePrevious = new wxImage(bitmap.ConvertToImage());
    // greyscale
    float const blur_kernel[3][3] = {
      {0, 1, 0},
      {1, 4, 1},
      {0, 1, 0},
    };

    loadedImage = new wxImage(bitmap.ConvertToImage());
    int intensity = 0;

    for( int i = 1; i < imgWidth; i++)
       for(int j = 1; j < imgHeight; j++){
          int newI = 0;
          int sumK = 0;
          for( int ik = -1; ik <= 1; ik++){
             for(int jk = -1; jk <= 1; jk++){
                 if(blur_kernel[ik+1][jk+1] > 0){
                     intensity = (int) (loadedImage->GetRed(i+ik,j+jk));   // get pixel value (any of the rgb)
                     sumK += blur_kernel[ik+1][jk+1];
                     newI += intensity * blur_kernel[ik+1][jk+1];
                 }
             }
           }
           newI = (int)(newI/sumK);
           printf("(%d,%d) [r = %d  | sumK = %x | b = %x] \n",i,j,newI,sumK,newI);
           if(ROIConfig == ROI_IMG){
               if(!isRoiCoordinates(i,j))
                   continue;
           }
           loadedImage->SetRGB(i,j,newI,newI,newI);
    }
    printf(" Finished convoluting.\n");

    Refresh();
}

// GLOBAL UTILS
void MyFrame::OnUndoPressed(wxCommandEvent & event){
        loadedImage = loadedImagePrevious;
    Refresh();
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

bool MyFrame::isRoiCoordinates(int i, int j){
    // top left
    int TOP_LEFT_X = coordinatesROI[0];
    int TOP_LEFT_Y = coordinatesROI[1];
    // bottom right
    int BOTTOM_R_X = coordinatesROI[2];
    int BOTTOM_R_Y = coordinatesROI[3];

    if( (j>TOP_LEFT_Y && j<BOTTOM_R_Y) && (i>TOP_LEFT_X && i<BOTTOM_R_X) )
        return true;
    return false;
}

void MyFrame::OnMouseDown(wxMouseEvent& event){
    // event.GetX()
    if(ROIConfig == ORIGINAL_IMG){
        cout << "Starting ROI. " << wxString::FromDouble(event.GetX()) <<  " " <<  wxString::FromDouble(event.GetY()) << endl;
        selectingROI = true;
        ROIConfig = ROI_IMG;
        coordinatesROI[0] = event.GetX();
        coordinatesROI[1] = event.GetY();
    }
}

void MyFrame::OnMouseUp(wxMouseEvent& event){
    // event.GetX()
    if(selectingROI && ROIConfig == ROI_IMG){
        cout << "Finished ROI. " << wxString::FromDouble(event.GetX()) <<  " " <<  wxString::FromDouble(event.GetY()) << endl;
        selectingROI = false;
        coordinatesROI[2] = event.GetX();
        coordinatesROI[3] = event.GetY();
        cout << "create subimage";
    }
}

void MyFrame::OnRightDown(wxMouseEvent& event){
    // event.GetX()
    if(!selectingROI && ROIConfig == ROI_IMG){
        cout << "Closing ROI";
        selectingROI = false;
        ROIConfig = ORIGINAL_IMG;
    }
}


BEGIN_EVENT_TABLE (MyFrame, wxFrame)
  EVT_MENU ( LOAD_FILE_ID,  MyFrame::OnOpenFile)
  EVT_MENU ( EXIT_ID,  MyFrame::OnExit)

    //###########################################################//
    //----------------------START MY EVENTS ---------------------//
    //###########################################################//

  EVT_MENU ( ALGORITHM_ONE,  MyFrame::MeanAndStandartDeviation)
  EVT_MENU ( ALGORITHM_TWO,  MyFrame::SimleThresholding)
  EVT_MENU ( SAVE_IMAGE_ID,  MyFrame::OnSaveImage)
  EVT_MENU ( ALGORITHM_THREE,  MyFrame::AutomatedThresholding)//--->To be modified!
  EVT_MENU ( ALGORITHM_FOUR,  MyFrame::OnConvolutionImage)
  EVT_MENU ( UNDO_ID,  MyFrame::OnUndoPressed)
  EVT_MENU ( ALGORITHM_FIVE,  MyFrame::HistogramEqualisation)
  EVT_LEFT_DOWN(MyFrame::OnMouseDown)
  EVT_LEFT_UP(MyFrame::OnMouseUp)
  EVT_RIGHT_DOWN(MyFrame::OnRightDown)
    //###########################################################//
    //----------------------END MY EVENTS -----------------------//
    //###########################################################//

  EVT_PAINT (MyFrame::OnPaint)
END_EVENT_TABLE()
