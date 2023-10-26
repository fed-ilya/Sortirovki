#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

int* vvod(int n)
{
	int* mas;
	mas = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		mas[i] = rand() % 101;
	}
	return mas;
}

int* copy(int* p, int n) {
	int* mas;
	mas = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		mas[i] = p[i];
	}
	return mas;
}

void print_mas(int* mas, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%i ", mas[i]);
	}
	printf("\n");
}

int lin_search(int mas[], int size, int a, int* ks) //Линейный поиск
{
	clock_t begin, end;
	begin = clock();
	*ks = 0;
	for (int i = 0; i < size; i++)
	{
		(*ks)++;
		if (mas[i] == a)
		{
			end = clock();
			printf("time = %f\n", (end - begin) / (float)CLOCKS_PER_SEC);
			printf("Количество сравнений- %i\n", *ks);
			return i;
		}
	}
	end = clock();
	printf("time = %f\n", (end - begin) / (float)CLOCKS_PER_SEC);
	printf("Количество сравнений- %i\n", *ks);
	return -1;
}

int bin_search(int mas[], int size, int a, int* f, int* ks) //Бинарный поиск
{
	clock_t begin, end;
	begin = clock();
	int r = size - 1, l = 0;
	*ks = 0;
	while (l <= r)
	{
		int mid = (l + r) / 2;
		(*ks)++;
		if (mas[mid] == a)
		{
			*f = mid;
			end = clock();
			printf("time = %f\n", (end - begin) / (float)CLOCKS_PER_SEC);
			printf("Количество сравнений- %i\n", *ks);
			return 1;
		}
		else
		{
			(*ks)++;
			if (mas[mid] > a)
			{
				r = mid - 1;
				*f = mid;
			}
			else
			{
				l = mid + 1;
				*f = mid + 1;
			}
		}
	}
	end = clock();
	printf("time = %f\n", (end - begin) / (float)CLOCKS_PER_SEC);
	printf("Количество сравнений- %i\n", *ks);
	return 0;
}

void swap(int* a, int* b)
{
	int c;
	c = *a;
	*a = *b;
	*b = c;
}

void sort_bubble(int* mas, int n, int *ks, int *ko) //Сортировка пузырьком
{
	clock_t begin, end;
	begin = clock();
	*ks = 0;
	*ko = 0;
	for (int i = 0; i < n; i++)
	{
		int flag = 0;
		for (int j = 0; j < n - i - 1; j++)
		{
			(*ks)++;
			if (mas[j] > mas[j + 1])
			{
				swap(&mas[j], &mas[j + 1]);
				(*ko)++;
				flag = 1;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}
	end = clock();
	printf("time = %f\n", (end - begin) / (float) CLOCKS_PER_SEC);
	printf("Количество сравнений- %i\nКоличество обменов- %i\n", *ks, *ko);
}

void sort_select(int* mas, int n, int* ks, int* ko) //Сортировка выбором
{
	clock_t begin, end;
	begin = clock();
	int pos, mini;
	*ks = 0;
	*ko = 0;
	for (int i = 0; i < n; i++)
	{
		mini = mas[i];
		pos = i;
		for (int j = i; j < n; j++)
		{
			(*ks)++;
			if (mas[j] < mini)
			{
				mini = mas[j];
				(*ko)++;
				pos = j;
			}
		}
		swap(&mas[i], &mas[pos]);
	}
	end = clock();
	printf("time = %f\n", (end - begin) / (float)CLOCKS_PER_SEC);
	printf("Количество сравнений- %i\nКоличество обменов- %i\n", *ks, *ko);
}

void sort_ins(int* mas, int n, int* ks, int* ko) //Сортировка вставками
{
	clock_t begin, end;
	begin = clock();
	int pos;
	*ks = 0;
	*ko = 0;
	for (int i = 1; i < n; i++)
	{
		pos = i;
		int l = 0, r = i - 1;
		while(l <= r)
		{
			int mid = (l + r) / 2;
			(*ks)++;
			if (mas[i] < mas[mid])
			{
				pos = mid;
				r = mid - 1;
			}
			else
			{
				l = mid + 1;
			}
		}
		int q = mas[i];
		for (int j = i; j > pos; j--)
		{
			(*ko)++;
			mas[j] = mas[j - 1];
		}
		(*ko)++;
		mas[pos] = q;
	}
	end = clock();
	printf("time = %f\n", (end - begin) / (float)CLOCKS_PER_SEC);
	printf("Количество сравнений- %i\nКоличество обменов- %i\n", *ks, *ko);
}

void sort_podschet(int* mas, int size, int* ks, int* ko) //Сортировка подсчётом(только для int, для отрицательных)
{
	clock_t begin, end;
	begin = clock();
	*ks = 0;
	*ko = 0;
	int min = mas[0], max = mas[0], razmer;
	for (int i = 0; i < size; i++)
	{
		if (mas[i] > max) max = mas[i];
		if (mas[i] < min) min = mas[i];
	}
	razmer = abs(max) + abs(min) + 1;
	int* p;
	p = (int*)malloc((razmer)*(sizeof(int)));
	for (int i = 0; i < razmer; i++) p[i] = 0;
	for (int i = 0; i < size; i++) p[mas[i]+abs(min)]++;
	int k = 0;
	for (int i = 0; i < razmer; i++)
	{
		for (int j = 0; j < p[i]; j++)
		{
			mas[k] = i - abs(min);
			(*ko)++;
			k++;
		}
	}
	free(p);
	end = clock();
	printf("time = %f\n", (end - begin) / (float)CLOCKS_PER_SEC);
	printf("Количество сравнений- %i\nКоличество обменов- %i\n", *ks, *ko);
}

void sort_quick(int* mas, int first, int last, int* ks, int* ko) //Быстрая сортировка
{
	int mid, tmp;
	int f = first, l = last;
	mid = mas[(f + l) / 2]; //Вычисление опорного элемента
	while (f < l) //Раскидывает направо элементы > mid, налево- < mid
	{
		while (mas[f] < mid) {
			f++;
			(*ks)++;
		}
		(*ks)++; //Последнее сравнение в while не сосчиталось

		while (mas[l] > mid) {
			l--;
			(*ks)++;
		}
		(*ks)++; //Последнее сравнение в while не сосчиталось

		if (f <= l) //Перестановка элементов
		{
			tmp = mas[f];
			mas[f] = mas[l];
			mas[l] = tmp;
			(*ko)++;
			f++;
			l--;
		}
	}
	if (first < l) sort_quick(mas, first, l, ks, ko);
	if (f < last) sort_quick(mas, f, last, ks, ko);
}

void merge(int mas1[], int left, int mid, int right, int* ks, int* ko)
{
	int* mas2;
	mas2 = (int*)malloc((right - left + 1) * sizeof(int));
	int i = left, j = mid + 1, k = 0;
	while (i <= mid && j <= right)
	{
		(*ks)++;
		if (mas1[i] < mas1[j])
		{
			mas2[k] = mas1[i]; i++; k++;
		}
		else
		{
			mas2[k] = mas1[j]; j++; k++;
		}
	}
	if (i > mid)
		while (j <= right)
		{
			mas2[k] = mas1[j]; j++; k++;
		}
	else
		while (i <= mid)
		{
			mas2[k] = mas1[i]; i++; k++;
		}
	k = 0;
	for (i = left; i <= right; i++)
	{
		(*ko)++;
		mas1[i] = mas2[k];
		k++;
	}
	free(mas2);
}

void sort_merge(int* mas1, int left, int right, int* ks, int* ko)
{
	if (left == right) return;
	int mid = (left + right) / 2;
	sort_merge(mas1, left, mid, ks, ko);
	sort_merge(mas1, mid + 1, right, ks, ko);
	merge(mas1, left, mid, right, ks, ko);
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	srand((unsigned int)time(NULL));
	clock_t begin, end;
	int n = 10, a, inahod, f = 0,  *p, *p1, *p_copy;
	int ko = 0, ks = 0; //ko - счётчик обменов, ks - счётчик сравнений
	p1 = (int*)malloc(n * sizeof(int));
	
	p = vvod(n);
	p_copy = copy(p, n);
	
	printf("Нажмите '1' - Сформировать массив\n");
	printf("Нажмите '2' - Вывести массив\n");
	printf("Нажмите '3' - Сортировка пузырьком\n");
	printf("Нажмите '4' - Сортировка выбором\n");
	printf("Нажмите '5' - Сортировка вставками\n");
	printf("Нажмите '6' - Сортировка подсчетом(Только для целых)\n");
	printf("Нажмите '7' - Быстрая сортировка\n");
	printf("Нажмите '8' - Сортировка слиянием\n");
	printf("Нажмите '9' - Линейный поиск\n");
	printf("Нажмите '0' - Бинарный поиск\n");

	while (1)
	{
		int kod;
		scanf_s("%i", &kod);
		switch (kod)
		{
		case 1: 
			free(p);
			free(p_copy);
			printf("Введите количество элементов в массиве\n");
			scanf_s("%i", &n);
			p = vvod(n);
			p_copy = copy(p, n);
			break;

		case 2: print_mas(p, n);
			break;

		case 3: p = copy(p_copy, n);
			sort_bubble(p, n, &ks, &ko);
			break;

		case 4: p = copy(p_copy, n);
			sort_select(p, n, &ks, &ko);
			break;

		case 5: p = copy(p_copy, n);
			sort_ins(p, n, &ks, &ko);
			break;

		case 6: p = copy(p_copy, n);
			sort_podschet(p, n, &ks, &ko);
			break;

		case 7: p = copy(p_copy, n);
			ks = 0; ko = 0;
			begin = clock();
			sort_quick(p, 0, n - 1, &ks, &ko);
			end = clock();
			printf("time = %f\n", (end - begin) / (float)CLOCKS_PER_SEC);
			printf("Количество сравнений- %i\nКоличество обменов- %i\n", ks, ko);
			break;

		case 8: p = copy(p_copy, n);
			ks = 0; ko = 0;
			begin = clock();
			sort_merge(p, 0, n - 1, &ks, &ko);
			end = clock();
			printf("time = %f\n", (end - begin) / (float)CLOCKS_PER_SEC);
			printf("Количество сравнений- %i\nКоличество обменов- %i\n", ks, ko);
			break;

		case 9: p = copy(p_copy, n);
			printf("Введите значение, которое нужно найти\n");
			scanf_s("%i", &a);
			inahod = lin_search(p, n, a, &ks);
			if (inahod != -1)
				printf("Искомое значение на %i индексе\n", inahod);
			else
			{
				printf("Искомого значения нет в массиве");
			}
			break;

		case 0: printf("Введите значение, которое нужно найти\n");
			scanf_s("%i", &a);
			sort_quick(p, 0, n - 1, &ks, &ko);
			inahod = bin_search(p, n, a, &f, &ks);
			if (inahod == 1)
				printf("Искомое значение на %i индексе\n", f);
			else
			{
				printf("Искомого значения нет в массиве, но его можно вставить на %i индекс\n", f);
			}
			break;
		}
	}
}