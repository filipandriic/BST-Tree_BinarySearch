#include<stdio.h>
#include<stdlib.h>
#define MAX 100
#define COUNT 10

typedef struct node {
	int value;
	struct node *left;
	struct node *right;
	struct node *next;
	int low;
	int high;
} Node;

void MakeTable(int tableArray[], int validArray[], int keyArray[], int n, int m, int factor) {
	int p = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < factor; j++) {
			tableArray[p] = keyArray[i];
			if (j == 0)
				validArray[p] = 1;
			else
				validArray[p] = 0;
			p++;
		}
	}
}

int BinarySearch(int tableArray[], int validArray[], int key, int n) {
	int low = 0, high = 1;
	int value = tableArray[0];

	while (value < key) {
		low = high;
		high *= 2;
		if (high > (n - 1))
			high = n - 1;
		if (low == (n - 1))
			return high;
		value = tableArray[high];
	}

	int mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (key == tableArray[mid]) {
			if (validArray[mid] == 1) {
				printf("Element vec postoji.\n");
				return -1;
			}
			else {
				int i = mid;
				while (tableArray[i] == key)
					i--;

				i++;
				if (validArray[i] == 0)
					return i;
				else
					return -1;
			}
		}
		else
			if (key < tableArray[mid])
				high = mid - 1;
			else
				low = mid + 1;
	}
	return mid;
}

int CheckAvailability(int validArray[], int n) {
	for (int i = 0; i < n; i++)
		if (validArray[i] == 0)
			return 1;
	return -1;
}

void AddElement(int tableArray[], int validArray[], int keyArray[], int m, int position, int key, int n) {
	int right = 1;
	if (validArray[position] == 0) {
		tableArray[position] = key;
		validArray[position] = 1;
		if ((tableArray[position + 1] < tableArray[position]) && (position != (n - 1))) {
			int i = position;
			while (tableArray[i + 1] < tableArray[i]) {
				tableArray[i + 1] = tableArray[i];
				i++;
			}
		}
	}
	else {
		int i = position;
		while (validArray[i] != 0) {
			i++;
			if (i > (n - 1)) {
				right = 0;
				break;
			}
		}

		if (right == 1) {
			validArray[i] = 1;
			if (key > tableArray[position])
				position++;
			while (i != position) {
				tableArray[i] = tableArray[i - 1];
				i--;
			}
		}
		else {
			while (validArray[i] != 0)
				i--;
			validArray[i] = 1;
			if (key < tableArray[position])
				position--;
			while (i != position) {
				tableArray[i] = tableArray[i + 1];
				i++;
			}
		}
		tableArray[position] = key;
	}
}

int BinaryLocating(int tableArray[], int key, int n) {
	int low = 0, high = 1;
	int value = tableArray[0];

	while (value < key) {
		low = high;
		high *= 2;
		if (high > (n - 1))
			high = n - 1;
		if (low == (n - 1))
			return high;
		value = tableArray[high];
	}

	int mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (key == tableArray[mid]) {
			return mid;
		}
		else
			if (key < tableArray[mid])
				high = mid - 1;
			else
				low = mid + 1;
	}
	return -1;
}

void EraseElement(int validArray[], int position) {
	validArray[position] = 0;
}

void Sort(int arr[], int n) {
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (arr[i] > arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
}

void Print(int arr[], int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
}

void Push(Node*** first, Node*** last, Node* cvor) {
	Node* temp = cvor;

	if (**first == NULL) {
		**first = temp;
		**last = temp;
	}
	else {
		(*(*last))->next = temp;
		**last = temp;
	}
}

Node* Pop(Node*** first, Node*** last) {
	Node* temp = **first;

	if (**first == **last) {
		**first = NULL;
		**last = NULL;
	}
	else {
		while (temp->next != **last)
			temp = temp->next;
		**last = temp;
		temp = temp->next;
		(*(*last))->next = NULL;
	}
	return temp;
}

Node* CreateStable(int keyArray[], int m, Node** first, Node** last) {
	int low = 0;
	int high = m - 1;

	int mid = (low + high) / 2;
	Node* root = malloc(sizeof(Node));
	root->value = keyArray[mid];
	root->next = NULL;
	root->left = NULL;
	root->right = NULL;

	Node* next = root;
	next->low = mid + 1;
	next->high = high;

	Push(&first, &last, next);
	high = mid - 1;
	while (low <= high) {
		next->left = malloc(sizeof(Node));
		next = next->left;
		mid = (low + high) / 2;
		next->value = keyArray[mid];
		next->next = NULL;
		next->left = NULL;
		next->right = NULL;
		next->low = mid + 1;
		next->high = high;
		Push(&first, &last, next);
		high = mid - 1;
	}
	next->left = NULL;

	while (*first != NULL) {
		next = Pop(&first, &last);
		low = next->low;
		high = next->high;

		if (low <= high) {
			next->right = malloc(sizeof(Node));
			next = next->right;
			mid = (low + high) / 2;
			next->value = keyArray[mid];
			next->next = NULL;
			next->left = NULL;
			next->right = NULL;
			next->low = mid + 1;
			next->high = high;
			Push(&first, &last, next);
			high = mid - 1;

			while (low < high) {
				next->left = malloc(sizeof(Node));
				next = next->left;
				mid = (low + high) / 2;
				next->value = keyArray[mid];
				next->next = NULL;
				next->left = NULL;
				next->right = NULL;
				next->low = mid + 1;
				next->high = high;
				Push(&first, &last, next);
				high = mid - 1;
			}

			next->left = NULL;
		}
		else
			next->right = NULL;
	}
	return root;
}

void InsertInStable(Node** root, int key) {
	Node* p = *root;
	Node* q = NULL;
	Node* add = malloc(sizeof(Node));
	add->left = NULL;
	add->right = NULL;
	add->next = NULL;
	add->value = key;

	while (p != NULL) {
		q = p;
		if (add->value == p->value) {
			printf("Kljuc vec postoji.\n");
			break;
		}
		else {
			if (add->value < p->value)
				p = p->left;
			else
				p = p->right;
		}
	}

	if (q == NULL)
		*root = add;
	else {
		if (add->value < q->value)
			q->left = add;
		else
			q->right = add;
	}
}

Node* SearchInStable(Node* root, int key) {
	Node* p = root;

	while ((p != NULL) && (key != p->value)) {
		if (key < p->value)
			p = p->left;
		else
			p = p->right;
	}

	if (p != NULL)
		printf("Pronadjen je element.\n");
	else
		printf("Nije pronadjen element.\n");

	return p;
}

Node* FindParent(Node* root, int key, int* left) {
	Node* p = root;
	Node* q = NULL;

	while ((p != NULL) && (key != p->value)) {
		q = p;
		if (key < p->value)
			p = p->left;
		else
			p = p->right;
	}

	if (p != NULL) {
		printf("Pronadjen je element.\n");
		if (q->left == p)
			*left = 1;
	}
	else
		printf("Nije pronadjen element.\n");

	return q;
}

void print2DUtil(Node* root, int space) {
	// Base case 
	if (root == NULL)
		return;

	// Increase distance between levels 
	space += COUNT;

	// Process right child first 
	print2DUtil(root->right, space);

	// Print current node after space 
	// count 
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%d\n", root->value);

	// Process left child 
	print2DUtil(root->left, space);
}

void print2D(Node *root)
{
	if (root == NULL)
		printf("Stablo izbrisano.\n");
	// Pass initial space count as 0 
	print2DUtil(root, 0);
}

void DeleteTreeElement(Node** root, int key) {
	Node* p = *root;
	Node* q = NULL;
	Node* rp = NULL;
	Node* f = NULL;
	Node* s = NULL;

	while ((p != NULL) && (key != p->value)) {
		q = p;
		if (key < p->value)
			p = p->left;
		else
			p = p->right;
	}

	if (p->left == NULL)
		rp = p->right;
	else
		if (p->right == NULL)
			rp = p->left;
		else {
			f = p;
			rp = p->right;
			s = rp->left;
			while (s != NULL) {
				f = rp;
				rp = s;
				s = rp->left;
			}

			if (f != p) {
				f->left = rp->right;
				rp->right = p->right;
			}
			rp->left = p->left;
		}
	if (q == NULL)
		*root = rp;
	else
		if (p == q->left)
			q->left = rp;
		else
			q->right = rp;

	free(p);
}

void Insert(Node*** first, Node*** last, Node* cvor) {
	Node* temp = cvor;

	if (**first == NULL) {
		**first = temp;
		**last = temp;
	}
	else {
		(*(*last))->next = temp;
		**last = temp;
	}
}

Node* Delete(Node*** first, Node*** last) {
	Node* temp = **first;

	if (**first == **last) {
		**first = NULL;
		**last = NULL;
	}
	else
		**first = (*(*first))->next;

	return temp;
}



void LevelOrder(Node** first, Node** last, Node* root) {
	Node* next = root;
	Insert(&first, &last, next);
	int endline = 1;
	int numNodes = 0;

	while (*first != NULL) {
		next = Delete(&first, &last);
		numNodes++;

		printf("%d ", next->value);
		if (numNodes == endline) {
			numNodes = 0;
			printf("\n");
			endline *= 2;
		}

		if (next->left != NULL)
			Insert(&first, &last, next->left);
		if (next->right != NULL)
			Insert(&first, &last, next->right);
	}
}

int main() {
	int keyArray[MAX], tableArray[MAX], validArray[MAX];
	int n, factor, m, key, position, choice, choice2;

	Node* root = NULL;
	Node* first = NULL;
	Node* last = NULL;

	printf("Unesi broj kljuceva: ");
	scanf("%d", &m);

	printf("Unesi kljuceve: ");
	for (int i = 0; i < m; i++)
		scanf("%d", &keyArray[i]);

	printf("Unesi faktor uvecanja: ");
	scanf("%d", &factor);

	n = m * factor;
	Sort(keyArray, m);
	printf("Vasi kljucevi: ");
	Print(keyArray, m);
	printf("\n");

	while (1) {
		printf("       MENU\n"
			"1. Napravite povecanu tabelu i bitove validnosti.\n"
			"2. Umetanje kljuca.\n"
			"3. Pretraga kljuca.\n"
			"4. Brisanje kljuca.\n"
			"5. Napravi BST.\n"
			"0. Napusti program.\n");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			MakeTable(tableArray, validArray, keyArray, n, m, factor);

			printf("\n");
			Print(tableArray, n);
			printf("\n");
			Print(validArray, n);
			printf("\n");
			break;

		case 2:
			printf("Koji broj zelite? ");
			scanf("%d", &key);

			int available = CheckAvailability(validArray, n);
			if (available == 1) {
				keyArray[m] = key;
				m++;
				position = BinarySearch(tableArray, validArray, key, n);
				if (position != -1)
					AddElement(tableArray, validArray, keyArray, m, position, key, n);
			}
			else {
				factor = 2;
				n = m * factor;
				Sort(keyArray, m);
				MakeTable(tableArray, validArray, keyArray, n, m, factor);
				position = BinarySearch(tableArray, validArray, key, n);
				if (position != -1)
					AddElement(tableArray, validArray, keyArray, m, position, key, n);
			}

			printf("\n");
			Print(tableArray, n);
			printf("\n");
			Print(validArray, n);
			printf("\n");
			break;

		case 3:
			printf("Koji broj zelite? ");
			scanf("%d", &key);

			position = BinaryLocating(tableArray, key, n);
			if (validArray[position] == 0) {
				int i = position;
				while (tableArray[i] == tableArray[position])
					i--;
				if (validArray[i + 1] == 0)
					position = -1;
				else
					position = i + 1;
			}

			if (position != -1)
				printf("Vas element je na poziciji %d.\n", position);
			else
				printf("Element ne postoji.\n");

			printf("\n");
			Print(tableArray, n);
			printf("\n");
			Print(validArray, n);
			printf("\n");
			break;

		case 4:
			printf("Koji broj zelite? ");
			scanf("%d", &key);

			position = BinaryLocating(tableArray, key, n);
			if (validArray[position] == 0) {
				int i = position;
				while (tableArray[i] == tableArray[position])
					i--;
				if (validArray[i + 1] == 0)
					position = -1;
				else
					position = i + 1;
			}

			if (position != -1)
				EraseElement(validArray, position);
			else
				printf("Element ne postoji.\n");

			printf("\n");
			Print(tableArray, n);
			printf("\n");
			Print(validArray, n);
			printf("\n");
			break;

		case 5:
			//Make stable
			root = CreateStable(keyArray, m, &first, &last);

			while (1) {
				printf("       MENU\n"
					"1. Pretraga kljuca u stablu.\n"
					"2. Umetanje kljuca u stablo.\n"
					"3. Ispisi stablo.\n"
					"4. Brisanje stabla.\n"
					"5. Rotacije.\n"
					"6. Ispisi stablo level orderom.\n"
					"0. Napusti program.\n");
				scanf("%d", &choice2);

				switch (choice2) {
				case 1:
					printf("Koji kljuc zelite? ");
					scanf("%d", &key);
					Node* x = SearchInStable(root, key);
					break;

				case 2:
					printf("Koji kljuc zelite? ");
					scanf("%d", &key);
					keyArray[m] = key;
					m++;
					InsertInStable(&root, key);
					break;

				case 3:
					print2D(root);
					break;
					
				case 4:
					Sort(keyArray, m);
					for (int i = 0; i < m; i++) {
						DeleteTreeElement(&root, keyArray[i]);
					}
					break;

				case 5:
					printf("\n");
					int choice3;
					printf("       MENU\n"
						"1. U levo.\n"
						"2. U desno.\n");
					scanf("%d", &choice3);
					switch (choice3) {
					case 1:
						printf("Oko kog cvora je rotacija? ");
						scanf("%d", &key);
						Node* x = SearchInStable(root, key);
						int left = 0;
						Node* q = FindParent(root, x->value, &left);
						Node* y = x->right;
						Node* temp = y->left;
						y->left = x;
						x->right = temp;
						if (x == root)
							root = y;
						else {
							if (left == 1)
								q->left = y;
							else
								q->right = y;
						}
						break;

					case 2:
						printf("Oko kog cvora je rotacija? ");
						scanf("%d", &key);
						x = SearchInStable(root, key);
						left = 0;
						q = FindParent(root, x->value, &left);
						y = x->left;
						temp = y->right;
						y->right = x;
						x->left = temp;
						if (x == root)
							root = y;
						else {
							if (left == 1)
								q->left = y;
							else
								q->right = y;
						}
						break;
					}
					break;

				case 6:
					LevelOrder(&first, &last, root);
					break;

				case 0:
					printf("Dovidjenja.\n");
					exit(0);
					break;
				}
			}
			break;

		case 0:
			printf("Dovidjenja.\n");
			exit(0);
			break;
		}
	}
}