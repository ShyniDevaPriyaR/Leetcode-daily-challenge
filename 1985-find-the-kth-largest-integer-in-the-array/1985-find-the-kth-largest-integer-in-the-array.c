int compare(char *a, char *b)
{
    int len1 = 0, len2 = 0;

    while (a[len1] != '\0')
        len1++;

    while (b[len2] != '\0')
        len2++;

    if (len1 > len2)
        return 1;

    if (len1 < len2)
        return -1;

    for (int i = 0; i < len1; i++)
    {
        if (a[i] > b[i])
            return 1;

        if (a[i] < b[i])
            return -1;
    }

    return 0;
}

void merge(char **nums, char **temp, int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (compare(nums[i], nums[j]) >= 0)
        {
            temp[k++] = nums[i++];
        }
        else
        {
            temp[k++] = nums[j++];
        }
    }

    while (i <= mid)
        temp[k++] = nums[i++];

    while (j <= right)
        temp[k++] = nums[j++];

    for (int p = left; p <= right; p++)
    {
        nums[p] = temp[p];
    }
}

void mergeSort(char **nums, char **temp, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(nums, temp, left, mid);
    mergeSort(nums, temp, mid + 1, right);

    merge(nums, temp, left, mid, right);
}

char* kthLargestNumber(char** nums, int numsSize, int k)
{
    char **temp = malloc(numsSize * sizeof(char *));

    if (temp == NULL)
        return NULL;

    mergeSort(nums, temp, 0, numsSize - 1);

    char *answer = nums[k - 1];

    free(temp);

    return answer;
}
