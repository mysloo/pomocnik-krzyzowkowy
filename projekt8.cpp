#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;
struct slowa{
	char s[50];
	slowa *next;
};
void info(){
	printf("Co chcesz zrobic: \n");
	printf("1 - wyjdz z programu \n");
	printf("2 - wyswietl slowa znajdujace sie na liscie \n");
	printf("3 - dodaj konkretne slowo z listy \n");
	printf("4 - usun konkretne slowo na liste \n");
	printf("5 - edytuj slowo \n");
	printf("6 - wyszukaj wzorca w bazie \n");
	printf("7 - przypomnij instrukcje obslugi \n");
}
void wyswietl(slowa **head){
	/*cout<<endl<<"WYSWIETLANIE"<<endl;
	cout<<"---------------"<<endl;*/
	slowa *start = *head;
	while((*head)){
		cout<<(*head)->s<<endl;
		*head=(*head)->next;
	}
	*head=start;
	//cout<<"---------------"<<endl;
}
void dodaj_dalej(slowa *head,slowa *tmp,char wyraz[]){
	slowa *pom = head;
	bool czy=false;
	while(strcmp(head->s,tmp->s)<0 && head->next!=NULL){
		head=head->next;
		if(czy){
			pom=pom->next;
		}
		czy=true;
	}
	if(strcmp(head->s,tmp->s)<0){
		strcpy(tmp->s,wyraz);
		head->next=tmp;
		tmp->next=NULL;
	}
	else {
		strcpy(tmp->s,wyraz);
		tmp->next=head;
		pom->next=tmp;
	}
}
void dodaj(slowa **head, char wyraz[]){
	slowa *tmp = new slowa;
	char slowo[50];
	for(int i=0;i<strlen(wyraz);i++){
		slowo[i]=tolower(wyraz[i]);
	}
	tmp->next=NULL;
	strcpy(tmp->s,slowo);
	if(strcmp((*head)->s,tmp->s)>=0){
		strcpy(tmp->s,wyraz);
		tmp->next=*head;
		*head=tmp;
	}
	else dodaj_dalej(*head,tmp,wyraz);
}
int usun_element(slowa **head,char slowo[]){
	bool czy=false;
	slowa *pom = *head;
	slowa *start = *head;
	while(strcmp((*head)->s,slowo)!=0 && (*head)->next!=NULL){
		*head=(*head)->next;
		if(czy){
			pom=pom->next;
		}
		czy=true;
	}
	if(strcmp((*head)->s,slowo)!=0){
		printf("Taki wyraz nie istnieje w bazie danych\n");
		*head=start;
		return true;
	}
	//usuwa pierwszy element
	if(!czy){
		pom=pom->next;
		delete *head;
		*head=pom;
		return false;
	}
	//usuwa element ktory znajduje sie dalej na liscie
	else {
		pom->next=(*head)->next;
		delete *head;
		*head=start;
		return false;
	}
}
void edytuj(slowa **head,char slowo[]){
	char pom[50];
	char nowe[50];
	char kopia[50];
	strcpy(nowe,slowo);
	strcpy(kopia,slowo);
	if(usun_element(head,slowo)) return;
	int dl=strlen(nowe);
	char znak;
	int i=0;
	//a usuwa 
	printf("Wcisniecie litery 'a' usunie ostatnia litere ze slowa: %s\n",slowo);
	while(dl!=0){
		cin>>znak;
		if(znak!='a'){
			pom[i]=nowe[dl-1];
			i++;
		}
		dl--;
	}
	pom[i]='\0';
	i=0;
	strcpy(nowe,pom);
	for(int j=strlen(nowe)-1;j>=0;j--){
		pom[i]=nowe[j];
		i++;
	}
	strcpy(nowe,pom);
	char x[50];
	//puste,1,>1
	printf("Tak wyglada Twoje slowo: %s\n",nowe);
	if(strlen(nowe)>1){
		printf("Powiedz, gdzie chcesz dodac swoje slowo (przed, w, za): ");
		scanf("%s",x);
		if((strcmp(x,"przed")!=0 && strcmp(x,"w")!=0 && strcmp(x,"za")!=0)){
			printf("Nie mozna wykonac\n");
			dodaj(head,kopia);
			return;
		}
	}
	else if(strlen(nowe)>0){
		printf("Powiedz, gdzie chcesz dodac swoje slowo (przed,za): ");
		scanf("%s",x);
		if((strcmp(x,"przed")!=0 && strcmp(x,"w")!=0 && strcmp(x,"za")!=0)){
			printf("Nie mozna wykonac\n");
			dodaj(head,kopia);
			return;
		}
	}
	if(strlen(nowe)<=1 && strcmp(x,"w")==0){
		printf("Nie mozna wykonac\n");
		dodaj(head,kopia);
		return;
	}
	printf("Podaj slowo jakie chcesz dodac: ");
	scanf("%s",pom);
	if(strlen(nowe)==0 && (strcmp(x,"przed")!=0 || strcmp(x,"w")!=0 || strcmp(x,"za")!=0)){
		strcpy(x,"przed");
		goto tu;
	}
	if(strcmp(x,"przed")==0 && strlen(nowe)>=1){
		tu:
		strcat(pom,nowe);
		printf("Oto Twoje slowo: %s\n",pom);
		dodaj(head,pom);
		return;
	}
	if(strcmp(x,"za")==0 && strlen(nowe)>=1){
		strcat(nowe,pom);
		printf("Oto Twoje slowo: %s\n",nowe);
		dodaj(head,nowe);
	}
	else if(strcmp(x,"w")==0 && strlen(nowe)>1){
		int dl=strlen(nowe),m=0,x=dl;;
		while(x!=0){
			m++;
			x/=10;
		}
		for(int i=0;i<dl;i++){
			printf("%*c ",m,nowe[i]);
		}
		printf("\n");
		for(int i=0;i<dl;i++){
			printf("%*d ",m,i);
		}
		string c,d;
		int a,b;
		char wynik[50];
		printf("\nPodaj miedzy, ktorymi pozycjami ma sie znajdowac Twoje slowo: \n");
		cin>>c>>d;
		a=atoi(c.c_str());
		b=atoi(d.c_str());
		if(b-a!=1 || a>=strlen(nowe) || b>=strlen(nowe)){
			printf("Nie mozna wykonac\n");
			dodaj(head,kopia);
			return;
		}
		strcat(pom,nowe+b);
		for(int i=0;i<a+1;i++){
			wynik[i]=nowe[i];
		}
		wynik[a+1]='\0';
		strcat(wynik,pom);
		printf("Oto Twoje slowo: %s\n",wynik);
		dodaj(head,wynik);
	}
}
void szukaj(slowa *head,char wzor[]){
	char slowo[50];
	int i=0,dl=0,p,dlugosc=0,j=0;
	bool gwiazdka=false,zm=false;
	vector <char> v[strlen(wzor)+10], zakres;
	while(i<strlen(wzor)){
		if(wzor[i]=='['){
			v[dl].push_back('[');
			while(wzor[i]!=']'){
				i++;
				if(wzor[i]!=',' && wzor[i]!=']'){
					zakres.push_back(wzor[i]);
				}
			}
		zakres.push_back(',');
		}
		else v[dl].push_back(wzor[i]);
		if(wzor[i]=='*'){
			gwiazdka=true;
			i++;
			while(wzor[i]!='*' && i<strlen(wzor)){
				if(wzor[i]=='['){
					v[dl].push_back('[');
					while(wzor[i]!=']'){
						i++;
						if(wzor[i]!=',' && wzor[i]!=']'){
							zakres.push_back(wzor[i]);
						}
					}
					zakres.push_back(',');
				}
				else {
					v[dl].push_back(wzor[i]);
				}
				i++;
				dlugosc++;
			}
			i--;
		}
		dlugosc++;
		dl++;
		i++;
	}
	v[dl].push_back('#');

	int k,m,poz,ile,x;
	bool czy,pom,war,istnieje;
	while(head!=NULL){
		strcpy(slowo,head->s);
		czy=false;
		i=0,j=0,ile=0;
		//---------------------------------
		while(i<strlen(slowo)){
			pom=false;
			if(dlugosc>strlen(slowo)){
				czy=true;
				break;
			}
			if(gwiazdka==false && strlen(slowo)>dlugosc){
				czy=true;
				break;
			}
			//1 litera
			if(v[j].size()==1 && v[j][0]!='['){
				if(slowo[i]==v[j][0] || v[j][0]=='?'){
					j++;
				}
				else if(v[j][0]=='*'){ //a****bca
					if(v[j+1][0]=='#') break;
					else {
						j++;
						continue;
					}
				}
				else {
					czy=true;
					break;
				}
			}
			// gwiazdka (przynajmniej 2 litery)
			else if(v[j][0]=='*'){
				k=v[j].size()-1;//ilosc znakow dla *ab[? jest rowna 4(bez *)
				if(v[j+1][0]!='*'){//wtedy biore ostatni mozliwy wzorzec
					poz=i;
					if(i==0) i++;
					for(int h=i;h<strlen(slowo)-k+1;h++){
						x=ile;
						for(int u=0;u<k;u++){
							if(slowo[h+u]!=v[j][u+1] && v[j][u+1]!='?' && v[j][u+1]!='['){
								zm=true;
							}
							else if(v[j][u+1]=='['){
								pom=false;
								while(zakres[x]!=','){
									if(slowo[h+u]==zakres[x] || zakres[x]=='?'){
										pom=true;
									}
									x++;
								}
								x++;
								if(pom==false) zm=true;
							}
						}
						if(zm==false){
							poz=h+k-1;
						}
						zm=false;
					}
					ile=x;
					if(poz-i==0){//nie znalazlo wzorca
						czy=true;
						break;
					}
					i=poz;
				}
				else { //pierwszy wzorzec
					poz=i;
					int ile_zapytania=0;
					for(int h=i;h<strlen(slowo)-k+1;h++){
						x=ile;
						for(int u=0;u<k;u++){
							if(slowo[h+u]!=v[j][u+1] && v[j][u+1]!='?' && v[j][u+1]!='[' ){
								zm=true;
							}
							else if(v[j][u+1]=='?') ile_zapytania=1;
							else if(v[j][u+1]=='['){
								pom=false;
								while(zakres[x]!=','){
									if(slowo[h+u]==zakres[x] || zakres[x]=='?'){
										pom=true;
									}
									x++;
								}
								x++;
								if(pom==false) zm=true;
							}
						}
						if(zm==false){
							poz=h+k-1+ile_zapytania;
							break;
						}
						ile_zapytania=0;
						zm=false;
					}
					ile=x;
					if(poz-i==0 || poz==strlen(slowo)-1){//nie znalazlo wzorca
						czy=true;
						break;
					}
					i=poz;
				}
				j++;
			}
			// przedzial [a,b,c]
			else if(v[j][0]=='['){
				while(zakres[ile]!=','){
					if(slowo[i]==zakres[ile] || zakres[ile]=='?'){
						pom=true;
					}
					ile++;
				}
				ile++;
				if(pom==false){
					czy=true;
					break;
				}
				j++;
			}
			i++;
		}
		if(czy==false){
			printf(": %s\n",slowo);
			istnieje=true;
		}
		head=head->next;
	}
	if(!istnieje) printf("Brak slow\n");
}
int sprawdz_poprawnosc(char wzor[],int x){
	bool a=false,b=false,czy=false;
	if(x==0){
		int y=0;
		for(int i=0;i<strlen(wzor);i++){
			y=wzor[i];
			if((wzor[i]>='A' && wzor[i]<='Z') || (wzor[i]>='a' && wzor[i]<='z'));
			else czy=true;
		}
	}
	for(int i=0;i<strlen(wzor);i++){
		if((wzor[i]>='A' && wzor[i]<='Z') || (wzor[i]>='a' && wzor[i]<='z'));
		else if(wzor[i]!=']' && wzor[i]!='[' && wzor[i]!=',' && wzor[i]!='*' && wzor[i]!='?'){
			czy=true;
		}
		if(wzor[i]=='[') a=true;
		if(wzor[i]==']') b=true;
		if(b==true && a==false){
			czy=true;
		}
		if(a==false && wzor[i]==',') czy=true;
		if(wzor[i]=='['){
			int j=i+1,w=0,x=0;
			while(wzor[j]!=']' && j<strlen(wzor)){
				if(wzor[j]=='[' || wzor[j]=='*' || wzor[j]=='?'){
					czy=true;
				}
				if(wzor[j+1]==']' && wzor[j]==']'){
				 czy=true;
				}
				if(wzor[j]==','){
					w++;
				}
				else if(wzor[j+1]==',' || wzor[j+1]==']'){
					x++;
				}
				else czy=true;
				j++;
			}
			a=false;
			b=false;
			if(x-w!=1) {
				czy=true;
			}
			i=j;
		}
	}
	if(czy==true) {
		return true;
	}
	else return false;
}
void wrzuc_do_pliku(slowa *head,string nazwa){
	ofstream plik;
	plik.open(nazwa);
	if(!plik){
		printf("Blad otwarcia pliku wyjscie.txt\n");
		return;
	}
	while(head->next){
		plik<<head->s<<'\n';
		head=head->next;
	}
}
char sl[50],wyraz[50];
string n;
int m;
bool czy;
int main(){
	setlocale( LC_ALL, "Polish" );
	//dodanie slow na liste ktore znajduja sie w pliku
	ifstream plik;
	plik.open("dane.txt");
	if(!plik){
		printf("Blad otwarcia pliku dane.txt\n");
		return 0;
	}
	slowa *head = new slowa;
	while(plik>>sl){
		strcpy(wyraz,sl);
		if(!czy){
			head->next=NULL;
			strcpy(head->s,sl);
			czy=true;	
		}
		else dodaj(&head,wyraz);
	}
	plik.close();
	///
	info();
	while(1){
		printf("Podaj liczbe: ");
		cin>>n;
		m=atoi(n.c_str());
		switch(m){
			case 1:{
				wrzuc_do_pliku(head,"wyjscie.txt");
				printf("Jesli chcesz , aby plik 'dane.txt' zastapic 'wyjscie.txt' wscisnij 1\n");
				cin>>n;
				m=atoi(n.c_str());
				if(m==1){
					wrzuc_do_pliku(head,"dane.txt");
				}
				printf("Wyszedles z programu\n");
				return 0;
				break;
			}
			case 2: {	
				wyswietl(&head);
				break;
			}
			case 3: {
				printf("Podaj wyraz, ktory chcesz dodac: ");
				cin>>sl;
				strcpy(wyraz,sl);
				if(sprawdz_poprawnosc(wyraz,0)!=0){
					printf("Nie mozna dodac takiego slowa\n");
					break;
				}
				dodaj(&head,wyraz);
				printf("Dodano\n");
				break;
			}
			case 4: {
				printf("Podaj wyraz, ktory chcesz usunac: ");
				scanf("%s",sl);
				strcpy(wyraz,sl);
				if(!usun_element(&head,sl)){
					printf("Usunieto\n");
				}
				break;
			}
			case 5: {
				printf("Podaj wyraz, ktory chcesz edytowac: ");
				scanf("%s",sl);
				strcpy(wyraz,sl);
				edytuj(&head,wyraz);
				break;
			}
			case 6: {
				printf("Wprowadz slowo klucz: ");
				scanf("%s",sl);
				strcpy(wyraz,sl);
				if(sprawdz_poprawnosc(wyraz,1)!=0){
					printf("Zly model wzorca\n");
					break;
				}
				szukaj(head,wyraz);
				break;
			}
			case 7: {
				info();
				break;
			}
			default: {
				break;
			}
		}
	}
	return 0;
}	