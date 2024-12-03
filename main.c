#include "contact.h"

int main()
{
    	 //all function calls should be inside the main 
   	 AddressBook addressBook;
   	 initialize(&addressBook); 
	 int choice,scan;
	 char ch;
	 while(1){
		 printf("\n");
		 printf("%68s","ADDRESS BOOK\n");
		 printf("%85s","CHOOSE ANY OPTION TO PERFORM PARTICULAR TASK\n");
		 printf("--------------------------------------------------------------------------------------------------------------------------------\n");
		 printf("1. Add\n2. Delete\n3. Search\n4. Edit\n5. List\n6. Save\n7. Exit\n");
		 printf("Press 7 to exit\n");
		 printf("** NOTE : Save & Exit **\n");

		 // clear buffer if no integeris read;
                 while(1){
			printf("Please select from the given option\n");
                        if(scanf("%d",&choice) == 1){
                                while((ch = getchar()) != '\n' && ch != EOF);
                                break;
                        }
                        else{
				printf("Invalid Option\n");
                                while((ch = getchar()) != '\n' && ch != EOF);

                        }
                 }
	
		 switch(choice){
			 case 1:
				 createContact(&addressBook);
				 break;
			 case 2:
				 deleteContact(&addressBook);
				 break;
			 case 3:
				 searchContact(&addressBook);
				 break;
			 case 4:
				 editContact(&addressBook);
				 break;
			 case 5:
				 listContacts(&addressBook);
				 break;
			 case 6:
				 saveContact(&addressBook);
				 break;
			 case 7: 
				 saveContact(&addressBook);
				 printf("Exited successfully\n");
				 return 0;
			 default :
				 printf("Please select from the given option\n");
				 break;
		 }
		 if(choice == 7){
			 break;
		 }
	 } 

   	 return 0;
}
