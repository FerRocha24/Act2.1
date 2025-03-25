// Fernando Rocha Martínez A00836634

/*
Instrucciones:
Utilizando la técnica de programación de "programación dinámica",
escribe en equipos de máximo dos personas, en C++ un programa que resuelva el problema del cambio de monedas.

El programa recibe un numero entero N, seguido de N valores enteros (uno en cada línea)
que representan las diferentes denominaciones disponibles de las monedas.
Seguido de esto, el programa recibe dos números enteros: P y Q,
(uno en cada línea) por la entrada estándar,
que representan P: el precio de un producto dado y Q: es el billete o moneda con el que se paga dicho producto.

La salida del programa es una lista de N valores correspondientes
al número de monedas de cada denominación, de mayor a menor, una en cada línea,
que se tienen que dar para dar el cambio por el producto pagado, utilizando programación dinámica,

Complejidad computacional:
El algoritmo implementado tiene una complejidad de O(N * cambio), donde:
    - N es la cantidad de denominaciones de monedas.
    - cambio es la cantidad a devolver.

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * @brief Calcula el cambio óptimo utilizando programación dinámica.
 * @param denominations Lista de denominaciones de monedas.
 * @param change Monto de cambio a devolver.
 * @return Vector con el número de monedas de cada denominación.
 */
vector<int> getChange(vector<int> &denominations, int change)
{
    int n = denominations.size();
    vector<int> dp(change + 1, 1e9); // Inicializar con un valor grande
    vector<int> used(change + 1, -1);
    dp[0] = 0;

    // Calcular la cantidad mínima de monedas necesarias para cada cantidad de cambio posible
    for (int i = 0; i < n; i++)
    {
        for (int j = denominations[i]; j <= change; j++)
        {
            if (dp[j - denominations[i]] + 1 < dp[j])
            {
                dp[j] = dp[j - denominations[i]] + 1;
                used[j] = i;
            }
        }
    }

    // Construir la solución de monedas utilizadas
    vector<int> result(n, 0);
    int temp_change = change;

    while (temp_change > 0 && used[temp_change] != -1)
    {
        result[used[temp_change]]++;
        temp_change -= denominations[used[temp_change]];
    }

    return result;
}

int main()
{
    int N; // Número de denominaciones de monedas
    cout << "Ingrese el número de denominaciones de monedas: ";
    cin >> N;

    vector<int> denominations(N);

    cout << "Ingrese las denominaciones de las monedas, una por línea:\n";
    for (int i = 0; i < N; i++)
    {
        cin >> denominations[i];
    }

    // Ordenar las denominaciones de mayor a menor para que la salida siga el formato requerido
    sort(denominations.rbegin(), denominations.rend());

    int P, Q; // Precio del producto y cantidad pagada
    cout << "Ingrese el precio del producto: ";
    cin >> P;
    cout << "Ingrese la cantidad pagada: ";
    cin >> Q;

    if (Q < P)
    {
        cout << "\nFalta dinero para pagar ese producto\n";
        return 0;
    }

    int change = Q - P;
    if (change == 0)
    {
        cout << "\nNo hay cambio por dar\n";
        return 0;
    }

    vector<int> result = getChange(denominations, change);

    // Imprimir la cantidad de monedas de cada denominación
    for (int i = 0; i < N; i++)
    {
        cout << result[i] << " moneda(s) de " << denominations[i] << "\n";
    }

    return 0;
}
