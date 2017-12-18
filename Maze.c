#include <stdio.h>
#include <termio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
int getch(void);
int flag;
struct Player{
    char name[20];
    double score;
}per[10],p,p2;
    struct xy{
        int x;
        int y;
    }XY,XY2;
void LoadPlayer();
void sortsaveboard();
void printboard();
int boss();//Boss Stage.exe
void bossmap(char map[40][40]);//Boss map
void start();
int map2();//mola;
int blindmaze();//1stage.exe
void blindmap(char map[20][20]);//1stage map
int stage2();//2stage.exe
void main(){

    
    char cmd;
    int pick;
    int stage1;
    int bossstage;
    LoadPlayer();
    intro:
    system("clear");
    XY.x=1;
    XY.y=1;
    XY2.x=1;
    XY2.y=20;
    p.score=0;
    
    fflush(stdin);
    start();
    pick=getch();
    if(pick=='x'){
        goto end ;
    }
    else if(pick=='z'){
        system("clear");
        printboard();
        printf("\n\n             press any button to quit\n");
        pick=getch();
        goto intro;
    }
    printf("\n                   Your Name:");
    scanf("%s",p.name);
    system("clear");
    printf("\n\n\n\n");
    printf("                             Loding..\n\n");
    printf("                    ########(      )(        )\n");
    sleep(1);
    system("clear");
    printf("\n\n\n\n");
    printf("                             Loding..\n\n");
    printf("                    ################(        )\n"); 
    sleep(1);
    system("clear");
    printf("\n\n\n\n");
    printf("                             Loding..\n\n");
    printf("                    ##########################\n");
    sleep(1);
    printf("Player : %s \n\n\n",p.name);
    stage1=blindmaze();//blindmaze fin
    if(stage1==1)
        goto intro;
    stage2();//stage2 게임 끝
    bossstage=boss();
    if(bossstage==1)
        goto intro;
   end:
   sleep(1);
   system("clear");
   printf("\n\n\n\n                              The End\n ");

    sleep(3);
    system("clear");
    sortsaveboard();
    printboard();
}//main끝

int getch(void){//getch함수

    struct termios oldt;
    struct termios newt;
    int ch;
    tcgetattr(STDIN_FILENO,&oldt);
    newt=oldt;
    newt.c_lflag &=~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
    return ch;
}//getch함수 끝
void start(){
    printf("########################################################################################\n");
    printf("############      ###      ########     ######            ####             #############\n");
    printf("###########   ###     ###   ######       ############    #####   #######################\n");
    printf("###########   ####   ####   #####  ###   ###########   #######   #######################\n");
    printf("###########   ####   ####   ####  #####  #########    ########   #######################\n");
    printf("###########   ####   ####   ###  ######  ####            #####             #############\n");
    printf("###########   ####   ####   ##            ######   ###########   #######################\n");
    printf("###########   ####   ####   #   #######   #####   ############   #######################\n");
    printf("###########   ####   ####   #  ########   ####            ####             #############\n");
    printf("########################################################################################\n");
    printf("\n\n");
    printf("                                 UP:W                                            \n\n");
    printf("                    LEFT:A                RIGHT:D\n\n");
    printf("                                DOWN:S \n");
    printf("\n\n\n                  Press any button (press 'x' to Exit)\n");
    printf("                           z:view leaderboard\n");
}
int blindmaze(){//재형이가 만든게임
    system("clear");
    double realc=0;
    int i,j,exit=0,mc=0;
    int count,count_cmd=0,cn;
    char map[20][20],cmd;
    char space=' ';
    char pick;
    XY.x=XY.y=2;
    blindmap(map);
    map[16][15]='&';//finish point

    printf("\n\n\n\n");
    printf("                        STAGE 1 \n\n");
    printf("            Maze is crumbling down! get hurry!\n");
    printf("       I.Memorize maze for 10 second and Go to &\n");
    printf("       II.You can't pass the wall (#,@) \n");
    printf("       III.If you don't escape this maze for 100moves you will die!\n");
    printf("             Are you Ready? Press 'g' to start!\n");
    pick=getch();
    while(pick!='g'){

        pick=getch();
    }
    
    system("clear");
    printf("Player : %s\n",p.name);
    map[XY.x][XY.y]='P';
        for(i=0;i<20;i++){
            for(j=0;j<20;j++){
                printf("%2c",map[i][j]);
            }
            printf("\n");
        }
        sleep(5);
        while(1){
            map[XY.x][XY.y]='P';
            system("clear");
            printf("Player : %s \n ",p.name);
            printf("Score : %.1f \n\n\n",70+(100-2*realc)*0.3);
            for(i=0;i<20;i++){
                for(j=0;j<20;j++){
                    if((2<=i&&i<=17)&&(2<=j&&j<=17)){
                        if(map[i][j]=='#')
                            printf("%2c",space);
                        else
                            printf("%2c",map[i][j]);
                    }
                    else
                        printf("%2c",map[i][j]);
                }
                printf("\n");
            }
            cmd=getch();
            switch(cmd){
                case 'w':
                    if(XY.x!=1&& map[XY.x-1][XY.y] != '#'&&map[XY.x-1][XY.y]!='@'){
                        count_cmd ++;
                        if(count_cmd>80){
                            realc =realc+2;
                        }
                        map[XY.x][XY.y]=' ';
                        XY.x --;
                    }
                    else map[XY.x-1][XY.y]='@';
                    break;
                case 'a':
                    if(XY.y!=1 && map[XY.x][XY.y-1]!= '#'&&map[XY.x][XY.y-1]!='@'){
                        count_cmd ++;
                        if(count_cmd>80){
                            realc=realc+2;
                        }
                        map[XY.x][XY.y]=' ';
                        XY.y --;
                    }
                    else
                        map[XY.x][XY.y-1]='@';
                    break;
                case 's':
                    if(XY.x != 18 && map[XY.x+1][XY.y]!= '#'&&map[XY.x+1][XY.y]!= '@'){
                        count_cmd ++;
                        if(count_cmd>80){
                            realc=realc+2;
                        }
                        map[XY.x][XY.y]=' ';
                        XY.x ++;
                    }
                    else
                        map[XY.x+1][XY.y]='@';
                    break;
                case 'd':
                    if(XY.y!= 18 && map[XY.x][XY.y+1]!='#'&&map[XY.x][XY.y+1]!='@'){
                        count_cmd ++;
                        if(count_cmd>80){
                            realc=realc+2;
                        }
                        map[XY.x][XY.y]=' ';
                        XY.y ++;
                    }
                    else
                        map[XY.x][XY.y+1]='@';
                    break;
            }
            if(count_cmd>100){
                printf("\n\n\n\n                  Failed....\n");
                sleep(3);
                return 1;
            }
            if(XY.x==16 &&XY.y==15){
                XY.x=XY.y=1;
                p.score=(100-(2*realc))*0.3;
                map[16][15]='P';
                map[17][15]=' ';
                system("clear");
            return 0;
            }
        }
return 0;
}
//재형이가 만든게임 끝
void blindmap(char map[20][20]){
    int i,j;

    for(i=0;i<20;i++){
        for(j=0;j<20;j++){
            map[i][j]=' ';
            if(i==19||i==18)
                map[i][j]='#';
            if(i==0||i==1||j==0||j==1||j==19||j==18){
                map[i][j]='#';
                } 
            }
        }
map[2][3]='#',map[2][16]='#',map[2][17]='#';
    map[3][3]='#',map[3][5]='#',map[3][7]='#',map[3][8]='#',map[3][10]='#',map[3][11]='#',map[3][12]='#',map[3][14]='#';
    map[4][3]='#',map[4][4]='#',map[4][8]='#',map[4][10]='#',map[4][11]='#',map[4][12]='#',map[4][13]='#',map[4][14]='#',map[4][15]='#',map[4][16]='#';
    map[5][6]='#',map[5][7]='#',map[5][10]='#',map[5][12]='#',map[5][17]='#';
    map[6][3]='#',map[6][4]='#',map[6][5]='#',map[6][9]='#',map[6][10]='#',map[6][12]='#',map[6][13]='#',map[6][15]='#';
    map[7][3]='#',map[7][4]='#',map[7][5]='#',map[7][7]='#',map[7][10]='#',map[7][13]='#',map[7][16]='#';
    map[8][4]='#',map[8][8]='#',map[8][9]='#',map[8][13]='#',map[8][15]='#';
    map[9][3]='#',map[9][6]='#',map[9][9]='#',map[9][11]='#',map[9][13]='#',map[9][16]='#';
    map[10][3]='#',map[10][5]='#',map[10][6]='#',map[10][7]='#',map[10][8]='#',map[10][11]='#',map[10][14]='#',map[10][16]='#';
    map[11][3]='#',map[11][10]='#',map[11][11]='#',map[11][12]='#',map[11][16]='#';
    map[12][3]='#',map[12][5]='#',map[12][7]='#',map[12][8]='#',map[12][10]='#',map[12][15]='#';
    map[13][3]='#',map[13][4]='#',map[13][5]='#',map[13][6]='#',map[13][7]='#',map[13][8]='#',map[13][9]='#',map[13][11]='#',map[13][13]='#',map[13][14]='#';
    map[14][11]='#',map[14][13]='#',map[14][16]='#';
    map[15][3]='#',map[15][5]='#',map[15][7]='#',map[15][8]='#',map[15][11]='#',map[15][12]='#',map[15][15]='#';
    map[16][8]='#',map[16][9]='#',map[16][11]='#',map[16][12]='#',map[16][13]='#',map[16][14]='#',map[16][16]='#';
    map[17][4]='#',map[17][6]='#',map[17][14]='#';
};//블라인드메이즈 맵 완성
int stage2(){//병욱이가 만든 게임
    char map[20][40];
    double count_cmd=0;
    int i,j;
    char cmd;
    char pick;
    for(i=0;i<20;i++){
        for(j=0;j<40;j++){
            map[i][j]=' ';
            if(j==39)
                map[i][j]='#';
            if(i==19)
                map[i][j]='#';
            if(i==0||i==0||j==0||j==19||(i==19&&j==19)){
                map[i][j]='#';
            } 
        }
    }//초기 맵 설정
    
        for(i=0;i<60;i++){
            
            map[rand()%20][rand()%20]='#';
            map[rand()%20][rand()%20+20]='#';
        }
    //for(i=3;i<10;i++){
   //     map[i][5]='#';
    //}
    //장애물(추후에 랜덤함수이용해서 할꺼임
    system("clear");
    printf("\n\n\n\n");
    printf("                        STAGE 2\n\n");
    printf("            You can't stop 'P' until you hit the wall!\n");
    printf("           I.'P' and 'D' move at a time\n");
    printf("          II.Take 'P'and'D' to &!!\n");

    printf("             Are you Ready? Press 'g' to start!\n");
    pick=getch();
    while(pick!='g'){

        pick=getch();
    }
    while(1){
        system("clear");
        printf("Player : %s ",p.name);
        printf("Score : %.1f\n\n\n",40+p.score+(100-count_cmd)*0.3);
        map[XY.x][XY.y]='P';
        map[XY2.x][XY2.y]='D';
        map[18][18]='&';
        map[18][38]='&';
        for(i=0;i<20;i++){
            for(j=0;j<40;j++){
                
                printf("%2c",map[i][j]);
            }
            printf("\n");
        }//맵 출력
        if(XY.x==18&&XY.y==18&&XY2.x==18&&XY2.y==38){//클리어 조건
            system("clear");
            XY.x=1,XY.y=1;
            XY2.x=1,XY2.y=19;
            sleep(1);
            p.score=p.score+(100-count_cmd)*0.3;
            return 0;
        }
        cmd=getch();

        switch(cmd){
            case 'w':
                if(XY.x!=1&&map[XY.x-1][XY.y]!='#'){
                    map[XY.x][XY.y]=' ';
                    while(map[XY.x-1][XY.y]!='#'){
                        XY.x--;
                    }
                }
                if(XY2.x!=1&&map[XY2.x-1][XY2.y]!='#'){
                    map[XY2.x][XY2.y]=' ';
                    while(map[XY2.x-1][XY2.y]!='#'){
                        XY2.x--;
                    }
                }
                count_cmd ++;
                break;
            case 'a':
               if(XY.y!=1&&map[XY.x][XY.y-1]!='#'){
                   map[XY.x][XY.y]=' ';
                    while(map[XY.x][XY.y-1]!='#'){
                        XY.y--;
                    }
                    
               }
               if(XY2.y!=1&&map[XY2.x][XY2.y-1]!='#'){
                   map[XY2.x][XY2.y]=' ';
                    while(map[XY2.x][XY2.y-1]!='#'){
                        XY2.y--;
                    }
               }
               count_cmd ++;
               break;
             case 's':
                 if(XY.x!=18&&map[XY.x+1][XY.y]!='#'){
                     map[XY.x][XY.y]=' ';
                      while(map[XY.x+1][XY.y]!='#'){
                        XY.x++;
                      }
                 }
                 if(XY2.x!=18&&map[XY2.x+1][XY2.y]!='#'){
                     map[XY2.x][XY2.y]=' ';
                      while(map[XY2.x+1][XY2.y]!='#'){
                        XY2.x++;
                      }
                 }
                 count_cmd ++;
                 break;
            case 'd':
                if(XY.y!=18&&map[XY.x][XY.y+1]!='#'){
                    map[XY.x][XY.y]=' ';
                    while(map[XY.x][XY.y+1]!='#'){
                        XY.y++;
                    }
                }
                if(XY2.y!=18&&map[XY2.x][XY2.y+1]!='#'){
                    map[XY2.x][XY2.y]=' ';
                    while(map[XY2.x][XY2.y+1]!='#'){
                        XY2.y++;
                    }
                }
                count_cmd ++;
                break;
        }//플레이어 이동
    }
}
void bossmap(char map[40][40]){
    int i,j;
    for(i=0;i<40;i++){
        for(j=0;j<40;j++){
            map[i][j]=' ';
            if(j==0||j==39||i==0||i==39||i==3&&j!=38){
                map[i][j]='#';
            }

        }
    }

}
int boss(){
    char map[40][40];
    int key=0;
    int mx[3];
    int my[3];//몬스터들의 좌표값
    int i=0,j=0,k=0;
    int life=3;
    char space=' ';
    char cmd;
    char pick;
    system("clear");
    bossmap(map);
    printf("\n\n\n\n");
    printf("                        ^BOSS STAGE^ \n\n");
    printf("            You are in the dark maze with a candle !\n");
    printf("       I.Collect 3 key(*) as avoiding monster (M)!!!!\n");
    printf("       II.If you collect 3 keys go to & to escape this maze! \n");
    
    printf("             Are you Ready? Press 'g' to start!\n");
    pick=getch();
    while(pick!='g'){

        pick=getch();
    }
    XY.x=XY.y=1;
    
    map[XY.x][XY.y]='P';
    for(i=0;i<300;i++){
            
        map[rand()%38+2][rand()%40]='#';
             
    }
    for(i=0;i<3;i++){
        mx[i]=rand()%36+5;
        my[i]=rand()%38;
        if(map[mx[i]][my[i]]!='#'){
            map[mx[i]][my[i]]='M';
        }
        else i--;

    }
    for(i=0;i<3;i++){
        if(map[rand()%36+2][rand()%38]!='#'&&map[rand()%36+2][rand()%38]!='M'){
            map[rand()%36+2][rand()%38]='*';
        }
        else i--;

    }


    map[36][38]='&';


        while(1){

            if(key==3){
                if(map[XY.x][XY.y]=='&'){
                    p.score=p.score+(life*33)*0.4;
                    system("clear");
                    printf("\n\n\n\n\n");
                    printf("                         Congratulation!!\n");
                    printf("                     You escape all of this maze!\n");
                    printf("                           Your Score:%.1f \n",p.score);
                    sleep(5);
                    return 0;
                }
            }
            if(life==0){
                system("clear");
                printf("\n\n\n\n                                Failed..\n");
                printf("                         You are loceked in this maze\n");
                sleep(5);
                return 1;
            }
            map[mx[0]][my[0]]='M';
            map[mx[1]][my[1]]='M';
            map[mx[2]][my[2]]='M';
            for(i=0;i<3;i++){
                if(map[XY.x][XY.y]==map[mx[i]][my[i]]){
                    XY.x=XY.y=1;
                    life--;
                }
            }
            map[XY.x][XY.y]='P';
            system("clear");
            printf("Player : %s\n",p.name);
            printf("Life : ");
            for(i=0;i<life;i++)
                printf("$ ");
            printf("\n");
            for(i=0;i<40;i++){
                for(j=0;j<40;j++){
                    if(i==0||i==39||j==0||j==39){
                        printf("%2c",map[i][j]);
                    }
                    else if((XY.x-i)*(XY.x-i)+(XY.y-j)*(XY.y-j)<25){
                        printf("%2c",map[i][j]);
                    }
                    else
                        printf("%2c",space);
                }
                printf("\n");
            }
            cmd=getch();
            switch(cmd){
                case 'w':
                    if(XY.x!=1&& map[XY.x-1][XY.y] != '#'){
                        if(map[XY.x-1][XY.y]=='*')
                            key++;
                        map[XY.x][XY.y]=' ';
                        XY.x --;
                    }
                    break;
                case 'a':
                    if(XY.y!=1 && map[XY.x][XY.y-1]!= '#'){
                        if(map[XY.x][XY.y-1]=='*')
                            key++;
                        map[XY.x][XY.y]=' ';
                        XY.y --;
                    }
                    break;
                case 's':
                    if(XY.x != 39 && map[XY.x+1][XY.y]!= '#'){
                        if(map[XY.x+1][XY.y]=='*')
                            key++;
                        map[XY.x][XY.y]=' ';
                        XY.x ++;
                    }
                    break;
                case 'd':
                    if(XY.y!= 39 && map[XY.x][XY.y+1]!='#'){
                        if(map[XY.x][XY.y+1]=='*')
                            key++;
                        map[XY.x][XY.y]=' ';
                        XY.y ++;
                    }
                    break;
            }// moving
            for(i=0;i<3;i++){
                if((XY.x-mx[i])*(XY.x-mx[i])+(XY.y-my[i])*(XY.y-my[i])<16){
                   if(XY.x>mx[i]&&map[mx[i]+1][my[i]]!='#'){
                        map[mx[i]][my[i]]=' ';
                        mx[i]++;

                   }
                   else if(XY.y>my[i] && map[mx[i]][my[i]+1]!='#'){
                        map[mx[i]][my[i]]=' ';
                        my[i]++;
                   }
                   else if(XY.x<mx[i] && map[mx[i]-1][my[i]]!='#'){
                        map[mx[i]][my[i]]=' ';
                        mx[i]--;
                   }
                   else if(XY.y<my[i] && map[mx[i]][my[i]-1]!='#'){
                       map[mx[i]][my[i]]=' ';
                       my[i]--;
                   }


                }



            }

    } 






}
void LoadPlayer(){
    int i=0;
    FILE *fp = fopen("leaderboard.txt","r+");

    if(fp==NULL){
        printf("Data Load Fail\n");
        return;
    }
    while(1){
        fscanf(fp,"%s %lf",per[i].name,&per[i].score);

    if(per[i].score==0){
        flag=i;
        break;
    }
    i++;
    }
    fclose(fp);
}

void sortsaveboard(){
    strcpy(per[flag].name,p.name);
    per[flag].score=p.score;

    for(int i=0;i<flag;i++){
        for(int j=0;j<flag-i;j++){
            if(per[j].score<per[j+1].score){
                struct Player temp = per[j];
                per[j]=per[j+1];
                per[j+1]=temp;
            }
        }
    }

    FILE *fp = fopen("leaderboard.txt","w+");
    for(int i=0;i<flag+1;i++){
        fprintf(fp,"\t\t%s\t\t%.1lf\n",per[i].name,per[i].score);
    }
    fclose(fp);
}

void printboard(){
    char i;
    FILE *fp = fopen("leaderboard.txt","r+");
    printf("\n\n\n");
    printf("\t\t  == leaderboard ==\n");
    printf("\t\tName\t\tScore\n");
    printf("\t\t=====================\n");

    while(1){

        i=fgetc(fp);
        if(i==EOF)break;
        putchar(i);
    }
    fclose(fp);
}
