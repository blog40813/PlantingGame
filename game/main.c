#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>

#define GAME_TERMINATE 666
#define TIMEMAX 2160
#define RESERVE_SAMPLES 4

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE *main_event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_BITMAP* cursor = NULL;
ALLEGRO_BITMAP* ch1 = NULL;
ALLEGRO_BITMAP* field = NULL;
ALLEGRO_BITMAP* lit_cot = NULL;
ALLEGRO_BITMAP* grass = NULL;
ALLEGRO_BITMAP* bug1 = NULL;
ALLEGRO_BITMAP* bug2 = NULL;
ALLEGRO_BITMAP* crop = NULL;
ALLEGRO_BITMAP* wit_cot = NULL;
ALLEGRO_BITMAP* win_ch_display = NULL;
ALLEGRO_BITMAP* best_nigga = NULL;
ALLEGRO_BITMAP* press_esc = NULL;
ALLEGRO_BITMAP* winword3 = NULL;
ALLEGRO_BITMAP* winword4 = NULL;
ALLEGRO_BITMAP* rainbow = NULL;
ALLEGRO_BITMAP* market = NULL;
ALLEGRO_BITMAP* rain1 = NULL;
ALLEGRO_BITMAP* rain2 = NULL;
ALLEGRO_BITMAP* wit_tree = NULL;
ALLEGRO_BITMAP* lose_word = NULL;
ALLEGRO_BITMAP* background = NULL;
ALLEGRO_BITMAP* background_lose = NULL;
ALLEGRO_BITMAP* title = NULL;
ALLEGRO_BITMAP* pass0 = NULL;
ALLEGRO_BITMAP* pass1 = NULL;
ALLEGRO_BITMAP* pass2 = NULL;
ALLEGRO_BITMAP* check = NULL;
ALLEGRO_BITMAP* about1 = NULL;
ALLEGRO_BITMAP* ch2 = NULL;
ALLEGRO_BITMAP* ch3 = NULL;
ALLEGRO_BITMAP* lit_rice = NULL;
ALLEGRO_BITMAP* rice = NULL;
ALLEGRO_BITMAP* wit_rice = NULL;
ALLEGRO_BITMAP* lit_tomato = NULL;
ALLEGRO_BITMAP* tomato = NULL;
ALLEGRO_BITMAP* wit_tomato = NULL;
ALLEGRO_BITMAP* crop_s = NULL;
ALLEGRO_BITMAP* rice_s = NULL;
ALLEGRO_BITMAP* tomato_s = NULL;
ALLEGRO_BITMAP* WASD = NULL;
ALLEGRO_BITMAP* seed_bag1 = NULL;
ALLEGRO_BITMAP* seed_bag2 = NULL;
ALLEGRO_BITMAP* seed_bag3 = NULL;
ALLEGRO_BITMAP* clerk = NULL;
ALLEGRO_BITMAP* fertilizer = NULL;
ALLEGRO_BITMAP* about2 = NULL;
ALLEGRO_BITMAP* about3 = NULL;
ALLEGRO_BITMAP* home = NULL;
ALLEGRO_BITMAP* cotton_talk = NULL;
ALLEGRO_BITMAP* rice_talk = NULL;
ALLEGRO_BITMAP* tomato_talk = NULL;
ALLEGRO_BITMAP* not_for_nigga = NULL;
ALLEGRO_BITMAP* fertilizer_update = NULL;
ALLEGRO_SAMPLE* game_bgm;
ALLEGRO_SAMPLE* coin_bgm;
ALLEGRO_SAMPLE* reaping_bgm;
ALLEGRO_SAMPLE* eating_bgm;
ALLEGRO_SAMPLE* killinging_bgm;
ALLEGRO_SAMPLE* planting_bgm;
ALLEGRO_SAMPLE* purchase_bgm;
ALLEGRO_SAMPLE* victory_bgm;
ALLEGRO_SAMPLE* sucked_bgm;

ALLEGRO_SAMPLE_ID game_bgm_id;
ALLEGRO_SAMPLE_ID coin_bgm_id;
ALLEGRO_SAMPLE_ID reaping_bgm_id;
ALLEGRO_SAMPLE_ID eating_bgm_id;
ALLEGRO_SAMPLE_ID killinging_bgm_id;
ALLEGRO_SAMPLE_ID planting_bgm_id;
ALLEGRO_SAMPLE_ID purchase_bgm_id;
ALLEGRO_SAMPLE_ID victory_bgm_id;
ALLEGRO_SAMPLE_ID sucked_bgm_id;


ALLEGRO_TIMER* game_update_timer;
ALLEGRO_TIMER* win_anime_timer;


//Parameter setting

bool key_state[1000];

//Windows size, FPS
const int width = 1600;
const int height = 1200;
const int FPS=60;

//Different size font
const ALLEGRO_FONT *font;
const ALLEGRO_FONT *font_15;
const ALLEGRO_FONT *font_30;
const ALLEGRO_FONT *font_50;


//Game time, Money in hand,Pass times
int time_run = 0;
int money = 0;
int pass_time = 0;
int TARGET=30;          //target money for pass the game


//Winning/Losing animation.

int up = 1;  //move direction
int down = 0;
int jump_count = 0;     //jump duration,display winning/losing time

int rain = 0;           //control which rain to be used (convert between 0 and 1)
int rain_count = 0;     //timer for switch the rain image

//Character,game instruction pages

int character = 1;
int about_page = 1;


//recording the status of plant;

int order[15]={0};      //valid plant in field[i]
int order_total=0;      //total valid plant in field
int crop_own=15;        //total seed in hand
int plant_status[15];   //plant status for plant[i]
int time_record[15];    //time record of each plant
int plant_type[15];     //type of plant[i]
int seed[5];            //number of seed in hand of each plant
int price[5];           //price of each seed
int income[5];          //profit of each seed


//plant grow setting
int grow_speed=1;
int grow_time[5];           //grow time with grow speed i
int grow_time_mature[5];    //withered time with grow speed i


//position setting
int pos_x, pos_y; // The position of the cursor.
int bug1_f;       // bug gerneration location(y)
int bug2_f;



// the position of plant and character
typedef struct{
    int x,y;
}ch;

ch p_check;     //choose character
ch p_ch1;       //character position
ch plant[15];   //plant position
ch p_bug1;
ch p_bug2;
ch judge_plant[15][3];  //area of valid planting
ch judge_bug[15][3];    //area of valid killing
ch win_ch;


//Other setting
int hand=0;
int purchase=0;


int game_status=0;
//game_status : 0 = mainlist ;
            //  1 = game ;
            //  2 = market
            //  4 = win
            //  5 = lose


//plant_status : 0 = haven't been planted
            //   1 = little size
            //   2 = middle size
            //   3 = done


// field number
/* 1 4 7 10
   2 5 8 11
   3 6 9 12  */



//declare function

void show_err_msg(int msg);
void game_init();
void game_begin();

void game_destroy();
void mainlist_background_reset();
void game_map_display();
void about_display();
void game_update();

void cropping();
void reaping();
void killing();
void eating();
void shopping();

void plant_status_change(int);

void win_update();
void win_anime_display();
void lose_anime_display();
void game_reset();


int process_event();
int game_run();

int valid(int,int);
int valid_bug(int ,int );


int main(int argc, char *argv[]) {
    int msg = 0;



    game_init(); //line55
    game_begin(); //line83
    printf("Hello world!!!\n");

    while (msg != GAME_TERMINATE) {
        msg = game_run();
        if (msg == GAME_TERMINATE)
            printf("See you, world\n");
    }
    game_destroy();
    return 0;
}


void show_err_msg(int msg) {
    fprintf(stderr, "unexpected msg: %d", msg);
    game_destroy();
    exit(9);
}

void game_init() {
    if (!al_init()) {
        show_err_msg(-1);
    }

    pos_x = 810;
    pos_y = 600;
    win_ch.x = 50;
    win_ch.y = 800;
    p_check.x = 1040;
    p_check.y = 850;

    display = al_create_display(width, height);
    main_event_queue = al_create_event_queue();

    if (display == NULL || main_event_queue == NULL) {
        show_err_msg(-1);
    }

    /*
        TODO: Something need to be created, initialized and registered.
    */

    game_update_timer = al_create_timer(1.5f / FPS);
    win_anime_timer = al_create_timer(1.5f / FPS);

    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(RESERVE_SAMPLES);
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(RESERVE_SAMPLES);

    al_register_event_source(main_event_queue, al_get_display_event_source(display));
    al_register_event_source(main_event_queue, al_get_keyboard_event_source());
    al_register_event_source(main_event_queue, al_get_mouse_event_source());
    al_register_event_source(main_event_queue, al_get_timer_event_source(game_update_timer));
    al_register_event_source(main_event_queue, al_get_timer_event_source(win_anime_timer));

}

void game_begin() {

    cursor=al_load_bitmap("image/cursor.png");
    ch1=al_load_bitmap("image/black_skin.png");
    ch2=al_load_bitmap("image/ch2.png");
    ch3=al_load_bitmap("image/ch3.png");
    win_ch_display=al_load_bitmap("image/black_skin.png");
    field=al_load_bitmap("image/field.jpg");
    lit_cot=al_load_bitmap("image/little tree.png");
    grass=al_load_bitmap("image/grass.png");
    crop=al_load_bitmap("image/cotton.png");
    wit_cot=al_load_bitmap("image/wit cotton.png");
    bug1=al_load_bitmap("image/bug.png");
    bug2=al_load_bitmap("image/bug.png");
    best_nigga=al_load_bitmap("image/win_word.png");
    press_esc=al_load_bitmap("image/win_word2.png");
    rainbow=al_load_bitmap("image/rainbow.png");
    market=al_load_bitmap("image/market.png");
    rain1=al_load_bitmap("image/rain1.png");
    rain2=al_load_bitmap("image/rain2.png");
    wit_tree=al_load_bitmap("image/wit_tree.png");
    lose_word=al_load_bitmap("image/lose_word.png");
    background=al_load_bitmap("image/background.png");
    background_lose=al_load_bitmap("image/background_lose.png");
    lit_rice=al_load_bitmap("image/lit_rice.png");
    rice=al_load_bitmap("image/rice.png");
    wit_rice=al_load_bitmap("image/wit_rice.png");
    lit_tomato=al_load_bitmap("image/lit_tomato.png");
    tomato=al_load_bitmap("image/tomato.png");
    wit_tomato=al_load_bitmap("image/wit_tomato.png");
    crop_s=al_load_bitmap("image/cotton_s.png");
    rice_s=al_load_bitmap("image/rice_s.png");
    tomato_s=al_load_bitmap("image/tomato_s.png");
    title=al_load_bitmap("image/title.png");
    pass2=al_load_bitmap("image/pass=2.png");
    pass1=al_load_bitmap("image/pass=1.png");
    pass0=al_load_bitmap("image/pass=0.png");
    check=al_load_bitmap("image/check.png");
    about1=al_load_bitmap("image/about1.png");
    WASD=al_load_bitmap("image/WASD.png");
    seed_bag1=al_load_bitmap("image/seed_bag1.png");
    seed_bag2=al_load_bitmap("image/seed_bag2.png");
    seed_bag3=al_load_bitmap("image/seed_bag3.png");
    clerk=al_load_bitmap("image/clerk.png");
    fertilizer=al_load_bitmap("image/fertilizer.png");
    about2=al_load_bitmap("image/about2.png");
    about3=al_load_bitmap("image/about3.png");
    home=al_load_bitmap("image/back.png");
    cotton_talk=al_load_bitmap("image/cotton_talk.png");
    rice_talk=al_load_bitmap("image/rice_talk.png");
    tomato_talk=al_load_bitmap("image/tomato_talk.png");
    not_for_nigga=al_load_bitmap("image/not_for_nigga.png");
    fertilizer_update=al_load_bitmap("image/fertilizer_update.png");
    winword3=al_load_bitmap("image/win_word3.png");
    winword4=al_load_bitmap("image/win_word4.png");

    game_bgm = al_load_sample("music/game_bgm.wav");
    coin_bgm = al_load_sample("music/coin.wav");
    reaping_bgm = al_load_sample("music/reaping.wav");
    planting_bgm = al_load_sample("music/planting.wav");
    purchase_bgm = al_load_sample("music/purchase.wav");
    killinging_bgm = al_load_sample("music/killing.wav");
    eating_bgm = al_load_sample("music/eating.wav");
    victory_bgm=al_load_sample("music/victory.wav");
    sucked_bgm=al_load_sample("music/sucked.wav");

    font=al_load_ttf_font("pirulen.ttf",40,0);
    font_15=al_load_ttf_font("pirulen.ttf",15,0);
    font_30=al_load_ttf_font("pirulen.ttf",30,0);



    for(int i=1;i<=12;i++)
    {
        if(i%3==1)
        {
            judge_plant[i][1].y=137;
            judge_plant[i][2].y=345;
        }
        if(i%3==2)
        {
            judge_plant[i][1].y=375;
            judge_plant[i][2].y=565;
        }
        if(i%3==0)
        {
            judge_plant[i][1].y=595;
            judge_plant[i][2].y=785;
        }
        if(1<=i&&3>=i)
        {
            judge_plant[i][1].x=280;
            judge_plant[i][2].x=500;
        }
        if(4<=i&&6>=i)
        {
            judge_plant[i][1].x=525;
            judge_plant[i][2].x=700;
        }
        if(7<=i&&9>=i)
        {
            judge_plant[i][1].x=725;
            judge_plant[i][2].x=940;
        }
        if(10<=i&&12>=i)
        {
            judge_plant[i][1].x=950;
            judge_plant[i][2].x=1165;
        }
    }


    for(int i=1;i<=12;i++)
    {
        if(i%3==1) plant[i].y=257;
        if(i%3==2) plant[i].y=480;
        if(i%3==0) plant[i].y=700;
        if(1<=i&&3>=i) plant[i].x=350;
        if(4<=i&&6>=i) plant[i].x=575;
        if(7<=i&&9>=i) plant[i].x=800;
        if(10<=i&&12>=i) plant[i].x=1025;
    }
        for(int i=1;i<=12;i++)
    {
        judge_bug[i][1].x=plant[i].x-15;
        judge_bug[i][2].x=plant[i].x+160;
        judge_bug[i][1].y=plant[i].y-38;
        judge_bug[i][2].y=plant[i].y+165;
    }

    price[1]=20;
    price[2]=40;
    price[3]=75;
    price[4]=50;
    grow_time[1]=250;
    grow_time[2]=120;
    grow_time[3]=50;
    grow_time_mature[1]=300;
    grow_time_mature[2]=350;
    grow_time_mature[3]=400;
    income[1]=10;
    income[2]=15;
    income[3]=25;




    p_ch1.x=1200;
    p_ch1.y=800;
    p_bug2.x=1800;


    mainlist_background_reset();
    al_flip_display();
}


void game_reset(){
    for(int i=1;i<=12;i++)
    {
        plant_type[i]=0;
        plant_status[i] = 0;
        time_record[i] = 0;
        order[i] = 0;
    }
    order_total=0;

    if(character==1)TARGET=100;
    if(character==2)TARGET=150;
    if(character==3)TARGET=200;

    crop_own = 15;
    seed[1]=crop_own;
    seed[2]=0;
    seed[3]=0;
    p_ch1.x=1200;
    p_ch1.y=800;
    jump_count = 0;
    win_ch.x = 0;
    money = 0;
    hand=0;
    time_run = 0;
    p_bug1.x=-300;
    bug1_f=rand()%800;
    p_bug2.x=1800;
    bug2_f=rand()%400;
    hand=0;
    purchase=0;
    grow_speed=1;
}


void mainlist_background_reset(){
    if(pos_y<600) pos_y+=150;
    else if(pos_y>900)pos_y-=150;


    al_clear_to_color(al_map_rgb(0,200,100));
    if (pass_time == 0 ) al_draw_bitmap(pass0,0,0,0);
    if (pass_time == 1 ) al_draw_bitmap(pass1,0,0,0);
    if (pass_time >= 2 ) al_draw_bitmap(pass2,0,0,0);
    al_draw_filled_rectangle(580,550,920,650, al_map_rgb(33,105,1));
    al_draw_filled_rectangle(580,700,920,800, al_map_rgb(33,105,1));
    al_draw_filled_rectangle(580,850,920,950, al_map_rgb(33,105,1));
    al_draw_bitmap(grass,0,0,0);
    al_draw_text(font,al_map_rgb(255,255,255),663,580,0,"START");
    al_draw_text(font,al_map_rgb(255,255,255),663,730,0,"about");
    al_draw_text(font,al_map_rgb(255,255,255),693,880,0,"EXIT");
    al_draw_bitmap(title,150,100,0);
    al_draw_bitmap(check,p_check.x,p_check.y,0);
    al_draw_bitmap(WASD,600,280,0);

    al_draw_bitmap(cursor,pos_x,pos_y,0);

}


void about_display()
{
    if (about_page==1)al_draw_bitmap(about1,0,0,0);
    else if(about_page==2) al_draw_bitmap(about2,0,0,0);
    else if(about_page==3) al_draw_bitmap(about3,0,0,0);
    al_draw_bitmap(home,10,80,0);
    al_flip_display();
}

void game_map_display(){
    al_clear_to_color(al_map_rgb(181,225,223));
    al_draw_bitmap(background,0,0,0);
    al_draw_bitmap(field,350,257,0);

    for(int i=1;i<=12;i++)
    {
        if(plant_status[i]==1)
        {
            if(plant_type[i]==1)al_draw_bitmap(lit_cot,plant[i].x,plant[i].y,0);
            if(plant_type[i]==2)al_draw_bitmap(lit_rice,plant[i].x,plant[i].y,0);
            if(plant_type[i]==3)al_draw_bitmap(lit_tomato,plant[i].x,plant[i].y,0);
        }

    }
    for(int i=1;i<=12;i++)
    {
        if(plant_status[i]==2)
        {
            if(plant_type[i]==1)al_draw_bitmap(crop,plant[i].x,plant[i].y,0);
            if(plant_type[i]==2)al_draw_bitmap(rice,plant[i].x,plant[i].y,0);
            if(plant_type[i]==3)al_draw_bitmap(tomato,plant[i].x,plant[i].y,0);
        }

    }
    for(int i=1;i<=12;i++)
    {
        if(plant_status[i]==3)
        {
            if(plant_type[i]==1)al_draw_bitmap(wit_cot,plant[i].x,plant[i].y,0);
            if(plant_type[i]==2)al_draw_bitmap(wit_rice,plant[i].x,plant[i].y,0);
            if(plant_type[i]==3)al_draw_bitmap(wit_tomato,plant[i].x,plant[i].y,0);
        }

    }

    al_draw_filled_rectangle(30,540,320,600,al_map_rgb(255,210,192));
    al_draw_textf(font_30,al_map_rgb(173,41,45),170,552,ALLEGRO_ALIGN_CENTER,"money:%03d",money);
    al_draw_filled_rectangle(30,620,320,680,al_map_rgb(255,210,192));
    al_draw_textf(font_30,al_map_rgb(173,41,45),150,632,ALLEGRO_ALIGN_CENTER,"seed: %03d",crop_own);

    al_draw_bitmap(bug1,p_bug1.x,p_bug1.y,0);
    al_draw_bitmap(bug2,p_bug2.x,p_bug2.y,0);
    al_draw_filled_rectangle(200,150,1400-time_run*1200/TIMEMAX,200,al_map_rgb(220,44,49));
    al_draw_text(font,al_map_rgb(164,30,34),200,100,0,"Time Left:");
    al_draw_textf(font,al_map_rgb(173,41,45),1250,100,ALLEGRO_ALIGN_CENTER,"Target:%d $",TARGET);
    if (character ==1) al_draw_bitmap(ch1,p_ch1.x,p_ch1.y,0);
    if (character ==2) al_draw_bitmap(ch2,p_ch1.x,p_ch1.y,0);
    if (character ==3) al_draw_bitmap(ch3,p_ch1.x,p_ch1.y,0);
    al_draw_bitmap(grass,0,0,0);
    al_draw_filled_rectangle(1525,975,1600,1050,al_map_rgb(255,168,104));
    al_draw_filled_rectangle(1525,1050,1600,1125,al_map_rgb(255,168,104));
    al_draw_filled_rectangle(1525,1125,1600,1200,al_map_rgb(255,168,104));

    //time left


    al_draw_bitmap(crop_s,1525,975,0);
    al_draw_bitmap(rice_s,1525,1050,0);
    al_draw_bitmap(tomato_s,1525,1125,0);
    if(hand==0)al_draw_rectangle(1525,975,1600,1050,al_map_rgb(255,0,0),3);
    if(hand==1)al_draw_rectangle(1525,1050,1600,1125,al_map_rgb(255,0,0),3);
    if(hand==2)al_draw_rectangle(1525,1125,1600,1200,al_map_rgb(255,0,0),3);
    al_draw_textf(font_30,al_map_rgb(0,0,0),1525,1000,ALLEGRO_ALIGN_CENTER,"%d",seed[1]);
    al_draw_textf(font_30,al_map_rgb(0,0,0),1525,1075,ALLEGRO_ALIGN_CENTER,"%d",seed[2]);
    al_draw_textf(font_30,al_map_rgb(0,0,0),1525,1150,ALLEGRO_ALIGN_CENTER,"%d",seed[3]);
    al_draw_bitmap(home,10,80,0);

    if(game_status==2)
    {
        al_draw_filled_rectangle(255,265,1355,710,al_map_rgb(255,255,255));
        al_draw_bitmap(clerk,840,300,0);
        al_draw_bitmap(market,200,150,0);
        al_draw_bitmap(seed_bag1,280,575,0);
        al_draw_bitmap(seed_bag2,530,575,0);
        al_draw_bitmap(seed_bag3,790,575,0);
        al_draw_bitmap(fertilizer,1175,580,0);
        al_draw_textf(font_15,al_map_rgb(0,0,255),380,730,ALLEGRO_ALIGN_CENTER,"%d$ for 5 seed ",price[1]);
        al_draw_textf(font_15,al_map_rgb(0,0,255),650,730,ALLEGRO_ALIGN_CENTER,"%d$ for 5 seed ",price[2]);
        al_draw_textf(font_15,al_map_rgb(0,0,255),910,730,ALLEGRO_ALIGN_CENTER,"%d$ for 5 seed ",price[3]);
        al_draw_textf(font_15,al_map_rgb(0,0,255),1250,730,ALLEGRO_ALIGN_CENTER,"%d$ for update ",price[4]);
        if(purchase==0)
        {
            al_draw_rectangle(270,570,505,720,al_map_rgb(0,255,0),5);
            al_draw_bitmap(cotton_talk,350,290,0);
            al_draw_textf(font_15,al_map_rgb(0,0,255),620,410,ALLEGRO_ALIGN_CENTER,"%d$ ",price[1]/5);
            al_draw_textf(font_15,al_map_rgb(0,0,255),620,435,ALLEGRO_ALIGN_CENTER,"%d$ ",income[1]);
            al_draw_textf(font_15,al_map_rgb(0,0,255),620,460,ALLEGRO_ALIGN_CENTER,"%d$ ",income[1]-price[1]/5);
        }

        if(purchase==1)
        {
            al_draw_rectangle(525,570,760,720,al_map_rgb(0,255,0),5);
            if(character==1)al_draw_bitmap(not_for_nigga,350,290,0);
            else
            {
                al_draw_bitmap(rice_talk,350,290,0);
                al_draw_textf(font_15,al_map_rgb(0,0,255),620,410,ALLEGRO_ALIGN_CENTER,"%d$ ",price[2]/5);
                al_draw_textf(font_15,al_map_rgb(0,0,255),620,435,ALLEGRO_ALIGN_CENTER,"%d$ ",income[2]);
                al_draw_textf(font_15,al_map_rgb(0,0,255),620,460,ALLEGRO_ALIGN_CENTER,"%d$ ",income[2]-price[2]/5);
            }
        }
        if(purchase==2)
        {
            al_draw_rectangle(785,570,1020,720,al_map_rgb(0,255,0),5);
            if(character==1)al_draw_bitmap(not_for_nigga,350,290,0);
            else
            {
                al_draw_bitmap(tomato_talk,350,290,0);
                al_draw_textf(font_15,al_map_rgb(0,0,255),620,410,ALLEGRO_ALIGN_CENTER,"%d$ ",price[3]/5);
                al_draw_textf(font_15,al_map_rgb(0,0,255),620,435,ALLEGRO_ALIGN_CENTER,"%d$ ",income[3]);
                al_draw_textf(font_15,al_map_rgb(0,0,255),620,460,ALLEGRO_ALIGN_CENTER,"%d$ ",income[3]-price[3]/5);
            }
        }
        if(purchase==3)
        {
            al_draw_rectangle(1165,580,1315,720,al_map_rgb(0,255,0),5);
            al_draw_bitmap(fertilizer_update,350,290,0);
        }

    }



    al_flip_display();
}




void plant_status_change(int num){

    if(plant_status[num]<3) plant_status[num]++;
    if(plant_status[num]==3) order[num] = 0;
    time_record[num] = time_run;
    return;
}

void game_update(){

if(game_status==1){

    order_total = 0;
    for(int i=1;i<=12;i++)
    {
        order_total += order[i];
    }

    printf("%d\n",order_total);
    if(key_state[ALLEGRO_KEY_W])
    {
        if(p_ch1.y>110) p_ch1.y-=30;
        else p_ch1.y=80;
    }
    if(key_state[ALLEGRO_KEY_S])
    {
        if(p_ch1.y<970) p_ch1.y+=30;
        else p_ch1.y=1000;
    }
    if(key_state[ALLEGRO_KEY_A])
    {
        if(p_ch1.x>30) p_ch1.x-=30;
        else p_ch1.x=0;
    }
    if(key_state[ALLEGRO_KEY_D])
    {
        if(p_ch1.x<1420) p_ch1.x+=30;
        else p_ch1.x=1450;
    }


    if(time_run<TIMEMAX) time_run+=1;
    else time_run=0;
    //printf("%d ",time_run);

    for(int a=1;a<=3;a++){

        for(int i=1;i<=12;i++)
        {

            if(grow_speed==a)
            {
                if(time_run-time_record[i] == grow_time[a] && plant_status[i]!=0 && plant_status[i]!=2) plant_status_change(i);
                if(time_run-time_record[i] == grow_time_mature[a] && plant_status[i]==2) plant_status_change(i);
            }

        }
    }


    bug1_f+=8;
    bug2_f+=8;
    p_bug1.x+=8;
    p_bug1.y=150*sin(0.012*bug1_f)+bug1_f*0.6;
    if(p_bug1.x>1600||p_bug1.y>1200)
    {
        p_bug1.x=-300;
        bug1_f=rand()%100;
    }
    p_bug2.x-=8;
    p_bug2.y=230*sin(0.010*bug2_f)+bug2_f*0.84;
    if(p_bug2.x<0||p_bug2.y>1200)
    {
        p_bug2.x=1600;
        bug2_f=rand()%100;
    }
    eating();


    if(money>=TARGET)
    {
        pass_time ++;
        al_stop_sample(&game_bgm_id);
        game_status = 4;
        al_play_sample(victory_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &game_bgm_id);
    }

    if(time_run == TIMEMAX)
    {
        game_status = 5;
        al_stop_sample(&game_bgm_id);
        al_play_sample(sucked_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &game_bgm_id);
    }
    if(crop_own<=0&&order_total<=0&&money<price[1])
    {
        game_status = 5;
        al_stop_sample(&game_bgm_id);
        al_play_sample(sucked_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &game_bgm_id);
    }

}

    game_map_display();
}

int valid_bug(int a,int b){
    for(int i=1;i<=12;i++)
    {
        if (judge_bug[i][1].x<a && judge_bug[i][2].x>a &&judge_bug[i][1].y<b&&judge_bug[i][2].y>b)
            return i;
    }


    return 0;
}

void eating(){
    int a;
    a= valid_bug(p_bug1.x,p_bug1.y);
    if(a!=0)
    {
        if(plant_status[a]!=0&&plant_status[a]!=3)
        {
            order[a]=0;
            plant_status[a]=0;
            time_record[a]=0;
            al_play_sample(eating_bgm, 1.0 , 0.0 , 1.0 ,ALLEGRO_PLAYMODE_ONCE,&eating_bgm_id);
        }
    }
    a= valid_bug(p_bug2.x,p_bug2.y);
    if(a!=0)
    {
        if(plant_status[a]!=0&&plant_status[a]!=3)
        {
            order[a]=0;
            plant_status[a]=0;
            time_record[a]=0;
            al_play_sample(eating_bgm, 1.0 , 0.0 , 1.0 ,ALLEGRO_PLAYMODE_ONCE,&eating_bgm_id);
        }
    }
    return;
}

int valid(int a,int b){
    for(int i=1;i<=12;i++)
    {
        if (judge_plant[i][1].x<a && judge_plant[i][2].x>a &&judge_plant[i][1].y<b&&judge_plant[i][2].y>b)
            return i;
    }
    return 0;
}

void cropping(){

        int a=valid(p_ch1.x,p_ch1.y);
        if(a!=0)
        {
            if(plant_status[a]==0)
            {

                if(hand==0&&seed[1]>0)
                {
                    plant_status[a]=1;
                    plant_type[a]=1;
                    seed[1]--;
                    crop_own--;
                    order[a]=1;
                    al_play_sample(planting_bgm,1,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&planting_bgm_id);
                }
                if(hand==1&&seed[2]>0)
                {
                    plant_status[a]=1;
                    plant_type[a]=2;
                    seed[2]--;
                    crop_own--;
                    order[a]=1;
                    al_play_sample(planting_bgm,1,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&planting_bgm_id);
                }
                if(hand==2&&seed[3]>0)
                {
                    plant_status[a]=1;
                    plant_type[a]=3;
                    seed[3]--;
                    crop_own--;
                    order[a]=1;
                    al_play_sample(planting_bgm,1,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&planting_bgm_id);
                }
                time_record[a]=time_run;
            }
        }

}

void reaping(){
        printf("valid= %d\n ",valid(p_ch1.x,p_ch1.y));
        int a;
        a=valid(p_ch1.x,p_ch1.y);
        if( a!=0)
        {
            if(plant_status[a]!=3&&plant_status[a]!=0)order[a]=0;
            for(int i=1;i<=3;i++)
            {

                if(plant_status[a]==2&&plant_type[a]==i)
                {
                    money=money+income[i];
                    al_play_sample(coin_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &coin_bgm_id);
                }
            }
            if(plant_status[a]!=0&&plant_status[a]!=2)al_play_sample(reaping_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &reaping_bgm_id);

            plant_type[a]=0;
            plant_status[a]=0;
            time_record[a]=0;
        }

}

void killing(){

        if(p_bug1.x>p_ch1.x-120 && p_bug1.x<p_ch1.x+235 && p_bug1.y>p_ch1.y-100 && p_bug1.y<p_ch1.y+260)
        {
            p_bug1.x=-500;bug1_f=rand()%600;
            al_play_sample(killinging_bgm,1,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&killinging_bgm_id);
        }
        if(p_bug2.x>p_ch1.x-120 && p_bug2.x<p_ch1.x+235 && p_bug2.y>p_ch1.y-100 && p_bug2.y<p_ch1.y+260)
        {
            p_bug2.x=2000;bug2_f=rand()%500;
            al_play_sample(killinging_bgm,1,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&killinging_bgm_id);
        }

}


void win_update(){
    if(win_ch.x<=1150) win_ch.x+=20;
    else if(jump_count<=1000)
    {
        jump_count ++;
        if(up) win_ch.y-=15;
        if (down) win_ch.y+=10;
        if(win_ch.y<=700)
        {
            down = 1;
            up = 0;
        }
        else if(win_ch.y>= 800)
        {
            down = 0;
            up = 1;
        }
    }


}

void win_anime_display()
{
    al_draw_bitmap(background,0,0,0);
    al_draw_bitmap(win_ch_display,win_ch.x,win_ch.y,0);
    if(jump_count>=1)
    {

        if(character==1) al_draw_bitmap(best_nigga,80,450,0);
        if(character==2) al_draw_bitmap(winword3,80,450,0);
        if(character==3) al_draw_bitmap(winword4,80,450,0);

    }
    if(jump_count>=50) al_draw_bitmap(press_esc,200,600,0);
    al_draw_bitmap(rainbow,0,30,0);
    al_draw_bitmap(grass,0,0,0);
    al_flip_display();
}

void lose_anime_display(){
    rain_count++;
    jump_count++;
    al_draw_bitmap(background_lose,0,0,0);

    if (rain == 0)
    {
        al_draw_bitmap(rain1,0,0,0);
        if(rain_count==20)
        {
            rain_count=0;
            rain = 1;
        }
    }
    else if(rain == 1)
    {
        al_draw_bitmap(rain2,0,0,0);
        if(rain_count==20)
        {
            rain_count=0;
            rain = 0;
        }
    }
    al_draw_bitmap(wit_tree,900,650,0);
    al_draw_bitmap(grass,0,0,0);
    if(jump_count>=50) al_draw_bitmap(lose_word,80,500,0);
    al_flip_display();

}

int process_event() {
    al_wait_for_event(main_event_queue, &event);
    /*
        TODO: Process the mouse event.
        Seperate the processing fo click event and moving event is encouraged.
    */

    if(game_status==0){
        mainlist_background_reset();
        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(event.keyboard.keycode)
            {
                case ALLEGRO_KEY_W:
                if(pos_x==810)pos_y-=150;
                mainlist_background_reset();
                break;

                case ALLEGRO_KEY_S:
                if(pos_x==810)pos_y+=150;
                mainlist_background_reset();
                break;

                case ALLEGRO_KEY_D:
                if(pos_y==750 && pos_x==810) pos_x+=230;
                else if(pos_y==750 && pos_x<=1340 ) pos_x+=185;
                break;

                case ALLEGRO_KEY_A:
                if(pos_y==750 && pos_x==1040) pos_x-=230;
                else if(pos_y==750 && pos_x>1040) pos_x-=185;
                break;

                case ALLEGRO_KEY_ENTER:
                if(pos_y==900) return GAME_TERMINATE;
                else if(pos_y==750 && pos_x==810)
                {
                    game_status=3;
                    about_display();
                }
                else if (pos_y==750 && pos_x==1040)
                {
                    character = 1;
                    win_ch_display=al_load_bitmap("image/black_skin.png");
                    p_check.x = 1040;
                    p_check.y = 850;
                }
                else if (pos_y==750 && pos_x==1225 && pass_time>=1)
                {
                    printf("ch2\n");
                    character = 2;
                    win_ch_display=al_load_bitmap("image/ch2.png");
                    p_check.x = 1225;
                }
                else if (pos_y==750 && pos_x==1410 && pass_time>=2)
                {
                    character = 3;
                    win_ch_display=al_load_bitmap("image/ch3.png");
                    p_check.x = 1410;
                }
                else if(pos_y==600)
                {
                    game_status=1;
                    game_reset();
                    game_map_display();
                    al_start_timer(game_update_timer);
                    al_play_sample(game_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &game_bgm_id);
                    break;
                }
            }
        }


        al_flip_display();
    }

    else if(game_status==1){

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            game_update();
            game_map_display();
        }
        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            (key_state[event.keyboard.keycode]) = true;
            switch(event.keyboard.keycode)
            {
                case ALLEGRO_KEY_J:
                {
                    if(crop_own>0) cropping();
                    break;
                }
                case ALLEGRO_KEY_L:
                {
                    reaping();
                    break;
                }
                case ALLEGRO_KEY_K:
                {
                    killing();
                    break;
                }
                case ALLEGRO_KEY_P:
                {
                    game_status=2;

                    break;
                }
                case ALLEGRO_KEY_H:
                {
                    if(hand<2)hand++;
                    else if(hand==2)hand=0;
                    break;
                }

                case ALLEGRO_KEY_ESCAPE:
                {
                    game_status = 0;
                    al_stop_timer(game_update_timer);
                    al_stop_sample(&game_bgm_id);
                    break;
                }


            }
        }
        else if(event.type == ALLEGRO_EVENT_KEY_UP) (key_state[event.keyboard.keycode]) = false;

    }
    else if(game_status==2){
        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            game_update();
            game_map_display();
        }
        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            (key_state[event.keyboard.keycode]) = true;
            switch(event.keyboard.keycode)
            {
                case ALLEGRO_KEY_P:
                {
                    game_status=1;
                    al_stop_sample(&purchase_bgm_id);
                    break;
                }
                case ALLEGRO_KEY_A:
                {
                    if(purchase>0)purchase-=1;
                    break;
                }
                case ALLEGRO_KEY_D:
                {
                    if(purchase<3)purchase+=1;
                    break;
                }
                case ALLEGRO_KEY_J:
                {
                    if(purchase==0&&money>=price[1])
                    {
                        money=money-price[1];
                        seed[1]+=5;
                        crop_own+=5;
                        al_play_sample(purchase_bgm,1,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&purchase_bgm_id);
                    }
                    if(purchase==1&&money>=price[2]&&character!=1)
                    {
                        money=money-price[2];
                        seed[2]+=5;
                        crop_own+=5;
                        al_play_sample(purchase_bgm,1,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&purchase_bgm_id);
                    }
                    if(purchase==2&&money>=price[3]&&character!=1)
                    {
                        money=money-price[3];
                        seed[3]+=5;
                        crop_own+=5;
                        al_play_sample(purchase_bgm,1,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&purchase_bgm_id);
                    }
                    if(purchase==3&&money>=price[4]&&grow_speed<=2)
                    {
                        money=money-price[4];
                        if(grow_speed<=2)grow_speed++;
                        al_play_sample(purchase_bgm,1,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&purchase_bgm_id);
                    }
                    break;
                }

            }
        }
        else if(event.type == ALLEGRO_EVENT_KEY_UP)
        {
            (key_state[event.keyboard.keycode]) = false;
        }

    }

     else if(game_status==3)
    {
        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(event.keyboard.keycode)
            {
                 case ALLEGRO_KEY_ESCAPE:
                 game_status = 0;
                 break;

                 case ALLEGRO_KEY_D:
                 if(about_page == 2) about_page = 3;
                 else if(about_page == 1) about_page = 2;
                 break;

                 case ALLEGRO_KEY_A:
                 if(about_page == 2) about_page = 1;
                 else if(about_page == 3) about_page = 2;
                 break;
            }

        }
        about_display();
    }


    else if(game_status==4)
    {
        if(event.type == ALLEGRO_EVENT_KEY_UP)(key_state[event.keyboard.keycode]) = false;
        if (event.type == ALLEGRO_EVENT_TIMER)
        {

            win_update();
            win_anime_display();
        }

        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(event.keyboard.keycode)
            {
                 case ALLEGRO_KEY_ESCAPE:
                 game_status = 0;
                 al_stop_timer(game_update_timer);
                 al_stop_sample(&game_bgm_id);
                 break;
            }
        }

        win_anime_display();

    }

    else if(game_status == 5)
    {
        if(event.type == ALLEGRO_EVENT_KEY_UP)(key_state[event.keyboard.keycode]) = false;
        if (event.type == ALLEGRO_EVENT_TIMER) lose_anime_display();

        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(event.keyboard.keycode)
            {
                 case ALLEGRO_KEY_ESCAPE:
                 game_status = 0;
                 al_stop_timer(game_update_timer);
                 al_stop_sample(&game_bgm_id);
                 break;
            }
        }

        lose_anime_display();
    }

    return 0;
}


int game_run(){
    int error = 0;
    if (!al_is_event_queue_empty(main_event_queue)) {
        error = process_event();
    }
    return error;
}

void game_destroy() {
    al_destroy_event_queue(main_event_queue);
    al_destroy_display(display);
    al_destroy_bitmap(cursor);
    al_destroy_bitmap(ch1);
    al_destroy_bitmap(field);
    al_destroy_bitmap(lit_cot);
    al_destroy_bitmap(grass);
    al_destroy_bitmap(bug1);
    al_destroy_bitmap(bug2);
    al_destroy_bitmap(crop);
    al_destroy_bitmap(wit_cot);
    al_destroy_bitmap(win_ch_display);
    al_destroy_bitmap(best_nigga);
    al_destroy_bitmap(press_esc);
    al_destroy_bitmap(rainbow);
    al_destroy_bitmap(market);
    al_destroy_bitmap(rain1);
    al_destroy_bitmap(rain2);
    al_destroy_bitmap(wit_tree);
    al_destroy_bitmap(lose_word);
    al_destroy_bitmap(background);
    al_destroy_bitmap(background_lose);
    al_destroy_bitmap(title);
    al_destroy_bitmap(pass0);
    al_destroy_bitmap(pass1);
    al_destroy_bitmap(pass2);
    al_destroy_bitmap(check);
    al_destroy_bitmap(about1);
    al_destroy_bitmap(ch2);
    al_destroy_bitmap(ch3);
    al_destroy_bitmap(lit_rice);
    al_destroy_bitmap(rice);
    al_destroy_bitmap(wit_rice);
    al_destroy_bitmap(lit_tomato);
    al_destroy_bitmap(tomato);
    al_destroy_bitmap(wit_tomato);
    al_destroy_bitmap(crop_s);
    al_destroy_bitmap(rice_s);
    al_destroy_bitmap(tomato_s);
    al_destroy_bitmap(WASD);
    al_destroy_bitmap(seed_bag1);
    al_destroy_bitmap(seed_bag2);
    al_destroy_bitmap(seed_bag3);
    al_destroy_bitmap(clerk);
    al_destroy_bitmap(fertilizer);
    al_destroy_bitmap(about2);
    al_destroy_bitmap(about3);
    al_destroy_bitmap(home);
    al_destroy_bitmap(cotton_talk);
    al_destroy_bitmap(rice_talk);
    al_destroy_bitmap(tomato_talk);
    al_destroy_bitmap(not_for_nigga);
    al_destroy_bitmap(fertilizer_update);
    al_destroy_sample(game_bgm);
    al_destroy_sample(coin_bgm);
    al_destroy_sample(reaping_bgm);
    al_destroy_sample(eating_bgm);
    al_destroy_sample(killinging_bgm);
    al_destroy_sample(planting_bgm);
    al_destroy_sample(purchase_bgm);
    al_destroy_timer(win_anime_timer);
    al_destroy_timer(game_update_timer);

}





