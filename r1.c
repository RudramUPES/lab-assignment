 int no_of_guesses;

    do
    {
      printf("guess the number : ");
      scanf("%d",&guessed);
      if(guessed>number){
        printf("enter a lower number");
      } else if(guessed<number){
        printf("enter a greater number");
      }else{
        printf("congrats!! you guessed it correctly ");
      }
   no_of_guesses++;

    } while (guessed != number);
    printf("you guessed the number in %d guesses", no_of_guesses);
    
    return 0;  // end of program
}
