#include <iostream>
#include <iomanip>
using namespace std;

void Depth_First_Search(int n, int** Graph, bool* Visited, int Node);
void Breadth_First_Search(int n, int** Graph, bool* Visited, int Node);
void Dijkstra(int n, int** Graph, int Node);
void Floyd(int n, int** Graph);

int main()
{
	system("chcp 1251");
	system("cls");

	int n;
	cout << "Введите количество узлов: ";
	cin >> n;

	//Инициализация двумерного динамического массива
	int** Graph = new int* [n];
	for (int i = 0; i < n; i++)
		Graph[i] = new int[n]();

	char answer;
	cout << "\nВыберите тип графа: (u - неориентированный / o - ориентированный)";
	cin >> answer;
	
	//Заполнение матрицы смежности
	switch (answer)
	{
	case 'u':
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
			{
				cout << i + 1 << " > " << j + 1 << ": ";
				cin >> Graph[i][j];
				Graph[j][i] = Graph[i][j];
			}
		cout << endl << "  ";
		break;
	case 'o':
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				cout << i + 1 << " > " << j + 1 << ": ";
				cin >> Graph[i][j];
			}
		cout << endl << "  ";
		break;
	default:
		break;
	}
	
	//Вывод матрицы смежности на экран
	for (int i = 0; i < n; i++)
		cout << setw(4) << i + 1;
	cout << endl << "  ";
	for (int i = 0; i < (n * 4 + 1); i++)
		cout << "_";
	for (int i = 0; i < n; i++)
	{
		cout << endl << i + 1 << " |";
		for (int j = 0; j < n; j++)
			cout << setw(4) << Graph[i][j];
	}

	//Поиск в глубину
	cout << endl << endl << "Поиск в глубину:" << endl;
	bool* Visited = new bool[n]();
	Depth_First_Search(n, Graph, Visited, 0);

	//Поиск в ширину
	cout << endl << "Поиск в ширину:" << endl;
	for (int i = 0; i < n; i++)
		Visited[i] = false;
	Breadth_First_Search(n, Graph, Visited, 0);

	//Алгоритм Дейкстры
	cout << endl << "Алгоритм Дейкстры:" << endl;
	Dijkstra(n, Graph, 0);

	//Алгоритм Флойда
	cout << endl << "Алгоритм Флойда:" << endl;
	Floyd(n, Graph);

	//Освобождение памяти
	for (int i = 0; i < n; i++)
		delete[] Graph[i];
	delete[] Graph;
	delete[] Visited;

	system("pause");
	return 0;
}

void Depth_First_Search(int n, int** Graph, bool* Visited, int Node)
{
	Visited[Node] = true;
	cout << "Посещённый узел: " << Node + 1 << endl;

	for (int i = 0; i < n; i++)
		if (Graph[Node][i] && !Visited[i])
			Depth_First_Search(n, Graph, Visited, i);
}

void Breadth_First_Search(int n, int** Graph, bool* Visited, int Node)
{
	int* List = new int[n](); //очередь
	int Count = 0, Head = 0;  //указатели очереди
	int i;

	//помещение в очередь вершины Node
	List[Count++] = Node;
	Visited[Node] = true;

	while (Head < Count)
	{
		//взятие вершины из очереди
		Node = List[Head++];
		cout << "Посещённый узел: " << Node + 1 << endl;

		//просмотр всех вершин, связанных с вершиной Node
		for (i = 0; i < n; i++)
			//если вершина ранее не просмотрена
			if (Graph[Node][i] && !Visited[i])
			{
				//заносим ее в очередь
				List[Count++] = i;
				Visited[i] = true;
			}
	}

	delete[] List;
}

void Dijkstra(int n, int** Graph, int Node)
{
	bool* Selected = new bool[n];
	int* Distance = new int[n];
	int* Path = new int[n];
	int i, j, Max_Sum = 0;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			Max_Sum += Graph[i][j];

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (Graph[i][j] == 0)
				Graph[i][j] = Max_Sum;

	for (i = 0; i < n; i++)
	{
		Selected[i] = false;
		Path[i] = Node;
		Distance[i] = Graph[Node][i];
	}

	Selected[Node] = true;
	Path[Node] = -1;

	for (i = 0; i < n - 1; i++)
	{
		int w = 0;
		for (j = 1; j < n; j++)
		{
			if (!Selected[w])
			{
				if (!Selected[j] && Distance[j] <= Distance[w])
					w = j;
			}
			else w++;
		}

		Selected[w] = true;

		for (j = 1; j < n; j++)
			if (!Selected[j])
				if (Distance[w] + Graph[w][j] < Distance[j])
				{
					Distance[j] = Distance[w] + Graph[w][j];
					Path[j] = w;
				}
	}

	cout << "Начальный узел: " << Node + 1 << endl;
	for (i = 0; i < n; i++)
		cout << setw(5) << i + 1;
	cout << endl;
	for (i = 0; i < (n * 5 + 1); i++)
		cout << "_";
	cout << endl;

	for (i = 0; i < n; i++)
		cout << setw(5) << Distance[i];
	cout << endl;
	
	for (i = 0; i < n; i++)
		cout << setw(5) << Path[i] + 1;
	cout << endl;
	
	delete[] Path;
	delete[] Distance;
	delete[] Selected;
}

void Floyd(int n, int** Graph)
{
	int i, j, k, Max_Sum = 0;
	
	int** ShortestPath = new int* [n];
	for (i = 0; i < n; i++)
		ShortestPath[i] = new int[n]();

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (i != j)
				ShortestPath[i][j] = Graph[i][j];
	
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			Max_Sum += ShortestPath[i][j];
	
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (ShortestPath[i][j] == 0 && i != j)
				ShortestPath[i][j] = Max_Sum;
	
	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if ((ShortestPath[i][k] + ShortestPath[k][j]) < ShortestPath[i][j])
					ShortestPath[i][j] = ShortestPath[i][k] + ShortestPath[k][j];

	cout << "  ";
	for (i = 0; i < n; i++)
		cout << setw(4) << i + 1;
	cout << endl << "  ";
	for (i = 0; i < (n * 4 + 1); i++)
		cout << "_";
	for (i = 0; i < n; i++)
	{
		cout << endl << i + 1 << " |";
		for (int j = 0; j < n; j++)
			cout << setw(4) << ShortestPath[i][j];
	}
	cout << endl;

	for (i = 0; i < n; i++)
		delete[] ShortestPath[i];
	delete[] ShortestPath;
}