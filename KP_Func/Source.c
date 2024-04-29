#define _CRT_SECURE_NO_WARNINGS
#include <locale.h> //����������� ���������
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

typedef double(*func) (double); //����������� ���� ��������� �� �������
double fact(int x); //��������� x!
double f1(double x); //������ ������� Y(x)
double f2(double x); //������ ������� V(x)
double f3e(double x); //������ ������� S(x,e) � ��������� e
double f3n(double x); //������ ������� S(x,n) � ������ ������ ���� n
double* tabl_func(func f, double xmin, double xmax, double dx); //��������� �������
double* make_xmass(func f, double xmin, double xmax, double dx); //�������� ������� �������� x
int print_console(double* xmass, double* ymass); //����� ������� � �������
int print_file(double* xmass, double* ymass); //����� ������� � ����
int bubble_sort(double* xmass, double* ymass, char d); //���������� ������� ����������� �������
int insertion_sort(double* xmass, double* ymass, char d); //���������� ������� ������� �������
int selection_sort(double* xmass, double* ymass, char d); //���������� ������� ����������� �������
int find_element(double* xmass, double* ymass); //����� ��������

const double e = 0.001; //�������� ��� 3 �������
int n; //���������� ������ ���� ��� 3 �������

int main() {
	char f = NULL, ans = NULL, dep = NULL; //��������� �������, �����������, ��������� �����, �������� �����
	double a = 0, b = 0, dx = 0; //������, ����� � ��� ���������
	double* ymass = NULL; //������ y
	double* xmass = NULL; //������ x

	system("chcp 1251");
	system("cls");

	do
	{
		system("cls");
		printf("1. ������� �������\n2. ������ ��������\n3. ���������\n4. ����������\n5. �����\n6. ���������\n7. �����\n\n");
		scanf("%c", &ans);
		switch (ans) {
		case '1': printf("�������� ����� ������� (1-3): ");
			scanf(" %c", &f);
			break;
		case '2': printf("������� ������ � ����� ���������: ");
			scanf(" %lf %lf", &a, &b);
			printf("������� ���: ");
			scanf(" %lf", &dx);
			break;
		case '3': switch (f) {
		case '1': ymass = tabl_func(f1, a, b, dx); xmass = make_xmass(f1, a, b, dx); break;
		case '2': ymass = tabl_func(f2, a, b, dx); xmass = make_xmass(f2, a, b, dx); break;
		case '3': printf("�� ���� ������� �������?\n1)���������� ������ ����\n2)��������\n");
			scanf(" %c", &dep);
			if (dep == '1') {
				ymass = tabl_func(f3n, a, b, dx);
				xmass = make_xmass(f3n, a, b, dx);
			}
			else if (dep == '2') {
				ymass = tabl_func(f3e, a, b, dx);
				xmass = make_xmass(f3e, a, b, dx);
			}
			else {
				printf("������ �����!\n"); system("pause");
			}
			break;
		default: printf("�� �� ������� �������!\n");
			system("pause");
			continue;
		}
				print_console(xmass, ymass);
				system("pause");
				break;
		case '4': if (ymass == NULL) {
			printf("������� ��������� ��������� �������!\n");
			system("pause");
			continue;
		}
				printf("1. �� �����������\n2. �� ��������\n");
				scanf(" %c", &dep);
				printf("1. ����������� �����\n2. ����� �������\n3. ����� ������� ������\n");
				scanf(" %c", &ans);
				switch (ans) {
				case '1': bubble_sort(xmass, ymass, dep); break;
				case '2': insertion_sort(xmass, ymass, dep); break;
				case '3': selection_sort(xmass, ymass, dep); break;
				default: printf("�������� ����!");
				}
				print_console(xmass, ymass);
				system("pause");
				break;
		case '5': if (ymass == NULL) {
			printf("������� ��������� ��������� �������!\n");
			system("pause");
			continue;
		}
				bubble_sort(xmass, ymass, '1');
				find_element(xmass, ymass);
				system("pause");
				break;
		case '6': if (ymass == NULL) {
			printf("������� ��������� ��������� �������!\n");
			system("pause");
			continue;
		}
				print_file(xmass, ymass);
				system("pause");
				break;
		case '7': printf("�� ������������� ������ �����? (0 - ���, 1 - ��)\n");
			scanf(" %c", &ans);
			if (ans == '1') {
				return 1;
			}
		default: break;
		}
	} while (ans != 7);
}

double fact(int x) {
	if (x < 0) return 0;
	if (x == 0) return 1;
	else
		return x * fact(x - 1);
}
/*
double f1(double x) {
	return (x * x) - 3.14 * x * cos(3.14 * x);
}
*/
double f1(double x) {
	double p, q;
	p = 0.000001 * sin(pow(x, 2) + pow(x, -1) + pow(x, 1.0 / 3.0));
	q = tan(exp(cos(sqrt(x))));
	//printf("\t%5.3lf\t %5.3lf\t", p, q);
	if (q != 0) return p / q;
	else return -1.0;
}
double f2(double x) {
	double s = 0.0;
	if (x > 0.0) {
		for (int k = 0; k <= 4; k++)
		{
			s += pow(x, k) / (double)fact(k) - 5;

		}
		return cos(s);
	}
	else {
		return exp(x) * atan(x);
	}

}

double f3e(double x) {
	double sum = x, a = 0, b = x, p = 1, q = 1, sign;
	int i = 0;
	while (fabs(a - b) > e) {
		b = a;
		sign = pow(-1, i);
		p = sign * (pow(x, 2 * i) * (2 * i + 1));
		q = fact(2 * i);
		a = p / q;
		sum += a;
		//printf("%5.3lf\t %5.3lf\t %5.3lf\t", sign, p, q);
		i++;
	};
	printf("\r\n");
	return sum;
}

double f3n(double x) {
	double sum = x, p = 1.0, q = 1.0, sign;
	for (int i = 0; i < n; i++) {
		sign = pow(-1, i);
		p = sign * (pow(x, 2 * i) * (2 * i + 1));
		q = fact(2 * i);
		sum += (p / q);
	}
	return sum;
}

double* tabl_func(func f, double xmin, double xmax, double dx) {
	n = fabs(xmax - xmin) / dx + 1;
	double* mass = (double*)malloc(n * sizeof(double));
	int i = 0;
	for (double x = xmin; x <= xmax; x += dx, i++)
	{
		mass[i] = f(x);
	}
	return mass;
}

double* make_xmass(func f, double xmin, double xmax, double dx) {
	double* xmass = (double*)malloc((n + 1) * sizeof(double));
	int i = 0;
	for (double x = xmin; x <= xmax; x += dx, i++) {
		xmass[i] = x;
	}
	return xmass;
}

int print_console(double* xmass, double* ymass) {
	printf("|   x   |   y   |\n");
	for (int i = 0; i < n; i++) {
		printf("|%7.3lf |%7.3lf |\n", xmass[i], ymass[i]);
	}
	return 1;
}

int print_file(double* xmass, double* ymass) {
	FILE* out;
	char fname[50];
	printf("������� ��� �����: ");
	scanf(" %s", fname);
	out = fopen(fname, "wb");
	if (out == NULL) {
		printf("�� ������� ������� ����!");
		system("pause");
		return 0;
	}
	fprintf(out, "| x | y |\n");
	for (int i = 0; i < n; i++) {
		fprintf(out, "|%7.2lf |%7.2lf |\r\n", xmass[i], ymass[i]);
	}
	fclose(out);
	printf("���� ������� �������!\n");
	return 1;
}

int bubble_sort(double* xmass, double* ymass, char d) {
	for (int i = 1; i < n; i++) {
		for (int j = i; j > 0; j--) {
			if (d == '1' && ymass[j] < ymass[j - 1] || d == '2' && ymass[j] > ymass[j - 1]) {
				double tmp = ymass[j];
				ymass[j] = ymass[j - 1];
				ymass[j - 1] = tmp;
				tmp = xmass[j];
				xmass[j] = xmass[j - 1];
				xmass[j - 1] = tmp;
			}
		}
	}
	return 1;
}

int insertion_sort(double* xmass, double* ymass, char d) {
	double new_element, new_xelement;
	int location;
	for (int i = 1; i < n; i++) {
		new_element = ymass[i];
		new_xelement = xmass[i];
		location = i - 1;
		while (location >= 0 && (d == '1' && ymass[location] > new_element || d == '2' && ymass[location] < new_element)) {
			ymass[location + 1] = ymass[location];
			xmass[location + 1] = xmass[location];
			location = location - 1;
		}
		ymass[location + 1] = new_element;
		xmass[location + 1] = new_xelement;
	}
	return 1;
}

int selection_sort(double* xmass, double* ymass, char d) {
	double temp;
	int min;
	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (int j = i + 1; j < n; j++) {
			if (d == '1' && ymass[j] < ymass[min] || d == '2' && ymass[j]>ymass[min]) {
				min = j;
			}
		}
		temp = ymass[i];
		ymass[i] = ymass[min];
		ymass[min] = temp;
	}
	return 1;
}

int find_element(double* xmass, double* ymass) {
	int ind;
	char ans;
	printf("��� ����� �����?\n1. ������������ ��������\n2. ����������� ��������\n3. ����������� �������� (�������)\n\n");
	scanf(" %c", &ans);
	switch (ans) {
	case '1': ind = n - 1; break;
	case '2': ind = 0; break;
	case '3':
		ind = n / 2;
		break;
	default: printf("�������� ����!\n"); return 0;
	}
	if (ind != -1) {
		printf("������� ��������: %.2lf\n", ymass[ind]);
		return 1;
	}
	else {
		printf("�������� �� �������\n");
		return 0;
	}
}
