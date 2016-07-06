// меню индикации/ввода
typedef enum {
	M_OCLOCK,     				// часы
	M_SET_MODE,					// установка режима меню
	M_SET_HOUR,					// установка часов
	M_SET_MINUTE,				// установка минут	
	M_CHOOSE_LESSN_OR_BREAK,		// выбор перемена или урок 
	M_CHOOSE_LESSN_OR_BREAK_NUM,	// выбор номера перемены или урока
	M_SET_LESSN_OR_BREAK,		// выбор номера перемены или урока
	M_SET_LESSNS_COUNT,			// установка количнства уроков
	M_SET_BEEP, 				// установка длительности звонка
	M_SET_START_SCHOOL_HOUR, 	// установка времени начала занятий
	M_SET_START_SCHOOL_MINUTE,	// установка времени начала занятий
	M_RESET, 					// сброс всех установок
	M_SHOW_STATE,				// показать состояние будильника
	M_SHOW_ELEPSED,				// показать сколько прошло минут после звонка
	M_SHOW_REMAINS,				// показать сколько осталось минут до звонка	
	M_COUNT
} Menu;

// режимы меню 
typedef enum  {
	MM_NORMAL,	// стандартный режим - показывать на индикаторе только часы
	MM_SETUP,	// режим настройки - установка значений 
	MM_DEBUG,	// режим отладки - показывать состояние будильника, 
                //                 сколько прошло секунд после звонка
                //                 сколько осталось секунд до звонка
	MM_COUNT
} Mode;

//пункты меню стандартного режима
int m_normal[] = { M_OCLOCK, M_SET_MODE, M_SET_HOUR, M_SET_MINUTE  };

//пункты меню режима настройки 
int m_setup[] = { M_OCLOCK, M_SET_MODE, 
	M_CHOOSE_LESSN_OR_BREAK,
	M_CHOOSE_LESSN_OR_BREAK_NUM,
	M_SET_LESSN_OR_BREAK,
	M_SET_LESSNS_COUNT,
	M_SET_BEEP,
	M_SET_START_SCHOOL_HOUR,
	M_SET_START_SCHOOL_MINUTE,
	M_RESET  };
//пункты меню режим отладки
int m_debug [] = {
	M_OCLOCK, M_SET_MODE,
	M_SHOW_STATE,
	M_SHOW_ELEPSED,
	M_SHOW_REMAINS
};
//запомнить количество пунктов меню для каждого из режимов
int m_len[MM_COUNT] = {
	sizeof(m_normal)/sizeof(int),
	sizeof(m_setup)/sizeof(int),
	sizeof(m_debug)/sizeof(int)
	};

// состояние ввода меню
Menu menu = M_OCLOCK;				// текущее меню
Mode mode = MM_NORMAL;				// текущий режим меню
int m_lessn_or_break = 1;			// что выбрано в меню - перемена или урок
int m_lessn_or_break_number = 1;	// номер выбраной в меню перемены или урока

// перейти к следующему меню в зависимости от режима меню
void set_next_menu(){
	int *mm = mode == MM_NORMAL ? m_normal : ( mode==MM_SETUP ? m_setup : m_debug );
	int len = m_len[mode];
	int n = 0;
	for(; n < len; ++n){
		if(mm[n] == menu)
			break;
	}
	if(++n>=len){
		n = 0;
	}  
    #pragma warn-
	menu = mm[n];      
    #pragma warn+

}