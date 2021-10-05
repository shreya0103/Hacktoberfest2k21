 #include <string.h>
  #include <stdio.h>

  void checkTriangle(char *side1)
  {
    int i;
    int found_letter = 0;
    int len = strlen(side1);

    for( i = 0; i < len; i++)
    {
        if(side1[i] < '0' || side1[i] > '9')
        {
            found_letter = 1; // this variable works as a boolean
            break;
        }
    }
    if(found_letter) // value 0 means false, any other value means true
        printf("You entered a string");
    else
        printf("You entered only numbers");
  }
