/* Exercise 3-1: Our binary search makes two tests inside the loop, when
 * one would suffice (at the price of more tests outside). Write a version
 * with only one test inside the loop and measure the difference in run-
 * time.
 */

void shellsort(int v[], int n)
{
    int gap, i, j, temp;
    for (gap = n / 2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j = i - gap;
                j >= 0 && v[j] > v[j + gap];
                j -= gap) {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
            }
}

/*
8 4 3 2 1 7 5 6
1 4 3 2 8 7 5 6
1 2 3 4 5 6 8 7
1 2 3 4 5 6 7 8
*/
