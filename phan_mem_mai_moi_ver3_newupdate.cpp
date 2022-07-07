#include<stdio.h>
#include <string.h>
#include<conio.h>
#define space ' '

int count=0; //so luong người trong danh sách
int soLuongSoThich; //số lượng sở thích của người dùng nhập từ bàn phím
int height; //chiều cao người dùng nhập từ bàn phím
int chon; //chọn chức năng trong menu
char heightCheck[6]; //kiểm tra lọc theo chiều cao


struct noiDung
{
    char data[50]; // 
};

struct infoPerson
{
    int sl_st; //số lượng sở thích của từng người
    noiDung tenSoThich[10]; 
    char tenCongViec[50];
    int chieuCao;
    int tuoi;
    int sdt;
    char ten[50];
};

//-----struct lưu dữ liệu nhập từ bàn phím --///

struct noiDungCheck
{
    char data_c[50]; //
};

struct infoPerson_input
{
    noiDungCheck tensoThich_input[10];
    char tenCongViec_input[15];
    char ten[50]; // tên đứa vừa nhập
    int tuoi;// tuoi scanf
    int tuoi_right;
    int tuoi_left;
    int sdt;
};
//---------------------------//

void deleteSpace(char s[]){ 
{
    int i = strlen (s) - 1 ;
    while (s[i] == space && i >= 0)
        i-- ;
    s[i+1] = 0 ; // hoặc s[i+1] = '\0' ;
}
}

 
infoPerson person[100]; 
infoPerson_input person_input; 

//---code đọc data từ file--//
void readData(FILE *st){
  int i=0;
  while(!feof(st))
     {
      i++;
      fscanf(st,"%d %d %20[^\n] %d %d",&person[i].sdt,&person[i].tuoi,&person[i].ten,&person[i].chieuCao,&person[i].sl_st); 
       deleteSpace(person[i].ten);// vì nó đọc luôn các khoảng trắng nên việc so sánh sẽ không đúng nên sẽ dùng hàm deleteSpace()
        count ++; //biến count để lưu số lượng person
       for (int j = 1; j <= person[i].sl_st; j++)
       {
             fscanf(st," %20[^\n]",person[i].tenSoThich[j].data);
         deleteSpace(person[i].tenSoThich[j].data);
       }
         fscanf(st," %20[^\n]",person[i].tenCongViec);
         deleteSpace(person[i].tenCongViec);
     }
}

void readFile(char gender){
  if (gender == 'a')
  {
      FILE *st = fopen("nam.txt","a+");
      readData(st);
      fclose(st); count--;
     
  } else {
      FILE *st = fopen("nu.txt","a+");
      readData(st);
      fclose(st); count--;
  }
}
//--- kết thúc code đọc data từ file---//






  //----tìm những thằng giống nhất để in ra--//
 int checkAgeAndHeight(int i){
  if (person[i].tuoi <= person_input.tuoi_right && person[i].tuoi >= person_input.tuoi_left )
  {  
    if ( heightCheck[0] == 't')
    {
      if ( person[i].chieuCao > height)
      {
        return 1;
      }
    } else if ( person[i].chieuCao < height)
      {
        return 1;
      }
    
  } else return 0;
  
}
void showResult(){
int dem[100]={0}; 
int soThuTu_AgeOk[100]; // dung de danh dau nhung ng co do tuoi và chieu cao thoa man yeu cau tìm kiem
int ok=0;
float tiLeHopNhau[100]={0};
for (int i = 1; i <= count; i++)
  { 
    if( checkAgeAndHeight(i) == 1 ){
      soThuTu_AgeOk[++ok] = 1;
        for (int  j = 1; j <= soLuongSoThich; j++)
        {
            for (int k =1 ; k <= person[i].sl_st ; k++)
            { 
               if ( strcmp(person_input.tensoThich_input[j].data_c,person[i].tenSoThich[k].data) == 0) {
                   dem[i]++;
                   break;
               }
            }
        }
        tiLeHopNhau[i] = (float)(dem[i])*100/ (float)(soLuongSoThich+person[i].sl_st - dem[i]);
      } else soThuTu_AgeOk[++ok] = 0;
      
  }

int stt=0;
float max=tiLeHopNhau[1];
for (int i = 1; i <= count; i++)
  {
    if(soThuTu_AgeOk[i]==1)
    {
      if (tiLeHopNhau[i]>max)
        {
          max =tiLeHopNhau[i];
        }
    }
  } 
if ( max ==0)
{  
  printf("Rat tiec :( khong co ai phu hop voi ban ca!\n");
} else {
printf("\n                            <<--- DE XUAT TOT NHAT CHO BAN --->> \n\n");
for(int i=0; i<=count; i++){
  if( tiLeHopNhau[i] == max ){
printf("%d. %-20s |  tuoi : %d  |  so dien thoai : 0%d  |  chieu cao : %dcm\n->> So thich : ",++stt,person[i].ten,person[i].tuoi,person[i].sdt,person[i].chieuCao);
             for (int j = 1; j <=person[i].sl_st; j++)
               {
                   printf("%s, ",person[i].tenSoThich[j].data);
               }   
               printf("\n->> nghe nghiep :");

                    printf(" %s,",person[i].tenCongViec);
               printf("\n TI LE HOP NHAU : %.2f %%",tiLeHopNhau[i]); printf("\n");
               printf("\n-----------------------------------------------------------------------------------------\n");
  }
} 
printf("\n                                ##-----------------------##");
printf("\n                                 >> MOT SO DE XUAT KHAC <<    \n\n");
int gioiHan =0;
for (int i = 1; i <= count; i++)
  {
    
     if(soThuTu_AgeOk[i]==1){
       if ( tiLeHopNhau[i] > 0 && tiLeHopNhau[i] != max )
        { 
          printf("%d. %-20s  |  tuoi : %d  |  so dien thoai : 0%d  |  chieu cao : %dcm\n->> So thich : ",++stt,person[i].ten,person[i].tuoi,person[i].sdt,person[i].chieuCao);
             for (int j = 1; j <=person[i].sl_st; j++)
               {
                   printf("%s, ",person[i].tenSoThich[j].data);
               }   
               printf("\n->> nghe nghiep :");

                    printf(" %s,",person[i].tenCongViec);
               printf("\n TI LE HOP NHAU : %.2f %%",tiLeHopNhau[i]); printf("\n");
               printf("\n------------------------------------------------------------------------------------------\n");
               gioiHan++;
               if(gioiHan == 6 ) break;
       } 
     }
  }
}
}


//--code đọc data nhập vào---//  
void inputInfor_age(){
    printf("8. Nhap khoang tuoi ban muon tim -> ");
    scanf("%d %d",&person_input.tuoi_left,&person_input.tuoi_right);

    printf("9. Nhap chieu cao ban muon tim vd: tren 160 hoac duoi 150 -> ");
    scanf("%s %d",heightCheck,&height);
}

void inputInfor(char gender[]){
   

    printf("1. Nhap ten -> ");
    fflush(stdin);
    gets(person_input.ten);

    printf("2. Nhap gioi tinh -> ");
    fflush(stdin);
    scanf("%s",gender);

    printf("3. Nhap tuoi -> ");
    scanf("%d",&person_input.tuoi);

    printf("4. Nhap so dien thoai -> ");
    fflush(stdin);
    scanf("%d",&person_input.sdt);

    printf("5. Nhap chieu cao cua ban -> ");
    scanf("%d",&height);

    printf("6. Nhap so luong so thich -> ");
    scanf("%d",&soLuongSoThich);
    printf(" Nhap so thich: \n");
    for (int i = 1; i <= soLuongSoThich; i++)
    {
      printf("-> ");
      fflush(stdin);
      gets(person_input.tensoThich_input[i].data_c);
    }

      printf("7. Nhap nghe nghiep -> ");
      fflush(stdin);
      gets(person_input.tenCongViec_input);
}
//---kết thúc code đọc data nhập vào--//

//ghi thêm dữ liệu mới vào file
void writeData(FILE *st){
         for (int i = 1; i <2; i++)
           {
                fprintf(st,"\n0%d %d",person_input.sdt,person_input.tuoi);

                fprintf(st," %-20s %d %d",person_input.ten,height,soLuongSoThich);

             for (int j = 1; j <=soLuongSoThich; j++)
                 {
                   fprintf(st," %-20s",person_input.tensoThich_input[j].data_c);
                 }

                   fprintf(st," %-20s",person_input.tenCongViec_input);
            }
}


void writeFile(char gender){
    if (gender == 'u')
    {
        FILE *st = fopen("nu.txt","a");
        writeData(st);
        fclose(st);
    } 
    else {
        FILE *st = fopen("nam.txt","a");
        writeData(st);
        fclose(st);
    }
}

//====hàm in ra danh sách
void listPerson(){
    int stt=0;
    printf("\n                                     >> DANH SACH MAI MOI <<                                           ");
    printf("\n=====================================================================================================\n");
    if (count == 0) 
      printf("                                      DANH SACH CHUA CO AI!                     ");
     for (int i = 1; i <= count; i++)
         {
              printf(" %d. %-20s  |  tuoi: %d  |  so dien thoai : 0%d  |  chieu cao : %dcm\n",++stt,person[i].ten,person[i].tuoi,person[i].sdt,person[i].chieuCao);
              printf(" ->> so thich    :");

             for (int j = 1; j <=person[i].sl_st; j++)
                 {
                    printf(" %s,",person[i].tenSoThich[j].data);
                 } 

                  printf("\n ->> nghe nghiep :");

                    printf(" %s,",person[i].tenCongViec);
                 printf("\n=====================================================================================================\n");
           }
}
int deleted;
int Delete(FILE *st){
     int dem=0;
      for (int i = 1; i <= count; i++)
      {
        if(person_input.sdt == person[i].sdt){
          deleted = i;
          continue;
        } else {
                dem++;
                fprintf(st,"\n0%d %d",person[i].sdt,person[i].tuoi);
                fprintf(st," %-20s %d %d",person[i].ten,person[i].chieuCao,person[i].sl_st);
             for (int j = 1; j <=person[i].sl_st; j++)
                 {
                   fprintf(st," %-20s",person[i].tenSoThich[j].data);
                 }

                   fprintf(st," %-20s",person[i].tenCongViec);
        }
      } return dem;

     
}
void deletePerson(){
  FILE *st;
  char gender[5];
  printf("Ban mua xoa nam hay nu : ");
  fflush(stdin);
  scanf("%s",gender);
  printf("Nhap so dien thoai nguoi ban muon xoa : ");
  fflush(stdin);
  scanf("%d",&person_input.sdt);
  if ( gender[1] == 'u')
    {
      readFile('u');
      st = fopen("nu.txt","w");
      if ( Delete(st) != count ) {
      printf("\n");
      printf("BAN VUA XOA THANH CONG ->> ");
      printf("%s | so dien thoai : 0%d",person[deleted].ten,person[deleted].sdt);
      } else {
        printf("\n>>>>KHONG CO THONG TIN NGUOI CAN XOA");
      }
    } else  if ( gender[1] == 'a'){
        readFile('a');
        st = fopen("nam.txt","w");
         if ( Delete(st) != count ) {
       printf("\n");
       printf("BAN VUA XOA THANH CONG ->> ");
      printf("%s | so dien thoai : 0%d",person[deleted].ten,person[deleted].sdt);
         } else {
        printf("\n>>>>KHONG CO THONG TIN NGUOI CAN XOA");
      }
    }
        fclose(st);
}

void rewriteData(FILE *st){
  int dem=0;
  for (int i = 1; i <= count; i++)
      {
        if(person_input.sdt == person[i].sdt){
        printf("Ban muon sua thong tin gi : ");
        printf("\n1. Ten");
        printf("\n2. Tuoi");
        printf("\n3. So thich");
        printf("\n4. Nghe nghiep");
        printf("\n5. So dien thoai");
        printf("\n6. Chieu cao\n");
        printf("\n Ban muon sua thong tin nao : ");
        int choose;
        scanf("%d",&choose);
        printf("\n                                 <<---THONG TIN CA NHAN HIEN TAI--->>\n\n");
        for (int j = i; j < i+1; j++)
         {
              printf(" %-20s  |  tuoi: %d  |  so dien thoai : 0%d  |  chieu cao : %dcm\n",person[j].ten,person[j].tuoi,person[j].sdt,person[j].chieuCao);
              printf(" ->> so thich    :");

             for (int f = 1; f <=person[j].sl_st; f++)
                 {
                    printf(" %s,",person[j].tenSoThich[f].data);
                 } 

                  printf("\n ->> nghe nghiep :");

                    printf(" %s,",person[j].tenCongViec);
           }
        switch ( choose )
        {
        case 1 :  printf("\n\n-> Nhap ten moi : ");
                  fflush(stdin);
                  gets(person[i].ten);
                  break;

        case 2 :  printf("-> Nhap lai tuoi moi : ");
                  scanf("%d",&person[i].tuoi);
                  break;
        
        case 3 :  printf("-> Nhap so luong so thich : ");
                  scanf("%d",&person[i].sl_st);
                  printf("-> Nhap so thich moi<-\n");
                 for (int j = 1; j <= person[i].sl_st; j++)
                    {
                     printf("-> ");
                     fflush(stdin);
                     gets(person[i].tenSoThich[j].data);
                     }
                    break;

        case 4:   printf("-> Nhap lai nghe nghiep : ");
                  fflush(stdin);
                  gets(person[i].tenCongViec);
                  break;

        case 5 :  printf("-> Nhap lai so dien thoai moi : ");
                  scanf("%d",&person[i].sdt);
                  break;

        case 6 :  printf("-> Nhap lai chieu cao moi : ");
                  scanf("%d",&person[i].chieuCao);
                  break;

        default:
                  break;
        }
        printf("\n................................SUA THONG TIN CA NHAN THANH CONG :>................................");
        printf("\n                                    THONG TIN CA NHAN MOI                                       \n\n");
        for (int j = i; j < i+1; j++)
         {
              printf(" %-20s  |  tuoi: %d  |  so dien thoai : 0%d  |  chieu cao : %dcm\n",person[j].ten,person[j].tuoi,person[j].sdt,person[j].chieuCao);
              printf(" ->> so thich    :");

             for (int f = 1; f <=person[j].sl_st; f++)
                 {
                    printf(" %s,",person[j].tenSoThich[f].data);
                 } 

                  printf("\n ->> nghe nghiep :");

                    printf(" %s,",person[j].tenCongViec);
           }
        for (int i = 1; i <= count; i++)
           {
                fprintf(st,"\n0%d %d",person[i].sdt,person[i].tuoi);
                fprintf(st," %-20s %d %d",person[i].ten,person[i].chieuCao,person[i].sl_st);
             for (int j = 1; j <=person[i].sl_st; j++)
                 {
                   fprintf(st," %-20s",person[i].tenSoThich[j].data);
                 }
                   fprintf(st," %-20s",person[i].tenCongViec);
        
           }
        break;
        } else dem++;
      }
       if (dem == count)
        {
          printf("\n----KHONG CO THONG TIN NGUOI CAN SUA :<<-----\n");
        }
}

void editData(){
  FILE *st;
       char gender[5];
  printf("Ban mua sua thong tin nam hay nu : ");
  fflush(stdin);
  scanf("%s",gender);
  printf("Nhap so dien thoai nguoi ban muon sua thong tin : ");
  fflush(stdin);
  scanf("%d",&person_input.sdt);
  
  if ( gender[1] == 'u')
    {
      readFile('u');     
      st = fopen("nu.txt","r+");
      rewriteData(st);
      fclose(st);
    } else if ( gender[1] == 'a'){
      readFile('a');
      st = fopen("nam.txt","r+");
      rewriteData(st);
      fclose(st);
    } else {
      printf("---->Nhap sai gioi tinh<-----");
    }
    
}

void Title(){
printf(" ____________________________________________DO AN PBL_______________________________________________\n");	
printf("|                                         lOP: 21TCLC_DT4                                            |\n");
printf("|                         SINH VIEN THUC HIEN: TRINH HUY NAM | NGUYEN DAC NHAT HOANG                 |\n");
printf("|======================================= PHAN MEM MAI MOI 2022 ======================================|\n");
printf("|____________________________________________________________________________________________________|\n");
                                                                                                    
printf("8888888888       8888888       888b    888       8888888b.    ___*##########*\n");	   
printf("888                888         8888b   888       888  \"Y88b   _*##############\n");	   
printf("888                888         88888b  888       888    888   __################\n");	   
printf("8888888            888         888Y88b 888       888    888   _##################_________*####*\n");	   
printf("888                888         888 Y88b888       888    888   __##################_____*##########\n");	   
printf("888                888         888  Y88888       888    888   __##################___*#############\n");	   
printf("888                888         888   Y8888       888  .d88P   ___#################*_###############*\n");	   
printf("888              8888888       888    Y888       8888888P\"    ____#################################*\n");	   
printf("                                                              ______###############################\n") ;                                                                                                                               
printf("888             .d88888b.       888     888      8888888888   _______#############################\n");
printf("888            d88P\" \"Y88b      888     888      888          ________=##########################\n");
printf("888            888     888      888     888      888          __________########################\n");
printf("888            888     888      Y88b   d88P      888          ___________*#####################\n");
printf("888            888     888       Y88b d88P       8888888888   ____________*##################\n");
printf("888            888     888        Y88o88P        888          _____________*###############\n");
printf("888            Y88b. .d88P         Y888P         888          _______________#############\n");
printf("88888888        \"Y88888P\"           Y8P          8888888888   ________________##########\n");                                                                                                                               
printf("|                                                             ________________=#######*\n");
printf("|                                                             _________________######\n");
printf("|                H A V E  A  G O O D D A Y :)                 __________________####\n"); 
printf("|                                                             __________________###\n");     
printf("|________________________________________________________________________________#\n");   
}

void DisplayMenu(){
printf("\n\n ============================================= MENU ================================================");
printf("\n|                                   1. Thuc hien mai moi                                            |");
printf("\n|                                   2. Them ban vao danh sach mai moi                               |");
printf("\n|                                   3. In ra danh sach mai moi                                      |");
printf("\n|                                   4. Xoa nguoi khoi danh sach                                     |");
printf("\n|                                   5. Chinh sua thong tin                                          |");
printf("\n|                                   0. Thoat chuong trinh.                                          |");
printf("\n|___________________________________________________________________________________________________|");
}


int findLove(char gender[]){
                inputInfor(gender);
                inputInfor_age();
                if (gender[1] == 'a')
                {
                 readFile('u');
                } else  if (gender[1] == 'u') readFile('a');
                else {
                  printf("Nhap sai gioi tinh");
                  return 0;
                }
			        	printf("Ban co muon them ban vao du lieu mai moi khong\nneu co nhan (y) neu khong nhan (n): ");
                char yesno;
                fflush(stdin);
                scanf("%c",&yesno);
                if (yesno == 'y')
                {
                  writeFile(gender[1]);
                }
                showResult();
}

void showList(char gender[]){
                printf("Ban muon in ra danh sach nam hay nu: ");
                scanf("%s",gender);
                readFile(gender[1]);
                listPerson();
                count=0;
}

void addPerson(char gender[]){
                inputInfor(gender);
                writeFile(gender[1]);
                printf("\t\t\n<.....GHI THANH CONG....>\n");
}

void chooseFuntion(){
                                                                                                                                                                               
do {
    char gender[10];
    DisplayMenu();
    printf("\nBan chon ? ");  	scanf("%d",&chon);
		switch(chon) {

			case 0:
			        	break;
				
			case 1:{
			        	findLove(gender);
                count=0;
			        	break;
            }

			case 2:
			        	addPerson(gender);
                count =0;
			        	break;
				
			case 3:
                showList(gender);
			        	break;

      case 4:   
                deletePerson();
                count =0;
                break;

      case 5:
                editData();
                count =0;
                break;

			default:
			        	printf("Sai chuc nang, vui long chon lai!\n");
			        	break;

		}
	} while(chon);
}

int main(){
  
   Title();                                                                                                                                                                                                                                           
   chooseFuntion();
   return 0;
}
