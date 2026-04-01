/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 typedef struct {
    int pos;
    int health;
    char dir;
    int idx;
} Robot;

int cmp(const void* a, const void* b) {
    return ((Robot*)a)->pos - ((Robot*)b)->pos;
}
int* survivedRobotsHealths(int* positions, int positionsSize, int* healths, int healthsSize, char* directions, int* returnSize) {
     int n = positionsSize;
     Robot* arr = (Robot*)malloc(sizeof(Robot) * n);

    // Step 1: store robots
    for(int i = 0; i < n; i++) {
        arr[i].pos = positions[i];
        arr[i].health = healths[i];
        arr[i].dir = directions[i];
        arr[i].idx = i;
    }

    // Step 2: sort by position
    qsort(arr, n, sizeof(Robot), cmp);

    // stack (store indices of arr)
    int* stack = (int*)malloc(sizeof(int) * n);
    int top = -1;

    for(int i = 0; i < n; i++) {

        if(arr[i].dir == 'R') {
            stack[++top] = i;
        } else {
            // current is 'L'
            while(top >= 0 && arr[stack[top]].dir == 'R' && arr[i].health > 0) {

                int j = stack[top];

                if(arr[j].health > arr[i].health) {
                    arr[j].health--;
                    arr[i].health = 0;
                } else if(arr[j].health < arr[i].health) {
                    arr[i].health--;
                    arr[j].health = 0;
                    top--; // pop
                } else {
                    arr[i].health = 0;
                    arr[j].health = 0;
                    top--; // pop
                    break;
                }
            }
        }
    }

    // Step 3: collect survivors
    int* result = (int*)malloc(sizeof(int) * n);
    int count = 0;

    // restore original order
    int* final = (int*)calloc(n, sizeof(int));

    for(int i = 0; i < n; i++) {
        if(arr[i].health > 0) {
            final[arr[i].idx] = arr[i].health;
        }
    }

    for(int i = 0; i < n; i++) {
        if(final[i] > 0) {
            result[count++] = final[i];
        }
    }

    *returnSize = count;

    free(arr);
    free(stack);
    free(final);

    return result;
}