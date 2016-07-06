
unsigned char ind[4];		// значение четырёх выводимых на индикацию символов
unsigned char ind_cnt=1; 	// номер знакоместа, выводимого в прерывании TCC0 Overflow
unsigned char numberCode [10]= 
	//    HGFEDCBA 
	{	0b00111111,
		0b00000110, 
		0b01011011, 
		0b01001111, 
		0b01100110, 
		0b01101101, 
		0b01111101, 
		0b00000111, 
		0b01111111, 
		0b01101111 };
	
unsigned char ind_encodeNumber(unsigned char number) {
    
	return (number < 10)  ? numberCode[number] : numberCode[0];
}   


void ind_indicateNumber(int DEC)
{
int DECtmp;
if (DEC<10000) {
   DECtmp=DEC;
   if (DECtmp>=1000) {ind[0]=ind_encodeNumber(DECtmp/1000);DECtmp=DECtmp-(int)(DECtmp/1000)*1000;
                      ind[1]=ind_encodeNumber(DECtmp/100);DECtmp=DECtmp-(int)(DECtmp/100)*100;
                      ind[2]=ind_encodeNumber(DECtmp/10);DECtmp=DECtmp-(int)(DECtmp/10)*10;
                      ind[3]=ind_encodeNumber(DECtmp);
                     }   
   else {
          if (DECtmp>=100) {ind[0]=0;
                            ind[1]=ind_encodeNumber(DECtmp/100);DECtmp=DECtmp-(int)(DECtmp/100)*100;
                            ind[2]=ind_encodeNumber(DECtmp/10);DECtmp=DECtmp-(int)(DECtmp/10)*10;
                            ind[3]=ind_encodeNumber(DECtmp);
                           } 
          
          else {                   
                if (DECtmp>=10) {ind[0]=0;
                                 ind[1]=0;
                                 ind[2]=ind_encodeNumber(DECtmp/10);DECtmp=DECtmp-(int)(DECtmp/10)*10;
                                 ind[3]=ind_encodeNumber(DECtmp);
                                } 
                
                else { ind[0]=0;
                       ind[1]=0;
                       ind[2]=0;
                       ind[3]=ind_encodeNumber(DECtmp);
                     
                     }                
          }
   }
}
}
