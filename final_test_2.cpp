#include<stdio.h>
#include <string.h>
#include<conio.h>
#define space ' '
char sex[10];
int count=0; 
int d=0;
int dem[100];
int soluong;
int chon;

struct hovaten {
    char ten[50];
    int stt[50];
};

struct noiDung
{
    char nd[50]; // nội dung sở thích
    int stt[100]; //số thứ tự của mỗi thằng
};

struct SoThich
{
    int sl[100]; // sô lượng sở thích của từng thằng
    noiDung x[10]; //từng sở thích của mỗi nhóm hobbie[i]
};

//-----cái struct có chữ Check hoặc _c phía sau dùng để lưu dữ liệu nhập vào --///

struct noiDungCheck
{
    char nd_c[50]; //
    int sl_c[100];
};

struct SoThichCheck
{
    noiDungCheck xCheck[10];
    char name[50]; // tên đứa vừa nhập
};
//---------------------------//

void xoakhoangtrang (char s[]){ 
  // xoá các ký tự trống cuối chuỗi
{
    int i = strlen (s) - 1 ;
    while (s[i] == space && i >= 0)
        i-- ;
// Lưu ý chỗ này nhé, không phải 'NULL' đâu
    s[i+1] = 0 ; // hoặc s[i+1] = '\0' ;
}
}

hovaten hoten[10];
SoThich hobbie[10]; // số nhóm sở thích ( mỗi nhóm là các sở thích của 1 thằng)
SoThichCheck hobbie_c; // tương tự cái hobbie nhưng có _c phía sau có nghĩa là check để lưu các sở thích nhập vào, vì mình nhập vào có 1 đứa nên k dùng mảng cho hobbie_c

//---code đọc data từ file--//

void docfile(){
    int i=0;
  if (sex[1] == 'u')
  {
      FILE *st = fopen("nam.txt","r");
    
   while(!feof(st))
     {
      i++;
      fscanf(st,"%d %d %20[^\n]",&hobbie[i].x[i].stt[i],&hobbie[i].sl[i],&hoten[i].ten); //đọc số thứ tự và số lượng sở thích
    //   fgets(hoten[i].ten,50, (FILE*)st ); // vì tên có nhiều từ nên phải dùng fgets để lấy hết chuỗi
       xoakhoangtrang(hoten[i].ten);// vì hàm fgets nó sẽ đọc luôn ký tự xuống dòng nên việc so sánh sẽ không đúng nên sẽ dùng hàm xoakhoangtrang()
      count ++; //biến count để lưu số lượng person
      printf("%d\n",count);
       for (int j = 1; j <= hobbie[i].sl[i]; j++)
       {
             fscanf(st," %20[^\n]",hobbie[i].x[j].nd);
        //  fgets(hobbie[i].x[j].nd,50,(FILE*)st );
         xoakhoangtrang(hobbie[i].x[j].nd);
       }
     } fclose(st);
     
  } else {
    FILE *st = fopen("nu.txt","r");
    while(!feof(st))
     {
      i++;
      fscanf(st,"%d %d %20[^\n]",&hobbie[i].x[i].stt[i],&hobbie[i].sl[i],&hoten[i].ten); 
        
    //   fgets(hoten[i].ten,50, (FILE*)st );
      xoakhoangtrang(hoten[i].ten);
      count ++;
        for (int j = 1; j <= hobbie[i].sl[i]; j++)
        {
              fscanf(st," %20[^\n]",&hobbie[i].x[j].nd);
        //  fgets(hobbie[i].x[j].nd,50, (FILE*)st );
        //  xoakhoangtrang(hobbie[i].x[j].nd);
        }
     } fclose(st);

  }
}
//--- kết thúc code đọc data từ file---//

 //----code tìm sở thích giống nhiều nhất--//
void search(){
for (int i = 1; i <= count; i++)
{
        for (int  j = 1; j <= soluong; j++)
        {
            for (int k =1 ; k <= hobbie[i].sl[i] ; k++)
            { 
                // printf("%s-%s\n",hobbie_c.xCheck[j].nd_c,hobbie[i].x[k].nd);
               if ( strcmp(hobbie_c.xCheck[j].nd_c,hobbie[i].x[k].nd) == 0) {
                   dem[i]++;
                   break;
               }
            }
        }
}
}//---kết thúc code đọc sở thích giống nhiều nhất---//

  //----tìm những thằng giống nhất để in ra--//
void xuat(){
int soTT=1;
int max=dem[1];
for (int i = 1; i <= count; i++)
{
    if (dem[i]>max)
    {
       max =dem[i];
       soTT =i;
    }
//  printf("%d\n",dem[i]);   
} 
for (int i = 1; i <= count; i++)
{
    if ( dem[i] == max ){
          printf("%d. %s ->> So thich : ",++d,hoten[i].ten);
             for (int j = 1; j <=hobbie[i].sl[i]; j++)
               {
                   printf("%s, ",hobbie[i].x[j].nd);
               }   printf("\n----------------\n");
       }
}
}


//--code đọc data nhập vào---//  
     
void nhap(){
      printf("nhap ten :");
      fflush(stdin);
      gets(hobbie_c.name);
      printf("nhap gioi tinh :");
      fflush(stdin);
      scanf("%s",sex);
    
    printf("nhap so luong so thich :");
    scanf("%d",&soluong);
    printf("nhap so thich :");
    for (int i = 1; i <= soluong; i++)
    {
      fflush(stdin);
      gets(hobbie_c.xCheck[i].nd_c);
    }
}
//---kết thúc code đọc data nhập vào--//

//ghi thêm dữ liệu mới vào file
void ghifile(){
    if (sex[1] == 'u')
    {
        FILE *st = fopen("nu.txt","a");
        sex[1]='a';
        docfile();
        sex[1]='u';
        int stt=count;
         for (int i = 1; i <2; i++)
           {
            fprintf(st,"\n%d %d",++stt,soluong);
            fprintf(st," %-20s",hobbie_c.name);
          for (int j = 1; j <=soluong; j++)
             {
                fprintf(st," %-20s",hobbie_c.xCheck[j].nd_c);
           
             } 
            }
     fclose(st);
    } 
    
    else {
          FILE *st = fopen("nam.txt","a");
        sex[1]='u';
        docfile();
        sex[1]='a';
        int stt=count;
         for (int i = 1; i <2; i++)
           {
           fprintf(st,"\n%d %d",++stt,soluong);
            fprintf(st," %-20s",hobbie_c.name);
          for (int j = 1; j <=soluong; j++)
             {
                fprintf(st," %-20s",hobbie_c.xCheck[j].nd_c);
           
             } 
            }
     fclose(st);
    }
}

//====hàm in ra danh sách
void inds(){
    int stt=0;
    printf("=======DANH SACH MAI MOI=========\n");
     for (int i = 1; i <= count; i++)
         {
              printf("%d. %s\n",++stt,hoten[i].ten);
              printf("so thich :");
             for (int j = 1; j <=hobbie[i].sl[i]; j++)
                 {
                    printf(" %s,",hobbie[i].x[j].nd);
                 } printf("\n----------------\n");
           }
}



int main(){

do {
		printf("=============== MENU ===============");
		printf("\n1. Thuc hien mai moi");
		printf("\n2. Them ban vao danh sach mai moi");
		printf("\n3. In ra danh sach mai moi");
		printf("\n0. Thoat chuong trinh.");
		printf("\nBan chon ? ");
		
		scanf("%d",&chon);
		
		
		switch(chon) {
			case 0:
				break;
				
			case 1:{
				nhap();
				docfile();
                search();
                if (sex[1]== 'u')
                {
                     printf("\n-------Nhung chang trai hop voi ban <3---------\n\n");
                } else printf("\n-------Nhung co gai hop voi ban <3---------\n\n");
                
                xuat();
				break;
            }

			case 2:
				nhap();
                ghifile();
                printf(".....Ghi thanh cong....\n");
				break;
				
			case 3:
                printf("Ban muon in ra danh sach nam hay nu: ");
                scanf("%s",sex);
                count =0;
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
				break;
				
			default:
				printf("Sai chuc nang, vui long chon lai!\n");
				break;
		}
		
	} while(chon);
	
	return 0;
  
  
}