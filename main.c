#include <io.h>			// I/O Registers definitions
#include "init.c"		// инициализация проца
#include "ind.c"		// индикация
#include "keyb.c"		// клавиатура
#include "menu.c"		// пункты и режимы меню

// счётчик задержки сканирования ввода клавиатуры в прерывании TCC0 Overflow
#define IND_T0_KEY_INIT 500
int ind_t0_key = IND_T0_KEY_INIT;	

#define FLICK_T0_KEY_INIT 0x0FFFFL
long int flick_t0_key = FLICK_T0_KEY_INIT;
unsigned char flick_t0_flag = 0;	

// часы
int scnd_oclck = 0;
int mint_oclck = 0;
int hour_oclck = 0;

// EEPROM
eeprom unsigned char eeprom_init;
eeprom int eeprom_lessn[50]; 			// продолжительность урока в минутах 
eeprom int eeprom_break[50]; 			// продолжительность перемены в минутах   
eeprom int eeprom_start_school_hour;     	// время отрытия школы, час
eeprom int eeprom_start_school_minute;		// время отрытия школы, минута
eeprom int eeprom_lessns_count;     		// количество уроков
eeprom int eeprom_beep;     			// длительность звонка
// локальные копии значений EEPROM, инициализируются в init_values_from_eeprom
int beep_ = 6; 						// длительность ипульса звонка в секундах
int lessn[50];  					// продолжительность урока в минутах 
int break_[50];      				// продолжительность перемены в минутах   
int start_school_hour = 8;  		// время отрытия школы, час
int start_school_minute = 30;		// время отрытия школы, минута
int lessns_count = 5;				// количество уроков

// сброс всех значений EEPROM
void reset_eeprom(){
	int n;
	eeprom_init = 0x55;    
	for(n=0; n<50; ++n){
		eeprom_lessn[n] = 45;
		eeprom_break[n] = 15;
	}
	eeprom_lessns_count = 5;
	eeprom_start_school_hour = 8;
	eeprom_start_school_minute = 30;
	eeprom_beep = 6;
}
// инициализировать копии значений EEPROM текущими значениями EEPROM
void init_values_from_eeprom(){
	int n;
	for(n=0; n<50; ++n){
		lessn[n] = eeprom_lessn[n];
		break_[n] = eeprom_break[n];
	}
    start_school_hour = eeprom_start_school_hour;  
	start_school_minute = eeprom_start_school_minute;
	lessns_count = eeprom_lessns_count;
	beep_ = eeprom_beep;
}
// увеличить/уменьшить на 1 (взависимости от значения increase)
// значение переменной EEPROM по адресу eeprom_target
// и значение её локальной копии по адресу value
void change_eeprom_value(eeprom int *eeprom_target, int *value, 
	int min, int max, unsigned char increase){
	*value += (increase ? 1 : -1);
	if (*value > max ){
		*value = max;
	} else if (*value < min ){
		*value = min;
	}
	*eeprom_target = *value;
}
// увеличить/уменьшить на 1 (взависимости от значения increase)
// значение переменной по адресу value
void change_local_value( int *value, int min, int max, unsigned char increase){
	*value += (increase ? 1 : -1);
	if (*value > max ){
		*value = min;
	} else if (*value < min ){
		*value = max;
	}
}
// вывести на на индикаторы ind_n, ind_n+1 значение DEC
void ind_indicateNumber2(int DEC, int ind_n){
	int DECtmp;
	DECtmp=DEC;
	if (DECtmp>=10) {
		ind[ind_n]=ind_encodeNumber(DECtmp/10);
		DECtmp=DECtmp-(int)(DECtmp/10)*10;
        ind[ind_n + 1]=ind_encodeNumber(DECtmp);
	} else {
		ind[ind_n]=ind_encodeNumber(0);
        ind[ind_n+1]=ind_encodeNumber(DECtmp);
	}
}

// вывести мерцающее значение value на индикаторы pos, pos+1 
void flick_value2(int value, int pos){
	if(flick_t0_flag ) { 
		ind_indicateNumber2(value, pos);
	} else {
		ind[pos] = 0;
		ind[pos+1] = 0;
	}
}

void flick_choosen_lessn_or_break_value(){
	int *p = m_lessn_or_break ? lessn : break_;
	int n = p[m_lessn_or_break_number-1];
	flick_value2(n, 2);	
}

void increase_lessn_or_break_value(unsigned char increase){
	int n = m_lessn_or_break_number-1;
	eeprom int *p = m_lessn_or_break ? eeprom_lessn : eeprom_break;
	int *p1 = m_lessn_or_break ? lessn : break_; 
	change_eeprom_value( p + n, p1 + n, 1, 99, increase);
}

// изменить выбранное в меню занчение
void change_chosen_value(unsigned char increase){
	int n;
	switch (menu) {
		case M_OCLOCK: {
			break;
		}
		case M_SET_MODE : {
			n = mode;
			change_local_value(&n, 0, MM_COUNT-1, increase); 
            #pragma warn-
			mode = n;
            #pragma warn+
			break;
		}
		case M_SET_HOUR:{
			change_local_value(&hour_oclck, 0, 23, increase);
			break;
		}
		
		case M_SET_MINUTE:{
			change_local_value(&mint_oclck, 0, 59, increase);
			break;			
		}
		case M_CHOOSE_LESSN_OR_BREAK: {
			m_lessn_or_break = !m_lessn_or_break;
			break;
		}			
		case M_CHOOSE_LESSN_OR_BREAK_NUM: {
			change_local_value(&m_lessn_or_break_number, 1, 50, increase);
			break;
		}
		case M_SET_LESSN_OR_BREAK: {
			increase_lessn_or_break_value(increase);
			break;
		}
		case M_SET_LESSNS_COUNT: {
			change_eeprom_value(&eeprom_lessns_count, &lessns_count, 1, 50, increase);
			break;
		}
		case M_SET_BEEP:{
			change_eeprom_value(&eeprom_beep, &beep_, 1, 99, increase);
			break;
		}
		case M_SET_START_SCHOOL_HOUR : {
			change_eeprom_value(&eeprom_start_school_hour, &start_school_hour, 0, 23, increase);
			break;
		}
		case M_SET_START_SCHOOL_MINUTE : {
			change_eeprom_value(&eeprom_start_school_minute, &start_school_minute, 0, 59, increase);
			break;
		}
		case M_RESET : {
			if(increase) { 
				reset_eeprom();
				init_values_from_eeprom();
				menu = M_OCLOCK;
			}
			break;
		}
		
	};
}

// вывести на индикаторы 0,1 символ `У` если в мню выбран урок, иначе `П`
void indicate_lessn_or_break(){
	ind[0] = m_lessn_or_break ?
			// 			HGFEDCBA
					  0b01101110 :
					  0b00110111 ;
	ind[1] = 0;
}

typedef enum  {
	INF_ST_NONE,	// в настоящее время нет уроков
	INF_ST_LESSN,	// идёт урок
	INF_ST_BREAK 	// идёт перемена
} WhatState;

// время начала первого урока в секундах
long get_start_school_time_sec() {
	long int start_school_hour_l, start_school_minute_l;
	start_school_hour_l = start_school_hour;
	start_school_minute_l = start_school_minute;	
	return 3600L * start_school_hour_l + 60L * start_school_minute_l;
}

// текущее время в секундах
long get_current_time_sec() {
	long int hour_oclck_l, mint_oclck_l, scnd_oclck_l;
	hour_oclck_l = hour_oclck;
	mint_oclck_l = mint_oclck;
	scnd_oclck_l = scnd_oclck;	
	return 3600L * hour_oclck_l + 60L * mint_oclck_l + scnd_oclck_l;
}

// тип, описывающий состояние будильника
struct State { 
	WhatState what; 			// код состояния - INF_ST_NONE, INF_ST_LESSN, INF_ST_BREAK
	int n;						// номер текущего урока/перемны
	long int elepsed; 			// сколько минут прошло после звонка
	long int remains;			//  сколько минут осталось до звонка
	} ;

// текущее состояние будильника
void get_school_state(struct State *ret){ 
	long int 
		d,
		n,	// индекс итерации по секундам 
		now; // запомнить текущее время в секундах

	n = get_start_school_time_sec();
	now = get_current_time_sec();

	if (now < n) { // если ткущее время меньше времени начала первого урока 
		ret->what =  INF_ST_NONE; 	// сейчас нет уроков
		ret->remains = n - now;		// осталось секунд до начала первого урока
		ret->elepsed = 0L;			
		return;
	}

	for (ret->n=0; ret->n < lessns_count; ++ret->n) {
		d = lessn[ret->n] * 60L;
		if(now >= n && now < n + d) {
			ret->what =  INF_ST_LESSN;
			ret->elepsed = now - n;
			ret->remains = n + d - now;
			return;			
		} else {
			n += d;
			d = break_[ret->n] * 60L;
			if(now >= n && now < n + d){ 
				ret->what =  INF_ST_BREAK;
				ret->elepsed = now - n;
				ret->remains = n + d - now;
				return;
			} else {
				n += d;
			}
		}
	}
	ret->what =  INF_ST_NONE;
	ret->elepsed = now - n;
	ret->remains = 0L;
}

//надо ли звонить звонок
unsigned char is_beep(struct State *x){
	long int beep_l;
	beep_l = beep_;
	return (x->what == INF_ST_LESSN || x->what == INF_ST_BREAK) &&  x->elepsed < beep_l ;
}

//  включить/выключить звонок в зависимости от состояня будильника
void process_beep(struct State *school_state){
	unsigned char porta;
	porta = PORTA.OUT;
	PORTA.OUT = is_beep(school_state)  ? (porta | 0b10000000) : (porta & 0b01111111);	
}

// вывести на индикацию соответственно выбранному меню и режиму
void indicate_menu_value(struct State *school_state){

	if(is_beep(school_state)){
		ind[0] = flick_t0_flag ? //HGFEDCBA
				 			  0b00000001 :
							  0b10001000 ;
		ind[1] = ind[2] = ind[3] = ind[0];
		return;
	}
	switch (menu) {
		case M_OCLOCK: {
			ind_indicateNumber2(hour_oclck, 0);
			ind_indicateNumber2(mint_oclck, 2);
			if(scnd_oclck % 2) {
				// 			HGFEDCBA 					
				ind[1] |= 0b10000000 ;
			}
			break;
		}

		case M_SET_MODE:{
			ind[0] = ind[1] = 0;
			if(flick_t0_flag ) { 
				ind[2] = //HGFEDCBA
					 	 0b01110011 ;;
				ind[3] = ind_encodeNumber(mode);
			} else {
				ind[2] = ind[3] = 0;
			}
			break;
		}

		case M_SET_HOUR:{
			flick_value2(hour_oclck, 0);
			ind_indicateNumber2(mint_oclck, 2);
			break;
		}
		
		case M_SET_MINUTE:{		
			ind_indicateNumber2(hour_oclck, 0);
			flick_value2(mint_oclck, 2);
			break;			
		}
		case M_CHOOSE_LESSN_OR_BREAK: {
			if(flick_t0_flag ) { 
				// вывести на индикаторы 0,1 символ `У` если в мню выбран урок, иначе `П`
				indicate_lessn_or_break();
			} else {
				ind[0] = 0;
				ind[1] = 0;				
			}
			
			ind_indicateNumber2(m_lessn_or_break_number,2);
			break;
		}			
		case M_CHOOSE_LESSN_OR_BREAK_NUM: {
			// вывести на индикаторы 0,1 символ `У` если в мню выбран урок, иначе `П`
			indicate_lessn_or_break();
			flick_value2(m_lessn_or_break_number,2);
			break;
		}
		case M_SET_LESSN_OR_BREAK : {
			ind[0] = // HGFEDCBA
					  0b01000000;
			ind[1] =  0b01000000;
			flick_choosen_lessn_or_break_value();
			break;
		}

		case M_SET_LESSNS_COUNT: {
			ind[0] = //HGFEDCBA
					  0b01101110;
			ind[1] = ind[0];
			flick_value2(lessns_count,2);
			break;
		}
		case M_SET_BEEP:{
			ind[0] = //HGFEDCBA
					 0b01100011 ;
			ind[1] = 0;
			flick_value2(beep_,2);
			break;
		}
		case M_SET_START_SCHOOL_HOUR : {
			flick_value2(start_school_hour, 0);
			ind_indicateNumber2(start_school_minute, 2);
			break;
		}

		case M_SET_START_SCHOOL_MINUTE : {
			ind_indicateNumber2(start_school_hour, 0);
			flick_value2(start_school_minute, 2);
			break;
		}

		case M_SHOW_STATE : {
			ind_indicateNumber2(school_state->what, 0);
			ind_indicateNumber2(school_state->n,2);
			break;
		}

		case M_SHOW_ELEPSED : {
			ind_indicateNumber(school_state->elepsed);
			break;
		}

		case M_SHOW_REMAINS : {
			ind_indicateNumber(school_state->remains);
			break;
		}

		case M_RESET : {
			if(flick_t0_flag ) { 
				ind[0] = //HGFEDCBA
						 0b01000000;				
			} else {
				ind[0] = 0;
			}
			ind[1] = ind[2] = ind[3] = ind[0];
			break;
		}

	};
}

// Timer/Counter TCC0 Overflow/Underflow interrupt service routine
interrupt [TCC0_OVF_vect] void tcc0_overflow_isr(void)
{
	// обнулить порт E для пердовращения мерцания 
	PORTE.OUT=0x00;
	// установка порта индикации
	switch (ind_cnt) {
		case 1: { 
			PORTD.OUT=ind[0];
			PORTE.OUT=0x01;   
			ind_cnt++; 
			break;}
		case 2:{
			PORTD.OUT=ind[1];
			PORTE.OUT=0x02;   
			ind_cnt++; 
			break;}
		case 3:{
			PORTD.OUT=ind[2];
			PORTE.OUT=0x04;   
			ind_cnt++; break;}
		case 4:{
			PORTD.OUT=ind[3];
			PORTE.OUT=0x08;   
			ind_cnt=1; break;} 
    
		default: ind_cnt=1;
    };
	
	// инкремент счётчика индикации
	if (!--ind_t0_key) {
		ind_t0_key = IND_T0_KEY_INIT;
		scan_key();
	}
	
	// инкремент счётчика мерцания
	if (!--flick_t0_key) {
		flick_t0_key = FLICK_T0_KEY_INIT;
		flick_t0_flag = !flick_t0_flag; // инвертировать флаш  мерцания
	}
}

// RTC overflow interrupt service routine
interrupt [RTC_OVF_vect] void rtcxm_overflow_isr(void)
{
	// увеличить текущее время на 1 секунду
	if(++scnd_oclck == 60){
		scnd_oclck = 0;
		if(++mint_oclck == 60){
			mint_oclck = 0;
			if(++hour_oclck==24){
				hour_oclck = 0;
			}
		}
	}
	
}





void main(void) {
	unsigned char key;
	struct State school_state;

	m_lessn_or_break = 1;			// что выбрано в меню - перемена или урок
	m_lessn_or_break_number = 1;	// номер выбраной в меню перемены или урока
	menu = M_OCLOCK;				// текущее меню
	mode = MM_NORMAL;				// текущий режим меню
	
	init_main();    
	if (eeprom_init != 0x55) {
        reset_eeprom();
    } 
    init_values_from_eeprom();
    while (1){
		// обработка ввода
		if (k_ready) {			// если установлен флаг наличия ввода
			key=get_key();		// какая клавиша была нажата
			if(key==KEY_SELECT ) {	// если "переход меню"
				set_next_menu();	// перейти к следующему меню в зависимости от режима меню
			} else if (key == KEY_RIGHT || key == KEY_LEFT){ // если клавиша <- или ->
				change_chosen_value(key == KEY_RIGHT); // изменить выбранное в меню занчение
			}
			k_ready=0;
		}
		// получить состояние будильника
		get_school_state(&school_state);
		// включить/выключить звонок в зависимости от состояня будильника 		
		process_beep(&school_state);
		// вывести на индикацию соответственно выбранному меню и режиму  
		indicate_menu_value(&school_state);	
    }
}
