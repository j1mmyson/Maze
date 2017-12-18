#include <stdio.h>
#include <string.h>
#include <termio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
int getch(void);
struct Player{
    char name[20];
    int x;
    int y;
    int stage;
};
int boss(struct Player p);//Boss Stage.exe
void bossmap(char map[40][40]);//Boss map
void start();
int map2(struct Player p);//mola;
int blindmaze(struct Player p);//1stage.exe
void blindmap(char map[20][20]);//1stage map
int stage2(struct Player p,struct Player p2);//2stage.exe
void main(){
    struct Player p,p2;
    
    char cmd;
    int pick;
    int stage1;
    int bossstage;
    intro:
    system("clear");
    p.x=1;
    p.y=1;
    p2.x=1;
    p2.y=20;
    
    fflush(stdin);
    start();
    pick=getch();
    if(pick=='x'){
        goto end ;
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
    stage1=blindmaze(p);//blindmaze fin
    if(stage1==1)
        goto intro;
    stage2(p,p2);//stage2 게임 끝
    bossstage=boss(p);
    if(bossstage==1)
        goto intro;
   end:
   sleep(1);
   system("clear");
   printf("                              Good bye\n ");
   sleep(3);
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
    printf("\n\n\n                  Press any button (press 'x' to Exit)");
}
int blindmaze(struct Player p){//재형이가 만든게임
    system("clear");
    int i,j,exit=0,mc=0;
    int count,count_cmd=0,cn;
    char map[20][20],cmd;
    char space=' ';
    p.x=p.y=2;
    blindmap(map);
    map[16][15]='&';//finish point

    printf("\n\n\n\n");
    printf("                        STAGE 1 \n\n");
    printf("            Maze is crumbling down! get hurry!\n");
    printf("       I.Memorize maze for 10 second and Go to &\n");
    printf("       II.You can't pass the wall (#,@) \n");
    printf("       III.If you don't escape this maze for 100moves you will die!\n");
    sleep(6);
    system("clear");
    printf("Player : %s\n",p.name);
    map[p.x][p.y]='P';
        for(i=0;i<20;i++){
            for(j=0;j<20;j++){
                printf("%2c",map[i][j]);
            }
            printf("\n");
        }
        sleep(5);
        while(1){
            map[p.x][p.y]='P';
            system("clear");
            printf("Player : %s \n\n\n",p.name);
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
                    if(p.x!=1&& map[p.x-1][p.y] != '#'&&map[p.x-1][p.y]!='@'){
                        count_cmd ++;
                        map[p.x][p.y]=' ';
                        p.x --;
                    }
                    else map[p.x-1][p.y]='@';
                    break;
                case 'a':
                    if(p.y!=1 && map[p.x][p.y-1]!= '#'&&map[p.x][p.y-1]!='@'){
                        count_cmd ++;
                        map[p.x][p.y]=' ';
                        p.y --;
                    }
                    else
                        map[p.x][p.y-1]='@';
                    break;
                case 's':
                    if(p.x != 18 && map[p.x+1][p.y]!= '#'&&map[p.x+1][p.y]!= '@'){
                        count_cmd ++;
                        map[p.x][p.y]=' ';
                        p.x ++;
                    }
                    else
                        map[p.x+1][p.y]='@';
                    break;
                case 'd':
                    if(p.y!= 18 && map[p.x][p.y+1]!='#'&&map[p.x][p.y+1]!='@'){
                        count_cmd ++;
                        map[p.x][p.y]=' ';
                        p.y ++;
                    }
                    else
                        map[p.x][p.y+1]='@';
                    break;
            }
            if(count_cmd>100){
                printf("\n\n\n\n                  Failed....\n");
                sleep(3);
                return 1;
            }
            if(p.x==16 &&p.y==15){
                map[16][15]='P';
                map[17][15]=' ';
                system("clear");
                for(i=0;i<20;i++){
                    for(j=0;j<20;j++){
                        printf("%2c",map[i][j]);
                    }
                    printf("\n");
                }
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
int stage2(struct Player p,struct Player p2){//병욱이가 만든 게임
    char map[20][40];
    int i,j;
    char cmd;
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
    sleep(8);

    while(1){
        system("clear");
        printf("Player : %s \n\n\n",p.name);
        map[p.x][p.y]='P';
        map[p2.x][p2.y]='D';
        map[18][18]='&';
        map[18][38]='&';
        for(i=0;i<20;i++){
            for(j=0;j<40;j++){
                
                printf("%2c",map[i][j]);
            }
            printf("\n");
        }//맵 출력
        if(p.x==18&&p.y==18&&p2.x==18&&p2.y==38){//클리어 조건
            system("clear");
            p.x=1,p.y=1;
            p2.x=1,p2.y=19;
            sleep(1);
            return 0;
        }
        cmd=getch();

        switch(cmd){
            case 'w':
                if(p.x!=1&&map[p.x-1][p.y]!='#'){
                    map[p.x][p.y]=' ';
                    while(map[p.x-1][p.y]!='#'){
                        p.x--;
                    }
                }
                if(p2.x!=1&&map[p2.x-1][p2.y]!='#'){
                    map[p2.x][p2.y]=' ';
                    while(map[p2.x-1][p2.y]!='#'){
                        p2.x--;
                    }
                }
                break;
            case 'a':
               if(p.y!=1&&map[p.x][p.y-1]!='#'){
                   map[p.x][p.y]=' ';
                    while(map[p.x][p.y-1]!='#'){
                        p.y--;
                    }
               }
               if(p2.y!=1&&map[p2.x][p2.y-1]!='#'){
                   map[p2.x][p2.y]=' ';
                    while(map[p2.x][p2.y-1]!='#'){
                        p2.y--;
                    }
               }
                break;
             case 's':
                 if(p.x!=18&&map[p.x+1][p.y]!='#'){
                     map[p.x][p.y]=' ';
                      while(map[p.x+1][p.y]!='#'){
                        p.x++;
                      }
                 }
                 if(p2.x!=18&&map[p2.x+1][p2.y]!='#'){
                     map[p2.x][p2.y]=' ';
                      while(map[p2.x+1][p2.y]!='#'){
                        p2.x++;
                      }
                 }
                break;
            case 'd':
                if(p.y!=18&&map[p.x][p.y+1]!='#'){
                    map[p.x][p.y]=' ';
                    while(map[p.x][p.y+1]!='#'){
                        p.y++;
                    }
                }
                if(p2.y!=18&&map[p2.x][p2.y+1]!='#'){
                    map[p2.x][p2.y]=' ';
                    while(map[p2.x][p2.y+1]!='#'){
                        p2.y++;
                    }
                }
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
int boss(struct Player p){
    char map[40][40];
    int key=0;
    int mx[3];
    int my[3];//몬스터들의 좌표값
    int i=0,j=0,k=0;
    int life=3;
    char space=' ';
    char cmd;
    system("clear");
    bossmap(map);
    printf("\n\n\n\n");
    printf("                        ^BOSS STAGE^ \n\n");
    printf("            You are in the dark maze with a candle !\n");
    printf("       I.Collect 3 key(*) as avoiding monster (M)!!!!\n");
    printf("       II.If you collect 3 keys go to & to escape this maze! \n");
    sleep(8);
    p.x=p.y=1;
    
    map[p.x][p.y]='P';
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
                if(map[p.x][p.y]=='&'){
                    system("clear");
                    printf("\n\n\n\n\n");
                    printf("                         Congratulation!!\n");
                    printf("                     You escape all of this maze!\n");
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
                if(map[p.x][p.y]==map[mx[i]][my[i]]){
                    p.x=p.y=1;
                    life--;
                }
            }
            map[p.x][p.y]='P';
            system("clear");
            for(i=0;i<3;i++){
            printf("m1x:%d m2x:%d \n",mx[i],my[i]);
            }
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
                    else if((p.x-i)*(p.x-i)+(p.y-j)*(p.y-j)<25){
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
                    if(p.x!=1&& map[p.x-1][p.y] != '#'){
                        if(map[p.x-1][p.y]=='*')
                            key++;
                        map[p.x][p.y]=' ';
                        p.x --;
                    }
                    break;
                case 'a':
                    if(p.y!=1 && map[p.x][p.y-1]!= '#'){
                        if(map[p.x][p.y-1]=='*')
                            key++;
                        map[p.x][p.y]=' ';
                        p.y --;
                    }
                    break;
                case 's':
                    if(p.x != 39 && map[p.x+1][p.y]!= '#'){
                        if(map[p.x+1][p.y]=='*')
                            key++;
                        map[p.x][p.y]=' ';
                        p.x ++;
                    }
                    break;
                case 'd':
                    if(p.y!= 39 && map[p.x][p.y+1]!='#'){
                        if(map[p.x][p.y+1]=='*')
                            key++;
                        map[p.x][p.y]=' ';
                        p.y ++;
                    }
                    break;
            }// moving
            for(i=0;i<3;i++){
                if((p.x-mx[i])*(p.x-mx[i])+(p.y-my[i])*(p.y-my[i])<16){
                   if(p.x>mx[i]&&map[mx[i]+1][my[i]]!='#'){
                        map[mx[i]][my[i]]=' ';
                        mx[i]++;

                   }
                   else if(p.y>my[i] && map[mx[i]][my[i]+1]!='#'){
                        map[mx[i]][my[i]]=' ';
                        my[i]++;
                   }
                   else if(p.x<mx[i] && map[mx[i]-1][my[i]]!='#'){
                        map[mx[i]][my[i]]=' ';
                        mx[i]--;
                   }
                   else if(p.y<my[i] && map[mx[i]][my[i]-1]!='#'){
                       map[mx[i]][my[i]]=' ';
                       my[i]--;
                   }


                }



            }

    } 






}
