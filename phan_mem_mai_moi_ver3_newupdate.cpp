#include<stdio.h>
#include <string.h>
#include<conio.h>
#define space ' '

int count=0; // so luong person
int soLuongSoThich; //so luong so thich nguoi dung nhap vao
int height; // chieu cao nguoi dùng nhập vào
int soLuongCongViec; //so luong cong viec, nghe nghiep input
int chon;
char heightCheck[6]; // check xem người dùng muốn trên hay dưới ví dụ tren 160 hoac duoi 170 ( chiều cao)


struct noiDung
{
    char data[50]; // 
};

struct infoPerson
{
    int sl_st; // sô lượng sở thích của từng thằng
    int sl_cv; // số luong công viec(nghề nghiệp)
    noiDung tenSoThich[10]; //từng sở thích của mỗi person[i]
    noiDung tenCongViec[10];
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
    noiDungCheck tenCongViec_input[10];
    char ten[50]; // tên đứa vừa nhập
    int tuoi;// tuoi scanf
    int tuoi_right;
    int tuoi_left;
    int sdt;
};
//---------------------------//

void xoakhoangtrang (char s[]){ 
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
void docdata(FILE *st){
  int i=0;
  while(!feof(st))
     {
      i++;
      fscanf(st,"%d %d %20[^\n] %d %d",&person[i].sdt,&person[i].tuoi,&person[i].ten,&person[i].chieuCao,&person[i].sl_st); 
       xoakhoangtrang(person[i].ten);// vì nó đọc luôn các khoảng trắng nên việc so sánh sẽ không đúng nên sẽ dùng hàm xoakhoangtrang()
        count ++; //biến count để lưu số lượng person
       for (int j = 1; j <= person[i].sl_st; j++)
       {
             fscanf(st," %20[^\n]",person[i].tenSoThich[j].data);
         xoakhoangtrang(person[i].tenSoThich[j].data);
       }
       fscanf(st,"%d",&person[i].sl_cv);
       for (int j = 1; j <= person[i].sl_cv; j++)
       {
         fscanf(st," %20[^\n]",person[i].tenCongViec[j].data);
         xoakhoangtrang(person[i].tenCongViec[j].data);
       }
     }
}

void docfile(char sex){
  if (sex == 'a')
  {
      FILE *st = fopen("nam.txt","r");
      docdata(st);
      fclose(st); count--;
     
  } else {
      FILE *st = fopen("nu.txt","r");
      docdata(st);
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
void xuat(){
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
printf("\n -------------DE XUAT TOT NHAT CHO BAN-------------------\n");
for(int i=0; i<=count; i++){
  if( tiLeHopNhau[i] == max ){
printf("%d. %s | tuoi : %d |so dien thoai : 0%d | chieu cao : %dcm\n->> So thich : ",++stt,person[i].ten,person[i].tuoi,person[i].sdt,person[i].chieuCao);
             for (int j = 1; j <=person[i].sl_st; j++)
               {
                   printf("%s, ",person[i].tenSoThich[j].data);
               }   
               printf("\n->> nghe nghiep :");

                  for (int j = 1; j <=person[i].sl_cv; j++)
                 {
                    printf(" %s,",person[i].tenCongViec[j].data);
                 }
               printf("\n TI LE HOP NHAU : %.2f %%",tiLeHopNhau[i]); printf("\n\n");
  }
}
printf("---------------MOT SO DE XUAT KHAC-------------------\n");

for (int i = 1; i <= count; i++)
  {
     if(soThuTu_AgeOk[i]==1){
       if ( tiLeHopNhau[i] > 0 && tiLeHopNhau[i] != max )
        { 
          printf("%d. %s | tuoi : %d |so dien thoai : 0%d | chieu cao : %dcm\n->> So thich : ",++stt,person[i].ten,person[i].tuoi,person[i].sdt,person[i].chieuCao);
             for (int j = 1; j <=person[i].sl_st; j++)
               {
                   printf("%s, ",person[i].tenSoThich[j].data);
               }   
               printf("\n->> nghe nghiep :");

                  for (int j = 1; j <=person[i].sl_cv; j++)
                 {
                    printf(" %s,",person[i].tenCongViec[j].data);
                 }
               printf("\n TI LE HOP NHAU : %.2f %%",tiLeHopNhau[i]); printf("\n\n");
       }
     }
  }
}
}


//--code đọc data nhập vào---//  
void nhapKhoangTuoi(){
    printf("nhap khoang tuoi ban muon tim : ");
    scanf("%d %d",&person_input.tuoi_left,&person_input.tuoi_right);

    printf("nhap chieu cao :");
    scanf("%s %d",heightCheck,&height);
}
void nhapSdt(){

    printf("nhap so dien thoai : ");
    fflush(stdin);
    scanf("%d",&person_input.sdt);

    printf("nhap chieu cao:");
    scanf("%d",&height);
}
void nhap(char sex[]){
   

    printf("nhap ten :");
    fflush(stdin);
    gets(person_input.ten);

    printf("nhap gioi tinh :");
    fflush(stdin);
    scanf("%s",sex);

    printf("nhap tuoi :");
    scanf("%d",&person_input.tuoi);

    printf("nhap so luong so thich :");
    scanf("%d",&soLuongSoThich);

    for (int i = 1; i <= soLuongSoThich; i++)
    {
      printf("Nhap so thich thu %d : ",i);
      fflush(stdin);
      gets(person_input.tensoThich_input[i].data_c);
    }
    printf("nhap so luong nghe nghiep :");
    scanf("%d",&soLuongCongViec);

    for (int i = 1; i <= soLuongCongViec; i++)
    {
      printf("Nhap nghe nghiep thu %d : ",i);
      fflush(stdin);
      gets(person_input.tenCongViec_input[i].data_c);
    }
}
//---kết thúc code đọc data nhập vào--//

//ghi thêm dữ liệu mới vào file
void ghidata(FILE *st){
         for (int i = 1; i <2; i++)
           {
                fprintf(st,"\n0%d %d",person_input.sdt,person_input.tuoi);

                fprintf(st," %-20s %d %d",person_input.ten,height,soLuongSoThich);

             for (int j = 1; j <=soLuongSoThich; j++)
                 {
                   fprintf(st," %-20s",person_input.tensoThich_input[j].data_c);
                 }

                 fprintf(st," %d",soLuongCongViec);

                 for (int j = 1; j <=soLuongCongViec; j++)
                 {
                   fprintf(st," %-20s",person_input.tenCongViec_input[j].data_c);
                 } 
            }
}


void ghifile(char sex){
    if (sex == 'u')
    {
        FILE *st = fopen("nu.txt","a");
        ghidata(st);
        fclose(st);
    } 
    else {
        FILE *st = fopen("nam.txt","a");
        ghidata(st);
        fclose(st);
    }
}

//====hàm in ra danh sách
void inds(){
    int stt=0;
    printf("\n\n========= DANH SACH MAI MOI ===========\n");
     for (int i = 1; i <= count; i++)
         {
              printf("%d. %s  |  tuoi: %d  |  so dien thoai : 0%d  |  chieu cao : %dcm\n",++stt,person[i].ten,person[i].tuoi,person[i].sdt,person[i].chieuCao);
              printf("->> so thich :");

             for (int j = 1; j <=person[i].sl_st; j++)
                 {
                    printf(" %s,",person[i].tenSoThich[j].data);
                 } 

                  printf("\n->> nghe nghiep :");

                  for (int j = 1; j <=person[i].sl_cv; j++)
                 {
                    printf(" %s,",person[i].tenCongViec[j].data);
                 } printf("\n----------------\n");
           }
}
int deleted;
void Delete(FILE *st){
     
      for (int i = 1; i <= count; i++)
      {
        if(person_input.sdt == person[i].sdt){
          deleted = i;
          continue;
        } else {

                fprintf(st,"\n0%d %d",person[i].sdt,person[i].tuoi);
                fprintf(st," %-20s %d %d",person[i].ten,person[i].chieuCao,person[i].sl_st);
             for (int j = 1; j <=person[i].sl_st; j++)
                 {
                   fprintf(st," %-20s",person[i].tenSoThich[j].data);
                 }

            fprintf(st," %d",person[i].sl_cv);

                 for (int j = 1; j <=person[i].sl_cv; j++)
                 {
                   fprintf(st," %-20s",person[i].tenCongViec[j].data);
                 } 
        }
      }
     
}
void xoaPerson(){
  FILE *st;
  char sex[5];
  printf("Ban mua xoa nam hay nu : ");
  fflush(stdin);
  scanf("%s",sex);
  printf("Nhap so dien thoai nguoi ban muon xoa : ");
  fflush(stdin);
  scanf("%d",&person_input.sdt);
  if ( sex[1] == 'u')
    {
      docfile('u');
      st = fopen("nu.txt","w");
      Delete(st);
      printf("======== BAN VUA XOA THANH CONG ========\n");
      printf("%s | tuoi : %d | so dien thoai : 0%d",person[deleted].ten,person[deleted].tuoi,person[deleted].sdt);
    } else {
        docfile('a');
        st = fopen("nam.txt","w");
        Delete(st);
        printf("\n======== BAN VUA XOA THANH CONG ========\n");
        printf("%s | tuoi : %d | so dien thoai : 0%d",person[deleted].ten,person[deleted].tuoi,person[deleted].sdt);
    }
        fclose(st);
}

int main(){
  
printf(" _________________________________________________________\n");	
printf("|                                                         |\n");
printf("|================= PHAN MEM MAI MOI 2022 =================|\n");
printf("|_________________________________________________________|\n");
                                                                                                    
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
                                                                                                                                                                              
do {
		printf("\n\n =============== MENU ===============");
		  printf("\n|  1. Thuc hien mai moi              |");
		  printf("\n|  2. Them ban vao danh sach mai moi |");
		  printf("\n|  3. In ra danh sach mai moi        |");
      printf("\n|  4. Xoa nguoi khoi danh sach       |");
		  printf("\n|  0. Thoat chuong trinh.            |");
		  printf("\n|____________________________________|");
		  printf("\n  Ban chon ? ");
		char sex[10];
		scanf("%d",&chon);
	
		
		switch(chon) {
			case 0:
			        	break;
				
			case 1:{
                printf("\n Ban can nhap cac thong tin sau :");
                printf("\n1. Ten\n2. Gioi tinh\n3. Tuoi\n4. So thich\n5. Cong viec");
                printf("\n6. Khoang tuoi vi du( 19 25 )\n7. Chieu cao mong muon( vi du tren 160 hoac duoi 170)\n\n");
			        	nhap(sex);
                nhapKhoangTuoi();
                if (sex[1] == 'a')
                {
                 docfile('u');
                } else docfile('a');
                
			        	
                // search(dem);
                if (sex[1]== 'u')
                {
                     printf("\n-------Nhung chang trai hop voi ban <3---------\n\n");
                } else printf("\n-------Nhung co gai hop voi ban <3---------\n\n");
                
                xuat();
                count=0;
			        	break;
            }

			case 2:
			        	nhap(sex);
                nhapSdt();
                ghifile(sex[1]);
                printf(".....Ghi thanh cong....\n");
                count =0;
			        	break;
				
			case 3:
                printf("Ban muon in ra danh sach nam hay nu: ");
                scanf("%s",sex);
                docfile(sex[1]);
                inds();
                count=0;
			        	break;

      case 4:
                xoaPerson();
                count =0;
                break;
			default:
			        	printf("Sai chuc nang, vui long chon lai!\n");
			        	break;
		}
	} while(chon);
	return 0;
}
