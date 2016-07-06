#define KEY_LEFT 1
#define KEY_RIGHT 2
#define KEY_SELECT 3

// Key flags initialisation and defenition
bit k_press=0;
bit k_prs  =0;
bit k_cnt  =0;
bit k_rep  =0;

bit k_ready =0;

unsigned char key_code=0, key_cnt=3;

// Keys at PINA.0...PINA.3 
#define key_port PORTA.IN     
#define key_mask 0x2e      
#define key_nopressed 0x2e      




unsigned char get_keypins()
{
 return (key_port & key_mask);
}         


/*unsigned char get_keypins()
{
 
 
 unsigned char key_half; 
  
 PORTC.7=1;
 PORTC.6=0;
 delay_us(1);
 key_half = ((key_port & key_mask)<<4)&0xf0;
 
 PORTC.6=1; 
 PORTC.7=0;  
 delay_us(1);
 
 key_half|=(key_port & key_mask);
 PORTC.6=1; 
 PORTC.7=1;  
     
 do  {I2C_bad=0;
      Key_tmp=(Recive_I2C_Data(0x7e)&(PIND|0x0f));}
 while (I2C_bad);
      if (!PIND.1) {Key_tmp=Key_tmp&0xf7;}
 return (Key_tmp);    //key_half
}   */                            

void scan_key()
{
// --- Scan keys ---
k_cnt=1; if (key_cnt) { key_cnt--; k_cnt=0; }            
if ( get_keypins() == key_nopressed )
   {//Key not press or relised               
    k_press=0; k_prs=0; k_cnt=0; key_cnt=5; k_rep=0; k_ready=1; key_code=key_nopressed; return;
   }
if (!k_press) { k_press=1; return; } //Key pressed at first pass
if (!k_prs)   { k_prs=1;   return; } //Key still pressed at second pass
if (k_cnt) //Key still pressed
   {//Autorepeat flag set
    k_cnt=0; key_code=get_keypins(); k_ready=1;
    if (k_rep==0) {key_cnt=150; k_rep=1;} else {key_cnt=30;}
   }
}
  


unsigned char get_key()
{
//return key_code;          
switch (key_code)
 {
  case 0x2c: return KEY_LEFT; 	// if K_<<        pressed      0001 1100
  case 0x2a: return KEY_RIGHT; 	// if K_>>        pressed      0001 1010
  case 0x26: return 3; 			// if K_B         pressed      0001 0110
  case 0x0e: return 4; 			// if K_Прокалка  pressed      0000 1110
  case 0x06: return 5; 			// if K_B & K_Прокалка pressed 0000 0110
  
   default  : return 0; // if K_RDY-flag not set
 }                    
}
