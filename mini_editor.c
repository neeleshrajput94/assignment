
// insertchar()
// deletechar()
// insertline()
// deleteline()


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct line {
	struct column *nextc;
	struct line *nextl;
};
struct column {
	char data;
	struct column *nextc;
};


void insertchar(struct line *startline, int line, int column, char ele) {
	int line1 = 1, column1 = 1;
	struct column *tempc = NULL;

	//traverse upto the line no. , if not found attach new line node
	while(line1 != line) {
		if(startline->nextl == NULL) {
			startline->nextl = (struct line*)malloc(sizeof(struct line));
			startline = startline->nextl;
			startline->nextl = NULL;
			startline->nextc = NULL;
			break;
		}
		startline = startline->nextl;
		line1++;
	}

	//if insert at first position of line
	if(startline->nextc == NULL || column == 1) {
		tempc = startline->nextc;
		startline->nextc = (struct column*)malloc(sizeof(struct column));
		startline->nextc->data = ele;
		startline->nextc->nextc = tempc;
	}
	else {
		tempc = startline->nextc;
		column1++;
		//traverse upto column no.
		while(column1 != column) {
			if(tempc->nextc == NULL)
				break;
			tempc = tempc->nextc;
			column1++;
		}

		//attache new node
		struct column *new = (struct column*)malloc(sizeof(struct column));
		new->data = ele;
		new->nextc = tempc->nextc;
		tempc->nextc = new;
	}
	
}


void deletechar(struct line *startline, int line, int column) {
	int line1 = 1, column1 = 1, breakflag = 0;;
	struct column *tempc = NULL;

	//traverse upto line no.
	while(line1 != line) {
		if(startline == NULL) {
			breakflag = 1; //line no. is not exist
			break;
		}
		startline = startline->nextl;
		line1++;
	}

	//line no. exist and line is not empty
	if(breakflag == 0 && startline->nextc != NULL) {
		if(column == 1) { //delete at first position
			tempc = startline->nextc;
			startline->nextc = tempc->nextc;
			free(tempc);
		}
		else { //delete at another position
			tempc = startline->nextc;
			column1++;
			//traverse upto column no.
			while(column1 != column) {
				if(tempc->nextc == NULL)
					break;
				tempc = tempc->nextc;
				column1++;
			}
			//deleting node
			if(tempc->nextc != NULL)
				tempc->nextc = tempc->nextc->nextc;
		}
	}
}


void insertline(struct line *startline, int line, char *str) {
	int line1 = 2, column1 = 1;
	struct line *templ = NULL;
	struct column *tempc = NULL;

	if(line == 1) { //insert at first line
		templ = startline->nextl;
		startline->nextl = (struct line*)malloc(sizeof(struct line));
		startline->nextl->nextl = templ;
		startline->nextl->nextc = startline->nextc;
		startline->nextc = NULL;
	}
	else {
		//traverse upto the line no. , if not found attach new line node
		while(line1 < line) {
			if(startline->nextl == NULL)
				break;
			startline = startline->nextl;
			line1++;
		}
		//attach new node for line
		templ = startline->nextl;
		startline->nextl = (struct line*)malloc(sizeof(struct line));
		startline = startline->nextl;
		startline->nextl = templ;
		startline->nextc = NULL;
	}

	//insert contents of line to line node
	for(int i = 0; i < strlen(str); i++) {
		insertchar(startline, 1, i+1, *(str+i));
	}

}


void deleteline(struct line *startline, int line) {
	int line1 = 2; //upto previous node
	int breakflag = 0; //indicates line not exist if it is 1.
	struct line *templ = startline;
	struct column *tempc = NULL; //content of deleted line to must be free

	//delete first line
	if(line == 1) {
		tempc = startline->nextc;
		templ = startline->nextl;
		startline->nextc = templ->nextc;
		startline->nextl = templ->nextl;
		free(templ);
	}
	else { //delete line except first line
		//traverse upto line no.
		while(line1 != line) {
			if(startline->nextl == NULL) {
				breakflag = 1; //line no. is not exist
				break;
			}
			startline = startline->nextl;
			line1++;
		}

		if(breakflag == 0 && startline->nextl != NULL) {
			templ = startline->nextl;
			startline->nextl = templ->nextl;
			tempc = templ->nextc;
			free(templ);
		}
	}

	if(breakflag = 0)
		while(tempc != NULL) {
			struct column *tempc1 = tempc;
			tempc = tempc->nextc;
			free(tempc1);
		}

}


void printtext(struct line *startline) {
	int lineno = 1;
	struct column *tempc = NULL;

	while(startline != NULL) {
		printf("%2d_", lineno);
		lineno++;
		tempc = startline->nextc;

		if(tempc == NULL) { //for empty line
			printf("\n");
			startline = startline->nextl;
			continue;
		}
		else {
			while(tempc != NULL) {
				printf("%c", tempc->data);
				tempc = tempc->nextc;
			}
		}
		printf("\n");
		startline = startline->nextl;
	}
}


void main() {
	struct line *startline = (struct line*)malloc(sizeof(struct line));
	
	insertchar(startline, 1, 1, 'a');
	insertchar(startline, 1, 1, 'b');
	insertchar(startline, 2, 1, 'c');
	insertchar(startline, 2, 2, 'd');
	insertchar(startline, 2, 4, 'e');
	insertchar(startline, 4, 2, 'f');
	printf("\n");
	printtext(startline);

	deletechar(startline, 1, 1);
	deletechar(startline, 1, 1);
	deletechar(startline, 2, 4);
	deletechar(startline, 2, 2);
	printf("\n");
	printtext(startline);

	deleteline(startline, 1);
	printf("\n");
	printtext(startline);

	insertline(startline, 1, "pqrs");
	insertline(startline, 5, "xyz");
	printf("\n");
	printtext(startline);

}


