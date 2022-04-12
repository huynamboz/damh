#include<stdio.h>
#include <string.h>
#include<conio.h>
#define space ' '
char sex[10];
int count=0; 
int d=0;
int soluong;
int chon;


struct noiDung
{
    char nd[50]; // nội dung sở thích
};

struct infoPerson
{
    int sl[100]; // sô lượng sở thích của từng thằng
    noiDung tenSoThich[10]; //từng sở thích của mỗi nhóm person[i]
    int tuoi;
    int sdt;
    char ten[50];
};

//-----cái struct có chữ Check hoặc _c phía sau dùng để lưu dữ liệu nhập vào --///

struct noiDungCheck
{
    char nd_c[50]; //
};

struct infoPerson_input
{
    noiDungCheck tensoThich_input[10];
    char name[50]; // tên đứa vừa nhập
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

infoPerson person[10]; // số nhóm sở thích ( mỗi nhóm là các sở thích của 1 thằng)
infoPerson_input person_input; // 

//---code đọc data từ file--//
void docdata(FILE *st){
  int i=0;
  while(!feof(st))
     {
      i++;
      fscanf(st,"%d %d %20[^\n] %d",&person[i].sdt,&person[i].sl[i],&person[i].ten,&person[i].tuoi); //đọc số thứ tự và số lượng sở thích
       xoakhoangtrang(person[i].ten);// vì hàm fgets nó sẽ đọc luôn ký tự xuống dòng nên việc so sánh sẽ không đúng nên sẽ dùng hàm xoakhoangtrang()
        count ++; //biến count để lưu số lượng person
       for (int j = 1; j <= person[i].sl[i]; j++)
       {
             fscanf(st," %20[^\n]",person[i].tenSoThich[j].nd);
         xoakhoangtrang(person[i].tenSoThich[j].nd);
       }
     }
}

void docfile(){
  if (sex[1] == 'u')
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
 int checkAge(int i){
  if (person[i].tuoi <= person_input.tuoi_right && person[i].tuoi >= person_input.tuoi_left )
  {
    return 1;
  } else return 0;
  
}
void xuat(){
int dem[100]={0}; 
int soThuTu_AgeOk[100]; // dung de danh dau nhung ng co do tuoi thoa man yeu cau tìm kiem
int ok=0;
for (int i = 1; i <= count; i++)
  { 
    if( checkAge(i) == 1 ){
      soThuTu_AgeOk[++ok] = 1;
        for (int  j = 1; j <= soluong; j++)
        {
            for (int k =1 ; k <= person[i].sl[i] ; k++)
            { 
               if ( strcmp(person_input.tensoThich_input[j].nd_c,person[i].tenSoThich[k].nd) == 0) {
                   dem[i]++;
                   break;
               }
            }
        }
      } else soThuTu_AgeOk[++ok] = 0;
  }

int stt=0;
int max=dem[1];
for (int i = 1; i <= count; i++)
  {
    if(soThuTu_AgeOk[i]==1)
    {
      if (dem[i]>max)
        {
          max =dem[i];
        }
    }
  } 
if ( max ==0)
{  
  printf("Rat tiec :( khong co ai phu hop voi ban ca!\n");
} else {
for (int i = 1; i <= count; i++)
  {
     if(soThuTu_AgeOk[i]==1){
       if ( dem[i] == max )
        { 
          printf("%d. %s | tuoi : %d |so dien thoai : 0%d\n->> So thich : ",++stt,person[i].ten,person[i].tuoi,person[i].sdt);
             for (int j = 1; j <=person[i].sl[i]; j++)
               {
                   printf("%s, ",person[i].tenSoThich[j].nd);
               }   printf("\n----------------\n");
       }
     }
  }
} 
}


//--code đọc data nhập vào---//  
void nhapKhoangTuoi(){
   printf("nhap khoang tuoi ban muon tim vidu: 19 25 :");
   scanf("%d %d",&person_input.tuoi_left,&person_input.tuoi_right);
}
void nhapSdt(){
  printf("nhap so dien thoai : ");
  fflush(stdin);
  scanf("%d",&person_input.sdt);
}
void nhap(){
    printf("nhap ten :");
    fflush(stdin);
    gets(person_input.name);

    printf("nhap gioi tinh :");
    fflush(stdin);
    scanf("%s",sex);

    printf("nhap tuoi :");
    scanf("%d",&person_input.tuoi);

    printf("nhap so luong so thich :");
    scanf("%d",&soluong);

    for (int i = 1; i <= soluong; i++)
    {
      printf("Nhap so thich thu %d : ",i);
      fflush(stdin);
      gets(person_input.tensoThich_input[i].nd_c);
    }
}
//---kết thúc code đọc data nhập vào--//

//ghi thêm dữ liệu mới vào file
void ghidata(FILE *st){
         for (int i = 1; i <2; i++)
           {
                fprintf(st,"\n0%d %d",person_input.sdt,soluong);
                fprintf(st," %-20s %d",person_input.name,person_input.tuoi);
             for (int j = 1; j <=soluong; j++)
                 {
                   fprintf(st," %-20s",person_input.tensoThich_input[j].nd_c);
                 } 
            }
}


void ghifile(){
    if (sex[1] == 'u')
    {
        FILE *st = fopen("nu.txt","a");
        sex[1]='a';
        docfile();
        sex[1]='u';
        ghidata(st);
        fclose(st);
    } 
    else {
        FILE *st = fopen("nam.txt","a");
        sex[1]='u';
        docfile();
        sex[1]='a';
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
              printf("%d. %s | tuoi: %d | so dien thoai : 0%d\n",++stt,person[i].ten,person[i].tuoi,person[i].sdt);
              printf("-->> so thich :");
             for (int j = 1; j <=person[i].sl[i]; j++)
                 {
                    printf(" %s,",person[i].tenSoThich[j].nd);
                 } printf("\n----------------\n");
           }
}



int main(){
printf(" _____________________________________________________\n");	
printf("|                                                     |\n");
printf("|=============== PHAN MEM MAI MOI 2022 ===============|\n");
printf("|_____________________________________________________|");
do {
		printf("\n\n =============== MENU ===============");
		  printf("\n|  1. Thuc hien mai moi              |");
		  printf("\n|  2. Them ban vao danh sach mai moi |");
		  printf("\n|  3. In ra danh sach mai moi        |");
		  printf("\n|  0. Thoat chuong trinh.            |");
		  printf("\n|____________________________________|");
		  printf("\n  Ban chon ? ");
		
		scanf("%d",&chon);
	
		
		switch(chon) {
			case 0:
			        	break;
				
			case 1:{
			        	nhap();
                nhapKhoangTuoi();
			        	docfile();
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
			        	nhap();
                nhapSdt();
                ghifile();
                printf(".....Ghi thanh cong....\n");
                count =0;
			        	break;
				
			case 3:
                printf("Ban muon in ra danh sach nam hay nu: ");
                scanf("%s",sex);
                //====Đống này để cho code nó đọc đúng file cần in ra
                // vì bình thường là mình nhập nam nó đọc nữ và ngược lại nên giờ phải đảo lại để nhập nữ đọc nữ, nhập nam đọc nam
                if ( sex[1]== 'u') 
                sex[1] ='a';
                else if (sex [1] == 'a'){
                sex[1]='u';
                 }
                 //===================//
                docfile();
                inds();
                count=0;
			        	break;
				
			default:
			        	printf("Sai chuc nang, vui long chon lai!\n");
			        	break;
		}
	} while(chon);
	return 0;
}
