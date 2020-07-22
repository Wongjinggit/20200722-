/*实验作业九 作者：王英杰  学号190320113  班级：自动化一班
  2019/11/17
  程序名称：【学生成绩管理系统V5.0】
  程序功能： 某班有最多不超过 30 人（具体人数由键盘输入），参加总数不超过6门的课程的考试，
             要求程序运行后先显示如下菜单驱动的学生成绩管理系统*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 30                                          /*学生总数不超过30人*/
#define L 20                                          /*姓名字符总数不超过30*/
#define COURSE_N 6                                      /*科目总数不超过6门*/
#define SUB_L 10                                         /*科目字符总数不超过10*/


typedef struct student
{
    long num;
    char name[L];
    int score[COURSE_N];
}STUDENT ;

void InputScore( STUDENT stu[] , int n , int sub_n );
int ReadSub( char sub[][SUB_L]  , int sub_n );
void AverofCourse( STUDENT stu[] , int n , int sub_n , int sum[] , float aver[] );
void AverofStud( STUDENT stu[] , int n , int sub_n , int sum[] , float aver[] );
void PrintScoreC(STUDENT stu[] , char sub[][SUB_L] , int n , int sub_n , int sumC[] , float averC[] );
void PrintScoreS( STUDENT stu[] , char sub[][SUB_L] , int n , int sub_n , int sumS[] , float averS[] );
void DescendingOrder(STUDENT stu[] ,  int n , int sub_n , int sum[] ,float aver[]);
void ScendingOrderScore( STUDENT stu[] , int n  , int sub_n , int sum[] , float aver[]);
void ScendingOrderNum( STUDENT stu[], int n , int sub_n , int sum[] , float aver[]);
int LinSearch( STUDENT stu[] , long x , int n );
void PrintRange( STUDENT stu[] , int n , int min , int max , int sumR[] , float percentR[] , int sub_n );
void SortString( STUDENT stu[] , int n , int sub_n , int sum[] , float aver[]);
int NameSearch( int n , STUDENT stu[] , char x[L] );
void WritetoFile( STUDENT stu[] , int n ) ;
int ReadfromFile( STUDENT stu[] , char sub[][SUB_L] , int n , int sub_n ,  int sumC[] , float averC[] , int sumS[] , float averS[]);

int main ()                                                          /*主程序*/
{
    printf(" Experiment No.9 Task No.1\n 【学生成绩管理系统V5.0】\n by 王英杰  Number 190320113\n");

    int n , sub_n ,sumS[N] , sumC[COURSE_N] , a , sumR[COURSE_N] ,m, ret;
    char sub[COURSE_N][SUB_L] ;
    float averS[N] , averC[COURSE_N] , percentR[COURSE_N];
    STUDENT stu[N];

    printf(" 1. Input record\n 2. Calculate total and average score of every course\n 3. Calculate total and average score of every student\n 4. Sort in descending order by total score of every student\n 5. Sort in ascending order by total score of every student\n 6. Sort in ascending order by number\n 7. Sort in dictionary order by name\n 8. Search by number\n 9. Search by name\n 10. Statistic analysis for every course\n 11. List record\n 12. Write to a file\n 13. Read from a file\n 0. Exit\n Please enter your choice: ");    /*打印选项菜单*/

    do{
            printf("\nPlease Enter Your Choice First:");     /*让用户选择菜单中的数字，然后进行相应操作*/
            ret = scanf("%d",&a);
            if (ret !=1 )
            {
                printf("Error Data!  Please Input Again!\n\n");
                fflush(stdin);
            }
      }while( a!=1);                                          /*强制用户必须先输入分数和学号才能进行下一操作*/

    if ( a==1 )
    {
            ret = 0;
            do{
            printf("How many students and courses?\n");
            ret = scanf("%d%*c%d" , &n , &sub_n);
            if (ret !=2 )
            {
                printf("Error Data!  Please Input Again!\n\n");
                fflush(stdin);
            }
            else
            {
                printf("Input names of courses:\n");
                ReadSub( sub , sub_n );
                InputScore( stu , n , sub_n);
                AverofStud( stu , n , sub_n , sumS , averS );
                AverofCourse( stu , n , sub_n , sumC , averC );
            }
            }while (ret != 2);

      do{
        ret = 0;
        do{
        printf("\nPlease Enter Your Choice First:");
        ret = scanf("%d",&a);
        if (ret !=1 )
        {
            printf("Error Data!  Please Input Again!\n\n");
            fflush(stdin);
        }
        else{
        if ( a==2 )
            PrintScoreC( stu , sub , n , sub_n , sumC , averC);

        if ( a==3 )
            PrintScoreS( stu , sub , n , sub_n , sumS , averS);

        if ( a==4 )
        {
            DescendingOrder( stu , n , sub_n , sumS , averS);
            PrintScoreS( stu , sub , n , sub_n , sumS , averS);
        }
        if ( a==5 )
        {
           ScendingOrderScore( stu , n , sub_n , sumS , averS);
           PrintScoreS( stu , sub , n , sub_n , sumS , averS);
        }
        if ( a==6 )
        {
           ScendingOrderNum( stu , n , sub_n ,sumS , averS );
           PrintScoreS( stu , sub , n , sub_n , sumS , averS);
        }
        if ( a==7 )
        {
            SortString( stu , n , sub_n , sumS , averS );
            PrintScoreS( stu , sub , n , sub_n , sumS , averS);
        }
        if ( a==8 )
        {
            int SearchResult;
            int x;
            printf("Please Input a Number:");
            scanf("%ld",&x);
            SearchResult = LinSearch( stu , x , n );
            if (SearchResult !=-1)
            {
                int i , j;
                printf("         [ID Number]\t          [Name]\t");
                for( j=0 ; j<sub_n ; j++)
                {
                    printf("%8s\t",sub[j]);
                }
                printf("     [SUM]\t    [AVERAGE]\t\n");
                printf("%20ld\t%16s\t", stu[SearchResult].num , stu[SearchResult].name);
                for( j=0 ; j<sub_n ; j++)
                {
                    printf("%8d\t", stu[SearchResult].score[j]);
                }
                printf("%10d\t%13.1f\n", sumS[SearchResult] , averS[SearchResult]);
                printf("\n");
            }
            else
                printf("\nNot Found!\n");
        }
        if ( a==9 )
        {
            int Res;
            char x[L];
            printf("Please Input a Name:");
            getchar();
            fgets( x , L , stdin );
            x[strlen(x)-1]='\0';
            Res = NameSearch(n,stu,x);
            if (Res !=-1)
            {
                int i , j;
                printf("         [ID Number]\t          [Name]\t");
                for( j=0 ; j<sub_n ; j++)
                {
                    printf("%8s\t",sub[j]);
                }
                printf("     [SUM]\t    [AVERAGE]\t\n");
                printf("%20ld\t%16s\t", stu[Res].num , stu[Res].name );
                for( j=0 ; j<sub_n ; j++)
                {
                    printf("%8d\t", stu[Res].score[j]);
                }
                printf("%10d\t%13.1f\n", sumS[Res] , averS[Res]);
                printf("\n");
            }
            else
                printf("\nNot Found!\n");
        }
        if ( a == 10 )
        {
            int j;
            printf("\n        [ScoreRange]\t");
            for( j=0 ; j<sub_n ; j++)
            {
                printf("%17s\t", sub[j]);
            }
            printf("\n");
            PrintRange( stu , n , 0 , 59 , sumR , percentR ,sub_n);
            PrintRange( stu , n , 60 , 69 , sumR , percentR , sub_n);
            PrintRange( stu , n , 70 , 79 , sumR , percentR , sub_n);
            PrintRange( stu , n , 80 , 89 , sumR , percentR , sub_n);
            PrintRange( stu , n , 90 , 100 , sumR , percentR , sub_n);
        }
        if( a == 11 )
        {
            int j;
            PrintScoreS( stu , sub , n , sub_n , sumS , averS);
            printf("       [SumofCourse]\t\t");
            for( j=0 ; j<sub_n ; j++)
            {
                printf("%8d\t", sumC[j]);
            }
            printf("\n      [AverofCourse]\t\t");
            for( j=0 ; j<sub_n ; j++)
            {
              printf("%8.1f\t", averC[j]);
            }
            printf("\n");
        }
        if( a == 12 )
            WritetoFile( stu , n);

        if( a == 13 )
        {

            m = ReadfromFile( stu , sub , n , sub_n , sumC , averC , sumS , averS);
            printf("\nFile has already been read! The number of students is %d.\n" ,m+1 );
        }
        }
        }while( ret!= 1);
      }while( a !=0 );                                                             /*当用户选择“0”选项时才结束程序*/

    }
}

void InputScore( STUDENT stu[] , int n, int sub_n )
{
    int i , j , ret;
    for ( i=0 ; i<n ; i++ )
    {
        ret = 0;
        do{
        printf( "\nInput Student[%d]'s  [ID] , [Name] , [score]:\n",i+1);
        ret = scanf("%ld" , &stu[i].num);
        if (ret !=1 )
        {
            printf("Error Data!Please Input Again!\n\n");
            fflush(stdin);
        }
        else
        {
            ret = 0;
            getchar();
            scanf("%s",stu[i].name);
            while(getchar()!='\n');
            for ( j=0 ; j<sub_n ; j++ )
            {
                do{
                      ret = scanf( "%ld" , &stu[i].score[j] );
                      if (ret !=1 )
                      {
                           printf("Error Data!Please Input Again!\n\n");
                           fflush(stdin);
                      }
                  }while(ret != 1);



            }
        }
        }while( ret != 1);
    }
}

int ReadSub( char sub[][SUB_L] , int sub_n )
{
    int j;
    for ( j=0 ; j<sub_n ; j++)
    {
        scanf("%s",sub[j]);
    }
}

void AverofCourse( STUDENT stu[] , int n , int sub_n , int sum[] , float aver[] )                              /*函数功能：求平均分*/
{
    int i , j;
    for( j=0 ; j<sub_n ; j++ )
    {
        sum[j]=0;
        for( i=0 ; i<n ; i++)
        {
            sum[j] = sum[j] + stu[i].score[j];                                            /*计算【第j门课程】的总分*/
        }
        aver[j] = (float)sum[j]/n;                                                    /*计算【第j门课程】的平均分*/
    }
}

void AverofStud( STUDENT stu[] , int n , int sub_n , int sum[] , float aver[] )
{
    int i,j;
    for( i=0 ; i<n ; i++ )
    {
        sum[i] = 0;
        for( j=0 ; j<sub_n ; j++ )
        {
            sum[i] = sum[i] + stu[i].score[j];                                            /*计算【第j门课程】的总分*/
        }
        aver[i] = (float)sum[i] / sub_n;                                                    /*计算【第j门课程】的平均分*/
    }
}

void PrintScoreC(STUDENT stu[] , char sub[][SUB_L] , int n , int sub_n , int sumC[] , float averC[] )                     /*函数功能：打印学号、分数*/
{
    int i , j;
    printf("         [ID Number]\t          [Name]\t");
    for( j=0 ; j<sub_n ; j++)
    {
        printf("%8s\t", sub[j]);
    }
    printf("\n");
    for(i= 0 ; i<n ; i++)
    {
        printf("%20ld\t%16s\t", stu[i].num , stu[i].name );
        for( j=0 ; j<sub_n ; j++)
        {
            printf("%8d\t", stu[i].score[j]);
        }
        printf("\n");
    }
    printf("\n       [SumofCourse]\t\t");
    for( j=0 ; j<sub_n ; j++)
        {
            printf("%8d\t", sumC[j]);
        }
    printf("\n      [AverofCourse]\t\t");
    for( j=0 ; j<sub_n ; j++)
        {
            printf("%8.1f\t", averC[j]);
        }
    printf("\n");
}

void PrintScoreS( STUDENT stu[] , char sub[][SUB_L] , int n , int sub_n , int sumS[] , float averS[] )                     /*函数功能：打印学号、分数*/
{
    int i , j;
    printf("         [ID Number]\t          [Name]\t");
    for( j=0 ; j<sub_n ; j++)
    {
        printf("%8s\t",sub[j]);
    }
    printf("     [SUM]\t    [AVERAGE]\t\n");
    for(i= 0 ; i<n ; i++)
    {
        printf("%20ld\t%16s\t", stu[i].num , stu[i].name);
        for( j=0 ; j<sub_n ; j++)
        {
            printf( "%8d\t" , stu[i].score[j]);                                      /*输出字符串*/
        }
        printf("%10d\t%13.1f\n", sumS[i] , averS[i]);
    }
    printf("\n");
}

void DescendingOrder(STUDENT stu[] , int n , int sub_n , int sum[] , float aver[])                /*函数功能：利用选择法将分数降序排序*/
{
    int i,k , j, temp1 , temp3;
    long temp2;
    char temp[L];
    float temp4;
    for(i=0;i<n-1;i++)
    {
        for( k=i+1 ; k<n ; k++)
        {
            if(sum[k] > sum[i])
            {
                 for( j=0 ; j < sub_n ; j++ )
                 {
                     temp1 = stu[k].score[j];
                     stu[k].score[j] = stu[i].score[j];
                     stu[i].score[j] = temp1;
                 }
                 temp3 = sum[k] ;
                 sum[k] = sum[i] ;
                 sum[i] = temp3;
                 temp2 = stu[k].num ;
                 stu[k].num = stu[i].num ;
                 stu[i].num = temp2;
                 strcpy(temp , stu[k].name);
                 strcpy(stu[k].name , stu[i].name);
                 strcpy(stu[i].name , temp);
                 temp4= aver[k] ;
                 aver[k] = aver[i];
                 aver[i] = temp4;
            }
         }
     }
}

void ScendingOrderScore( STUDENT stu[] , int n ,  int sub_n , int sum[] , float aver[])             /*函数功能：利用选择法将分数升序排序*/
{
    int i,k, j,temp1,temp3;
    long temp2;
    char temp[L];
    float temp4;
    for(i=0;i<n-1;i++)
    {
        for( k=i+1 ; k<n ; k++)
        {
            if(sum[k] < sum[i])
            {
                 for( j=0 ; j < sub_n ; j++ )
                 {
                     temp1 = stu[k].score[j];
                     stu[k].score[j] = stu[i].score[j];
                     stu[i].score[j] = temp1;
                 }
                 temp3 = sum[k] ;
                 sum[k] = sum[i] ;
                 sum[i] = temp3;
                 temp2 = stu[k].num ;
                 stu[k].num = stu[i].num ;
                 stu[i].num = temp2;
                 strcpy(temp , stu[k].name);
                 strcpy(stu[k].name , stu[i].name);
                 strcpy(stu[i].name , temp);
                 temp4= aver[k] ;
                 aver[k] = aver[i];
                 aver[i] = temp4;
            }
         }
     }
}

void ScendingOrderNum( STUDENT stu[] , int n , int sub_n , int sum[] , float aver[])                /*函数功能：利用选择法将学号升序排序*/
{
    int i,k, j,temp1,temp3;
    long temp2;
    char temp[L];
    float temp4;
    for(i=0;i<n-1;i++)
    {
        for( k=i+1 ; k<n ; k++)
        {
            if( stu[k].num < stu[i].num )
            {
                 for( j=0 ; j < sub_n ; j++ )
                 {
                     temp1 = stu[k].score[j];
                     stu[k].score[j] = stu[i].score[j];
                     stu[i].score[j] = temp1;
                 }
                 temp3 = sum[k] ;
                 sum[k] = sum[i] ;
                 sum[i] = temp3;
                 temp2 = stu[k].num ;
                 stu[k].num = stu[i].num ;
                 stu[i].num = temp2;
                 strcpy(temp , stu[k].name);
                 strcpy(stu[k].name , stu[i].name);
                 strcpy(stu[i].name , temp);
                 temp4= aver[k] ;
                 aver[k] = aver[i];
                 aver[i] = temp4;
            }
         }
     }
}

int LinSearch( STUDENT stu[] ,long x,int n)                            /*函数功能：输入学号，查找对应成绩*/
{
    int i , b;
    for (i=0;i<n;i++)
    {
        b=0;
        if ( stu[i].num == x)
        {
            b++;
            return i;
        }
    }
    if ( b=0 )
        return -1;
}

void PrintRange( STUDENT stu[] , int n , int min , int max , int sumR[] , float percentR[] , int sub_n)    /*函数功能：打印指定范围内的分数及对应学号*/
{
    int i , j ;
    printf("[%d <= score <= %d]\t",min,max);
    {
        for( j=0 ; j<sub_n ; j++)
        {
            sumR[j] = 0;
            for( i=0 ; i<n ; i++)
            {
                if ( ( stu[i].score[j]<max ||  stu[i].score[j]==max ) && ( stu[i].score[j] > min || stu[i].score[j]==min ) )
                {
                   sumR[j]++;
                }
            }
            percentR[j] = ( (float)sumR[j]*100 ) / n;
        }
    }
    for( j=0 ; j<sub_n ; j++)
    {
        printf("%10d(%.1f%%)\t",sumR[j], percentR[j] );
    }
    printf("\n");
}

void SortString(STUDENT stu[] , int n , int sub_n, int sum[] , float aver[])
{
    int i,k,j, temp1,temp2;
    long temp3;
    char temp[L];
    float temp4;
    for(i=0;i<n-1;i++)
    {
        for( k=i+1 ; k<n ; k++)
        {
            if( strcmp( stu[k].name , stu[i].name ) < 0 )
            {
                 for( j=0 ; j < sub_n ; j++ )
                 {
                     temp1 = stu[k].score[j];
                     stu[k].score[j] = stu[i].score[j];
                     stu[i].score[j] = temp1;
                 }
                 temp3 = sum[k] ;
                 sum[k] = sum[i] ;
                 sum[i] = temp3;
                 temp2 = stu[k].num ;
                 stu[k].num = stu[i].num ;
                 stu[i].num = temp2;
                 strcpy(temp , stu[k].name);
                 strcpy(stu[k].name , stu[i].name);
                 strcpy(stu[i].name , temp);
                 temp4= aver[k] ;
                 aver[k] = aver[i];
                 aver[i] = temp4;
            }
         }
     }
}

int NameSearch(int n , STUDENT stu[] , char x[L])                                            /*函数功能：查找人名。输入人名，若与数组里已有人名一致，则返回相应下标；否则返回-1*/
{
    int i , b;
    for (i=0;i<n;i++)
    {
        b=0;
        if( strcmp( x , stu[i].name) == 0 )
        {
            b++;
            return i ;
        }
    if (b=0)
        return -1;
    }
}

void WritetoFile( STUDENT stu[] , int n )                               /*函数功能：将n个同学的信息写入文件student.txt中*/
{
    FILE *fp;
    if( (fp = fopen("student.txt" , "wb") ) == NULL )
    {
        printf("failure to open student.txt!\n");
        exit(0);
    }
    else
    {
        fwrite( stu , sizeof(STUDENT) , n , fp);
        fclose(fp);
        printf("\nFile has been written successfully!\n");
    }

}

int ReadfromFile( STUDENT stu[] , char sub[][SUB_L] , int n , int sub_n ,  int sumC[] , float averC[] , int sumS[] , float averS[])                     /*函数功能：将n个同学的信息从文件student.txt中读取*/
{
    FILE *fp;
    int i;
    if( (fp = fopen("student.txt" , "rb") ) == NULL )
    {
        printf("failure to open student.txt!\n");
        exit(0);
    }
    for ( i=0 ; !feof(fp) ; i++ )
    {
        fread( &stu[i] , sizeof(STUDENT) , 1 , fp );
    }
    fclose(fp);

    int  j;
    printf("         [ID Number]\t          [Name]\t");
    for( j=0 ; j<sub_n ; j++)
    {
        printf("%8s\t",sub[j]);
    }
    printf("     [SUM]\t    [AVERAGE]\t\n");
    for(i= 0 ; i<n ; i++)
    {
        printf("%20ld\t%16s\t", stu[i].num , stu[i].name);
        for( j=0 ; j<sub_n ; j++)
        {
            printf( "%8d\t" , stu[i].score[j]);                                      /*输出字符串*/
        }
        printf("%10d\t%13.1f\n", sumS[i] , averS[i]);
    }
    printf("\n");
    printf("       [SumofCourse]\t\t");
    for( j=0 ; j<sub_n ; j++)
    {
        printf("%8d\t", sumC[j]);
    }
    printf("\n      [AverofCourse]\t\t");
    for( j=0 ; j<sub_n ; j++)
    {
        printf("%8.1f\t", averC[j]);
    }
    printf("\n");
    return i-1;
}

