#include "contact.h"
// function to list all the contacts in addressbook
void listContacts(AddressBook *addressBook) 
{
	printf("\n");
	printf("%68s","CONTACTS LIST\n");
	int i;
    	//print all the data from the addressBook
	printf("%-13s   %-13s   %-15s","NAME","PHONE NUMBER","EMAIL");
	printf("\n");
	printf("\n");
	for(i=0;i<addressBook->contactCount;i++){
		printf("%-15.15s	%-11s	%-15s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
		printf("\n");
	}
	
}

// function to copy contents from file to struct array
int copy(AddressBook *addressBook){
        FILE *fp;
        int i,c;
        fp = fopen("contacts.csv","r");
        if(fp == NULL){
                perror("ERROR :");
                 return -1;
        }
        fscanf(fp,"#%d#",&addressBook->contactCount);
        c = addressBook->contactCount;
        for(i=0;i<c;i++){
                fscanf(fp," %[^,],%[^,],%[^\n]",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        fclose(fp);
}

void initialize(AddressBook *addressBook) 
{
	addressBook->contactCount = 0;
	copy(addressBook);
}

// save the contents from array to file
int saveContact(AddressBook *addressBook){
        FILE *fp;
        int i,c;
        fp = fopen("contacts.csv","w");
        if(fp == NULL){
                perror("ERROR :");
                 return -1;
        }
        c = addressBook->contactCount;
        fprintf(fp,"#%d#\n",c);
        for(i=0;i<c;i++){
                fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        fclose(fp);
        printf("Contact saved successfully !\n");

}

void createContact(AddressBook *addressBook) 
{
	printf("\n");
	int a=0,d=0,i,j,k=0,m,exist;
	i = addressBook->contactCount;
	// read the name of the contact
	printf("Enter the Name : ");
	scanf(" %[^\n]",addressBook->contacts[i].name); 

	printf("Enter the number : ");
	scanf(" %[^\n]",addressBook->contacts[i].phone);
	// validation for phone number
        while(strlen(addressBook->contacts[i].phone) != 10){ // condition checks for 10 digits
		printf("Enter 10 digits only : ");
                scanf(" %[^\n]",addressBook->contacts[i].phone);
	} 
	while(strlen(addressBook->contacts[i].phone) == 10){
		exist = 0;
		for(m=0;m<i;m++){
			if(strcmp(addressBook->contacts[m].phone,addressBook->contacts[i].phone) == 0){ 
				// checks whether the number aldready exsist in addressbook
				exist ++; 
				break;
			}
		}
		if(exist != 0){ // if exist enter another number
			printf("Number already exists\n");
			printf("Enter the Number : ");
                	scanf(" %[^\n]",addressBook->contacts[i].phone);
			continue;
		}
                j=0;
                while(addressBook->contacts[i].phone[j] != '\0'){
			// check all the characters entered are only digits
                        if((addressBook->contacts[i].phone[j] < 48) || (addressBook->contacts[i].phone[j] > 57)){
                                break;
                        }
                        j++;
                }
                if(j == 10){
                        break;
                }
		printf("Numer not valid\n");
                printf("Enter the Number : ");
                scanf(" %[^\n]",addressBook->contacts[i].phone);

        }

	// validation for email ID
	while(1){
		int a_count = 0,d_count = 0,val=0;
		k = 0;
		char *ptr;
		printf("Enter Mail Id : ");
		scanf(" %[^\n]",addressBook->contacts[i].email);
		exist = 0;
                for(m=0;m<i;m++){
                        if(strcmp(addressBook->contacts[m].email,addressBook->contacts[i].email) == 0){
                                // checks whether the email already exist in addressbook
                                exist ++;
                                break;
                        }
                }
                if(exist != 0){ // if exist enter another number
                        printf("Mail Id already exists\n");
                        continue;
                }

		// '@' and ".com" should be present compulsory 
		if((strchr(addressBook->contacts[i].email,'@') != NULL) && (strstr(addressBook->contacts[i].email,".com") != NULL)){
			// to validate for no characters present after ".com";
			ptr = strstr(addressBook->contacts[i].email,".com");
			if(ptr[4] != '\0'){
				val ++;
			}
			while(addressBook->contacts[i].email[k] != '\0'){
				if(addressBook->contacts[i].email[k] == '@'){
					a = k;
					a_count++; //checks if @ is present only 1 time
				}
				if(addressBook->contacts[i].email[k] == '.'){
					d = k;
					d_count++; //checks if . is present only 1 time
				}
				k++;
			}
		}		
		if((val == 0) && (a_count == 1) && (d_count == 1) && (a<d) && (addressBook->contacts[i].email[0] != '@') && (addressBook->contacts[i].email[a + 1] != '.') && (strchr(addressBook->contacts[i].email,' ') == NULL)){ 
			// if all the condition are true it breaks the loop
			break;
		}
		else{
			printf("Mail Id not valid\n");
		}
	}
	printf("Contact added successfully\n");
	addressBook->contactCount++;
}

int searchContact(AddressBook *addressBook) 
{
	int choice,i,j,sts,k=0,a,d,scan,c=addressBook->contactCount,m,exist=0,val=0;
	char ch,*ptr;
	// create strings for user to enter name/number/mailID to search
	char name[20];
	char number[20];
	char mail[20];

	while(1){
		// display menu for user to choose action
		printf("\n");
		printf("1. Search by Name\n2. Search by number\n3. Search by MailID\n4. Exit\n");
		scan = scanf(" %d",&choice);
		// clear buffer if no integer is read; 
		while(1){
			if(scan == 1){
				while((ch = getchar()) != '\n' && ch != EOF);
				break;
			}
			else{
				while((ch = getchar()) != '\n' && ch != EOF);
				break;
			}
		}
		// user action 
		switch(choice){
			case 1:
				// search by NAME
				printf("Enter Name to search : ");
				scanf(" %[^\n]",name);
				printf("\n");

				for(i=0;i<addressBook->contactCount;i++){
					// compare the user entered name with names in addressBook
					sts = strcmp(addressBook->contacts[i].name,name);
					if(sts == 0){
						break;
					}
				}
				if (sts != 0){
					// display msg if not found
					printf("Contact with the Name not found\n");
					return -1;

				}
				 exist = 0;
				for(m=0;m<c;m++){
                                         if(strcmp(addressBook->contacts[m].name,addressBook->contacts[i].name) == 0){
                                                  // checks whether the number aldready exsist in addressbook
                                                  exist ++;
						  printf("%s      %s      %s\n",addressBook->contacts[m].name,addressBook->contacts[m].phone,addressBook->contacts[m].email);
                                                  
                                         }
                                }
				if(exist > 1){
					printf("\n");
					printf("** More than 1 contact found **\n< Try searching by 'Number' or 'Mail Id' >\n");
					continue;
				}
				// if found print the details of the contact
				printf("\n");
				printf("!Contact found!\n");
               			printf("\n");
				return i;
				break;

			case 2:
				// search by NUMBER
				printf("Enter Number to search (10 digits) : ");
				scanf(" %[^\n]",number);
				printf("\n");
				// number validation
				while(strlen(number) != 10){
                                        printf("Enter 10 digits only : ");
                                        scanf(" %[^\n]",number);
                                }
                                while(strlen(number) == 10){
                                        j=0;
                                        while(number[j] != '\0'){
                                                if((number[j] < 48) || (number[j] > 57)){
                                                        break;
                                                }
                                        j++;
                                        }
                                if(j == 10){
                                        break;
                                }
				printf("Number not valid\n");
                                printf("Enter the Number : ");
                                scanf(" %[^\n]",number);
				}

                                for(i=0;i<addressBook->contactCount;i++){
					// compare the user entered number with numbers in addressBook
                                        sts = strcmp(addressBook->contacts[i].phone,number);
                                        if(sts == 0){
                                                break;
                                        }
                                }
                                if (sts != 0){
					// display msg if contact not found
                                        printf("Contact with the phone number not found\n");
                                        return -1;
                                }
				// if found print the details of the contact
				printf("!Contact found!\n");
                                printf("%s      %s      %s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                                printf("\n");
				return i;
                                break;

			case 3:
				// search by MAIL-ID
				
				// validation for email ID
        			while(1){
                			int a_count = 0,d_count = 0;
	                		k = 0;
					// search by MAIL-ID
                                	printf("Enter E-mail ID to search : ");
                              	 	scanf(" %[^\n]",mail);
					printf("\n");
        		        	// '@' and ".com" should be present compulsory 
                			if((strchr(mail,'@') != NULL) && (strstr(mail,".com") != NULL)){
                        			while(mail[k] != '\0'){
                                			if(mail[k] == '@'){
                                		        	a = k;
                                        			a_count++; //checks if @ is present only 1 time
	         		                       	}
        	                       			if(mail[k] == '.'){
                	        	                	d = k;
                        	                		d_count++; //checks if . is present only 1 time
                      			          	}
                                			k++;
         		               		}
                			}	
                			if((val == 0) && (a_count == 1)&&(d_count == 1)&&(a<d)&&(mail[0] != '@')&&(mail[a + 1] != '.')&&(strchr(mail,' ') == NULL)){ 
					// if all the condition are true it breaks the loop
                      	 		break;
                			}
					else{
						printf("Mail Id not valid\n");
					}
        			}

				for(i=0;i<addressBook->contactCount;i++){
                                        // compare the user entered Mail-Id with Mail-Ids in addressBook
                                        sts = strcmp(addressBook->contacts[i].email,mail);
                                        if(sts == 0){
                                                break;
                                        }
                                }
                                if (sts != 0){
                                        // display msg if contact not found
                                        printf("Contact with the Mail-Id not found\n");
                                        return -1;
                                }
                                // if found print the details of the contact
				printf("!Contact found!\n");
                                printf("%s      %s      %s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                                printf("\n");
				return i;
                                break;

			case 4:
				printf("Search menu exited !\n");
				return -2;
				break;	

			default:
				printf("\n");
				printf("Choose given options \n");
		}
		if(choice == 4){
			break;
		}
	}
}

void editContact(AddressBook *addressBook) 
{
	int i,j,m,exist=0,c,val=0;
	char ch,*ptr;
	// the repetation is checked for contactCount times
	c = addressBook->contactCount;
	while(1){
		printf("\n");
		int choice,scan;
		printf("1. Edit Name\n2. Edit Number\n3. Edit Mail Id\n4. Exit\n");
		scan = scanf(" %d",&choice);
		// clear buffer if no integeris read;
                while(1){
                        if(scan == 1){
                                while((ch = getchar()) != '\n' && ch != EOF);
                                break;
                        }
                        else{
                                while((ch = getchar()) != '\n' && ch != EOF);
				break;
                        }
                }

		switch(choice){
			case 1:
				// Editing Name of contact
				i = searchContact(addressBook);
				if(i == -2){
                                        break;
                                }
				if(i != -1){
					printf("\n");
					printf("Enter the Name : ");
					scanf(" %[^\n]",addressBook->contacts[i].name);
					printf("Name updated successfully\n");
				}
				else{
					printf("Enter existing Name to edit\n");
				}
				break;
		
			case 2:
			       	// Editing Phn.number of contact
				i = searchContact(addressBook);
				if(i == -2){
					break;
				}
				if(i != -1){
				printf("\n");
                                printf("Enter the Number : ");
			       	scanf(" %[^\n]",addressBook->contacts[i].phone);
				// validation for phone number
			        while(strlen(addressBook->contacts[i].phone) != 10){ // condition checks for 10 digits
              				printf("Enter 10 digits only : ");
              				scanf(" %[^\n]",addressBook->contacts[i].phone);
        			}
      				while(strlen(addressBook->contacts[i].phone) == 10){
        	        		exist = 0;
                			for(m=0;m<c;m++){
                        			if(strcmp(addressBook->contacts[m].phone,addressBook->contacts[i].phone) == 0){
                                			// checks whether the number aldready exsist in addressbook
                                			exist ++;
                        			}
                			}
	                		if(exist != 1){ // if exist enter another number
                	        		printf("Number already exists\n");
        	                		printf("Enter the Number : ");
                        			scanf(" %[^\n]",addressBook->contacts[i].phone);
                        			continue;
                			}
                			j=0;
                			while(addressBook->contacts[i].phone[j] != '\0'){
                        			// check all the characters entered are only digits
                        			if((addressBook->contacts[i].phone[j] < 48) || (addressBook->contacts[i].phone[j] > 57)){
                        			        break;
                        			}
                        			j++;
                			}
                			if(j == 10){
                        			break;
                			}
					printf("Number not valid\n");
                			printf("Enter the Number : ");
                			scanf(" %[^\n]",addressBook->contacts[i].phone);
				}
				printf("Number updated successfully\n");
				}
				else{
					printf("Enter existing Number to edit\n");
				}
				break;	
				
			case 3:
				// Editing Mail Id of contact
				i = searchContact(addressBook);
				if(i == -2){
                                        break;
                                }
				if(i != -1){
				int a,d,k;

				// validation for email ID
			        while(1){
               				int a_count = 0,d_count = 0;
                			k= 0;
					printf("\n");
                			printf("Enter the Mail Id : ");
                			scanf(" %[^\n]",addressBook->contacts[i].email);
                			exist = 0;
                			for(m=0;m<c;m++){
                        			if(strcmp(addressBook->contacts[m].email,addressBook->contacts[i].email) == 0){
                                		// checks whether the email aldready exsist in addressbook
                                		exist ++;
                        			}
                			}
                			if(exist != 1){ // if exist enter another number
  	        	              		printf("Mail Id already exists\n");
                        			continue;
                			}		

       	        			// '@' and ".com" should be present compulsory 
                			if((strchr(addressBook->contacts[i].email,'@') != NULL) && (strstr(addressBook->contacts[i].email,".com") != NULL)){
                        			while(addressBook->contacts[i].email[k] != '\0'){
                                			if(addressBook->contacts[i].email[k] == '@'){
                                        			a = k;
                                        			a_count++; //checks if @ is present only 1 time
                                			}
                                			if(addressBook->contacts[i].email[k] == '.'){
                                        			d = k;
                                        			d_count++; //checks if . is present only 1 time
                                			}
                                			k++;
                        			}
                			}
                			if((a_count == 1) && (d_count == 1) && (a<d) && (addressBook->contacts[i].email[0] != '@') && (addressBook->contacts[i].email[a + 1] != '.') && (strchr(addressBook->contacts[i].email,' ') == NULL)){
					        // if all the conditions re true, loop breaks;	
                        			printf("Mail Id updated successfully\n");
						break;
                			}
					else{
						printf("Mail Id not valid\n");
					}				
        			}
				}
				else{
					printf("Enter existing Mail Id to edit\n");
				}
				break;
		
			case 4:
				printf("Edit menu exited !\n");
				break;

			default:
				printf("\n");
                                printf("Choose given options \n");
                                break;

		}
		if(choice == 4){
			break;
		}
	}		
}

void deleteContact(AddressBook *addressBook) 
{
	printf("\n");
	int i,c,j;
	c = addressBook->contactCount;
	printf("Choose the contact to delete\n");
	i=searchContact(addressBook);
	if(i != -1 && i != -2){
		// to search for the required contact
		for(j=i;j<c;j++){
			addressBook->contacts[j] = addressBook->contacts[j+1];
		}
		printf("Contact deleted successfully\n");
		addressBook->contactCount-- ;
	}
	else{
		printf("No contact found to delete\n");	
	}
}
//exit;

