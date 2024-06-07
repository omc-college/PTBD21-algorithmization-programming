/*****************************************************************************/ 
#include <iostream>
#include <iomanip> // Підключаємо бібліотеку для форматування виведення
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

 // Ініціалізація змінних
  const int SM_qnt=4; // кількість магазинів  
  const int TP_qnt=3; // кількість товарних позицій 
  const int OV_qnt=6; // кількість одиниць вимірювання
  const int IND_qnt=4; // кількість показників
  const int kvart=4;
  struct SM {  // supermarket
      int SM_code;
      string SM_name;
  } SM_desc[SM_qnt]={{1,"Сільпо"},{2,"SM-2"},{3,"SM-3"},{4,"SM-4"}}; // Your name!!!
  struct OV { // UNITS
      int OV_code;
      string OV_name;
  } OV_desc[OV_qnt]={{1,"нат"},{2,"тис.грн"},{3,"л"},{4,"кг"},{5,"ц"},{6,"шт"}};
   struct TP {  // PRODUCT  YOUR POSITION!!!
      int TP_code;
      int TP_TPcode;
      string TP_name;
      int TP_unit;
  } TP_desc[TP_qnt]={{1,202,"М'ясні продукти",5},
                     {2,243,"Цукрові кондитерські вироби",5},
                     {3,276,"кава",4}};
  struct IND { // iNDEXES 3-torg
      int IND_code;
      string IND_short_name;
      string IND_name;
      int IND_unit;
  } IND_desc[IND_qnt]={{1,"Обсяг  роздрібу",
  "Обсяг  роздрібного продажу (у натуральному вираженні)",  0},
  {2,"Роздр.товарооборот",
  "Роздрібний товарооборот за звітний квартал     (з ПДВ)",2},
  {3,"вироблені на України",
  "У тому числі роздрібний товарооборот від продажу товарів, що вироблені" 
  "на території України",2},
  {4,"Запаси на кінець року",
  "Запаси товарів у торговій мережі та на складах на кінець звітного року",2}};
  struct ZvitBody{
      int ZB_TP_code[TP_qnt]; // Product Code
      float ZB_IndValue[TP_qnt][IND_qnt]; // 3-torg Indexes
  };
  struct ZvitSM { // iNDEXES 3-torg for quater
      int ZSM_code; // SM code in Output
      ZvitBody ZvSM[kvart];
  } ;
  ZvitSM QZ_SM[SM_qnt]; // SM reports - показники по магазинах по кварталах
  ZvitBody TmpBody;
  void printForm(void)
  {
     for (int i=0;i<SM_qnt;i++) //  магазин
     {   cout<<"# SM "<<QZ_SM[i].ZSM_code<<" - "<<SM_desc[i].SM_name<<endl;
         for (int j=0;j<kvart;j++) // квартал
         {cout<<"квартал "<<i+1<<endl;
           for (int k=0;k<TP_qnt;k++) // товарна позиція
           { int tmp = QZ_SM[i].ZvSM[j].ZB_TP_code[k];
             cout<<tmp<<" - "  << TP_desc[tmp-1].TP_TPcode
           <<" - " << TP_desc[tmp-1].TP_name<< "-"<<TP_desc[tmp-1].TP_unit<<"-"
           << OV_desc[TP_desc[tmp-1].TP_unit-1].OV_name<<endl;
           for (int l=0;l<IND_qnt;l++) // показник 
                 cout << IND_desc[l].IND_short_name<<'\t';
                 cout <<endl;
                for (int l=0;l<IND_qnt;l++) 
                   cout <<fixed<<setw(10)<< setprecision (2)<< 
                   QZ_SM[i].ZvSM[j].ZB_IndValue[k][l]<<'\t';
                 cout <<endl;
         }
     }  
     }
    
};
  void  printSM (void);
  void  printOV(void);
  void  printTP(void);
  void  printIND(void);
  void  fillForm(void);
//  void  printForm(void);
  void  fillBody(void);
int main() {
   system("color F0");
  int choice;
  bool filled = false;
  bool ForChoice=true;
  do { cout <<" Fill forms-1\n Control Forms-2 \n Output Forms-3 \n"<<
            " Output SM-4\n Output Units-5 \n Output PRODUCT-6 \n Output iNDEXES-7 \n"<<
            "fillBody - 8 \n"<<
            " Exit - 0 \n Input Your Choice"<<endl;
       cin >>  choice;
       switch (choice)
       {
           case 0: ForChoice=false; break;
           case 1: fillForm();filled =true;break;
           case 2: cout <<"Not Designed\n";break;
           case 3: if (!filled) cout << "Data not formed.Fill forms!";
                   else printForm();break;
           case 4: printSM();;break;
           case 5: printOV();;break;
           case 6: printTP();;break;
           case 7: printIND();;break;
           case 8: fillBody();break;   // testing
           default:  cout <<"Error\n";break;
       }
      
  } while(ForChoice);
  return 0; // Інструкція повернення для завершення програми з кодом 0 (успішне виконання)
  }
  void fillBody(){
     for (int k=0;k<TP_qnt;k++) // товарна позиція 
     {TmpBody.ZB_TP_code[k]=TP_desc[k].TP_code;
      /* cout <<"******"<<TP_desc[k].TP_name<< "-"<<TP_desc[k].TP_unit<<"-"
           << OV_desc[TP_desc[k].TP_unit-1].OV_name<<endl; */
     for (int l=0;l<IND_qnt;l++) // показник 
     {TmpBody.ZB_IndValue[k][l]=rand() % 11; 
      if(l==2 && TmpBody.ZB_IndValue[k][l]>TmpBody.ZB_IndValue[k][l-1])
       { cout<<"Error "<<IND_desc[l-1].IND_short_name<<"="<<TmpBody.ZB_IndValue[k][l-1]<<
         "<(LESS)"<<IND_desc[l].IND_short_name<<"="<<TmpBody.ZB_IndValue[k][l]<<" corrected!"<<endl;
           TmpBody.ZB_IndValue[k][l]=TmpBody.ZB_IndValue[k][l-1];
       };
     /* cout<<IND_desc[l].IND_short_name <<" "
                    <<IND_desc[l].IND_code  << " "<<
                 TmpBody.ZB_IndValue[k][l]<<endl; */
     }
     }
  }
  ;
 void  fillForm(void){
     for (int i=0;i<SM_qnt;i++) //  магазин
     {   QZ_SM[i].ZSM_code=SM_desc[i].SM_code;
         cout<<SM_desc[i].SM_code<<" "<<SM_desc[i].SM_name<<endl;
         for (int j=0;j<kvart;j++) // квартал
         { cout<<" квартал "<<j+1<<endl;
          fillBody();  
          QZ_SM[i].ZvSM[j]=TmpBody;
        }
     }
 };

 void  printSM (void) {cout << "List of Supermarkets \n";
  for (int i=0;i<SM_qnt;i++) cout << SM_desc[i].SM_code <<" - "
           << SM_desc[i].SM_name<< endl;};
  void  printOV(void)          
    {cout << "List of Units \n";
  for (int i=0;i<OV_qnt;i++) cout << OV_desc[i].OV_code <<" - "
            << OV_desc[i].OV_name<< endl; }
  void  printTP(void)
  {cout << "Товарні позиції \n";          
  for (int i=0;i<TP_qnt;i++) { 
       cout << TP_desc[i].TP_code <<" - "
           << TP_desc[i].TP_TPcode<<" - "
           << TP_desc[i].TP_name<< "-"<<TP_desc[i].TP_unit<<"-"
           << OV_desc[TP_desc[i].TP_unit-1].OV_name<<endl; };}
void  printIND(void)
  {cout << "Indexes \n";          
  for (int i=0;i<IND_qnt;i++) { 
       cout << IND_desc[i].IND_code <<" - "
           << IND_desc[i].IND_short_name<<" - "
           << IND_desc[i].IND_name<< "-";
           if (IND_desc[i].IND_unit==0) cout <<"None";
           else cout << OV_desc[IND_desc[i].IND_unit-1].OV_name<<endl; };}
