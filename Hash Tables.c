//Ahmed Osama AbdulMaksoud Ali  BN : 1		Sec:1
//Ahmed Ali ElSayed				BN : 13		sec:1
//Hussam Ali Ahmed Mohamed		BN : 56		Sec:1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define N 100000 //check the number
struct b_day
{
	int day;
	int month;
	int year;
};
struct student
{
	char name[50];
	int ID;
	struct b_day bday;
	int score_;
};
typedef struct node
{
	struct student students;
	struct node* next;
}node;

//globals
char garbage;
int hash_size = 0;

//chained hashing functions
void chainedHashing();
unsigned int hash(char* word);
void nullify(node* table[]); //common
void addNode(node* table[],int op);
void get_data(node** n);
int add_integer(int* req);
void print_n(node* table[]);
void unload(node* table[]);
node* findhash(node* table[]);
void lowercase(char* word);
void print_element(node* tmp_);
void remove_(node* table[]);
void auto_data(node* n); //common

//Probing functions
void Probing();
unsigned int hash_b(node* p);
void addNode_b(node* table[], int method, int op);
int is_hashfull();
void get_data_b(node* n);
int add_integer(int* req);
void print_table(node* table[]);
void print_element(node* tmp_);
void findhash_b(node* table[], int method);
void remove_b(node* table[], int method);


int main()
{
	int choice;
	printf("Choose an option to continue.\n(1)Chained Hashing.\n(2)Probing.\nInput:");
	if (scanf_s("%d", &choice) == 0)
		return 0;
	if (choice == 1)
	{
		chainedHashing();
	}
	else if (choice == 2)
	{
		Probing();
	}
	else
	{
		printf("Invalid Input");
		return 0;
	}
}

void nullify(node* table[])
{
	for (int i = 0; i < N; i++)
	{
		table[i] = NULL;
	}
}
int add_integer(int* req) //added
{
	while (1)
	{
		scanf_s("%c", &garbage, 1);
		if (scanf_s("%i", req) == 1)
			if (*req >= 0)
				return *req;
	}
}
void print_element(node* tmp_)
{
	printf("\nthe name of student is %s\n", tmp_->students.name);
	printf("The ID of student is %i\n", tmp_->students.ID);
	printf("The student was born in %i/%i/%i\n", tmp_->students.bday.day, tmp_->students.bday.month, tmp_->students.bday.year);
	printf("The grade of the student is %i\n", tmp_->students.score_);
	printf("The index is : %i\n\n", hash(tmp_->students.name));
}

//chained hashing functions
unsigned int hash(char* word)
{
	int hash = 0;
	int n;
	int z = strlen(word);
	for (int i = 0; i < z; i++)
	{
		if (isalpha(word[i]))
			n = tolower(word[i]) - 'a' + 1;
		else
			n = 27;
		hash = ((hash * 8) + n) % N; //increase the range of the hash
	}
	return hash;
}

void addNode(node* table[], int op)
{
	node* n = malloc(sizeof(node));
	if (n == NULL)
	{
		return;
	}
	if (op == 1)
	{
		get_data(&n);
	}
	else if (op == 2)
	{
		auto_data(n);
	}
	int hashed = hash(n->students.name);
	n->next = table[hashed];
	table[hashed] = n;
}
void get_data(node** n)
{
	printf("\nEnter the name of the student  : ");
	scanf_s("%c", &garbage, 1);
	scanf_s("%[^\n]", (*n)->students.name, 50);
	printf("Enter the ID of the student ");
	(*n)->students.ID = add_integer(&(*n)->students.ID);
	printf("Enter the birth day of the student. \n");
	printf("Day : ");
	do
	{
		(*n)->students.bday.day = add_integer(&(*n)->students.bday.day);
	} while ((*n)->students.bday.day > 31);
	printf("Month : ");
	do
	{
		(*n)->students.bday.month = add_integer(&(*n)->students.bday.month);
	} while ((*n)->students.bday.month > 12);
	printf("Year : ");
	(*n)->students.bday.year = add_integer(&(*n)->students.bday.year);
	printf("Score: ");
	(*n)->students.score_ = add_integer(&(*n)->students.score_);
}
void auto_data(node* n)
{
	//*n->students.name = "Cayde";
	char name[] = "Cayde";
	strcpy_s((n->students.name),6, name);
	n->students.ID = 45;
	n->students.bday.day = 4;
	n->students.bday.month = 9;
	n->students.bday.year = 2018;
	n->students.score_ = 7777;
}

void print_n(node* table[])
{

	for (int i = 0; i < N; i++)
	{
		if (table[i] != NULL)
		{
			for (node* tmp_ = table[i]; tmp_ != NULL; tmp_ = tmp_->next)
			{
				print_element(tmp_);
			}
		}
	}
}
void unload(node* table[])
{
	node* temp;
	node* crawler;

	for (int n = 0; n < N; n++)
	{
		if (table[n] != NULL)
		{
			// If only 1 node free it
			crawler = table[n];
			while (crawler != NULL)
			{
				temp = crawler->next;
				free(crawler);
				crawler = temp;

			}
			// free last node in list
			temp = crawler;
			free(temp);
		}
	}
	return;
}
node* findhash(node* table[])
{
	char name[50];
	char compared[50];
	printf("Enter the name : ");
	scanf_s("%s", name, 50);
	lowercase(name);
	int hashed = hash(name);
	node* tmp = NULL;
	for (tmp = table[hashed]; tmp != NULL; tmp = tmp->next)
	{
		strcpy_s(compared, 50, tmp->students.name);
		lowercase(compared);
		if (strcmp(name, compared) == 0)
			return tmp;
	}
	return NULL;
}
void lowercase(char* word)
{

	for (int i = 0, len = strlen(word); i < len; i++)
	{
		word[i] = tolower(word[i]);
	}
}
void remove_(node* table[])
{
	char name[50], compared[50];
	printf("Enter the name to be removed : ");
	scanf_s("%s", name, 50);
	lowercase(name);
	int hashed = hash(name);
	node** spec_table = &table[hashed];
	while (*spec_table)
	{
		node* tmp = *spec_table;
		strcpy_s(compared, 50, tmp->students.name);
		lowercase(compared);

		if (strcmp(name, compared) == 0)
		{
			*spec_table = tmp->next;
			free(tmp);
			break;
		}
		else
		{
			spec_table = &(*spec_table)->next;
		}

	}
}

//probing functions
unsigned int hash_b(node* p)
{
	int h = 0;
	return ((((p->students.bday.day) * 5 + (p->students.bday.month) * 4 + (p->students.bday.year) / 48)) / 7) % N;
}
void addNode_b(node* table[], int method, int op)
{
	if (is_hashfull())
	{
		printf("The table is full");
		return;
	}
	node* n = malloc(sizeof(node));
	if (n == NULL)
	{
		return;
	}
	if (op == 1)
	{
		get_data_b(n);
	}
	else if (op == 2)
	{
		auto_data(n);
	}
	int hashed = hash_b(n);
	int i = 0;
	//printf("%i\n", hashed);
	while (1)
	{
		if (table[hashed] == NULL)
		{
			n->next = table[hashed];
			table[hashed] = n;
			hash_size++;
			return;
		}
		else if (method == 1)
			hashed = (++hashed) % N;
		else if (method == 2)//Quade Probe
		{
			hashed = (hashed + i * i) % N;
			i++;
		}
	}
}
int is_hashfull()
{
	return(hash_size == N);
}
void get_data_b(node* n)
{
	printf("\nEnter the name of the student  : ");
	scanf_s("%c", &garbage, 1);
	scanf_s("%[^\n]", n->students.name, 50);
	printf("Enter the ID of the student : ");
	n->students.ID = add_integer(&n->students.ID);
	printf("Enter the birth day of the student. \n");
	printf("Day : ");
	do
	{
		n->students.bday.day = add_integer(&n->students.bday.day);
	} while (n->students.bday.day > 31);
	printf("Month : ");
	do
	{
		n->students.bday.month = add_integer(&n->students.bday.month);
	} while (n->students.bday.month > 12);
	printf("Year : ");
	n->students.bday.year = add_integer(&n->students.bday.year);
	printf("Score: ");
	n->students.score_ = add_integer(&n->students.score_);
}
void print_table(node* table[])
{

	for (int i = 0; i < N; i++)
	{
		if (table[i] != NULL)
		{
			printf("--->node number : %i\n", i); //utility to check the hash function. REMOVE AFTER TESTING
			print_element(table[i]);

		}
	}
}

void findhash_b(node* table[], int method)
{
	node* tmp = malloc(sizeof(node));
	if (tmp == NULL)
		return;
	printf("Enter the birthday of the student you wish to find\n");
	printf("Day : ");
	do
	{
		tmp->students.bday.day = add_integer(&tmp->students.bday.day);
	} while (tmp->students.bday.day > 31);
	printf("Month : ");
	do
	{
		tmp->students.bday.month = add_integer(&tmp->students.bday.month);
	} while (tmp->students.bday.month > 12);
	printf("Year : ");
	tmp->students.bday.year = add_integer(&tmp->students.bday.year);

	int hashed = hash_b(tmp);
	int j = 0;
	for (int i = 0; i < N; i++)
	{
		while (table[hashed])
		{
			if (tmp->students.bday.day == table[hashed]->students.bday.day && tmp->students.bday.month == table[hashed]->students.bday.day && tmp->students.bday.year == table[hashed]->students.bday.year)
			{
				print_element(table[hashed]);
				hashed = ((++hashed) % N);

			}
			else if (method == 1)
				hashed = (++hashed) % N;
			else if (method == 2)//Quad probe
			{
				hashed = (hashed + j * j) % N;
				j++;
			}

		}
	}
	free(tmp);
}
void remove_b(node* table[], int method)
{
	node* tmp = malloc(sizeof(node));
	if (tmp == NULL)
		return;
	printf("Enter the birthday of the student you wish to remove\n");
	printf("Day : ");
	do
	{
		tmp->students.bday.day = add_integer(&tmp->students.bday.day);
	} while (tmp->students.bday.day > 31);
	printf("Month : ");
	do
	{
		tmp->students.bday.month = add_integer(&tmp->students.bday.month);
	} while (tmp->students.bday.month > 12);
	printf("Year : ");
	tmp->students.bday.year = add_integer(&tmp->students.bday.year);

	int hashed = hash_b(tmp);
	int j = 0;
	for (int i = 0; i < N; i++)
	{
		while (table[hashed])
		{
			if (tmp->students.bday.day == table[hashed]->students.bday.day && tmp->students.bday.month == table[hashed]->students.bday.month && tmp->students.bday.year == table[hashed]->students.bday.year)
			{
				free(table[hashed]);
				table[hashed] = NULL;
				hashed = (++hashed) % N;
				hash_size--;
			}
			else if (method == 1)
				hashed = (++hashed) % N;
			else if (method == 2)//Quad probe
			{
				hashed = (hashed + j * j) % N;
				j++;
			}
		}
	}
	free(tmp);
}
void chainedHashing()
{

	int choice;
	node* table[N];//to be
	nullify(table);
	printf("Welcome!\nEnter the number of students: ");
	int num_nodes;
	scanf_s("%i", &num_nodes);
	for (int i = 0; i < num_nodes; i++)
	{
		addNode(table,1);
	}
	node* holder = NULL;
	printf("Size : %i\n", num_nodes*sizeof(node) );
	while (1)
	{
		printf("1: print table\n2: Insert an element\n3: Find a certain element\n4: Delete an element\n5: show the time complexity\n6: Exit\n");
		scanf_s("%i", &choice);
		if (choice == 1)
		{
			print_n(table);
		}
		if (choice == 2)
		{
			addNode(table,1);
		}
		if (choice == 4)
		{
			remove_(table);
		}
		if (choice == 3)
		{
			holder = findhash(table);
			if (holder != NULL)
			{
				print_element(holder);
			}
			printf("Does not exist in the table\n");
		}
		if (choice == 5)
		{
			clock_t start;
			clock_t end;
			for (int i = 0; i < 50000; i++)
			{
				start = clock();
				addNode(table, 2);
				end = clock();
				double TimeTaken = (double)(end - start) / CLOCKS_PER_SEC;
				printf("Time needed for open chaining : %f\n", TimeTaken);
			}

			break;
		}
		if (choice == 6)
		{
			break;
		}

	}

	unload(table);
	return;

}

void Probing()
{
	int choice;
	node* table[N];//to be
	nullify(table);
	printf("Enter the number of students: ");
	int num_nodes;
	if (scanf_s("%i", &num_nodes) == 0)
		return ;
	//hash_size = num_nodes;
	printf("1:Linear probing\n2:Quad probing\n");
	if (scanf_s("%i", &choice) == 0)
		return ;
	if (choice == 1)
	{
		for (int i = 0; i < num_nodes; i++)
		{
			addNode_b(table, 1,1);
		}
	}
	else if (choice == 2)
	{
		for (int i = 0; i < num_nodes; i++)
		{
			addNode_b(table, 2,1);
		}
	}
	else
		return ;
	printf("Size : %i\n", num_nodes * sizeof(node));
	//print_table(table);
	int op;
	while (1)
	{
		printf("1: print table\n2: Insert an element with linear probing\n3: Insert an element with quad probing\n4: Find a certain element\n5: Time comlpexity for linear probing\n6: Time comlpexity for quad probing \n7: Remove an element\n8: Exit\n");
		scanf_s("%i", &op);
		if (op == 1)
			print_table(table);
		if (op == 2)
			addNode_b(table, 1,1);
		if (op == 3)
			addNode_b(table, 2,1);
		if (op == 4)
			findhash_b(table, 1);
		if (op == 7)
			remove_b(table, 1);
		if (op == 5)
		{
			
			clock_t start;
			clock_t end;
			for (int i = 0; i < 50000; i++)
			{
				start = clock();
				addNode_b(table, 1, 2);
				end = clock();
				double TimeTaken = (double)(end - start) / CLOCKS_PER_SEC;
				printf("Time needed for linear probing : %f\n", TimeTaken);
			}
		}
		if (op == 6)
		{
			clock_t start;
			clock_t end;
			for (int i = 0; i < 50000; i++)
			{
				start = clock();
				addNode_b(table, 2, 2);
				end = clock();
				double TimeTaken = (double)(end - start) / CLOCKS_PER_SEC;
				printf("Time needed for quad probing : %f\n", TimeTaken);
			}
			

		}
		if (op == 8)
			return;
	}
}

