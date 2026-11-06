int countDigits(int num) {
    int count = 0;
    int digits;
    int original = num;
    if(num==0)
    {
      return 1;
    }
    if(num<0)
    {
        num=-num;
    }
    while(num>0)
    {
        digits=num%10;
        if(digits != 0 && original%digits == 0)
        {
        count++;
        }
        num=num/10;
    }
    return count;
    
}