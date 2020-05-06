#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<cmath>

#define POPULATION 1589
#define XRANGE 50000
#define YRANGE 50000

using namespace std;

class human{
 private:
  double home_x,home_y;
  double now_locate_x,now_locate_y;
  double time_after_infection=0.0;
  bool covid_flag=false;
  bool die_flag=false;
  bool recover_flag=false;
  bool stop_flag;
  double theta;
 public:
  human();
  double get_now_x(){return now_locate_x;}
  double get_now_y(){return now_locate_y;}
  bool get_covid_flag(){return covid_flag;}
  bool get_die_flag(){return die_flag;}
  bool get_recover_flag(){return recover_flag;}
  double get_day(){return time_after_infection;}
  void Move(){
    double x,y;
    if(stop_flag!=true&&die_flag!=true){
      x=now_locate_x+100*cos(theta);
      y=now_locate_y+100*sin(theta);
      if(x>XRANGE || y>YRANGE || x<0 || y<0){
	theta+=M_PI/2.;
      }
      else{
	now_locate_x+=100*cos(theta);
	now_locate_y+=100*sin(theta); 
      }
    }
  }
  void go_home(){
    //実装途中
    now_locate_x+=(home_x-now_locate_x);
    
  }
  void Infection(){ 
    const double infection_probability=100;   
    if(rand()%100<infection_probability) covid_flag=true;
  }
  void Die(){
    const double die_probability=20;
    covid_flag=false;
    if(rand()%100<die_probability) die_flag=true;
  }
  void Recovery(){
    covid_flag=false;
    recover_flag=true;
    time_after_infection=0.0;
  }
  void Infection_time_count(){
    time_after_infection+=1;
  }
};

human::human()
{
  double x=XRANGE,y=YRANGE;
  home_x=x*rand()/RAND_MAX;
  home_y=y*rand()/RAND_MAX;
  now_locate_x=home_x;
  now_locate_y=home_y;
 
  theta=(rand()%360/180.-1)*2*M_PI;
  if(rand()%100<80) stop_flag=true;
  else stop_flag=false;
  if(rand()%100<1) covid_flag=true;
  else covid_flag=false;
}

class people{
 private:
  human tokyo_human[POPULATION];
  int touch_flag[POPULATION];
 public:
  people();
  void simulate_life_day(int day);
  void touch_check();
  void file_output(int step);
};

people::people(){
  for(int i=0;i<POPULATION;i++){
    touch_flag[i]=0;
  }
}

void people::simulate_life_day(int day){
  double day_time=day*24*60/15.;
  int infection=0,die=0,recover=0,helth=0;
  ofstream ofs("rate.dat");
  for(int step=0;step<day_time;step++){
    for(int i=0;i<POPULATION;i++){
      tokyo_human[i].Move();
      if(tokyo_human[i].get_covid_flag()) tokyo_human[i].Infection_time_count();
      if(tokyo_human[i].get_day()>50+rand()%25&&(tokyo_human[i].get_die_flag()!=true||tokyo_human[i].get_recover_flag()!=true)){
	if(rand()%100<10) tokyo_human[i].Die();
	else tokyo_human[i].Recovery();
      }
    }
    
    infection=0;
    die=0;
    recover=0;
    helth=0;
    for(int i=0;i<POPULATION;i++){
      if(tokyo_human[i].get_covid_flag()) infection++;
      else if(tokyo_human[i].get_die_flag()) die++;
      else if(tokyo_human[i].get_recover_flag()) recover++;
      else helth++;
    }
    ofs<<step<<" "<<infection<<" "<<infection+helth<<" "<<infection+helth+recover<<" "<<infection+helth+recover+die<<endl;
    file_output(step);
    touch_check();
  }
}

void people::touch_check(){
  double distanse;
  for(int i=0;i<POPULATION;i++){
    if(tokyo_human[i].get_recover_flag()==false && tokyo_human[i].get_die_flag()==false){
      for(int j=0;j<POPULATION;j++){
	distanse=sqrt(pow(tokyo_human[i].get_now_x()-tokyo_human[j].get_now_x(),2)+pow(tokyo_human[i].get_now_y()-tokyo_human[j].get_now_y(),2));
	if(i!=j&&distanse<1000&&tokyo_human[j].get_covid_flag())touch_flag[i]++;
      }
      if(touch_flag[i]>0) tokyo_human[i].Infection();
    }
  }
}

void people::file_output(int step){
  ofstream ofs0("./output/Not_infection"+to_string(step)+".dat");
  ofstream ofs1("./output/Infection"+to_string(step)+".dat");
  ofstream ofs2("./output/Recovery"+to_string(step)+".dat");

  for(int i=0;i<POPULATION;i++){
    if(tokyo_human[i].get_covid_flag()==false){
      if(tokyo_human[i].get_recover_flag()==false)
	ofs0<<tokyo_human[i].get_now_x()<<" "<<tokyo_human[i].get_now_y()<<endl;
      else
	ofs2<<tokyo_human[i].get_now_x()<<" "<<tokyo_human[i].get_now_y()<<endl;
    }
    else
      ofs1<<tokyo_human[i].get_now_x()<<" "<<tokyo_human[i].get_now_y()<<endl;
  }
}

int main(int argc,char *argv[])
{
  int day=atoi(argv[1]);
  srand((unsigned int)time(NULL));
  people tokyo;
  tokyo.simulate_life_day(day);
}
