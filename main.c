#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int pages;
char  algorithm[256];
int count = 0;
int countt = 0; //faults
int ref[100]; // size of refrence array for big inputs increase size


void readstdin()   // input from user
{
    scanf("%d",&pages);
    scanf("%s",algorithm);
    while (1)
    {
        scanf("%d",&ref[count]);
        if(ref[count]==-1)
        {
            ref[count]=0;
            break;
        }
        else
            count ++;
    }
}

void CLOCK()
{

    int frame[pages] ;
    int usage[pages] ;
    int index = 0;
    int pointer = 0;
    int flag = 0;
    int flagRemove = 0;

    printf("Replacement Policy = CLOCK\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");


    for(int i = 0; i < pages; i++)
    {
        frame[i] = -1;
    }


    for(int i = 0; i < count; i++)
    {

        //if the page exist in pages
        flag = 0;
        for(int j = 0; j < pages; j++)
        {
            if(ref[i] == frame[j])
            {
                flag = 1;
                usage[j] = 1;
                break;
            }
        }

        if(flag == 0)
        {
            if(frame[index] == -1)
            {
                frame[index] = ref[i];
                usage[index++] = 1;
                printf("%02d     ",ref[i]);
                for(int j = 0 ; j < index ; j++)
                {
                    printf("%02d ",frame[j]);
                }
                printf("\n");
            }
            else
            {
                flagRemove = 0;
                while(!flagRemove)
                {
                    pointer = pointer % pages;
                    if(usage[pointer] == 1)
                    {
                        usage[pointer++] = 0;
                    }
                    else if(usage[pointer] == 0)
                    {
                        frame[pointer] = ref[i];
                        usage[pointer++] = 1;
                        flagRemove = 1;
                    }
                }
                countt++;
                printf("%02d F   ",ref[i]);
                for(int j = 0 ; j < pages ; j++)
                {
                    printf("%02d ",frame[j]);
                }
                printf("\n");
            }
        }
        else
        {
            printf("%02d     ",ref[i]);
            for(int j = 0 ; j < index ; j++)
            {
                printf("%02d ",frame[j]);
            }
            printf("\n");
        }
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",countt);


}

int find_LRU(int arr[])
{
    int max = -9999;
    int index;
    int i;
    for(i=0;i<pages;i++){
        if(arr[i]>max){
            max = arr[i];
            index = i;
        }
    }
    return index;
}

void LRU()
{
    int frame[pages];
    int usage[pages];
    int index,iterator,i,j,k;
    int flag1,flag2;

    printf("Replacement Policy = LRU\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    for(i=0;i<pages;i++)
        frame[i]=-1;
    for(i=0;i<pages;i++)
        usage[i] = 0;


    for(i=0;i<count;i++){
        printf("%02d ",ref[i]);
        flag1 = 0;
        flag2 = 0;

        for(j=0;j<pages;j++){
            if(ref[i]==frame[j]){
                flag1 = 1;
                index = j;
            }
        }
        //page already exists
        if(flag1 == 1){
            printf("    ");
            for(j=0;j<pages;j++)
                usage[j]++;
            usage[index]=0;
            for(j=0;j<pages;j++){
                if(frame[j]==-1)
                    continue;
                printf("%02d ",frame[j]);
            }
        }
        //page does note exists

        else if(flag1 == 0){
            for(j=0;j<pages;j++){
                if(frame[j]==-1){
                    flag2 = 1;  //there is an empty slot in frame array
                    frame[j] = ref[i];
                    for(k=0;k<pages;k++)
                        usage[k]++;
                    usage[j] = 0;
                    break;
                }
            }
            if(flag2 == 0){
                iterator = find_LRU(usage);
                frame[iterator] = ref[i];
                for(k=0;k<pages;k++)
                    usage[k]++;
                usage[iterator] = 0;
                printf("F   ");
                countt++;
            }
            else if(flag2==1)
                printf("    ");
            for(j=0;j<pages;j++){
                if(frame[j]==-1)
                    continue;
                printf("%02d ",frame[j]);
            }

        }
        printf("\n");
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",countt);
}

void FIFO()
{
    int frame[pages],i,j,k;
    int iterator=0;
    int flag;

    for(i=0;i<pages;i++)
        frame[i]=-1;

    printf("Replacement Policy = FIFO\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    for(i=0;i<count;i++){
        printf("%02d ",ref[i]);
        flag=0;
        for(j=0;j<pages;j++)
            if(frame[j] == ref[i])
                flag = 1;

        if(flag==0){
            if(frame[iterator] == -1){
                frame[iterator] = ref[i];
                iterator++;
                if(iterator == pages)
                    iterator=0;
                printf("    ");
                for(j=0;j<pages;j++){
                    if(frame[j]==-1)
                        continue;
                    printf("%02d ",frame[j]);
                }
            }
            else{
                countt++;
                frame[iterator] = ref[i];
                iterator++;
                if(iterator == pages)
                    iterator=0;
                printf("F   ");
                for(j=0;j<pages;j++){
                    if(frame[j]==-1)
                        continue;
                    printf("%02d ",frame[j]);
                }

            }
        }
        else if(flag==1){
            printf("    ");
            for(j=0;j<pages;j++){
                if(frame[j]==-1)
                    continue;
                printf("%02d ",frame[j]);
            }
        }
        printf("\n");
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",countt);
}

void OPTIMAL ()   // OPTIMAL algorithm func
{
    int i,j,k,pos,temp[10],flag1,flag2,flag3,max,arr[pages];
    printf("Replacement Policy = OPTIMAL\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    for(i = 0; i < pages; ++i)
    {
        arr[i] = -1;
    }

    for(i = 0; i < count; ++i)
    {
        flag1 = flag2 = 0;

        for(j = 0; j < pages; ++j)
        {
            if(arr[j] == ref[i])
            {
                flag1 = flag2 = 1;
                printf("%02d ",ref[i]);
                printf("    ");
                for(j = 0; j < pages; ++j)
                {
                    if(arr[j] == -1)
                        continue;
                    printf("%02d ", arr[j]);
                }
                break;
            }
        }
        if(flag1 == 0)
        {
            for(j = 0; j < pages; ++j)
            {
                if(arr[j] == -1)
                {
                    arr[j] = ref[i];
                    flag2 = 1;
                    printf("%02d ",ref[i]);
                    printf("    ");
                    for(j = 0; j < pages; ++j)
                    {
                        if(arr[j] == -1)
                            continue;
                        printf("%02d ", arr[j]);

                    }
                    break;
                }
            }
        }

        if(flag2 == 0)
        {
            flag3 =0;
            for(j = 0; j < pages; ++j)
            {
                temp[j] = -1;

                for(k = i + 1; k < count; ++k)
                {
                    if(arr[j] == ref[k])
                    {
                        temp[j] = k;
                        break;
                    }
                }
            }
            for(j = 0; j < pages; ++j)
            {
                if(temp[j] == -1)
                {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }
            if(flag3 ==0)
            {
                max = temp[0];
                pos = 0;
                for(j = 1; j < pages; ++j)
                {
                    if(temp[j] > max)
                    {
                        max = temp[j];
                        pos = j;
                    }
                }
            }

            arr[pos] = ref[i];
            countt++;
            printf("%02d ",ref[i]);
            printf("F   ");
            for(j = 0; j < pages; ++j)
            {
                if(arr[j] == -1)
                    continue;
                printf("%02d ", arr[j]);

            }
        }
        printf("\n");
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",countt);
}


int main()
{
    char file[256];
    int x;
    //printf("Enter 1 for file input or 2 for standard input: ");
    //scanf("%d",&x);
    x = 2;


    if (x==2)
    {
        readstdin();
    }

    if (strcmp(algorithm,"FIFO")==0)
    {
        FIFO();
    }
    else if (strcmp(algorithm,"CLOCK")==0)
    {
        CLOCK();
    }
    else if (strcmp(algorithm,"LRU")==0)
    {
        LRU();
    }
    else if (strcmp(algorithm,"OPTIMAL")==0)
    {
        OPTIMAL();
    }

    else
    {
        printf("No such file\n");
    }
    return 0;
}
