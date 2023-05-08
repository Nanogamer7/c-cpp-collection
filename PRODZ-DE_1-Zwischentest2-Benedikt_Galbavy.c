#include <stdio.h> 
enum type{passenger = 'P', sleeper = 'S', diner = 'D'} typedef type;
struct carriage{type type;int capacity;} typedef carriage;
struct train{carriage carriage[10];int length;} typedef train;
void printCarriage(carriage carriage); // outputs one cart
void printTrain(train *train); // outputs all carriages plus train length
char getMenu(); // lists options (see main)
carriage getCarriage(); // validates user input for a new carriages
int getPosition(int length); // validates user input for the position of a new carriages
int insertCarriage(train* train, int pos, carriage carriage); // inserts a carriage (struct) at the specified position, or returns an error code
int sumCapacity(train* train, type type); // returns the capacities of all carriages of a specific type
void printTrainStats(train* train); // prints the capacities per type of carriages
void printError(int error); // prints error codes from inserCarriages()
void invalidInput(){printf("\nInput invalid! Try again: ");} // to avoid duplicate strings
int main(){
	train train = { .length = 0 }; // empty train, thus length
	while(1){
		char input = getMenu();
		switch(input){ // x = exit, p = print, n = new carriages, s = stats
			case 'x': goto exit; // goto to exit a while loop from within a switch
			case 'p':
				printTrain(&train);
				break;
			case 'n': ;
				carriage carriage = getCarriage();
				int pos = getPosition(train.length);
				int error = insertCarriage(&train, pos, carriage);
				if(error) printError(error);
				break;
			case 's':
				printTrainStats(&train);
				break;
		}
	}
	exit: ; // line 40
	return 0;
}
void printCarriage(carriage carriage){printf("[%c:%03d]", carriage.type, carriage.capacity);}
void printTrain(train* train){
	printf("\nTrain: ");
	if(train->length){ // different output for empty train
		for(int i = 0; i < train->length; i++){
			printf("%d:", i);
			printCarriage(train->carriage[i]);
			if(i+1<train->length) printf("-");
		}
		printf(" Length: %d", train->length);
	}else printf( "No Carriages!");
}
char getMenu(){
	char input;
	printf("\nChoose Action: print train (p), new carriage (n), print stats (s) or exit (x): ");
	while(1){ // while until a valid input
		scanf(" %c", &input);
		switch(input){
			case 'p':case 'n':case 's':case 'x': // same statement for all cases
				goto exit; // goto to exit a while loop from within a switch
			default:
				invalidInput();
				break;
		}
	}
	exit:
	return input;
}
carriage getCarriage(){
	char input;
	type type;
	int capacity;
	printf("\nChoose type of carriage: passenger (p), sleeper (s) or diner (d): ");
	while(1){
		scanf(" %c", &input);
		switch(input){
			case 'p':
				type = passenger;
				goto exit; // goto to exit a while loop from within a switch
			case 's':
				type = sleeper;
				goto exit;
			case 'd':
				type = diner;
				goto exit;
			default:
				invalidInput();
				break;
		}
	}
	exit: ;
	printf("\nChoose capacity (20 - 130): ");
	while(1){
		scanf("%d", &capacity);

		if(capacity <= 130 && capacity >= 20)
			break;
		else
			invalidInput();
	}
	carriage carriage = { type, capacity };
	return carriage;
}
int getPosition(int length){
	int pos;
	printf("\nChoose position for the new carriage (0-%d): ", length);

	while(1){
		scanf("%d", &pos);
		if(pos <= length && pos >= 0) break;
		else invalidInput();
	}
	return pos;
}
int insertCarriage(train* train, int pos, carriage carriage){
	int error = 0;
	if(train->length >= 10) error = -1;
	if(pos < 0 || pos > train->length) error = -2;
	if((carriage.type == 'S') && ((pos < 2) || ((train->carriage[pos-1].type != 'P') || (train->carriage[pos-2].type != 'P')))) error = -3;

	if(!error){
		for(int i = train->length; i > pos; i--) train->carriage[i] = train->carriage[i-1];
		train->carriage[pos] = carriage;
		train->length++;
	}
	return error;
}
int sumCapacity(train* train, type type){
	int count = 0;
	for(carriage* p = train->carriage; p < train->carriage + train->length; p++) if((p->type == type)) count += p->capacity;
	return count;
}

void printTrainStats(train* train){
	printTrain(train);
	printf("\nCapacities: ");
	printf("\n  Passenger: %d", sumCapacity(train, passenger));
	if(sumCapacity(train, passenger) > 100) printf(" - invalid");
	printf("\n  Sleeper: %d", sumCapacity(train, sleeper));
	printf("\n  Diner: %d", sumCapacity(train, diner));
}

void printError(int error){
	switch(error){
		case -1:
			printf("\nError: Train too long!");
			break;
		case -2:
			printf("\nError: Position not possible!");
			break;
		case -3:
			printf("\nError: Sleeper only possible directly after two passenger carriages!");
			break;
	}
}