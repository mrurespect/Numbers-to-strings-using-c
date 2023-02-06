#include<stdio.h>
#include <locale.h>
#include <malloc.h>
#include <string.h>
#include<math.h>
  unsigned int  nbc ;
  char *ptr ; // pointeur utilisee dans strtol
char * SaisirChaineClavier()
{
     unsigned int c;
     nbc = 0 ;
     char * ch = NULL ;
     int i=0 ;
     while((c = getchar()) != '\n')
				    {
				        ch = realloc(ch, (nbc+1)*sizeof(char));
				        ch[nbc++] = c ;
				    }
     ch = realloc(ch, (nbc+1)*sizeof(char));
     ch[nbc] = '\0' ;
     return ch ;
}

char * SaisirLigneFichier(FILE * pf)
{
    unsigned int c ;
    nbc = 0 ;
    char * ch = NULL ;
    while(((c = fgetc(pf)) != '\n') && (c != EOF))
	    {
	        ch = realloc(ch, (nbc+1)*sizeof(char));
	        ch[nbc++] = c ;
	    }
    if((nbc > 0) || (c == '\n'))
	    {
	        ch = realloc(ch, (nbc+1)*sizeof(char));
	        ch[nbc] = '\0' ;
	        return ch ;
	    }

    return NULL ;
}

char ** CreerVecteurNombres(char *nf , unsigned int * taille)
{
    FILE * pf = fopen(nf, "r") ;
    char * str = NULL ;
    unsigned int i = 0 ;
    char ** VN = NULL ;
    if(pf == NULL)
	    {
	        printf("\n probleme lors de l ouverture du fichier %s\n", nf) ;
	        fclose(pf) ;
	        *taille = 0 ;
	        return NULL ;
	    }

    while((str = SaisirLigneFichier(pf)) != NULL)
	    {
	        VN = realloc(VN, (i+1)*sizeof(char*)) ;
	        VN[i++] = str ;
	    }
    fclose(pf) ;
    *taille = i ;
    return VN ;
}

void int_to_char(int chiffre,char ** TC){

    if(chiffre<=99 ){
					printf(" %s ", TC[chiffre]) ;
				    }
    else
    if(chiffre <= 999){
	    	  if((chiffre/100)==1){
			 			printf(" cent %s ",TC[chiffre% 100] ) ; //pour eviter un  cent
				 				  }
	    	  else {
		      			printf(" %s cent %s ",TC[chiffre/100],TC[chiffre% 100] ) ;
					}
		  			  }
	else
	if(chiffre <= 999999){ //les milles
	   		if(chiffre<=99999){ if((chiffre/1000)==1)printf(" mille" ) ;// eviter un mille
						   		else
						      	printf(" %s mille ", TC[chiffre/1000]) ;
			  				  }
	    	 else{ if((chiffre/100000)==1)printf(" cent %s mille ", TC[(chiffre/1000)%100])  ; // Cent cinquante mille
	    	        else      printf(" %s cent %s mille ", TC[chiffre/100000],TC[(chiffre/1000)%100]) ;
					}
		      chiffre=chiffre%1000;  //1k
		      int_to_char(chiffre,TC);
			  			  }
	else
	if(chiffre <= 999999999){ //les millions 999M
			if(chiffre <= 99999999){  if(chiffre/1000000 ==1 )printf(" un million ") ;// 1 million sans " s "
									  else printf(" %s millions ",TC[chiffre/1000000]) ;
			                       }
		    else { if(chiffre/100000000 ==1 )printf(" cent %s millions ",TC[(chiffre/1000000)%100]) ;//eviter un-cent--million
			        else printf(" %s cent %s millions ",TC[chiffre/100000000],TC[(chiffre/1000000)%100]) ;
			     }
		    chiffre=chiffre%1000000;// divise par 1M pour obtenir les milliers
		    int_to_char(chiffre,TC);
			  			    }
	}

void milliard(char * chi,char ** TC ){
    int y= strlen(chi);
    int chiffre =0 ;
	if(strlen(chi)==10){
							int chiffre10=chi[0]-48 ;
							if(chiffre10==1)printf("un milliard ");
							else printf("%s milliards",TC[chiffre10]);
							int j=pow(10,y-1),i,k=10;
							for(i=1;i<=y;i++){
								chiffre =chiffre+(*(chi+i)-48)*(j/k);
								j=j/10 ;
											 }
							int_to_char(chiffre,TC);
	                   }
	else
	if(strlen(chi)==11){
							int s   =chi[0]-48 ;
							int s1  =chi[1]-48 ;
							int chiffre11= s*10+s1 ;
							printf(" %s milliards",TC[chiffre11]);
							int j=pow(10,y-2),i,k=100;// pour y-1 on depasse la limite
							for(i=2;i<=y;i++){
								chiffre =chiffre+(*(chi+i)-48)*(j/k);
								j=j/10 ;
											 }
							chiffre= chiffre*10 + (*(chi+10)-48);//dernier chiffre
							int_to_char(chiffre,TC);
	                   }
	else
	if(strlen(chi)==12){	int chiffre12=chi[0]-48 ;
							int chiffre1= (chi[1]-48)*10+(chi[2]-48) ;
							if(chiffre12==1)printf(" cent %s milliards",TC[chiffre1]);
							else printf(" %s cent %s milliards",TC[chiffre12],TC[chiffre1]);
							int j=pow(10,y-3),i,k=1000;
							for(i=3;i<=y;i++){
								chiffre =chiffre+(*(chi+i)-48)*(j/k);
								j=j/10 ;
											 }
							chiffre= chiffre*10 + (*(chi+10)-48); //  avant dernier chiffre
							chiffre= chiffre*10 + (*(chi+11)-48) ; // dernier chiffre
							int_to_char(chiffre,TC);
	                   }
	               }
        void partie_decimal(char*chi,char *partie_droite,int pos,char **TC){
            int i,j=0 ;
            for(i=pos+1;i<strlen(chi);i++){
                if(chi[i]=='0'){ j++;}
                else break ;
            }
            printf(" virgule ");
            if(j!=0)for(i=0;i<j;i++)printf(" zero ");
                int virg=strlen(chi)-pos-1;
                if(virg-j>9){
                            milliard(partie_droite,TC);
                            }
                else {
                        int chiffre0 = strtol(partie_droite, &ptr, 10);
                        int_to_char(chiffre0,TC);
                     }
                                     }

        void partie_entiere(char*chi,char *partie_gauche,int pos,char **TC){
            if(pos > 9){
            milliard(partie_gauche,TC);
                       }
            else {
                int chiffre1 = strtol(chi, &ptr, 10);
                int_to_char(chiffre1,TC);
                }
                                        }
void menu(){
    printf("\n Saisir un nombre entre 0 et 999999999999,999999999999 : ") ;
    char *chi = SaisirChaineClavier();
    int chiffre = strtol(chi, &ptr, 10); // on transforme la chaine de caractere en entier ainsi que la partie entier en ces d un reel "123,67":123
    char ** TC = CreerVecteurNombres("CL_FR0.txt" , &nbc) ;
    setlocale(LC_CTYPE,"") ;
    if(chiffre==0)printf(" zero ");TC[0]="" ;
    //entier
    int i,j,exi=0 ;
    for(i=0;i<strlen(chi);i++){ // exi c est l index de la virgule dans la chaine
        if(chi[i]==','){exi++; break ;}
    }
    int pos_virg = i ; // position de la virgule et la taille de la partie entiere
    int deci_size = strlen (chi) - pos_virg - 1 ;// size de la partie decimal
    char partie_droite [deci_size] ;// partie droite a la virgule cad la partie decimal
    int k ;
    char partie_gauche[pos_virg] ;// partie gauche  a la virgule cad la partie entiere
    for(j=0;j<pos_virg;j++){	*(partie_gauche+j) = *(chi + j); }
    partie_gauche[pos_virg]='\0';
    // decimal
    for(j= pos_virg + 1, k=0; j < strlen(chi); j++,k++){//on compie la partie decimal daans une nouvelle chaine
        *(partie_droite+k)=*(chi+j);
    }
    partie_droite[strlen(chi)]='\0';
    // l appelle
    partie_entiere(chi, partie_gauche, pos_virg, TC);
    if(exi!=0) //cad la virgule n existe pas
        partie_decimal(chi, partie_droite, pos_virg, TC);
}

int main()
{
    menu();
}
