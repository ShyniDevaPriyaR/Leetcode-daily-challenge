int getLucky(char* s, int k) {
    int sum = 0;
    for (int i=0; s[i]!='\0'; i++ )
    {
        int value = s[i]-'a'+1;
        while(value > 0)
        {
            
            sum = sum+ value%10;
            value= value/10;
        }
    }
    for(int i=1; i<k; i++)
    {
        int temp = sum;
        sum = 0;
        while(temp>0)
        {
            sum = sum+temp%10;
            temp = temp/10;
        }

    }
   return sum;
    
}