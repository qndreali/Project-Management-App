/**********************************************************************************
Description: This function loads the record from a file into an array of structs,
	         specifically, an array of structs for the personnel record.
	@param personnelArray: An array of structs that stores personnel information.
    @param numPersonnel: The number of current personnels.
    @param filename: The name of the text file containing the personnel information.
**********************************************************************************/
void 
loadFile(struct personnel personnelArray[],
         int *numPersonnel,
         str24 fileName)
{
    FILE *fp;
    int  id,
         index;

    fp = fopen(fileName, "r");

    if (fp == NULL)
    {
        fp = fopen(fileName, "w");
        fprintf(fp, "9999 \nadmin \nadmin123 \n1 \n1\n\n");
        fclose(fp);
    }

    fclose(fp);

    fp = fopen(fileName, "r");

    while ((fscanf(fp, "%d", &id) != EOF) && (*numPersonnel < MAX_PERSONNEL))
    {
      	index = findPersonnel(id, personnelArray, *numPersonnel);
        if (index == -1)
        {  
            personnelArray[*numPersonnel].personnelID = id;
            fscanf(fp, "%s\n%s\n%d\n%d", personnelArray[*numPersonnel].username, personnelArray[*numPersonnel].password, 
                                         &personnelArray[*numPersonnel].active, &personnelArray[*numPersonnel].access);
            (*numPersonnel)++;
        }
	}
	
    fclose(fp);

}
/**********************************************************************************
Description: This function checks whether the personnel username exists.
	@param personnelArray: An array of structs that stores personnel information.
	@param numPersonnel: The number of current personnels.
	@param username: The username from user input.
	@return i: This function returns the index of the personnel in the array with the
		   matching username as the user input.
	@return -1: This function returns -1 if the username does not exist.
**********************************************************************************/
int 
checkPersonnelUsername(struct personnel personnelArray[], 
		               int numPersonnel, 
		               char *username)
{
	int i;

    for(i = 0; i < numPersonnel; i++)
    	if(strcmp(personnelArray[i].username, username) == 0)
        	return i;
        
    return -1; 
}

/**********************************************************************************
Description: This function serves as the login (main) menu that checks if the entered
	         valid username matches the entered password.
	@param personnelArray: An array of structs that stores personnel information.
	@param numPersonnel: The number of current personnels.
	@param personnelID: address where the personnelID will be passed to
	@return personnelIndex: returns the index of the personnel in the personnelArray.
**********************************************************************************/
int 
login(struct personnel personnelArray[], 
      int numPersonnel, int *personnelID)
{
	char username[40],
	     password[40];
    int  personnelIndex = -1;

   	do
    {
    	do
    	{
	   		displayHeader();
	        printf("\nUsername: ");
	    	fgets(username, 40, stdin);
	        if (username[strlen(username) - 1] == '\n')
	        		username[strlen(username) - 1] = '\0'; // terminates the newline character at the end of the string
	
	    	personnelIndex = checkPersonnelUsername(personnelArray, numPersonnel, username);
	
	    	if(personnelIndex == -1)
			{
	        		printf("\e[1;31m" "Error: Username not found.\n" "\e[1;97m");
	        		clearScreen();
	    	}
    	} while (personnelIndex == -1);
    
		printf("Password: ");
        fgets(password, 40, stdin);
        if(password[strlen(password) - 1] == '\n')
        	password[strlen(password) - 1] = '\0'; // terminates the newline character at the end of the string
        
        if(strcmp(personnelArray[personnelIndex].password, password) != 0)
		{
			printf("\e[1;31m" "Wrong Password. Try again.\n" "\e[1;97m");
			clearScreen();
        }
		else if(personnelArray[personnelIndex].access == 0)
		{
			printf("\e[1;31m" "Access Disabled. Please contact an Admin.\n" "\e[1;97m");
			clearScreen();
		}
        else
		{
        	printDivider();
        	printf("\e[1;32m" "\nWelcome, %s!\n" "\e[1;97m", personnelArray[personnelIndex].username);
        	clearScreen();
		}
        
    } while(strcmp(personnelArray[personnelIndex].password, password) != 0);

	*personnelID = personnelArray[personnelIndex].personnelID;
    return personnelArray[personnelIndex].access;
}

/**********************************************************************************
Description: This function generates a randomized 4-digit number for the personnelID.
	@param personnelArray: An array of structs that stores personnel information.
	@param numPersonnel: The number of current personnels.
	@return personnelID: returns the generated unique ID.
**********************************************************************************/
int 
randomPersonnelID(struct personnel personnelArray[], 
		          int numPersonnel)
{
    int personnelID, 
	    uniqueID,
	    i;	
	srand(time(NULL));

    do
	{
        uniqueID = 1;
        personnelID = rand() % 9000 + 1000;

        for(i = 0; i < numPersonnel; i++) // checks if the personnelID already exists
       		if (personnelArray[i].personnelID == personnelID)
            	uniqueID = 0;
                
    } while(!uniqueID);

    return personnelID;
}

/**********************************************************************************
Description: This function lets the user with admin access to add a new personnel.
	         The personnel information is stored in the personnelArray and is added
	         to the preloaded.txt file.
	@param personnelArray: An array of structs that stores personnel information.
	@param *numPersonnel: The number of current personnels.
**********************************************************************************/
void 
addUser(struct personnel personnelArray[], 
	    int *numPersonnel)
{

	struct personnel newPersonnel;
	int    usernameExists;
	
	displayAddUserHeader();

    if(*numPersonnel >= 100)
        printf("Error: Maximum personnel count reached.\n");
    else
	{
    	newPersonnel.personnelID = randomPersonnelID(personnelArray, *numPersonnel);

	    printf("Enter Personnel Information:\n\n");

		do
		{
		    printf("[1] Admin [2] Manager [3] User.\nAccess: ");
	    	scanf("%d", &newPersonnel.access);
	    	fflush(stdin);
		        	
	        if(newPersonnel.access < 1 || newPersonnel.access > 3)
	        	printf("\e[1;31m" "Invalid Input. Please choose between [1] Admin [2] Manager [3] User.\n" "\e[1;97m");
	            
		} while(newPersonnel.access < 1 || newPersonnel.access > 3);
	
		do
		{
			printf("\nUsername: ");
			scanf("%s", newPersonnel.username);
			fflush(stdin);

			if(strlen(newPersonnel.username) > 40)
				printf("\e[1;31m" "Invalid input. Username must not be greater than 40 characters.\n" "\e[1;97m");

			usernameExists = checkPersonnelUsername(personnelArray, *numPersonnel, newPersonnel.username);

			if(usernameExists >= 0)
				printf("\e[1;31m" "This username already exists. Try again.\n" "\e[1;97m");
			
		} while (strlen(newPersonnel.username) > 40 || usernameExists >= 0);
	
		if(newPersonnel.access == 3)
		{
			printf("Password: tempPass\n");    
			strcpy(newPersonnel.password, "tempPass");
		}
		else
		{
			do
			{
				printf("Password: ");
				scanf("%s", newPersonnel.password);
				fflush(stdin);

				if(strlen(newPersonnel.password) > 40)
					printf("\e[1;31m" "Invalid input. Password must not be greater than 40 characters.\n" "\e[1;97m");
					
			} while (strlen(newPersonnel.password) > 40);
		}
	    
	    do
		{
		    printf("\n[1] Active [2] Inactive\nActive: ");
	    	scanf("%d", &newPersonnel.active);
	    	fflush(stdin);
		        	
	        if(newPersonnel.active < 1 || newPersonnel.active > 2)
	        	printf("\e[1;31m" "Invalid Input. Please choose between [1] Active [2] Inactive\n" "\e[1;97m");
	            
		} while(newPersonnel.active < 1 || newPersonnel.active > 2);
	    
	    printDivider();
        printf("\e[1;32m" "\nNew Personnel added successfully.\n" "\e[1;97m");
	
	    personnelArray[*numPersonnel] = newPersonnel;
	    (*numPersonnel) ++;
	}
}

/**********************************************************************************
Description: This function lets the user with admin access to update a personnel.
	         The personnel information is updated in the personnelArray and the
	         changes are also applied to the preloaded.txt file.
	@param personnelArray: An array of structs that stores personnel information.
	@param numPersonnel: The number of current personnels.
**********************************************************************************/
void 
updateUser(struct personnel personnelArray[], 
	       int numPersonnel)
{
	int   i, 
 	      option, 
	      found = 0,
	      personnelID,
	      newAccess,
		  newActive,
	      usernameExists;
    str40 newUsername, 
	      newPassword;
    
    viewUsers(personnelArray, numPersonnel);
    
	printf("\n\nEnter personnel ID to update: ");
	scanf("%d", &personnelID);
	
	for(i = 0; i < numPersonnel; i++)
	{
	    if(personnelArray[i].personnelID == personnelID)
		{
	        found = 1;
			system("cls");
	        
	        displayUpdateUserHeader();
			
			// dislays the information of the selected personnel
			printf("%c Personnel ID: %-43d %c %-56s %c\n", TVLINE, personnelArray[i].personnelID, TVLINE, "Select Field to Update:", TVLINE);
			printf("%c Username: %-47s %c %-56s %c\n", TVLINE, personnelArray[i].username, TVLINE, "[1] Username", TVLINE);
			printf("%c Password: %-47s %c %-56s %c\n", TVLINE, personnelArray[i].password, TVLINE, "[2] Password", TVLINE);
			printf("%c Active: %-49d %c %-56s %c\n", TVLINE, personnelArray[i].active, TVLINE, "[3] Active", TVLINE);
			printf("%c Access: %-49d %c %-56s %c\n", TVLINE, personnelArray[i].access, TVLINE, "[4] Access", TVLINE);
			
			displayUpdateUserDivider();
	            
			do
			{
				printf("\nOption: ");
				scanf("%d", &option);
				fflush(stdin);
		        	
				if(option < 1 || option > 4)
					printf("\e[1;31m" "Invalid Input. Try again.\n" "\e[1;97m");
	            
			} while(option < 1 || option > 4);
	
			switch(option)
			{
				case 1:
					do
					{
						printf("New Username: ");
						scanf("%s", newUsername);

						if(strlen(newUsername) > 40)
							printf("\e[1;31m" "Invalid Input. Username must not be greater than 40 characters.\n" "\e[1;97m");
							
						usernameExists = checkPersonnelUsername(personnelArray, numPersonnel, newUsername);

						if(usernameExists >= 0)
							printf("\e[1;31m" "This username already exists. Try again.\n" "\e[1;97m");

					} while(strlen(newUsername) > 40 || usernameExists >= 0);

					strcpy(personnelArray[i].username, newUsername);
					break;
				case 2:
					do
					{
						printf("New Password: ");
						scanf("%s", newPassword);

						if(strlen(newPassword) > 40)
							printf("\e[1;31m" "Invalid Input. Password must not be greater than 40 characters.\n" "\e[1;97m");

					} while(strlen(newPassword) > 40);

					strcpy(personnelArray[i].password, newPassword);
					break;
				case 3:
					do
					{
						printf("[1] Active [2] Inactive\nNew Active Level: ");
						scanf("%d", &newActive);
						fflush(stdin);

						if(newActive < 1 || newActive > 2)
							printf("\e[1;31m" "Invalid Input. Please choose between [1] Active [2] Inactive\n" "\e[1;97m");

					} while(newActive < 1 || newActive > 2);

					personnelArray[i].active = newActive;
					break;
				case 4:
					do
					{
						printf("[1] Admin [2] Manager [3] User.\nNew Access Level: ");
						scanf("%d", &newAccess);
						fflush(stdin);

						if(newAccess < 1 || newAccess > 3)
							printf("\e[1;31m" "Invalid Input. Please choose between [1] Admin [2] Manager [3] User.\n" "\e[1;97m");

					} while(newAccess < 1 || newAccess > 3);

					personnelArray[i].access = newAccess;
					break;
	        }
			
			printDivider();
			printf("\e[1;32m" "\nPersonnel updated successfully.\n" "\e[1;97m");
	    }
	}
	
	if(!found)
	{
		printf("\e[1;31m" "Personnel ID does not exist. Please input an existing Personnel ID.\n\n" "\e[1;97m");
		clearScreen();
		updateUser(personnelArray, numPersonnel);
	}
}

/**********************************************************************************
Description: This function lets the user with admin access to delete a personnel.
	         The personnel information is removed in the personnelArray and it is
	         also removed in the preloaded.txt file. The tasks assigned to the
	         deleted personnel is then assigned to the admin. 
	@param personnelArray: An array of structs that stores personnel information.
	@param numPersonnel: The number of current personnels.
	@param taskArray: An array of structs that stores task information.
	@param numTasks: The number of tasks.
	@param projectArray: An array of structs that stores project information.
	@param numProjects: The number of projects.
**********************************************************************************/
void 
deleteUser(struct personnel personnelArray[], 
	       int *numPersonnel,
	       struct task taskArray[], 
	       int  numTasks,
	       struct project projectArray[],
	       int numProjects)
{
	int  i,
	     j, 
	     k,
	     personnelID, 
	     found = 0;
    char option;
    
    viewUsers(personnelArray, *numPersonnel);
    
    printf("\nEnter personnel ID to delete: ");
	scanf("%d", &personnelID);    
	getchar();

	if(personnelID == 9999){
		printf("\e[1;31m" "Invalid input. Admin 9999 cannot be deleted.\n" "\e[1;97m"); 
		found = 1;
	}
	else
	{
		for(i = 0; i < *numPersonnel; i++)
		if (personnelArray[i].personnelID == personnelID)
		{
            found = 1;
           	do
			{
				printf("Delete User %s? \n[Y/N]: ", personnelArray[i].username);
				scanf("%c", &option);
				fflush(stdin);
				
				if(option != 'Y' && option != 'y' && option != 'N' && option != 'n')
					printf("\e[1;31m" "Invalid Input. Try again.\n" "\e[1;97m");
		
			} while (option != 'Y' && option != 'y' && option != 'N' && option != 'n'); 
            
            if (option == 'Y' || option == 'y')
			{
                for (j = i; j < *numPersonnel - 1; j++)
                    personnelArray[j] = personnelArray[j + 1];
                (*numPersonnel)--;
                printDivider();
                printf("\e[1;32m" "\nPersonnel deleted successfully.\n" "\e[1;97m");
                i--;
                
				for(k = 0; k < numTasks; k++)
					if(taskArray[k].assignID == personnelID)
					{
						taskArray[k].assignID = 9999;
						printf("\e[1;32m" "Task %d assigned to admin.\n" "\e[1;97m", taskArray[k].taskID);
					}
					
				for(int k = 0; k < numProjects; k++)
					if(projectArray[k].assignID == personnelID)
					{
						projectArray[k].assignID = 9999;
						printf("\e[1;32m" "Project %d assigned to admin.\n" "\e[1;97m", projectArray[k].projectID);
					}
			}
            else
              	printf("\e[1;31m" "User deletion cancelled.\n" "\e[1;97m");
	}
    
        }
	   	if(!found)
	    {
	    	printf("\e[1;31m" "Personnel ID does not exist. Please input an existing Personnel ID.\n\n" "\e[1;97m");
			clearScreen();
			deleteUser(personnelArray, numPersonnel, taskArray, numTasks, projectArray, numProjects);
		}
}


/**********************************************************************************
Description: This function lets the user with admin access to archive a personnel.
			 The personnel access level is changes to disabled and the active status
			 is changed to inactive (2). This change is also reflected in the txt file.
	@param personnelArray: An array of structs that stores personnel information.
	@param numPersonnel: The number of current personnels.
**********************************************************************************/
void 
archiveUser(struct personnel personnelArray[], 
	        int numPersonnel)
{
	int  i,
	     personnelID, 
	     found = 0,
		 newAccess;
    char option;
	
    
    viewUsers(personnelArray, numPersonnel);
    
    printf("\nEnter personnel ID to Archive: ");
	scanf("%d", &personnelID);    
	getchar();

	if(personnelID == 9999){
		printf("\e[1;31m" "Invalid input. Admin 9999 cannot be archived.\n" "\e[1;97m"); 
		found = 1;
	}
	else
	{
		for(i = 0; i < numPersonnel; i++)
			if (personnelArray[i].personnelID == personnelID)
			{
				found = 1;
				
				if (personnelArray[i].access == 0)
				{
					do{
					printf("\nUser %s is already Archived.\n Would you like to give back access? [Y/N]: ", personnelArray[i].username);
					scanf("%c", &option);
					fflush(stdin);

					if(option != 'Y' && option != 'y' && option != 'N' && option != 'n')
						printf("\e[1;31m" "Invalid Input. Try again.\n" "\e[1;97m");

					} while(option != 'Y' && option != 'y' && option != 'N' && option != 'n');

					if (option == 'Y' || option == 'y')
					{
						personnelArray[i].active = 1;
						
						do
						{
							printf("New Access Level: ");
							scanf("%d", &newAccess);
							fflush(stdin);

							if(newAccess < 1 || newAccess > 3)
								printf("\e[1;31m" "Invalid Input. Please choose between [1] Admin [2] Manager [3] User.\n" "\e[1;97m");

						} while(newAccess < 1 || newAccess > 3);

						personnelArray[i].access = newAccess;


						printDivider();
						printf("\e[1;32m" "\nPersonnel access changed successfully.\n" "\e[1;97m");
					}
					else
						printf("\e[1;31m" "Personnel kept archived.\n" "\e[1;97m");
				}
				else
				{
					do
					{
						printf("Archive User %s? \n[Y/N]: ", personnelArray[i].username);
						scanf("%c", &option);
						fflush(stdin);
						
						if(option != 'Y' && option != 'y' && option != 'N' && option != 'n')
							printf("\e[1;31m" "Invalid Input. Try again.\n" "\e[1;97m");
				
					} while (option != 'Y' && option != 'y' && option != 'N' && option != 'n'); 
					
					if (option == 'Y' || option == 'y')
					{
						personnelArray[i].active = 2;
						personnelArray[i].access = 0;
						printDivider();
						printf("\e[1;32m" "\nPersonnel archived successfully.\n" "\e[1;97m");
					}
					else
						printf("\e[1;31m" "Personnel archiving cancelled.\n" "\e[1;97m");

				}
			}
		}

	   	if(!found)
	    {
	    	printf("\e[1;31m" "Personnel ID does not exist. Please input an existing Personnel ID.\n\n" "\e[1;97m");
			clearScreen();
			archiveUser(personnelArray, numPersonnel);
		} 
}

/**********************************************************************************
Description: This function lets the user with admin access to assign a project to a manager.
	@param projectArray: An array of structs that stores project information.
	@param numProject: The number of current projects.
	@param personnelArray: An array of structs that stores personnel information.
	@param numPersonnel: The number of current personnels.
**********************************************************************************/
void
assignProject(struct project projectArray[], 
           int numProjects, 
           struct personnel personnelArray[],
           int numPersonnel)
{
    int targetID,
		newAssignID, 
		projectIndex, 
		i, 
		index,
		count = 0,
		valid; 

	displayHeader();
    displayAdminHeader();
	displayProjects(projectArray, numProjects);
    
    do 
	{
        printf("\nEnter Project ID to Assign: ");
        scanf("%d", &targetID);
        fflush(stdin);

        projectIndex = findProject(targetID, projectArray, numProjects);
        
        if (projectIndex == -1)
            printf("\e[1;31m" "Invalid Input. Task ID does not match to any existing task.\n" "\e[1;97m");
            
    } while (projectIndex == -1);
    
    system("cls");
    displayHeader();
    displayAdminHeader();
    displayProjectDetail(projectArray, targetID);
	printf("\n");
	printLine(TTLCORNER, THLINE, TTRCORNER, 118);
	printf("\n");
    displayAssignProjectHeader();
    
    printf("\n%c %-116s %c\n", TVLINE, "To whom would you like to re-assign this project to?",TVLINE);
	printLine(TVLINE, 32, TVLINE, 118);	
	printf("\n%c Current Personnel: %-97d %c\n", TVLINE, projectArray[projectIndex].assignID ,TVLINE);
	printLine(TVLINE, 32, TVLINE, 118);
	for (i = 0; i < numPersonnel; i++)
    {
    	if (personnelArray[i].access == 2) 
        {
            count++;
            printf("\n%c \t%d. %d %-102s %c", TVLINE, count, personnelArray[i].personnelID, personnelArray[i].username, TVLINE);
            if(count == 0)
                printf("\n%c" "\e[1;31m" " %-116s " "\e[1;97m" "%c", TVLINE, "There are no Active Personnels.", TVLINE);	
        }
    }printf("\n");
	printLine(TBLCORNER, THLINE, TBRCORNER, 118);
	printf("\n");
	
	do 
	{
	    printf("\nEnter Personnel ID: ");
	    scanf("%d", &newAssignID);
	    fflush(stdin);
	           
	    index = findPersonnel(newAssignID, personnelArray, numPersonnel);
		valid = index != -1;

		if(valid)
			if (personnelArray[index].access != 2)
				valid = 0;
	        
	    if (!valid)
	        printf("\e[1;31m" "Invalid Personnel. Please input an existing Manager Personnel ID.\n" "\e[1;97m");
	                
    } while (!valid);
    
    projectArray[projectIndex].assignID = newAssignID;
    
    printDivider();
    printf("\e[1;32m" "\nProject Assigned successfully.\n" "\e[1;97m");
}

/**********************************************************************************
Description: This function gets the current time in HH:MM format and stores it in 
        a string. This function also uses a 24-hour format. 
    @param currentTime - destination string where the current time will be stored
**********************************************************************************/
void 
getTime(str12 currentTime) 
{
    str24 z;
    time_t t;

    time(&t);
    strcpy(z, ctime(&t));

    str12 copy = {z[11], z[12], z[13], z[14], z[15], '\0'};
    strcpy(currentTime, copy);
}

/**********************************************************************************
Description: Upon login, this function adds the user's details to the login 
    history including the time & date they logged in. It then exports these details
    into the "log.txt" file.
    @param user - struct containing all the user's details
**********************************************************************************/
void 
updateLoginHistory(struct personnel user)
{
    str12 currentDate,
          currentTime;
     FILE *fp;
    
    getDate(currentDate, 1);
    getTime(currentTime);

    fp = fopen("log.txt", "a");
    if (fp == NULL)
        fp = fopen("log.txt", "w");
    
    fprintf(fp, "%d %s %d %s %s\n", user.personnelID, user.username, user.access, currentTime, currentDate);
    fclose(fp);
}

/**********************************************************************************
Description: This function displays the login history. It displays every user, and
        their details & login date, who logged in the application. Only admins may 
        be able to  view all users who logged in, while managers may only be able 
        to check all users w/ an access level of 3
Precondition: Only admins & managers have access to this feature
        @param access - 1 if the user accessing this feature is an admin;
                        2 if manager
**********************************************************************************/
void 
displayLoginHistory(int access)
{
    struct personnel record[MAX_PERSONNEL * 2];
    struct personnel temp; // placeholder struct for readability purposes 

     str12 dates[MAX_PERSONNEL * 2], // arrays to hold login date & time 
           time[MAX_PERSONNEL * 2],
           currentDate; 
    
       int logCount = 0,
           userLogCount = 0,
           i = 0;
    
      FILE *fp;

    getDate(currentDate, 1);

    fp = fopen("log.txt", "r"); // fp can never = null bc updateLoginHistory() always creates a file

    while (fscanf(fp, "%d ", &record[i].personnelID) != EOF)
    {
        fscanf(fp, "%s %d",  record[i].username, &record[i].access);
        fscanf(fp, "%s %s", time[i], dates[i]); 
        logCount++;
        i++;
    }
    fclose(fp);

    displayHeader();
	displayAdminHeader();
	printf("%-44c Login History as of %s %44c\n", TVLINE, currentDate, TVLINE);
	printLine(TVLLINE, THLINE, THDLINE, 5);
	for(i = 0; i < 6; i++)
			printf("%c", THLINE);
	printLine(THDLINE, THLINE, THDLINE, 42);
	for(i = 0; i < 41; i++)
			printf("%c", THLINE);
	printLine(THDLINE, THLINE, THDLINE, 7);
	for(i = 0; i < 12; i++)
			printf("%c", THLINE);
	printf("%c", TVRLINE);
    printf("\n%c %-3s %c %-4s %c %-40s %c %-39s %c %-5s %c %-10s %c\n", TVLINE, "No.", TVLINE, "ID:", TVLINE, "Username", TVLINE, "Access Level", TVLINE, "Time:", TVLINE, "Datestamp:", TVLINE);

    if (access == 1) 
    {
        for (i = 1; i <= logCount; i++)
        {
            temp = record[logCount - i]; 
            displayLoginHistoryDivider();
            printf("\n%c %-3d %c %-4d %c %-40s %c %-39s %c %-5s %c %-10s %c\n", TVLINE, i + 1, TVLINE,  temp.personnelID, TVLINE, temp.username, TVLINE, temp.access == 1 ? "Admin" : temp.access == 2 ? "Manager" : "User", TVLINE, time[logCount - i], TVLINE, dates[logCount - i], TVLINE);
        }
    }

    if (access == 2)
    {
        for (i = 1; i <= logCount; i++)
        {   
            temp = record[logCount - i];
            if (temp.access != 1) // managers may only be able to view managers & users 
            {
                userLogCount++;
                displayLoginHistoryDivider();
                printf("\n%c %-3d %c %-4d %c %-40s %c %-39s %c %-5s %c %-10s %c\n", TVLINE, i, TVLINE,  temp.personnelID, TVLINE, temp.username, TVLINE, temp.access == 1 ? "Admin" : temp.access == 2 ? "Manager" : "User", TVLINE, time[logCount - i], TVLINE, dates[logCount - i], TVLINE);
            }
        }
    } 
    
    printLine(TBLCORNER, THLINE, THULINE, 5);
    for(i = 0; i < 6; i++)
        printf("%c", THLINE);
    printLine(THULINE, THLINE, THULINE, 42);
    for(i = 0; i < 41; i++)
        printf("%c", THLINE);
    printLine(THULINE, THLINE, THULINE, 7);
    for(i = 0; i < 12; i++)
        printf("%c", THLINE);
    printf("%c", TBRCORNER);
}
/**********************************************************************************
Description: This function displays the admin menu and serves as the main hub for 
	         all of the possible actions that an admin can perform.
	@param personnelArray: An array of structs that stores personnel information.
	@param numPersonnel: The number of current personnels.
	@param taskArray: An array of structs that stores task information.
	@param numTasks: The number of tasks.
	@param projectArray: An array of structs that stores project information.
	@param numProjects: The number of projects.
	@return 0 if user wishes to go back to the main menu 
            1 if they wish to exit the program
**********************************************************************************/
int
adminMenu(struct personnel personnelArray[], 
	      int *numPersonnel,
	  	  struct task taskArray[],
	  	  int numTasks,
	  	  struct project projectArray[],
	  	  int numProjects)
{
	int option = 0;
    
    do
	{
        displayHeader();
       	displayAdminHeader();
        
       	printf("%-50c [1] View all Users %50c", TVLINE, TVLINE);
       	printf("\n%-50c [2] Add New User %52c", TVLINE, TVLINE);
       	printf("\n%-50c [3] Update User %53c", TVLINE, TVLINE);
       	printf("\n%-50c [4] Delete User %53c", TVLINE, TVLINE);
       	printf("\n%-50c [5] Archive User %52c", TVLINE, TVLINE);
       	printf("\n%-50c [6] Assign Project %50c", TVLINE, TVLINE);
		printf("\n%-50c [7] Login History%52c", TVLINE, TVLINE);
       	printf("\n%-50c [8] Back to Main Menu %47c", TVLINE, TVLINE);
       	printf("\n%-50c [9] Exit %60c\n", TVLINE, TVLINE);
        
        printLine(TBLCORNER, THLINE, TBRCORNER, 118);
        
        do
		{
			printf("\n\nOption: ");
			scanf("%d", &option);
			fflush(stdin);

			if(option < 1 || option > 9)
		    	printf("\e[1;31m" "Invalid Input. Try again.\n" "\e[1;97m");
		    		
		} while(option < 1 || option > 9);
		
		fflush(stdin);
		system("cls");

        switch(option)
		{
			case 1:
				viewUsers(personnelArray, *numPersonnel);
				clearScreen();
				break;
		    case 2:
				addUser(personnelArray, numPersonnel);
				clearScreen();
				break;
			case 3:
				updateUser(personnelArray, *numPersonnel);
				clearScreen();
				break;
			case 4: //t
				deleteUser(personnelArray, numPersonnel, taskArray, numTasks, projectArray, numProjects);
				clearScreen();
				break;
			case 5:
				archiveUser(personnelArray, *numPersonnel);
				clearScreen();
				break;
			case 6:
				if(numProjects > 0)
                	assignProject(projectArray, numProjects, personnelArray, *numPersonnel);
                else
                	printf("\e[1;31m" "There are no registered tasks yet. Please make a task first.\n" "\e[1;97m");
                clearScreen();
				break;
			case 7:	
				displayLoginHistory(1);
				clearScreen();
				break;
			case 8:
			case 9: 
				printf("Logging out.\n");
				clearScreen();
				break;
        }
    } while(option <= 7);

	if (option == 8)
		return 0;
	return 1;

}

/**********************************************************************************
Description: This function asks the user to input a new password for a personnel
            account. It validates the new password by checking if it is unidentical 
            to their old password and if it doesn't exceed the password character 
            limit of 40. If the new password is invalid, then the function calls 
            itself.
    @param password - the existing password of the personnel, also where the 
            new password will be stored
**********************************************************************************/
void 
changePW(str40 password)
{   
    str40 newPass;  

    printf("Input new password: ");
    scanf("%s", newPass);

    // recursive cases
        if (strcmp(newPass, password) == 0) 
        {
            printf("\e[1;31m" "Invalid input. Please choose a different password.\n" "\e[1;97m");
            changePW(password);
        } 
        else if (strlen(newPass) > 40) { 
            printf("\e[1;31m" "Invalid input. Password must not be greater than 40 characters.\n" "\e[1;97m");
			changePW(password);
        }
    // base case
        strcpy(password, newPass);
        printDivider();
        printf("\e[1;32m" "\nPassword updated successfully.\n" "\e[1;97m");
        clearScreen();
}

/**********************************************************************************
Description: This function displays tasks assigned to the login user where the 
    current date is included within the range of the task startdate and enddate.
    @param taskArray - struct array containing all task records to be accessed
    @param numTasks - number of existing tasks in taskArray
    @param personnelID - ID of the user  
**********************************************************************************/
void 
showCurrentTasks(struct task taskArray[], 
                 int numTasks,
                 int personnelID)
{
    str12 currentDate, 
          start,
          end;
      int count = 0, 
          current;

    getDate(currentDate, 3); // gets date in YYYY/MM/DD
    
    
    displayCurrentTaskHeader(); 
    for (int i = 0; i < numTasks; i++)
    {   
        if (taskArray[i].assignID == personnelID)
        {
           reverseDate(taskArray[i].startdate, start);
           reverseDate(taskArray[i].enddate, end);
           current = (strcmp(start, currentDate) != 1) && (strcmp(currentDate, end) != 1);
                            // @todo : debug / recheck
           if (current)
           {
                count++;
                printLine(TTLCORNER, THLINE, TTRCORNER, 118);
                printf("\n");
                displayTask(taskArray[i]);
           }
        }
    }
    // @todo improve
    printf("\n");
    printf("Total number of tasks for today: %d\n\n", count);
}

/**********************************************************************************
 Description: This function displays tasks assigned to the login user
    @param taskArray - struct array containing all task records to be accessed
    @param numTasks - number of existing tasks in taskArray
    @param personnelID - ID of the user  
**********************************************************************************/
void
showAllTasks(struct task taskArray[],
              int numTasks,
              int personnelID)
{
    int count = 0;
    
    displayAllTaskHeader();

    for (int i = 0; i < numTasks; i++)
        if (taskArray[i].assignID == personnelID)
        {
            count++;
            printLine(TTLCORNER, THLINE, TTRCORNER, 118);
                printf("\n");
                displayTask(taskArray[i]);
        }
    printf("\n");
    printf("Total number of tasks assigned: %d\n\n", count);
}

/**********************************************************************************
 Description: This function displays all tasks assigned to the login user and 
    allows the user to update a task's status
    @param taskArray - struct array containing all task records to be accessed
    @param numTasks - number of existing tasks in taskArray
    @param personnelID - ID of the user  
**********************************************************************************/
void
updateTaskStatus(struct task taskArray[], 
                 int numTasks, 
                 int personnelID)
{
    int targetID, taskIndex, valid;
    
    showAllTasks(taskArray, numTasks, personnelID); 
    do {
        printf("Enter ID of task to be updated: \n");
        scanf("%d", &targetID);
        taskIndex = findTask(targetID, taskArray, numTasks);
        valid = (taskIndex != -1) && (taskArray[taskIndex].assignID == personnelID);

        if (!valid)
            printf("\nInvalid ID. Please input from the given task IDs\n");
    } while (!valid);
    system("cls");

    displayTask(taskArray[taskIndex]);
    printf("Update Task Status\n\n");
    printf("[1] Not Started\n");
    printf("[2] In Progress\n");
    printf("[3] Done\n\n");
    
    do {
        printf("Update status [1-3]: ");
        scanf("%d", &taskArray[taskIndex].status);
        if (taskArray[taskIndex].status < 1 || taskArray[taskIndex].status > 3)
            printf("Invalid input.\n");
    } while (taskArray[taskIndex].status < 1 || taskArray[taskIndex].status > 3);
    
    printf("\nStatus of Task %d has been updated.\n\n", taskArray[taskIndex].status);
}

/**********************************************************************************
Description: This function displays the user menu when the login user has an access
        value of 3. It allows the user to view their tasks and update their status.
        If this is the user's first login, then the functions first prompts them to 
        change their password, before displaying the menu. 
    @param user - struct containing the login user's details
    @param taskArray - struct array containing all the tasks to be accessed 
    @param numTasks - number of existing tasks in taskArray
    @return 0 if user wishes to go back to the main menu;
            1 if user wishes to exit the program
**********************************************************************************/
int 
userMenu(struct personnel user,
         struct task taskArray[], 
         int numTasks, struct personnel personnelArray[],
         int numPersonnel)
{
    int option, i; 
    
    // If this is the user's first login
    if (strcmp(user.password, "tempPass") == 0)
    {
        displayHeader();
        displayUserHeader();
        printf("%c %-116s %c\n", TVLINE, "Since this is your first login, you are required to change your password.", TVLINE);
        printLine(TBLCORNER, THLINE, TBRCORNER, 118);
        printf("\n");
        changePW(user.password);

        FILE *fPersonnel = fopen("preloaded.txt", "w");

        for(i = 0; i < numPersonnel; i++)
        {
            if (personnelArray[i].personnelID == user.personnelID)
                strcpy(personnelArray[i].password, user.password);
                
            fprintf(fPersonnel, "%d\n%s\n%s\n%d\n%d\n\n", personnelArray[i].personnelID, personnelArray[i].username, personnelArray[i].password, 
                                                    personnelArray[i].active, personnelArray[i].access);
        }

        fclose(fPersonnel);

        system("cls");
    }

    do {
        displayHeader();
        displayUserHeader();
        printf(  "%-50c [1] Show Today's Tasks %46c", TVLINE, TVLINE);
       	printf("\n%-50c [2] Show all Assigned Tasks %41c", TVLINE, TVLINE);
        printf("\n%-50c [3] Update Task Status %46c", TVLINE, TVLINE); 
        printf("\n%-50c [4] Back to main menu %47c", TVLINE, TVLINE);
        printf("\n%-50c [5] Exit %60c\n", TVLINE, TVLINE);
        printLine(TBLCORNER, THLINE, TBRCORNER, 118);

        do {
            printf("\nInput option: ");
            scanf("%d", &option);
            if (option < 1 || option > 5)
                printf("Invalid option. Input 1-5 only.\n");
        } while (option < 1 || option > 5);

        system("cls");
        fflush(stdin);

        switch(option){
            case 1: 
                showCurrentTasks(taskArray, numTasks, user.personnelID);
                break;
            case 2: 
                showAllTasks(taskArray, numTasks, user.personnelID);
                break; 
            case 3: 
                updateTaskStatus(taskArray, numTasks, user.personnelID);
                break;
            case 4:
            case 5: 
                printf("Logging out.\n");
        }
        clearScreen();
    } while (option <= 3);

    if (option == 4)
        return  0;
    return 1;
}
