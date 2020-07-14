//---------------------------------------------------------------------------

#ifndef cfgmainH
#define cfgmainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AdvEdit.hpp"
#include "AdvGlowButton.hpp"
#include "AdvGroupBox.hpp"
#include "AdvOfficeButtons.hpp"
#include "AdvOfficePager.hpp"
#include "AdvOfficePagerStylers.hpp"
#include "AdvPanel.hpp"
#include <ExtCtrls.hpp>
#include "AdvGrid.hpp"
#include "BaseGrid.hpp"
#include <Buttons.hpp>
#include <Grids.hpp>
#include "FolderDialog.hpp"
#include <Dialogs.hpp>
#include <ImgList.hpp>
#include <Sysutils.hpp>
#include "master_config.h"
#include <Graphics.hpp>
#include "AdvMemo.hpp"

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TAdvPanel *AdvPanel1;
        TAdvPanelStyler *AdvPanelStyler1;
        TAdvOfficePager *AdvOfficePager1;
        TAdvOfficePagerOfficeStyler *AdvOfficePagerOfficeStyler1;
        TAdvOfficePage *AdvOfficePage1;
        TAdvOfficePage *AdvOfficePage2;
        TAdvOfficePage *AdvOfficePage3;
        TAdvGlowButton *AdvGlowButton1;
        TAdvGlowButton *AdvGlowButton2;
        TBevel *Bevel1;
        TAdvOfficeRadioGroup *AdvOfficeRadioGroup1;
        TAdvGroupBox *AdvGroupBox1;
        TAdvEdit *Edit1;
        TAdvOfficeCheckBox *AdvOfficeCheckBox1;
        TAdvEdit *Edit2;
        TAdvGroupBox *AdvGroupBox2;
        TAdvEdit *AdvEdit2;
        TAdvGroupBox *AdvGroupBox3;
        TAdvEdit *AdvEdit3;
        TAdvEdit *AdvEdit4;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TAdvStringGrid *AdvStringGrid1;
        TAdvStringGrid *AdvStringGrid2;
        TFolderDialog *FolderDialog1;
        TSaveDialog *SaveDialog1;
        TOpenDialog *OpenDialog1;
        TAdvGlowButton *AdvGlowButton3;
        TImageList *ImageList1;
        TAdvOfficeCheckBox *AdvOfficeCheckBox2;
        TAdvGroupBox *AdvGroupBox4;
        TLabel *Label1;
        TImage *Image1;
        TLabel *Label2;
        TAdvOfficeCheckBox *AdvOfficeCheckBox3;
        TAdvOfficePage *AdvOfficePage4;
        TAdvMemo *AdvMemo1;
        TAdvGlowButton *AdvGlowButton4;
        TAdvGlowButton *AdvGlowButton5;
        TAdvGlowButton *AdvGlowButton6;
        TAdvGlowButton *AdvGlowButton7;
        void __fastcall AdvGlowButton2Click(TObject *Sender);
        void __fastcall AdvStringGrid1GetEditorType(TObject *Sender,
          int ACol, int ARow, TEditorType &AEditor);
        void __fastcall AdvStringGrid2CanEditCell(TObject *Sender,
          int ARow, int ACol, bool &CanEdit);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall AdvGlowButton1Click(TObject *Sender);
        void __fastcall AdvStringGrid2GetEditorType(TObject *Sender,
          int ACol, int ARow, TEditorType &AEditor);
        void __fastcall AdvGlowButton4Click(TObject *Sender);
        void __fastcall AdvGlowButton5Click(TObject *Sender);
        void __fastcall AdvGlowButton6Click(TObject *Sender);
        void __fastcall AdvGlowButton7Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);

private:	// User declarations
         void __fastcall TForm1::LoadConfig(void);
         void __fastcall TForm1::SetDefault(void);
         void __fastcall TForm1::SetReadFile(void);
         void __fastcall TForm1::GetWriteFile(void);
         void __fastcall TForm1::LoadDDF(void);
         void __fastcall TForm1::LoadPDF(void);
         void __fastcall TForm1::InitDDF(void);
         void __fastcall TForm1::InitPDF(void);
         void __fastcall TForm1::MakeDDF(char *bfr);
         void __fastcall TForm1::MakePDF(char *bfr);

         int __fastcall TForm1::GetItemCode(String maker,String item);
         String __fastcall TForm1::SetMakerName(int code);
         String __fastcall TForm1::SetItemName(int mcode,int icode);
         int __fastcall TForm1::GetInitCode(int gr,String str);
         int __fastcall TForm1::GetReadCode(int gr,String str);
         int __fastcall TForm1::GetWriteCode(int gr,String str);
         int __fastcall TForm1::GetMakerCode(int gr,String str);
         int __fastcall TForm1::GetMakerCode(String name);
         int __fastcall TForm1::GetServiceCode(String maker,String srv);
         String __fastcall TForm1::SetServiceName(int mcode,int icode);
         void __fastcall TForm1::ReSetCaption(void);

public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void __fastcall TForm1::InitPortTable(void);
        void __fastcall TForm1::SetPortTableTitle(int ix);
        SHMCFG    shmcfg;
        DDF ddf[50];
        PDF pdf[11];
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
