#include<stdio.h>
#include<stdlib.h>
//#define TEST
#define NAMEVAR(var) #var
typedef enum {false_t,true_t} bool_t;
typedef struct
{
    int **const coords_aim;
    int size_coords;
    int count_aim;
    int radius;
    int max_x;
    int max_y;
    bool_t isCorrect;
} file_info;
file_info *init(char *name_file,int radius);//input coord in array
file_info *nuke_coord(file_info *const info);//calculation of coordinate
void destroy(file_info *const);//freeing memory
int max(int a,int b);
int main(int argc,char **argv)
{
    if(argc==3)
    {
        int num=atoi(argv[2]);
        destroy(nuke_coord(init(argv[1],num)));
    }
    else
    {
        printf("Incorrect input\n");
        exit(1);
    }
}
file_info *init(char* name_file,int radius)
{

    file_info *const ptr_info=(file_info*)malloc(sizeof(ptr_info));
    if(ptr_info==NULL)
    {
        printf("Memory not selected for %s pointer\n",NAMEVAR(ptr_info));
        exit(1);
    }
#ifdef TEST
    else
    {

        printf("Memory selected for %s pointer\n",NAMEVAR(file_info));

    }
#endif // TEST
    if(radius<=0)
    {
        ptr_info->isCorrect=false_t;
        printf("Error\nRadius <=0\n");
        return ptr_info;
    }
    FILE* fp=NULL;
    if((fp=fopen(name_file,"r"))==NULL)
    {
        printf("Error,file not found\n");
        exit(1);
    }
#ifdef TEST
    else
    {

        printf("FILE OPEN\n");

    }
#endif // TEST

    int max_x=0;
    int max_y=0;

    for(int x, y; fscanf(fp,"%d,%d",&x,&y)!=EOF;)
    {
        max_x=max(max_x,x);
        max_y=max(max_y,y);
#ifdef TEST
        printf("x = %d,y = %d\n",x,y);
#endif // TEST
    }
    max_x+=1;
    max_y+=1;
    rewind(fp);
    int size_coord=0;
    if(max_x>max_y)
    {
        size_coord=max_x;
    }
    else
    {
        size_coord=max_y;
    }
    int **const coords_aim=(int**)calloc(size_coord,sizeof(int*));
    if(coords_aim==NULL)
    {
        printf("Memory not selected for %s pointer\n",NAMEVAR(coords_aim));
        exit(1);
    }
    int count_aim=0;
    for(int i = 0; i<size_coord; i++)
    {
        coords_aim[i]=(int*)calloc(size_coord,sizeof(int));
    }
    if(coords_aim[size_coord-1]==NULL)
    {
        printf("Memory not selected for %s pointer\n",NAMEVAR(coords_aim[size_coord-1]));
        exit(1);
    }
    for(int x,y; fscanf(fp,"%d,%d",&x,&y)!=EOF;)
    {

        coords_aim[y][x]+=1;
        if(coords_aim[y][x]==2)
        {
            coords_aim[y][x]=1;
            continue;
        }
        count_aim++;
    }

#ifdef TEST
    printf("Count aim:%d\n",count_aim);
    for(int i = 0; i<size_coord; i++)
    {
        for(int j = 0; j<size_coord; j++)
        {
            printf("%d",coords_aim[i][j]);
        }
        printf("\n");
    }
#endif // TEST
    fclose(fp);
#ifdef TEST
    printf("FILE CLOSE\n");
#endif // TEST
    *(void**)&(ptr_info->coords_aim)=coords_aim;
    ptr_info->count_aim=count_aim;
    ptr_info->size_coords=size_coord;
    ptr_info->radius=radius;
    ptr_info->max_x=max_x;
    ptr_info->max_y=max_y;
    ptr_info->isCorrect=true_t;
    return (file_info *const )ptr_info;
}

int max(int a,int b)
{
    return a>b?a:b;
}

file_info *nuke_coord(file_info *const info)
{
    if(!info->isCorrect)
    {
        return info;
    }
    if(info->radius>=info->size_coords/2)
    {
        printf("Max destroy = %d\nby coordinates:x = %d and y = %d\n",info->count_aim,info->max_x/2,info->max_y/2);
        return info;
    }
    int max_destroy=0;
    int coords_destroy[2]= {0,0};
    int counter_str=(2*info->radius+1);
#ifdef TEST
    int cycle=0;
#endif // TEST

    for(int i = info->radius; i<info->size_coords-info->radius; i++)
    {

        for(int j = info->radius; j<info->size_coords-info->radius; j++)
        {
            int tmpMax=0;
            int cnt_cycle_string=0;
            int counterX=j-info->radius;
            int counterY=i-info->radius;
            int tmp_Y=counterY;
            while(1)
            {
                if(info->coords_aim[counterY][counterX+cnt_cycle_string]==1)
                {
#ifdef TEST
                    printf("coords_aim[%d][%d]\n",counterX+cnt_cycle_string,counterY);
#endif // TEST
                    tmpMax++;
                }
                cnt_cycle_string++;
                if(cnt_cycle_string==counter_str)
                {
                    cnt_cycle_string=0;
                    counterY++;
                }

                if(counterY==tmp_Y+(2*info->radius)+1)
                {
                    break;
                }
            }
            if(max_destroy<tmpMax)
            {
                max_destroy=tmpMax;
                coords_destroy[0]=j;
                coords_destroy[1]=i;
            }
#ifdef TEST
            cycle++;
            printf("CYCLE %d\n",cycle);
#endif // TEST
        }
    }
    printf("Max destroy = %d\nby coordinates:x = %d and y = %d\n",
           max_destroy,coords_destroy[0],coords_destroy[1]);
    return info;
}
void destroy(file_info *const info)
{
    if(info->isCorrect)
    {
        for(int i = 0; i<info->size_coords; i++)
        {
            free(info->coords_aim[i]);

        }
        free(info->coords_aim);
    }
    free(info);
#ifdef TEST
    printf("ALL DESTROY\n");
#endif // TEST
}
