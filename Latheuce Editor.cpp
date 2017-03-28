#include <iostream>
#include <fstream>
#include <locale.h>
#include <cmath>
#include <string.h>
#include <string>
#include <ctime>
#include <cstdlib>


#define MAXALTURA 2000
#define MAXLARGURA 2000
#define COR 3
#define MAXALTURA2 3
#define MAXLARGURA2 3
#define MAXCOR 3

using namespace std;



int main(){
	static unsigned char imagem_cinza[MAXALTURA][MAXLARGURA], imagem_colorida[MAXALTURA][MAXLARGURA][COR], auxiliar_cinza1[MAXALTURA][MAXLARGURA], auxiliar_cinza2[MAXALTURA][MAXLARGURA], auxiliar_cinza3[MAXALTURA][MAXLARGURA];//Vetores utilizados para fazer opera��es e filtros.
	static unsigned char auxiliar_colorida1[MAXALTURA][MAXLARGURA][MAXCOR], auxiliar_colorida2[MAXALTURA][MAXLARGURA][MAXCOR], auxiliar_colorida3[MAXALTURA][MAXLARGURA][MAXCOR];//Vetores para fazer filtros.
	static char gy[MAXALTURA2][MAXLARGURA2] = {{1, 2, 1}, {0, 0, 0},{-1, -2, -1}}, gx[MAXALTURA2][MAXLARGURA2] = {{1, 0, -1},{2, 0, -2},{1, 0, -1}}, gr[MAXALTURA2][MAXLARGURA2] = {{0, -1, 0}, {-1, 5, -1},{0, -1, 0}};//Filtros.
	static char glp[MAXALTURA2][MAXLARGURA2] = {{0, -1, 0}, {-1, 4, -1},{0, -1, 0}}, gdg[MAXALTURA2][MAXLARGURA2] = {{1, 2, 1}, {2, 4, 2},{1, 2, 1}};//Filtros.
	static char comentario[200], c;//Coment�rio.
	int largura, altura, n, z, guardar, cor = 3;//Dimens�es do vetor..
	static char nome_arquivo[50],arq_saida[50];//Nome do arquivo de entrada e sa�da.
	static char tipoimg[50];//Tipo da imagem.
	ifstream arquivoin;//Arquivo de entraa.
	ofstream arquivoout;//Arquivo de saida.
	int fatorescuro, fatorclaro, gostaria1, gostaria2, valor;//Fatores e selecionadores.	
	
	setlocale(LC_ALL, "Portuguese");//Usar acentos BR.
   	cout << "===========================================================" << endl;  //Entrada maneira.
   	cout << "Bem-Vindo ao Latheuce, o melhor editor de imagens do mundo." << endl;
   cout << "===========================================================" << endl;
   cout << "******Desenvolvido por Lawrence Silva e Matheus Reis******" << endl;
   cout << endl;
	cout << "Digite o nome da imagem.pnm (Utilize o .pnm): ";//Entrar o nome da imagem de entrada.
	
	
	cin >> nome_arquivo;
	cout << endl;
	
	arquivoin.open(nome_arquivo,ios::in);
	
	arquivoin >> tipoimg; //Recebe o tipo da imagem.
	arquivoin.get();    

   	if (strcmp(tipoimg,"P2")==0) {				//L� o tipo da imagem.
      cout << "Imagem em tons de cinza\n";
    }
    
    else if (strcmp(tipoimg,"P3")==0) {
      cout << "Imagem colorida\n";
    }
    
    else if (strcmp(tipoimg,"P5")==0 || strcmp(tipoimg,"P6")==0) {
      cout << "Imagem no formato RAW\n";
      cout << "Desculpe, mas nao trabalho com esse tipo de imagem.\n";
      arquivoin.close();
      return 0;
    }

    while((c = arquivoin.get()) == '#')   //Tira o coment�rio.
       arquivoin.getline(comentario,200); 

    arquivoin.putback(c);  
                            
	if(strcmp(tipoimg,"P2")==0){  //Lendo a imagem se for cinza.
    	arquivoin >> largura >> altura;  
    	cout << "Tamanho: " << largura << " x " << altura << endl;
    	
    	arquivoin >> valor;    
    	
    	for(int i=0;i<altura;i++)
      		for(int j=0;j<largura;j++) {
        		arquivoin >> valor;
        		imagem_cinza[i][j] = (unsigned char)valor;
      }
   		arquivoin.close();   
}

	else if (strcmp(tipoimg,"P3")==0){	//lendo a imagem se for colorida.
			arquivoin >> largura >> altura;  
    	cout << "Tamanho: " << largura << " x " << altura << endl;
    	
    	arquivoin >> valor;  
    	
    	for(int i=0;i<altura;i++){
      		for(int j=0;j<largura;j++) {
        		for(int k = 0; k < cor; k++){
        			arquivoin >> valor;
        			imagem_colorida[i][j][k] = (unsigned char)valor;
			}
		}
	}
		arquivoin.close();
}
   
    if(strcmp(tipoimg,"P2")==0){    //IN�CIO DAS CINZAS (Explica��es de como funcionam no Relat�rio)
    	cout << "Gostaria de:   1.Opera��es   2.Filtros   (Digite apenas 1 ou 2)" << endl; //Escolhendo o que quer fazer.
    	cin >> gostaria1;
    	
    	z = largura - 1;
    	
    	if(gostaria1 == 1){//In�cio das opera��es.
    	cout << endl;
    	cout << "Gostaria de: 1.Clareamento   2.Escurecimento   3.Negativo   4.Espelhar (Digite apenas 1, 2, 3 ou 4)" << endl;//Escolhendo a opera��o.
    	cin >> gostaria2;
    	
    	if(gostaria2 == 1){//Clareamento .
    		cout << "Voc� escolheu o clareamento." << endl;
    		cout << endl;
    		cout << "Qual o fator de clareamento? (Digite um n�mero)" << endl;
    		cin >> fatorclaro;
    		for(int i = 0; i < altura; i++){//Soma nos pixels.
    			for(int j = 0; j < largura; j++){
    				valor = (int)imagem_cinza[i][j];
    				valor += fatorclaro;
    				if(valor > 255)
    					valor = 255;
    				imagem_cinza[i][j] = (unsigned char)valor;	
				}
			}
		}
    		
		else if(gostaria2 == 2){//Escurecimento.
			cout << "Voc� escolheu o escurecimento." << endl;
			cout << endl;
			cout << "Qual o fator de escurecimento? (Digite um n�mero)" << endl;
			cin >> fatorescuro;
    	for(int i = 0; i < altura; i++){//Subtrae nos pixels.
    		for(int j = 0; j < largura; j++){
    			valor = (int)imagem_cinza[i][j];
    			valor -= fatorescuro;
    			if(valor < 0)
    				valor = 0;
    			imagem_cinza[i][j] = (unsigned char)valor;	
			}
		}   		
    }
    
    	else if(gostaria2 == 3){//Negativo.
    		cout << "Voc� escolheu o negativo." << endl;
    		for(int i = 0; i < altura; i++){
    			for(int j = 0; j < largura; j++){//Faz o m�dulo da subtra��o.
    				valor = (int)imagem_cinza[i][j];
    				valor = abs(valor - 255);
    				imagem_cinza[i][j] = (unsigned char)valor;
				}
			}
		}
		
		else if(gostaria2 == 4){//Espelhar.
    		cout << "Voc� escolheu espelhar." << endl;
    		for(int i = 0; i < largura; i++){
    			for(int j = 0; j < altura; j++){//Inverte as colunas.		
    				guardar = (int)imagem_cinza[j][i];
    				valor = (int)imagem_cinza[j][z];
    				imagem_cinza[j][i] = (unsigned char)valor;
    				imagem_cinza[j][z] = (unsigned char)guardar;
				}
				z--;
				if(i >= z)	
					break;
			}
		}		
	}//Fim das opera��es.
		
		else if(gostaria1 == 2){//In�cio dos Filtros (Explica��es de como funcionam no Relat�rio)
		cout << "Gostaria de: 1.Filtro de Sobel   2.Filtro de Real�ar   3.Filtro de Laplace   4.Filtro Gaussiano   (Digite apenas 1, 2, 3 ou 4)" << endl;//Escolhendo o Filtro.
		cin >> gostaria2;
		
			if(gostaria2 == 1){ //Sobel.
			cout << "Voc� escolheu o Filtro de Sobel." << endl;
			cout << endl;
			valor = 0;
			
			for(int i = 0, c1 = 0, c2 = 0; i < altura; i++){//Aplica o filtro gy.
				for(int j = 0; j < largura; j++){
					for(int k = 0, x1 = 1; k < 3; k++, x1--){
						for(int l = 0, x2 = 1; l < 3; l++, x2--){
							if(i - x1 < 0 || j - x2 < 0 || i - x1 >= altura || j - x2 >= largura){
								valor += 0;
							}
							else{	
								c1 = (int)gy[k][l];
								c2 = (int)imagem_cinza[i - x1][j - x2];
								valor += c1 * c2;
							}
						}
					}
				if(valor < 0){
						auxiliar_cinza1[i][j] = 0;
					}
					else if(valor > 255){
						auxiliar_cinza1[i][j] = 255;
					}
					else{
						auxiliar_cinza1[i][j] = (unsigned char)valor;
					}
					valor = 0;
				}
			}
			
			valor = 0;	
				
			for(int i = 0, c1 = 0, c2 = 0; i < altura; i++){//Aplica o FIltro gx.
				for(int j = 0; j < largura; j++){
					for(int k = 0, x1 = 1; k < 3; k++, x1--){
						for(int l = 0, x2 = 1; l < 3; l++, x2--){
							if(i - x1 < 0 || j - x2 < 0 || i - x1 >= altura || j - x2 >= largura){
								valor += 0;
							}
							else{	
								c1 = (int)gx[k][l];
								c2 = (int)imagem_cinza[i - x1][j - x2];
								valor += c1 * c2;
							}
						}
					}
				if(valor < 0){
						auxiliar_cinza2[i][j] = 0;
					}
					else if(valor > 255){
						auxiliar_cinza2[i][j] = 255;
					}
					else{
						auxiliar_cinza2[i][j] = (unsigned char)valor;
					}
					valor = 0;
				}
			}
			
			valor = 0;
			int y1, y2, y3;
    	
    		for(int i = 0; i < altura; i++){//Faz a m�dia dos dois em um terceiro.
    			for(int j = 0; j < largura; j++){
    				y1 = (int)auxiliar_cinza1[i][j];
    				y2 = (int)auxiliar_cinza2[i][j];
    				y3 = ((y1 + y2) / 2);
    				auxiliar_cinza3[i][j] = (unsigned char) y3;
				}
			}
    	
    		cout << "Digite o nome da imagem gerada (Utilize o .pnm)" << endl;//Saida da imagem.
			cin >> arq_saida;
			cout << endl;
		
			arquivoout.open(arq_saida,ios::out);

    		arquivoout << tipoimg << endl;                            
    		arquivoout << "# INF110\n";  
    		arquivoout << largura << " " << altura << endl;       
    		arquivoout << 255 << endl;                            
    		for(int i=0;i<altura;i++)
      			for(int j=0;j<largura;j++)
        			arquivoout << (int)auxiliar_cinza3[i][j] << endl;           

    		arquivoout.close();    
    	
    		cout << "Imagem gerada com sucesso!" << endl;
			
			return 0;
    } 
    
	
		else if(gostaria2 == 2){ //Real�ar
			cout << "Voc� escolheu o Filtro de Real�ar." << endl;
			cout << endl;
			valor = 0;
			
			for(int i = 0, c1 = 0, c2 = 0; i < altura; i++){//Aplica o filtro gr.
				for(int j = 0; j < largura; j++){
					for(int k = 0, x1 = 1; k < 3; k++, x1--){
						for(int l = 0, x2 = 1; l < 3; l++, x2--){
							if(i - x1 < 0 || j - x2 < 0 || i - x1 >= altura || j - x2 >= largura){
								valor += 0;
							}
							else{	
								c1 = (int)gr[k][l];
								c2 = (int)imagem_cinza[i - x1][j - x2];
								valor += c1 * c2;
							}
						}
					}
				if(valor < 0){
						auxiliar_cinza1[i][j] = 0;
					}
					else if(valor > 255){
						auxiliar_cinza1[i][j] = 255;
					}
					else{
						auxiliar_cinza1[i][j] = (unsigned char)valor;
					}
					valor = 0;
				}
			}
			
    	
    		cout << "Digite o nome da imagem gerada (Utilize o .pnm)" << endl;//Saida da imagem.
			cin >> arq_saida;
			cout << endl;
		
			arquivoout.open(arq_saida,ios::out);

    		arquivoout << tipoimg << endl;                            
    		arquivoout << "# INF110\n";  
    		arquivoout << largura << " " << altura << endl;       
    		arquivoout << 255 << endl;                            
    		for(int i=0;i<altura;i++)
      			for(int j=0;j<largura;j++)
        			arquivoout << (int)auxiliar_cinza1[i][j] << endl;           

    		arquivoout.close();    
    	
    		cout << "Imagem gerada com sucesso!" << endl;
			
			return 0;
    } 
	
	
	
		else if(gostaria2 == 3){ //Laplace
			cout << "Voc� escolheu o Filtro Laplace." << endl;
			cout << endl;
			valor = 0;
			
			for(int i = 0, c1 = 0, c2 = 0; i < altura; i++){//Aplica  filtro glp.
				for(int j = 0; j < largura; j++){
					for(int k = 0, x1 = 1; k < 3; k++, x1--){
						for(int l = 0, x2 = 1; l < 3; l++, x2--){
							if(i - x1 < 0 || j - x2 < 0 || i - x1 >= altura || j - x2 >= largura){
								valor += 0;
							}
							else{	
								c1 = (int)glp[k][l];
								c2 = (int)imagem_cinza[i - x1][j - x2];
								valor += c1 * c2;
							}
						}
					}
				if(valor < 0){
						auxiliar_cinza1[i][j] = 0;
					}
					else if(valor > 255){
						auxiliar_cinza1[i][j] = 255;
					}
					else{
						auxiliar_cinza1[i][j] = (unsigned char)valor;
					}
					valor = 0;
				}
			}
			
    	
    		cout << "Digite o nome da imagem gerada (Utilize o .pnm)" << endl;//Saida da imagem.
			cin >> arq_saida;
			cout << endl;
		
			arquivoout.open(arq_saida,ios::out);

    		arquivoout << tipoimg << endl;                            
    		arquivoout << "# INF110\n";  
    		arquivoout << largura << " " << altura << endl;       
    		arquivoout << 255 << endl;                            
    		for(int i=0;i<altura;i++)
      			for(int j=0;j<largura;j++)
        			arquivoout << (int)auxiliar_cinza1[i][j] << endl;           

    		arquivoout.close();    
    	
    		cout << "Imagem gerada com sucesso!" << endl;
			
			return 0;
    } 
	
	
	else if(gostaria2 == 4){ //Gaussiano
			cout << "Voc� escolheu o Filtro Gaussiano." << endl;
			cout << endl;
			valor = 0;
			
			for(int i = 0, c1 = 0, c2 = 0; i < altura; i++){//Aplica o filtro gdg
				for(int j = 0; j < largura; j++){
					for(int k = 0, x1 = 1; k < 3; k++, x1--){
						for(int l = 0, x2 = 1; l < 3; l++, x2--){
							if(i - x1 < 0 || j - x2 < 0 || i - x1 >= altura || j - x2 >= largura){
								valor += 0;
							}
							else{	
								c1 = (int)gdg[k][l];
								c2 = (int)imagem_cinza[i - x1][j - x2];
								valor += c1 * c2;
							}
						}
					}
					valor /= 16;
				    if(valor < 0){
						auxiliar_cinza1[i][j] = 0;
					}
					else if(valor > 255){
						auxiliar_cinza1[i][j] = 255;
					}
					else{
						auxiliar_cinza1[i][j] = (unsigned char)valor;
					}
					valor = 0;
				}
			}
			
			
    	
    		cout << "Digite o nome da imagem gerada (Utilize o .pnm)" << endl;//Saida da imagem.
			cin >> arq_saida;
			cout << endl;
		
			arquivoout.open(arq_saida,ios::out);

    		arquivoout << tipoimg << endl;                            
    		arquivoout << "# INF110\n";  
    		arquivoout << largura << " " << altura << endl;       
    		arquivoout << 255 << endl;                            
    		for(int i=0;i<altura;i++)
      			for(int j=0;j<largura;j++)
        			arquivoout << (double)auxiliar_cinza1[i][j] << endl;           

    		arquivoout.close();    
    	
    		cout << "Imagem gerada com sucesso!" << endl;
			
			return 0;
    } 
}//Fim dos filtros.
	
	
		cout << "Digite o nome da imagem gerada (Utilize o .pnm)" << endl;//Saida da imagem.
		cin >> arq_saida;
		cout << endl;
		
		arquivoout.open(arq_saida,ios::out);

    	arquivoout << tipoimg << endl;                            
    	arquivoout << "# INF110\n";  
    	arquivoout << largura << " " << altura << endl;       
    	arquivoout << 255 << endl;                            
    	for(int i=0;i<altura;i++)
      		for(int j=0;j<largura;j++)
        		arquivoout << (int)imagem_cinza[i][j] << endl;           

    	arquivoout.close();    
    	
    	cout << "Imagem gerada com sucesso!" << endl;
	} //FIM DAS CINZAS
	
	
	if (strcmp(tipoimg,"P3")==0){ //IN�CIO DAS COLORIDAS
		cout << "Gostaria de:   1.Opera��es   2.Filtros   (Digite apenas 1 ou 2)" << endl;//Escolher opera��o ou filtro. 
    	cin >> gostaria1;
		
		z = largura - 1;
	
		if(gostaria1 == 1){//Opera��es (Explicados no relat�rio)
		cout << "Gostaria de: 1.Clareamento   2.Escurecimento   3.Negativo   4.Espelhar   5.Preto e Branco   6.Patriota (Digite apenas 1, 2, 3, 4, 5 ou 6)" << endl;//Escolher a opera��o.
		cin >> gostaria2;
			
		if(gostaria2 == 1){//Clareamento
    		cout << "Voc� escolheu o clareamento." << endl;
    		cout << endl;
    		cout << "Qual o fator de clareamento? (Digite um n�mero)" << endl;
    		cin >> fatorclaro;
    		for(int i = 0; i < altura; i++){//Soma nos pixels,
    			for(int j = 0; j < largura; j++){
    				for(int k = 0; k < cor; k++){
    					valor = (int)imagem_colorida[i][j][k];
    					valor += fatorclaro;
    					if(valor > 255)
    					valor = 255;
    					imagem_colorida[i][j][k] = (unsigned char)valor;	
    				}
				}
			}
		}
	
		else if(gostaria2 == 2){//Escurecimento.
			cout << "Voc� escolheu o escurecimento." << endl;
			cout << endl;
			cout << "Qual o fator de escurecimento? (Digite um n�mero)" << endl;
			cin >> fatorescuro;
    	for(int i = 0; i < altura; i++){//Subtrai nos pixels.
    		for(int j = 0; j < largura; j++){
    			for(int k = 0; k < cor; k++){
    				valor = (int)imagem_colorida[i][j][k];
    				valor -= fatorescuro;
    				if(valor < 0)
    					valor = 0;
    				imagem_colorida[i][j][k] = (unsigned char)valor;	
    			}
			}
		}   		
    }
    	
    	else if(gostaria2 == 3){//Negativo
    		cout << "Voc� escolheu o negativo." << endl;
    		for(int i = 0; i < altura; i++){
    			for(int j = 0; j < largura; j++){//Faz o m�dulo da subtra��o nos pixels.
    				for(int k = 0; k < cor; k++){
    					valor = (int)imagem_colorida[i][j][k];
    					valor = abs(valor - 255);
    					imagem_colorida[i][j][k] = (unsigned char)valor;
    				}
				}
			}
		}	
		
		else if(gostaria2 == 4){//Espelhar.
    		cout << "Voc� escolheu espelhar." << endl;
    		for(int i = 0; i < largura; i++){//Inverte as colunas.
    			for(int j = 0; j < altura; j++){
					for(int k = 0; k < cor; k++){	
    					guardar = (int)imagem_colorida[j][i][k];
    					valor = (int)imagem_colorida[j][z][k];
    					imagem_colorida[j][i][k] = (unsigned char)valor;
    					imagem_colorida[j][z][k] = (unsigned char)guardar;
    				}
				}
				z--;
				if(i >= z)	
					break;
			}
		}
		
		else if(gostaria2 == 5){//Preto e Branco
			string muda = "P2";//Muda o tipo de imagem para P2
			cout << "Voc� escolheu deixar em preto e branco." << endl;
			for(int i = 0; i < altura; i++){//Passa o vetor de tr�s dimens�es para um de dois.
    			for(int j = 0; j < largura; j++){
    				valor = ((int)imagem_colorida[i][j][0] + (int)imagem_colorida[i][j][1] + (int)imagem_colorida[i][j][2]) / 3;
    				if(valor < 0)
    					valor = 0;
    				else if(valor > 255)
						valor = 255;	
    				imagem_cinza[i][j] = (unsigned char)valor;
				}
			}
    	cout << "Digite o nome da imagem gerada (Utilize o .pnm)" << endl;//Sa�da da imagem.
		cin >> arq_saida;
		cout << endl;
		
		arquivoout.open(arq_saida,ios::out);

    	arquivoout << muda << endl;                            
    	arquivoout << "# INF110\n";  
    	arquivoout << largura << " " << altura << endl;       
    	arquivoout << 255 << endl;                            
    	for(int i=0;i<altura;i++)
      		for(int j=0;j<largura;j++)
        		arquivoout << (int)imagem_cinza[i][j] << endl;           

    	arquivoout.close();    
    	
    	cout << "Imagem gerada com sucesso!" << endl;
    	
    	return 0;
	} 	
	
		else if(gostaria2 == 6){//PATRIOTA **VIVA O BRASIL**
			cout << "Voc� decidiu mostrar o seu amor � P�tria Amada!" << endl;//(VER RELAT�RIO PARA FUNCIONAMENTO)
			int fator = 3;
     		
     
   			fator*=15;
     
    		for ( int i = 0, k=0;i <= altura/2; i++,k++)
        		for (int j = 0; j < ((largura/2)-(1.5*k)); j++) {
 
            		if( (int)imagem_colorida[i][j][1]+fator < 255)
                		imagem_colorida[i][j][1] +=fator;
       		}
         
    		for ( int i = 0, k=0;i < altura/2; i++,k++)
       		 for (int j = largura; j >= ((largura/2)+(1.5*k)); j--) {
 
           		 if( (int)imagem_colorida[i][j][1]+fator < 255)
                		imagem_colorida[i][j][1] +=fator;
       		 }
         
    		for ( int i = altura, k=0;i > altura/2; i--,k++)
       		 for (int j = 0; j < (largura/2)-(1.5*k); j++) {
 
           		 if( (int)imagem_colorida[i][j][1]+fator < 255)
              		  imagem_colorida[i][j][1] += fator;
        		}
         
   		 for ( int i = altura, k=0;i >= altura/2; i--,k++)
       		 for (int j = largura; j > ((largura/2)+(1.5*k)); j--) {
 
            		if( (int)imagem_colorida[i][j][1]+fator < 255)
               		 imagem_colorida[i][j][1] +=fator;
       		 }
     
    		for ( int i = 0, k=0;i <= altura/2; i++,k++)
       		 	for (int j = largura/2; j >= ((largura/2)-(k*1.5)); j--) {
 
           		 if((int)imagem_colorida[i][j][0]+fator < 255)
              		imagem_colorida[i][j][0] += fator;
                 
            	if( (int)imagem_colorida[i][j][1]+fator < 255)
                	imagem_colorida[i][j][1] +=fator;
        }
         
    		for ( int i = altura, k=0;i > altura/2; i--,k++)
       			for (int j = largura/2; j >= ((largura/2)-(k*1.5)); j--) {
           		 if( (int)imagem_colorida[i][j][0]+fator < 255)
              		  imagem_colorida[i][j][0] +=fator;

           		 if( (int)imagem_colorida[i][j][1]+fator < 255)
               		 imagem_colorida[i][j][1] +=fator;
        }
     
    		for ( int i = altura, k=0;i >= altura/2; i--,k++)
       			for (int j = 1+(largura/2); j < (largura/2)+(k*1.5); j++) {
           			if( (int)imagem_colorida[i][j][0]+fator < 255)
                		imagem_colorida[i][j][0] +=fator;
                 
            		if((int)imagem_colorida[i][j][1]+fator < 255)
                		imagem_colorida[i][j][1] +=fator;
        }
     
   		 for ( int i = 0, k=0;i < altura/2; i++,k++)
        		for (int j = 1+(largura/2); j < (largura/2)+(k*1.5); j++) {
            		if( (int)imagem_colorida[i][j][0]+fator < 255)
               			imagem_colorida[i][j][0] +=fator;
                 
           			 if( (int)imagem_colorida[i][j][1]+fator < 255)
                		imagem_colorida[i][j][1]+=fator;
        }
     
   		 int distancia,imedio=altura/2,jmedio=largura/2,raio = altura/3;;
     
    		for ( int i = 0;i < largura; i++)
        		for (int j = 0; j < largura; j++) {
            		distancia=(int) sqrt(pow(abs(imedio-i),2)+pow(abs(jmedio-j),2));
             
           		 if ( distancia <= raio && (int)imagem_colorida[i][j][2]+fator < 255)
               		 imagem_colorida[i][j][2] += fator;           
    		}
			
	}
}

	else if(gostaria1 == 2){//Filtros
		cout << "Gostaria de: 1.Filtro de Sobel   2.Filtro de Real�ar   3.Filtro de Laplace   4.Filtro Gaussiano   (Digite apenas 1, 2, 3 ou 4)" << endl;//Escolhendo o filtro.
		cin >> gostaria2;
		
		 if(gostaria2 == 1){ //Sobel.
			cout << "Voc� escolheu o Filtro de Sobel." << endl;
			cout << endl;
			valor = 0;
			
			for(int i = 0, c1 = 0, c2 = 0, c3 = 0; i < altura; i++){//Aplica o filtro gy
				for(int j = 0; j < largura; j++){
					for(int k = 0; k < 3; k++){
						for(int l = 0, x1 = 1; l < 3; l++, x1--){
							for(int m = 0, x2 = 1; m < 3; m++, x2--){
								if(i - x1 < 0 || j - x2 < 0 || i - x1 >= altura || j - x2 >= largura){
									c3 += 0;
								}
								else{
									c1 = (int)gy[l][m];
									c2 = (int)imagem_colorida[i - x1][j - x2][k];
									c3 += c1 * c2;
								}
							}
						}
						if(c3 < 0){
							auxiliar_colorida1[i][j][k] = 0;
						}
						else if(c3 > 255){
							auxiliar_colorida1[i][j][k] = 255;
						}
						else{
							auxiliar_colorida1[i][j][k] = (unsigned char)c3;
						}
						c3 = 0;	
					}
				}
			}
			
				for(int i = 0, c1 = 0, c2 = 0, c3 = 0; i < altura; i++){//Aplica o filtro gx
				for(int j = 0; j < largura; j++){
					for(int k = 0; k < 3; k++){
						for(int l = 0, x1 = 1; l < 3; l++, x1--){
							for(int m = 0, x2 = 1; m < 3; m++, x2--){
								if(i - x1 < 0 || j - x2 < 0 || i - x1 >= altura || j - x2 >= largura){
									c3 += 0;
								}
								else{
									c1 = (int)gx[l][m];
									c2 = (int)imagem_colorida[i - x1][j - x2][k];
									c3 += c1 * c2;
								}
							}
						}
						if(c3 < 0){
							auxiliar_colorida2[i][j][k] = 0;
						}
						else if(c3 > 255){
							auxiliar_colorida2[i][j][k] = 255;
						}
						else{
							auxiliar_colorida2[i][j][k] = (unsigned char)c3;
						}
						c3 = 0;	
					}
				}
			}
			
			int y1, y2, y3;
			
			for(int i = 0; i < altura; i++){//Faz a m�dia em um terceiro.
				for(int j = 0; j < largura; j++){
					for(int k = 0; k < 3; k++){
						y1 = (int)auxiliar_colorida1[i][j][k];
						y2 = (int)auxiliar_colorida2[i][j][k];
						y3 = (y1 + y2)/2;
						auxiliar_colorida3[i][j][k] = (unsigned char)y3; 
					}
				}
			}
			
    	
    	cout << "Digite o nome da imagem gerada (Utilize o .pnm)" << endl;//Sa�da da imagem.
		cin >> arq_saida;
		cout << endl;
		
		arquivoout.open(arq_saida,ios::out);

    	arquivoout << tipoimg << endl;                            
    	arquivoout << "# INF110\n";  
    	arquivoout << largura << " " << altura << endl;       
    	arquivoout << 255 << endl;                            
    	for(int i=0;i<altura;i++)
      		for(int j=0;j<largura;j++) 
        		for(int k = 0; k < cor; k++)
        			arquivoout << (int)auxiliar_colorida3[i][j][k] << endl;
			
		arquivoout.close();	
		
		cout << "Imagem gerada com sucesso!" << endl;	
			
			return 0;
    } 
    
    else if(gostaria2 == 2){//Real�ar.
    	cout << "Voc� escolheu o Filtro de Real�ar." << endl;
    	
    		for(int i = 0, c1 = 0, c2 = 0, c3 = 0; i < altura; i++){//Aplica o filtro gr.
				for(int j = 0; j < largura; j++){
					for(int k = 0; k < 3; k++){
						for(int l = 0, x1 = 1; l < 3; l++, x1--){
							for(int m = 0, x2 = 1; m < 3; m++, x2--){
								if(i - x1 < 0 || j - x2 < 0 || i - x1 >= altura || j - x2 >= largura){
									c3 += 0;
								}
								else{
									c1 = (int)gr[l][m];
									c2 = (int)imagem_colorida[i - x1][j - x2][k];
									c3 += c1 * c2;
								}
							}
						}
						if(c3 < 0){
							auxiliar_colorida1[i][j][k] = 0;
						}
						else if(c3 > 255){
							auxiliar_colorida1[i][j][k] = 255;
						}
						else{
							auxiliar_colorida1[i][j][k] = (unsigned char)c3;
						}
						c3 = 0;	
					}
				}
			}
			
		cout << "Digite o nome da imagem gerada (Utilize o .pnm)" << endl;//Sa�da de imagem	
		cin >> arq_saida;
		cout << endl;
		
		arquivoout.open(arq_saida,ios::out);

    	arquivoout << tipoimg << endl;                            
    	arquivoout << "# INF110\n";  
    	arquivoout << largura << " " << altura << endl;       
    	arquivoout << 255 << endl;                            
    	for(int i=0;i<altura;i++)
      		for(int j=0;j<largura;j++) 
        		for(int k = 0; k < cor; k++)
        			arquivoout << (int)auxiliar_colorida1[i][j][k] << endl;
			
		arquivoout.close();	
		
		cout << "Imagem gerada com sucesso!" << endl;	
			
			return 0;		
	}
    
    else if(gostaria2 == 3){//Laplace
    	cout << "Voc� escolheu o Filtro de Laplace." << endl;
    	
    		for(int i = 0, c1 = 0, c2 = 0, c3 = 0; i < altura; i++){//Aplica o filtro glp
				for(int j = 0; j < largura; j++){
					for(int k = 0; k < 3; k++){
						for(int l = 0, x1 = 1; l < 3; l++, x1--){
							for(int m = 0, x2 = 1; m < 3; m++, x2--){
								if(i - x1 < 0 || j - x2 < 0 || i - x1 >= altura || j - x2 >= largura){
									c3 += 0;
								}
								else{
									c1 = (int)glp[l][m];
									c2 = (int)imagem_colorida[i - x1][j - x2][k];
									c3 += c1 * c2;
								}
							}
						}
						if(c3 < 0){
							auxiliar_colorida1[i][j][k] = 0;
						}
						else if(c3 > 255){
							auxiliar_colorida1[i][j][k] = 255;
						}
						else{
							auxiliar_colorida1[i][j][k] = (unsigned char)c3;
						}
						c3 = 0;	
					}
				}
			}
			
		cout << "Digite o nome da imagem gerada (Utilize o .pnm)" << endl;//Sa�da de imagem
		cin >> arq_saida;
		cout << endl;
		
		arquivoout.open(arq_saida,ios::out);

    	arquivoout << tipoimg << endl;                            
    	arquivoout << "# INF110\n";  
    	arquivoout << largura << " " << altura << endl;       
    	arquivoout << 255 << endl;                            
    	for(int i=0;i<altura;i++)
      		for(int j=0;j<largura;j++) 
        		for(int k = 0; k < cor; k++)
        			arquivoout << (int)auxiliar_colorida1[i][j][k] << endl;
			
		arquivoout.close();	
		
		cout << "Imagem gerada com sucesso!" << endl;	
			
			return 0;		
	}
    
    else if(gostaria2 == 4){//Gaussiano
    	cout << "Voc� escolheu o Filtro Gaussiano." << endl;
    	double c3 = 0;
    	
    		for(int i = 0, c1 = 0, c2 = 0; i < altura; i++){//Aplica o filtro gdg
				for(int j = 0; j < largura; j++){
					for(int k = 0; k < 3; k++){
						for(int l = 0, x1 = 1; l < 3; l++, x1--){
							for(int m = 0, x2 = 1; m < 3; m++, x2--){
								if(i - x1 < 0 || j - x2 < 0 || i - x1 >= altura || j - x2 >= largura){
									c3 += 0;
								}
								else{
									c1 = (int)gdg[l][m];
									c2 = (int)imagem_colorida[i - x1][j - x2][k];
									c3 += c1 * c2;
								}
							}
						}
						c3 /= 16;
						if(c3 < 0){
							auxiliar_colorida1[i][j][k] = 0;
						}
						else if(c3 > 255){
							auxiliar_colorida1[i][j][k] = 255;
						}
						else{
							auxiliar_colorida1[i][j][k] = (unsigned char)c3;
						}
						c3 = 0;	
					}
				}
			}
			
		cout << "Digite o nome da imagem gerada (Utilize o .pnm)" << endl;//Sa�da de imagem
		cin >> arq_saida;
		cout << endl;
		
		arquivoout.open(arq_saida,ios::out);

    	arquivoout << tipoimg << endl;                            
    	arquivoout << "# INF110\n";  
    	arquivoout << largura << " " << altura << endl;       
    	arquivoout << 255 << endl;                            
    	for(int i=0;i<altura;i++)
      		for(int j=0;j<largura;j++) 
        		for(int k = 0; k < cor; k++)
        			arquivoout << (int)auxiliar_colorida1[i][j][k] << endl;
			
		arquivoout.close();	
		
		cout << "Imagem gerada com sucesso!" << endl;	
			
			return 0;		
	}
    
    
}
		cout << "Digite o nome da imagem gerada (Utilize o .pnm)" << endl;//Sa�da de imagem
		cin >> arq_saida;
		cout << endl;
		
		arquivoout.open(arq_saida,ios::out);

    	arquivoout << tipoimg << endl;                            
    	arquivoout << "# INF110\n";  
    	arquivoout << largura << " " << altura << endl;       
    	arquivoout << 255 << endl;                            
    	for(int i=0;i<altura;i++)
      		for(int j=0;j<largura;j++) 
        		for(int k = 0; k < cor; k++)
        			arquivoout << (int)imagem_colorida[i][j][k] << endl;
			
		arquivoout.close();	
		
		cout << "Imagem gerada com sucesso!" << endl;	
	
} //FIM DAS COLORIDAS
	
	return 0;//Fim do melhor software dessa gera��o.
}
