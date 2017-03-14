#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class cadre : public wxFrame
{
  public :
    cadre();
  private :
    void OnCharger(wxCommandEvent& e);
    void OnSave(wxCommandEvent& e);
    void OnExit(wxCommandEvent& e);
    void OnAfficherPersonnes(wxCommandEvent& e);
};
