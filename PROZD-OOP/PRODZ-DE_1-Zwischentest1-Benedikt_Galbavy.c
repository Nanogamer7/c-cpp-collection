#include <stdio.h>

void current_points(double zt, double at, double ue, double total){

	printf("\nZT Punkte: %.2lf", zt);
	printf("\nAT Punkte: %.2lf", at);
	printf("\nUE Punkte: %.2lf", ue);
	printf("\nErreichbare Gesamtpunkte: %.2lf", total);
}

void print_final_grade(double points, double percent, int grade){

	printf("\nGesamtpunkte absolut: %.2lf", points);
	printf("\nGesamtpunkte %%: %.2lf %%", percent);

	printf("\nNote: %d", grade);
}

void final_grade(double zt, double at, double ue, double total){

	double points = zt+at+ue;
	double percent, percent_ue;

	// Sonderfall keine* Eingaben
	if(total){
		percent = (zt+at) / total * 100;
		percent_ue = points / total * 100;
	}else{
		percent = 0;
		percent_ue = 0;
	}

	int grade;

	// Notenschlüssel
	if(percent < 55){
		grade = 5;
		points = zt+at;
		// Keine schöne Umsetzung der Variablen gegenber des beabsichtigten Zwecks
		// It works^tm
		percent_ue = percent;
	}else if(percent_ue < 67){
		grade = 4;
	}else if(percent_ue < 78){
		grade = 3;
	}else if(percent_ue < 89){
		grade = 2;
	}else{
		grade = 1;
	}

	// Sonderfall keine* Eingaben
	// Nachgestellt um verschachtelungen zu verringern
	if(!total){
		grade = 0;
		points = 0;
	}

	print_final_grade(points, percent_ue, grade);
}


int main(){

	// zt, at, ue, total und at_done werden wärend jeder Ausführung von while benötigt
	double zt, at, ue, total = 0;
	int at_done = 0;


	// Anzahl der Durchläufe unbekannt
	// Nachdem es nur eine exit condition gibt, ist break; einfacher
	while(1){
		// Variablen für den Input
		char in_c;
		double in_d;

		// Aktuellen Stand ausgeben
		current_points(zt, at, ue, total);

		printf("\nTyp: ");
		scanf(" %c", &in_c);

		// Falls die Note ausgegeben werden soll
		if(in_c == '='){
			final_grade(zt, at, ue, total);
			break;
		}

		printf("\nPunkte: ");
		scanf(" %lf", &in_d);
		

		// Drei weitere Möglichkeiten als Typ
		switch(in_c){
			case 'z':
				// Erlaubter Punkteberreich
				if(in_d >= 0 && in_d <= 10){
					zt += in_d;
					total += 10;
				}else{
					printf("\nungueltiger Bereich: min 0.00, max 10.00");
				}
				break;
			case 'a':
				// Wie oben
				if(in_d >= 0 && in_d <= 70){
					at = in_d;
					// Gesamt Mögliche Punkte nur erhöhen falls noch kein
					// Abschlusstest eingegeben wurde
					//
					// *Vermutlich gibt es eine elegantere Lösung*
					if(!at_done){
						total += 70;
						at_done = 1;
					}
				}else{
					printf("\nungueltiger Bereich: min 0.00, max 70.00");
				}
				break;
			case 'u':
				// Wie oben
				if(in_d >= 0 && in_d <= 0.5){
					// if-statement um Uebungspunkte auf 10 zubegrenzen
					ue = ue + in_d <= 10 ? in_d + ue : 10;
				}else{
					printf("\nungueltiger Bereich: min 0.00, max 0.50");
				}
				break;

		}

	}

	return 0;
}