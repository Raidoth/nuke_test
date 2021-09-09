#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int max(int a,int b);
int main(int argc,char** argv)
{
    if(argc==3)
    {
        const char* name_file=argv[1];
        int radius=atoi(argv[2]);

        FILE* fp=NULL;
        if((fp=fopen(name_file,"r"))==NULL)
        {
            printf("File not found\n");
            return 1;
        }
        int max_x=0;
        int max_y=0;

        for(int x, y; fscanf(fp,"%d,%d",&x,&y)!=EOF;)
        {
            max_x=max(max_x,x);
            max_y=max(max_y,y);
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

        int coords_aim[size_coord][size_coord];
        memset(coords_aim,0,sizeof(coords_aim));
        int count_aim=0;
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
        if(radius>=size_coord/2)
        {
            printf("Max destroy = %d\nby coordinates:x = %d and y = %d\n",count_aim,max_x/2,max_y/2);
            return 0;

        }
        int max_destroy=0;
        int coords_destroy[2]= {0,0};
        int counter_str=(2*radius+1);

        for(int i = radius; i<size_coord-radius; i++)
        {

            for(int j = radius; j<size_coord-radius; j++)
            {
                int tmpMax=0;
                int cnt_cycle_string=0;
                int counterX=j-radius;
                int counterY=i-radius;
                int tmp_Y=counterY;
                while(1)
                {
                    if(coords_aim[counterY][counterX+cnt_cycle_string]==1)
                    {
                        tmpMax++;
                    }
                    cnt_cycle_string++;
                    if(cnt_cycle_string==counter_str)
                    {
                        cnt_cycle_string=0;
                        counterY++;
                    }

                    if(counterY==tmp_Y+(2*radius)+1)
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

            }
        }
        printf("Max destroy = %d\nby coordinates:x = %d and y = %d\n",
               max_destroy,coords_destroy[0],coords_destroy[1]);
        fclose(fp);
    }
    else
    {
        printf("Incorrect input\n");
    }


}
int max(int a,int b)
{
    return a>b?a:b;
}
