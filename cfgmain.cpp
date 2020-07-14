//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "cfgmain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvEdit"
#pragma link "AdvGlowButton"
#pragma link "AdvGroupBox"
#pragma link "AdvOfficeButtons"
#pragma link "AdvOfficePager"
#pragma link "AdvOfficePagerStylers"
#pragma link "AdvPanel"
#pragma link "AdvGrid"
#pragma link "BaseGrid"
#pragma link "FolderDialog"
#pragma link "AdvMemo"
#pragma resource "*.dfm"
TForm1 *Form1;


const String PORT_TABLE[15] = {"MASTER",
                               "SLAVE",
                               "MASTER RDO",
                               "SLAVE RDO",
                               "TOTALIZER ",
                               "CAMERA",
                               "NDS",
                               "FAIL DETECTOR",
                               "EXTRA PORT1",
                               "EXTRA PORT2",
                               "EXTRA PORT3",
                               "EXTRA PORT4",
                               "EXTRA PORT5",
                               "EXTRA PORT6",
                               "EXTRA PORT7"};

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AdvGlowButton2Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AdvStringGrid1GetEditorType(TObject *Sender,
      int ACol, int ARow, TEditorType &AEditor)
{

        if(ARow==1)                 AEditor = edNormal;
        else if(ARow==2 || ARow==3) AEditor = edFloat;
        else if(ARow==4)
        {
                AEditor = edComboList;
                AdvStringGrid1->ClearComboString();

                String mk =  AdvStringGrid1->Cells[ACol][5];
                if(mk=="") return;
                int ixx=1000;
                for(int i=0;i<50;i++)
                {
                        if(ddf[i].maker==mk)  ixx=i;
                }
                if(ixx>=50) return;

                for(int i=0;i<50;i++)
                {
                        String s = ddf[ixx].calc[i];
                        if(s!="") AdvStringGrid1->AddComboString(s);
                }
        }

        else if(ARow==5)
        {
                AEditor = edComboList;
                AdvStringGrid1->ClearComboString();
                for(int i=0;i<50;i++)
                {
                        String s = ddf[i].maker;
                        if(s!="")   AdvStringGrid1->AddComboString(s);
                }

        }
        else if(ARow==6)
        {
                AEditor = edComboList;
                AdvStringGrid1->ClearComboString();
                String mk =  AdvStringGrid1->Cells[ACol][5];
                if(mk=="") return;
                int ixx=1000;
                for(int i=0;i<50;i++)
                {
                        if(ddf[i].maker==mk)  ixx=i;
                }
                if(ixx>=50) return;

                for(int i=0;i<5;i++)
                {
                        String s = ddf[ixx].item[i];
                        if(s!="") AdvStringGrid1->AddComboString(s);
                }

        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::InitPortTable(void)
{
        AdvStringGrid2->RowCount=10;

        for(int i=0;i<10;i++)  SetPortTableTitle(i);

}

void __fastcall TForm1::SetPortTableTitle(int ix)
{
        int cnt =  AdvStringGrid2->RowCount;
        if(ix>0)   AdvStringGrid2->RowCount = cnt+9;
        int x =    AdvStringGrid2->RowCount-9;

        AdvStringGrid2->Colors[1][x+1] = clGreen;

        for(int i=0;i<10;i++) AdvStringGrid2->Colors[i][x] = clGreen;
        for(int i=2;i<10;i++)
        {
                for(int j=2;j<=8;j++)  AdvStringGrid2->Colors[i][x+j] = clGreen;
        }
        AdvStringGrid2->FontColors[0][x] = clYellow;
        AdvStringGrid2->Cells[0][x] = PORT_TABLE[ix];
        AdvStringGrid2->Cells[0][x+1] = "Port No";
        AdvStringGrid2->Cells[0][x+2] = "Init Service";
        AdvStringGrid2->Cells[0][x+3] = "Read Service";
        AdvStringGrid2->Cells[0][x+4] = "Write Service";
        AdvStringGrid2->Cells[0][x+5] = "Link Device";
        AdvStringGrid2->Cells[0][x+6] = "Link Item#1";
        AdvStringGrid2->Cells[0][x+7] = "Link Item#2";
        AdvStringGrid2->Cells[0][x+8] = "Link Item#3";
}
void __fastcall TForm1::AdvStringGrid2CanEditCell(TObject *Sender,
      int ARow, int ACol, bool &CanEdit)
{
        if(ARow<=0) CanEdit=false;
        else if((ARow-1)%9==0) CanEdit =false;
        else if(ACol>1 && (((ARow-1)%9)>1)) CanEdit=false;
        else if(ACol==1 && (ARow-1)%9==1) CanEdit =false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
        if(FolderDialog1->Execute())
        {
                AdvEdit4->Text =  FolderDialog1->Directory;
        }        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
        #ifndef _LANG_ENGLISH
        OpenDialog1->Filter="SEH사용자 설정파일(*.shg)|*.shg";
        #else
        OpenDialog1->Filter="SEH System Setting File(*.shg)|*.shg";
        #endif
        if(OpenDialog1->Execute())
        {
           AdvEdit3->Text = OpenDialog1->FileName;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::InitDDF(void)
{
        for(int i=0;i<50;i++)
        {
                ddf[i].maker="";
                for(int j=0;j<5;j++) ddf[i].item[j]="";
        }
}
void __fastcall TForm1::InitPDF(void)
{
        for(int i=0;i<10;i++)
        {
                for(int j=0;j<50;j++)
                {
                        pdf[i].init[j]="";
                        pdf[i].read[j]="";
                        pdf[i].write[j]="";
                        pdf[i].maker[j]="";

                }
        }
}

void __fastcall TForm1::MakeDDF(char *bfr)
{
        String s_ddf = String(bfr);
        int len = s_ddf.Length();

        int ix =-1;
        int iy =0;
        int iz=0;
        int k=1;
        int kk=1;
        int jj=1;

        for(int i=1;i<=len;i++)
        {
                String st = s_ddf.SubString(i,1);
                if(st=="[")
                {
                        ix++;
                        k=i;

                }
                else if(st=="]")
                {
                        String s = s_ddf.SubString(k+1,i-1-k);
                        ddf[ix].maker = s;
                         iy=0;
                         iz=0;
                }
                else if(st=="{")
                {
                        kk=i;
                }
                else if(st=="}")
                {
                        String s =   s_ddf.SubString(kk+1,i-1-kk);
                        ddf[ix].item[iy++] = s;
                }
                else if(st=="<")
                {
                        jj=i;
                }
                else if(st==">")
                {
                       String s =   s_ddf.SubString(jj+1,i-1-jj);
                       ddf[ix].calc[iz++] = s;
                }

        }



}

void __fastcall TForm1::MakePDF(char *bfr)
{
        String s_pdf = String(bfr);
        String target="";
        int len = s_pdf.Length();

        int ix =-1;
        int iy =-1;
        int iz=0;
        int k=1;
        int kk=1;
        int kx=1;
        int ky=1;

        for(int i=1;i<=len;i++)
        {
                String st = s_pdf.SubString(i,1);
                if(st=="[")
                {
                        k=i;
                }
                else if(st=="]")
                {
                        String s = s_pdf.SubString(k,i-k+1);

                        if(s=="[MASTER PORT]")       ix=0;
                        else if(s=="[SLAVE PORT]")   ix=1;
                        else if(s=="[MASTER RDO]")   ix=2;
                        else if(s=="[SLAVE RDO]")    ix=3;
                        else if(s=="[TOTALIZER]")    ix=4;
                        else if(s=="[CAMERA PORT]")  ix=5;
                        else if(s=="[NDS PORT]")     ix=6;
                        else if(s=="[FAIL DETECTOR]")ix=7;
                        else if(s=="[EXTRA PORT1]")  ix=8;
                        else if(s=="[EXTRA PORT2]")  ix=9;
                        //else if(s=="[EXTRA PORT3]")  ix=8;
                        //else if(s=="[EXTRA PORT4]")  ix=9;

                }
                else if(st=="(")
                {
                        kk=i;
                }
                else if(st==")")
                {
                       target = s_pdf.SubString(kk,i-kk+1);
                       iy=0;
                }
                else if(st=="<")
                {
                        kx=i;
                }
                else if(st==">")
                {
                        String s = s_pdf.SubString(kx,i-kx+1);
                        if(target=="(INIT)")       pdf[ix].init[iy++]=s;
                        else if(target=="(READ)")  pdf[ix].read[iy++]=s;
                        else if(target=="(WRITE)") pdf[ix].write[iy++]=s;
                        else if(target=="(MAKER)") pdf[ix].maker[iy++]=s;
                }
        }
}



void __fastcall TForm1::LoadDDF(void)
{

        String s_ddf;
        InitDDF();

        int fp=FileOpen(DEVICE_LIST_FILE_NAME,fmOpenRead) ;
        if(fp==-1)
        {
                #ifndef _LANG_ENGLISH
                Application->MessageBox("device.sdd 파일을 찿을수 없습니다","오류",MB_OK);
                #else
                Application->MessageBox("Can not found device.sdd file","Error",MB_OK);
                #endif
                Close();
        }
        else
        {
                int len = FileSeek(fp,0,2);
                char *bfr = new char[len+1];
                FileSeek(fp,0,0);
                int rbytes = FileRead(fp,bfr,len);
                FileClose(fp);
                MakeDDF(bfr);
                delete bfr;
        }
}

void __fastcall TForm1::LoadPDF(void)
{

        String s_ddf;
        InitPDF();

        int fp=FileOpen(PORT_LIST_FILE_NAME,fmOpenRead) ;
        if(fp==-1)
        {
                #ifndef _LANG_ENGLISH
                Application->MessageBox("device.sdd 파일을 찿을수 없습니다","오류",MB_OK);
                #else
                Application->MessageBox("Can not found device.sdd file","Error",MB_OK);
                #endif
                Close();
        }
        else
        {
                int len = FileSeek(fp,0,2);
                char *bfr = new char[len+1];
                FileSeek(fp,0,0);
                int rbytes = FileRead(fp,bfr,len);
                FileClose(fp);
                MakePDF(bfr);
                delete bfr;
        }
}

void __fastcall TForm1::LoadConfig(void)
{
        int fp=FileOpen(MASTER_CONFIG_FILE_NAME,fmOpenRead);
        if(fp==-1)
        {
                SetDefault();
        }
        else
        {
                FileRead(fp,(char *)&shmcfg,sizeof(SHMCFG));
                FileClose(fp);
                SetReadFile();
        }

}


void __fastcall TForm1::SetDefault(void)
{
        #ifndef _LANG_ENGLISH
        AdvEdit2->Text="비인가 사용자";
        #else
        AdvEdit2->Text="Unregistered user";
        #endif
        AdvOfficeRadioGroup1->ItemIndex=0;
        Edit1->IntValue=16;
        Edit2->IntValue=1;
        AdvOfficeCheckBox1->Checked=false;
        AdvOfficeCheckBox2->Checked=false;
        AdvEdit4->Text="";
        AdvEdit3->Text="";

        #ifndef _LANG_ENGLISH
        AdvStringGrid1->Cells[1][1]="중량";
        #else
        AdvStringGrid1->Cells[1][1]="Weight";
        #endif
        AdvStringGrid1->Cells[1][2]=1500;
        AdvStringGrid1->Cells[1][3]=0;

        AdvStringGrid1->Cells[2][1]="NA";
        AdvStringGrid1->Cells[2][2]=0;
        AdvStringGrid1->Cells[2][3]=0;

        AdvStringGrid1->Cells[3][1]="NA";
        AdvStringGrid1->Cells[3][2]=0;
        AdvStringGrid1->Cells[3][3]=0;

        AdvStringGrid1->Cells[4][1]="NA";
        AdvStringGrid1->Cells[4][2]=0;
        AdvStringGrid1->Cells[4][3]=0;

        AdvStringGrid1->Cells[5][1]="NA";
        AdvStringGrid1->Cells[5][2]=0;
        AdvStringGrid1->Cells[5][3]=0;

}

void __fastcall TForm1::SetReadFile(void)
{

        AdvEdit2->Text                  =shmcfg.customer;
        AdvOfficeRadioGroup1->ItemIndex =shmcfg.lane-1;
        Edit1->IntValue                 =shmcfg.drop;
        Edit2->IntValue                 =shmcfg.itn;
        AdvOfficeCheckBox1->Checked     =shmcfg.labeller;
        AdvOfficeCheckBox2->Checked     =shmcfg.totalizer;
        AdvOfficeCheckBox3->Checked     =shmcfg.do_ext;
        AdvEdit4->Text                  =shmcfg.work_dir;
        AdvEdit3->Text                  =shmcfg.work_fn;

        for(int i=0;i<5;i++)
        {
            AdvStringGrid1->Cells[1+i][1] =shmcfg.item[i].name;
            AdvStringGrid1->Floats[1+i][2] =shmcfg.item[i].max;
            AdvStringGrid1->Floats[1+i][3] =shmcfg.item[i].min;
            AdvStringGrid1->Cells[1+i][4] =SetServiceName(shmcfg.item[i].maker,shmcfg.item[i].service);
            AdvStringGrid1->Cells[1+i][5] =SetMakerName(shmcfg.item[i].maker);
            AdvStringGrid1->Cells[1+i][6] =SetItemName(shmcfg.item[i].maker,shmcfg.item[i].item);
        }

        for(int i=0;i<10;i++)
        {
             int y = 2+i*9;
             for(int j=0;j<8;j++)   AdvStringGrid2->Ints[2+j][y] = shmcfg.shport[i].port[j];

             int val = shmcfg.shport[i].svc_init;
             if(val<0) val=0;
             AdvStringGrid2->Cells[1][y+1] = pdf[i].init[val];

             val = shmcfg.shport[i].svc_read;
             if(val<0) val=0;
             AdvStringGrid2->Cells[1][y+2] = pdf[i].read[val];

             val = shmcfg.shport[i].svc_write;
             if(val<0) val=0;
             AdvStringGrid2->Cells[1][y+3] = pdf[i].write[val];

             val = shmcfg.shport[i].maker;
             if(val<0) val =0;
             AdvStringGrid2->Cells[1][y+4] = pdf[i].maker[val];
             String smaker = pdf[i].maker[val];
             smaker = smaker.SubString(2,smaker.Length()-2);
             int mcode = GetMakerCode(smaker);

             AdvStringGrid2->Cells[1][y+5] = SetItemName(mcode,shmcfg.shport[i].link[0]);
             AdvStringGrid2->Cells[1][y+6] = SetItemName(mcode,shmcfg.shport[i].link[1]);
             AdvStringGrid2->Cells[1][y+7] = SetItemName(mcode,shmcfg.shport[i].link[2]);
        }
}


int __fastcall TForm1::GetMakerCode(String name)
{
        for(int i=0;i<50;i++)
        {
                String s = ddf[i].maker;
                if(s==name) return i;
        }
        return -1;
}


int __fastcall TForm1::GetItemCode(String maker,String item)
{
        int ix = GetMakerCode(maker);
        if(ix<0) return -1;
        for(int i=0;i<5;i++)
        {
                String s = ddf[ix].item[i];
                if(s==item) return i;

        }
        return -1;
}

int __fastcall TForm1::GetServiceCode(String maker,String srv)
{
        int ix = GetMakerCode(maker);
        if(ix<0) return -1;
        for(int i=0;i<50;i++)
        {
                String s = ddf[ix].calc[i];
                if(s==srv) return i;

        }
        return -1;
}


String __fastcall TForm1::SetMakerName(int code)
{
        if(code>=50 ||code<0) return "";
        return ddf[code].maker;
}

String __fastcall TForm1::SetItemName(int mcode,int icode)
{
        if(mcode>=50 ||mcode<0) return "";
        if(icode>=5  ||icode<0) return "";

        return ddf[mcode].item[icode];
}

String __fastcall TForm1::SetServiceName(int mcode,int icode)
{
        if(mcode>=50 ||mcode<0) return "";
        if(icode>=50  ||icode<0) return "";

        return ddf[mcode].calc[icode];
}

int __fastcall TForm1::GetInitCode(int gr,String str)
{
        for(int i=0;i<50;i++)
        {
                String s = pdf[gr].init[i];
                if(s==str) return i;
        }
        return -1;
}

int __fastcall TForm1::GetReadCode(int gr,String str)
{
        for(int i=0;i<50;i++)
        {
                String s = pdf[gr].read[i];
                if(s==str) return i;
        }
        return -1;

}

int __fastcall TForm1::GetWriteCode(int gr,String str)
{
        for(int i=0;i<50;i++)
        {
                String s = pdf[gr].write[i];
                if(s==str) return i;
        }
        return -1;

}
int __fastcall TForm1::GetMakerCode(int gr,String str)
{
        for(int i=0;i<50;i++)
        {
                String s = pdf[gr].maker[i];
                if(s==str) return i;
        }
        return -1;

}



void __fastcall TForm1::GetWriteFile(void)
{

        strcpy(shmcfg.customer,AdvEdit2->Text.c_str())           ;
        shmcfg.lane             =AdvOfficeRadioGroup1->ItemIndex+1 ;
        shmcfg.drop             =Edit1->IntValue                 ;
        shmcfg.itn              =Edit2->IntValue                 ;
        shmcfg.labeller         =AdvOfficeCheckBox1->Checked     ;
        shmcfg.totalizer        =AdvOfficeCheckBox2->Checked     ;
        shmcfg.do_ext           =AdvOfficeCheckBox3->Checked     ;
        strcpy(shmcfg.work_dir,AdvEdit4->Text.c_str())           ;
        strcpy(shmcfg.work_fn,AdvEdit3->Text.c_str())            ;

        for(int i=0;i<5;i++)
        {
            strcpy(shmcfg.item[i].name,AdvStringGrid1->Cells[1+i][1].c_str()) ;
            shmcfg.item[i].max          =AdvStringGrid1->Floats[1+i][2] ;
            shmcfg.item[i].min          =AdvStringGrid1->Floats[1+i][3] ;
            shmcfg.item[i].service      =GetServiceCode(AdvStringGrid1->Cells[1+i][5],AdvStringGrid1->Cells[1+i][4]) ;
            shmcfg.item[i].maker        =GetMakerCode(AdvStringGrid1->Cells[1+i][5]);
            shmcfg.item[i].item         =GetItemCode(AdvStringGrid1->Cells[1+i][5],AdvStringGrid1->Cells[1+i][6]);
        }

        for(int i=0;i<10;i++)
        {
             int y = 2+i*9;
             for(int j=0;j<8;j++)   shmcfg.shport[i].port[j]    =AdvStringGrid2->Ints[2+j][y];
             shmcfg.shport[i].svc_init          =GetInitCode(i,AdvStringGrid2->Cells[1][y+1]) ;
             shmcfg.shport[i].svc_read          =GetReadCode(i,AdvStringGrid2->Cells[1][y+2]) ;
             shmcfg.shport[i].svc_write         =GetWriteCode(i,AdvStringGrid2->Cells[1][y+3]) ;
             shmcfg.shport[i].maker        =GetMakerCode(i,AdvStringGrid2->Cells[1][y+4]) ;
             String maker =  AdvStringGrid2->Cells[1][y+4];
             maker = maker.SubString(2,maker.Length()-2);
             shmcfg.shport[i].link[0]           =GetItemCode(maker,AdvStringGrid2->Cells[1][y+5]) ;
             shmcfg.shport[i].link[1]           =GetItemCode(maker,AdvStringGrid2->Cells[1][y+6]) ;
             shmcfg.shport[i].link[2]           =GetItemCode(maker,AdvStringGrid2->Cells[1][y+7]) ;
        }


}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
        #ifndef _LANG_ENGLISH
        for(int i=1;i<=5;i++) AdvStringGrid1->Cells[i][0] = "아이템"+String(i);
        AdvStringGrid1->Cells[0][0] = "아이템설정";
        AdvStringGrid1->Cells[0][1] = "아이템명";
        AdvStringGrid1->Cells[0][2] = "최대값";
        AdvStringGrid1->Cells[0][3] = "최소값";
        AdvStringGrid1->Cells[0][4] = "연산프로토콜";
        AdvStringGrid1->Cells[0][5] = "센서메이커";
        AdvStringGrid1->Cells[0][6] = "선별아이템";
        AdvStringGrid2->Cells[0][0] = "포트설정";
        AdvStringGrid2->Cells[1][0] = "설정값";
        for(int i=2;i<=9;i++) AdvStringGrid2->Cells[i][0] = String(i-1)+"조";
        #else
        for(int i=1;i<=5;i++) AdvStringGrid1->Cells[i][0] = "ITEM"+String(i);
        AdvStringGrid1->Cells[0][0] = "Item";
        AdvStringGrid1->Cells[0][1] = "Alias";
        AdvStringGrid1->Cells[0][2] = "Max";
        AdvStringGrid1->Cells[0][3] = "Min";
        AdvStringGrid1->Cells[0][4] = "Portocol";
        AdvStringGrid1->Cells[0][5] = "Maker";
        AdvStringGrid1->Cells[0][6] = "Name";
        AdvStringGrid2->Cells[0][0] = "Port";
        AdvStringGrid2->Cells[1][0] = "Value";
        for(int i=2;i<=9;i++) AdvStringGrid2->Cells[i][0] = "L"+String(i-1);
        #endif

        InitPortTable();
        LoadDDF();
        LoadPDF();
        LoadConfig();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AdvGlowButton1Click(TObject *Sender)
{
         char szFileName[MAXFILE+4];


        GetWriteFile();
        if(FileExists(MASTER_CONFIG_FILE_NAME))
        {
                fnsplit(MASTER_CONFIG_FILE_NAME.c_str(), 0, 0, szFileName, 0);
                strcat(szFileName, ".BAK");
                RenameFile(MASTER_CONFIG_FILE_NAME, szFileName);
        }
        int fp =FileCreate(MASTER_CONFIG_FILE_NAME);
        FileWrite(fp,(char *)&shmcfg,sizeof(SHMCFG));
        FileClose(fp);


}
//---------------------------------------------------------------------------



void __fastcall TForm1::AdvStringGrid2GetEditorType(TObject *Sender,
      int ACol, int ARow, TEditorType &AEditor)
{
       if(ARow<1) return;
       int val = ARow-1;
       int div = val/9;
       int reg = val%9;

       if(ACol>1 && reg==0) AEditor = edNumeric;
       else if(ACol==1 && reg>=2 && reg<=5)
       {
                AEditor = edComboList;
                AdvStringGrid2->ClearComboString();
                String s="";
                for(int i=0;i<50;i++)
                {
                        if(reg==2)      s= pdf[div].init[i];
                        else if(reg==3) s= pdf[div].read[i];
                        else if(reg==4) s= pdf[div].write[i];
                        else if(reg==5) s= pdf[div].maker[i];
                       if(s!="") AdvStringGrid2->AddComboString(s);
                }
       }
       else if(ACol==1 && reg>5)
       {
               AEditor = edComboList;
               AdvStringGrid2->ClearComboString();
               String s="";

              int row = 9*div+6;
              String ts =AdvStringGrid2->Cells[1][row];
              ts = ts.SubString(2,ts.Length()-2);
              int nr =  GetMakerCode(ts);
              for(int j=0;j<5;j++)
              {
                String ss = ddf[nr].item[j];
                if(ss!="") AdvStringGrid2->AddComboString(ss);
              }


       }


}
//---------------------------------------------------------------------------


void __fastcall TForm1::AdvGlowButton4Click(TObject *Sender)
{
        AdvMemo1->Lines->Clear();
        AdvMemo1->Lines->LoadFromFile(DEVICE_LIST_FILE_NAME);
        AdvMemo1->Lines->SaveToFile(DEVICE_LIST_FILE_BAK_NAME);
        AdvOfficePage4->Caption="device.sdd";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AdvGlowButton5Click(TObject *Sender)
{
        AdvMemo1->Lines->Clear();
        AdvMemo1->Lines->LoadFromFile(PORT_LIST_FILE_NAME);
        AdvMemo1->Lines->SaveToFile(PORT_LIST_FILE_BAK_NAME);
        AdvOfficePage4->Caption="port.spd";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AdvGlowButton6Click(TObject *Sender)
{
        String str=AdvMemo1->Lines->Strings[0];
        if(str=="device.sdd")
        {
                AdvMemo1->Lines->SaveToFile(DEVICE_LIST_FILE_NAME);
                //AdvMemo1->Lines->SaveToFile(DEVICE_LIST_FILE_NAME);
        }
        else if(str=="port.spd")
        {
                AdvMemo1->Lines->SaveToFile(PORT_LIST_FILE_BAK_NAME);
                //AdvMemo1->Lines->SaveToFile(PORT_LIST_FILE_BAK_NAME);
        }
        else
        {
                #ifndef _LANG_ENGLISH
                Application->MessageBox("저장할 내용이 없거나 잘못된 양식입니다","저장오류",MB_OK);
                #else
                Application->MessageBox("No data to be saved","Error",MB_OK);
                #endif
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AdvGlowButton7Click(TObject *Sender)
{
        AdvMemo1->Lines->Clear();
        AdvOfficePage4->Caption="noname.sdd";        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormShow(TObject *Sender)
{
        #ifdef _LANG_ENGLISH
        ReSetCaption();
        #endif
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ReSetCaption(void)
{

        Form1->Caption="SEH SYSTEM SETTING";
        AdvOfficePage1->Caption="Basic Setting";
        AdvOfficePage2->Caption="Items";
        AdvOfficePage3->Caption="Communication Setting";

        AdvGlowButton7->Caption="Delete";
        AdvGlowButton6->Caption="Save";

        AdvGroupBox2->Caption="Customer";
        AdvOfficeRadioGroup1->Caption="Lanes";
        AdvGroupBox1->Caption="Drop/Labeller";
        AdvGroupBox3->Caption="Working Directory/File";

        Edit1->LabelCaption="Drop Count";
        Edit2->LabelCaption="Item Count";
        AdvOfficeCheckBox1->Caption="Use Labeller";
        AdvOfficeCheckBox2->Caption="Use Totalizer";
        AdvEdit3->LabelCaption="Working File";
        AdvEdit4->LabelCaption="Working Directory";
        AdvGlowButton1->Caption="Save";
        AdvGlowButton2->Caption="Close";
        AdvGlowButton3->Caption="Read";


}
