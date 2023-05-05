// Defines all the extended ASCII characters to be used for the program's GUI.
#define HLINE 			205
#define VLINE 			186
#define TLCORNER	 	201
#define TRCORNER 		187
#define BLCORNER 		200
#define BRCORNER 		188

#define THLINE 			196
#define TVLINE 			179
#define TTLCORNER		218
#define TTRCORNER		191
#define TBLCORNER		192
#define TBRCORNER		217
#define THDLINE			194
#define THULINE			193
#define TVLLINE			195
#define TVRLINE			180
#define TVHLINE			197

/**********************************************************************************
Description: This function prints out a line composed of 3 parts of the chosen 
			 extended ASCII Characters.
@param lSide: Extended ASCII Character for the left most part of the line.
	   mLine: Extended ASCII Character in the middle that will be iterated.
	   rSide: Extended ASCII Character for the right most part of the line.
	   num: Number of times the mLine character will be printed.
**********************************************************************************/
void 
printLine(char lSide, 
		  char mLine, 
		  char rSide, 
		  int num)
{
    int i;
    
    printf("%c", lSide);
    for(i = 0; i < num; i++)
        printf("%c", mLine);
    printf("%c", rSide);
}

void 
printDivider()
{
    int i;
    
    printf("\n");
    for(i = 0; i < 120; i++)
		printf("%c", THLINE);
}

/**********************************************************************************
Description: This function displays the program's main header.
**********************************************************************************/
void 
displayHeader()
{
	
	printLine(TLCORNER, HLINE, TRCORNER, 118);
	printf("\n%-39c Andrea & Ryan's Project Management App ! %39c\n", VLINE, VLINE);
	printLine(BLCORNER, HLINE, BRCORNER, 118);
}

/**********************************************************************************
Description: This function displays the primary header of the admin menu.
**********************************************************************************/
void 
displayAdminHeader()
{
	
	printf("\n");
	printLine(TTLCORNER, THLINE, TTRCORNER, 118);	
	printf("\n%-54c Admin Menu %54c\n", TVLINE, TVLINE);
	printLine(TVLLINE, THLINE, TVRLINE, 118);
	printf("\n");
}

/**********************************************************************************
Description: This function displays all the personnels and their respective details. 
@param personnelArray: An array of structs that stores personnel information.
	   numPersonnel: The number of current personnels.
**********************************************************************************/
void 
viewUsers(struct personnel personnelArray[], 
		  int numPersonnel)
{
	int  i;
	char accessLevel[10], 
	     activeStatus[10];
	
	displayHeader();
	displayAdminHeader();
	printf("%-49c Viewing All Users ... %48c", TVLINE, TVLINE);
	
	printf("\n");
	printLine(TVLLINE, THLINE, THDLINE, 8);
	for(i = 0; i < 43; i++)
		printf("%c", THLINE);
	printLine(THDLINE, THLINE, THDLINE, 43);
	for(i = 0; i < 10; i++)
		printf("%c", THLINE);
	printLine(THDLINE, THLINE, TVRLINE, 10);
	printf("\n");
	
	printf("%c %-6s %c %-41s %c %-41s %c %-8s %c %-8s %c\n", 
		TVLINE, "ID", TVLINE, "Username", TVLINE, 
		"Password", TVLINE, "Active", TVLINE, "Access", TVLINE);

	printLine(TVLLINE, THLINE, TVHLINE, 8);
	for(i = 0; i < 43; i++)
		printf("%c", THLINE);
	printLine(TVHLINE, THLINE, TVHLINE, 43);
	for(i = 0; i < 10; i++)
		printf("%c", THLINE);
	printLine(TVHLINE, THLINE, TVRLINE, 10);
	printf("\n");
	
	for (i = 0; i < numPersonnel; i++)
	{
	    switch (personnelArray[i].access) // displays the corresponding string for the access level.
		{
	        case 1:
	            strcpy(accessLevel, "Admin");
	            break;
	        case 2:
	            strcpy(accessLevel, "Manager");
	            break;
	        case 3:
	            strcpy(accessLevel, "User");
	            break;
	        default:
	            strcpy(accessLevel, "Disabled");
	            break;
	    }
	    if (personnelArray[i].active == 1) // displays the corresponding string for the active status.
	    	strcpy(activeStatus, "Active");
	    else
	        strcpy(activeStatus, "Inactive");
	    
	    printf("%c %-6d %c %-41s %c %-41s %c %-8s %c %-8s %c\n",
	        TVLINE, personnelArray[i].personnelID,              
	        TVLINE, personnelArray[i].username,                 
	        TVLINE, personnelArray[i].password,                 
	        TVLINE, activeStatus, TVLINE, 
			accessLevel, TVLINE);                       
	}


	printLine(TBLCORNER, THLINE, THULINE, 8);
	for(i = 0; i < 43; i++)
		printf("%c", THLINE);
	printLine(THULINE, THLINE, THULINE, 43);
	for(i = 0; i < 10; i++)
		printf("%c", THLINE);
	printLine(THULINE, THLINE, TBRCORNER, 10);
}

/**********************************************************************************
Description: This function displays the secondary header of the admin menu for 
			 Adding a new user.
**********************************************************************************/
void 
displayAddUserHeader()
{
	displayHeader();
	displayAdminHeader();
	
	printf("%-50c Adding New User ... %49c", TVLINE, TVLINE);
	printf("\n");
	printLine(TBLCORNER, THLINE, TBRCORNER, 118);
	printf("\n");	
}

/**********************************************************************************
Description: This function displays the secondary header of the admin menu for 
			 Updating a user.
**********************************************************************************/
void
displayUpdateUserHeader()
{
	int i;
	
	displayHeader();
	displayAdminHeader();
	
	printf("%-51c Updating User ... %50c", TVLINE, TVLINE);
	printf("\n");
	printLine(TVLLINE, THLINE, THDLINE, 59);
	for(i = 0; i < 58; i++)
		printf("%c", THLINE);
	printf("%c\n", TVRLINE);
}

/**********************************************************************************
Description: This function displays a divider for the Update User Interface.
**********************************************************************************/
void
displayUpdateUserDivider()
{
	int i;
	
	printLine(TBLCORNER, THLINE, THULINE, 59);
	for(i = 0; i < 58; i++)
		printf("%c", THLINE);
	printf("%c\n", TBRCORNER);
}

/**********************************************************************************
Description: This function displays the primary header for the Manager Menu.
**********************************************************************************/
void
displayManagerHeader()
{
	
	printf("\n");
	printLine(TTLCORNER, THLINE, TTRCORNER, 118);	
	printf("\n%-53c Manager Menu %53c\n", TVLINE, TVLINE);
	printLine(TVLLINE, THLINE, TVRLINE, 118);
	printf("\n");
}

/**********************************************************************************
Description: This function displays the secondary header of the Manager menu for 
			 Adding a Project.
**********************************************************************************/
void
displayAddProjectHeader()
{
	displayHeader();
	displayManagerHeader();
	printf("%-48c Adding New Project ... %48c", TVLINE, TVLINE);
	printf("\n");
	printLine(TVLLINE, THLINE, TVRLINE, 118);
	printf("\n");
	printLine(TVLINE, 32, TVLINE, 118);
}

/**********************************************************************************
Description: This function displays the secondary header of the Manager menu for 
			 Adding a Task.
**********************************************************************************/
void
displayAddTaskHeader()
{
	displayHeader();
	displayManagerHeader();
	printf("%-49c Adding New Task ... %50c", TVLINE, TVLINE);
	printf("\n");
	printLine(TVLLINE, THLINE, TVRLINE, 118);
	printf("\n");
	printLine(TVLINE, 32, TVLINE, 118);
}

/**********************************************************************************
Description: This function displays the divider for the Add Task User Interface.
**********************************************************************************/
void
displayAddTaskDivider()
{
	printf("\n");
	printLine(TVLINE, 32, TVLINE, 118);	
    printf("\n");
	printLine(TBLCORNER, THLINE, TBRCORNER, 118);
}

/**********************************************************************************
Description: This function displays the secondary header of the Manager menu for 
			 Displaying Tasks.
**********************************************************************************/
void
displayTasks(struct task taskArray[], 
             int numTasks)
{
	int  i, j;
	char status[20];
	
	displayHeader();
    displayManagerHeader();
	printf("%-49c Viewing All Tasks ... %48c\n", TVLINE, TVLINE);
	
	for(j = 0; j < numTasks; j++)
	{
		printLine(TVLLINE, THLINE, THDLINE, 17);
		for(i = 0; i < 16; i++)
			printf("%c", THLINE);
		printLine(THDLINE, THLINE, THDLINE, 49);
		for(i = 0; i < 16; i++)
			printf("%c", THLINE);		
		printLine(THDLINE, THLINE, TVRLINE, 16);
	
		printf("\n%c ProjectID: %-4d %c TaskID: %-6d %c Name: %-41s %c S: %-11s %c E: %-11s %c\n", 
						TVLINE, taskArray[j].projectID, TVLINE, taskArray[j].taskID, TVLINE, 
						taskArray[j].name, TVLINE, taskArray[j].startdate, TVLINE, taskArray[j].enddate, TVLINE);
						
		printLine(TVLLINE, THLINE, THULINE, 17);
		for(i = 0; i < 16; i++)
			printf("%c", THLINE);
		printLine(THULINE, THLINE, THULINE, 49);
		for(i = 0; i < 16; i++)
			printf("%c", THLINE);		
		printLine(THULINE, THLINE, TVRLINE, 16);
		
		switch (taskArray[j].status)
		{
	        case 1:
	            strcpy(status, "Not Started");
	            break;
	        case 2:
	            strcpy(status, "In Progress");
	            break;
	        case 3:
	            strcpy(status, "Done");
	            break;
	    }
		
		printf("\n%c Desciption: %-104s %c\n", TVLINE, taskArray[j].description, TVLINE);
		printf("%c Assigned Personnel: %-96d %c\n", TVLINE, taskArray[j].assignID, TVLINE);
		printf("%c Status: %-108s %c\n", TVLINE, status, TVLINE);
		printf("%c Sequence: %-106d %c\n", TVLINE, taskArray[j].sequence, TVLINE);
		printf("%c Total Duration [Days]: %-10.2f %84c\n", TVLINE, taskArray[j].totalDuration, TVLINE);
	}
	
	printLine(TBLCORNER, THLINE, TBRCORNER, 118);
	printf("\n");
}

/**********************************************************************************
Description: This function displays the secondary header of the Manager menu for 
			 Updating a Task.
**********************************************************************************/
void
displayUpdateTaskHeader()
{
	printf("%-51c Updating Task ... %50c\n", TVLINE, TVLINE);
	printLine(TVLLINE, THLINE, TVRLINE, 118);
}

/**********************************************************************************
Description: This function displays the secondary header of the Manager menu for 
			 Displaying the list of Active Personnels.
**********************************************************************************/
void
displayPersonnelListHeader()
{
	displayHeader();
    displayManagerHeader();
    printf("%-48c Active Personnel List: %48c\n", TVLINE, TVLINE);
	printLine(TVLLINE, THLINE, TVRLINE, 118);
}

/**********************************************************************************
Description: This function displays the secondary header of the Manager menu for 
			 Assigning a task to a personnel.
**********************************************************************************/
void
displayAssignTaskHeader()
{
	printf("%-50c Assinging Task ... %50c\n", TVLINE, TVLINE);
	printLine(TVLLINE, THLINE, TVRLINE, 118);
}

/**********************************************************************************
Description: This function displays the secondary header of the Manager menu for 
			 Displaying Project Details.
**********************************************************************************/
void
displayProjectDetailsHeader()
{
	displayHeader();
    displayManagerHeader();
    printf("%-46c Viewing Active Projects ... %45c\n", TVLINE, TVLINE);
}

/**********************************************************************************
Description: This function displays the secondary header of the Manager menu for 
			 Displaying Delayed Tasks.
**********************************************************************************/
void
displayDelayedTaskHeader()
{
	displayHeader();
    displayManagerHeader();
	printf("%-47c Viewing Delayed Tasks ... %46c\n", TVLINE, TVLINE);
	printLine(TVLLINE, THLINE, TVRLINE, 118);
}

/**********************************************************************************
Description: This function displays the secondary header of the Manager menu for 
			 Running Project Completion.
**********************************************************************************/
void
displayProjectCompletionHeader()
{	
	displayHeader();
    displayManagerHeader();
	printf("%-44c Running Project Completion ... %44c\n", TVLINE, TVLINE);
	printLine(TVLLINE, THLINE, TVRLINE, 118);
}

void
displayLoginHistoryDivider()
{
	int i;

	printLine(TVLLINE, THLINE, TVHLINE, 5);
	for(i = 0; i < 6; i++)
			printf("%c", THLINE);
	printLine(TVHLINE, THLINE, TVHLINE, 42);
	for(i = 0; i < 41; i++)
			printf("%c", THLINE);
	printLine(TVHLINE, THLINE, TVHLINE, 7);
	for(i = 0; i < 12; i++)
			printf("%c", THLINE);
	printf("%c", TVRLINE);
}

void
displayProjects(struct project projectArray[], 
           int numProjects)
{
	int i, j;
	str12 status;

    printf("%-47c Viewing All Projects ... %47c\n", TVLINE, TVLINE);
    
    for(j = 0; j < numProjects; j++)
    {
        printLine(TVLLINE, THLINE, THDLINE, 17);
		for(i = 0; i < 48; i++)
			printf("%c", THLINE);
		printLine(THDLINE, THLINE, THDLINE, 21);
		for(i = 0; i < 29; i++)
			printf("%c", THLINE);		
		printf("%c", TVRLINE);

        switch (projectArray[j].status)
		{
	        case 1:
	            strcpy(status, "Not Started");
	            break;
	        case 2:
	            strcpy(status, "In Progress");
	            break;
	        case 3:
	            strcpy(status, "Done");
	            break;
	    }
			
		printf("\n%c ProjectID: %-4d %c Name: %-40s %c Status: %-11s %c Assigned Personnel: %-7d %c\n", 
							TVLINE, projectArray[j].projectID, TVLINE, projectArray[j].name, TVLINE, status,
							TVLINE, projectArray[j].assignID, TVLINE);
			
		printLine(TVLLINE, THLINE, THULINE, 17);
		for(i = 0; i < 48; i++)
			printf("%c", THLINE);
		printLine(THULINE, THLINE, THULINE, 21);
		for(i = 0; i < 29; i++)
			printf("%c", THLINE);		
	    printf("%c", TVRLINE);
				
		printf("\n%c Description: %-103s %c\n", TVLINE, projectArray[j].description, TVLINE);
		printf("%c Project Completion [%%]: %-10.2f %83c\n", TVLINE, projectArray[j].completion, TVLINE); 
    }
	printLine(TBLCORNER, THLINE, TBRCORNER, 118);
	printf("\n");
}

void
displayProjectDetail(struct project projectArray[], 
					 int index)
{
	int i;
	str12 status;

		switch (projectArray[index].status)
		{
	        case 1:
	            strcpy(status, "Not Started");
	            break;
	        case 2:
	            strcpy(status, "In Progress");
	            break;
	        case 3:
	            strcpy(status, "Done");
	            break;
	    }

		printLine(TVLLINE, THLINE, THDLINE, 17);
		for(i = 0; i < 48; i++)
			printf("%c", THLINE);
		printLine(THDLINE, THLINE, THDLINE, 21);
		for(i = 0; i < 29; i++)
			printf("%c", THLINE);		
		printf("%c", TVRLINE);
			
		printf("\n%c ProjectID: %-4d %c Name: %-40s %c Status: %-11s %c Assigned Personnel: %-7d %c\n", 
                                TVLINE, projectArray[index].projectID, TVLINE, projectArray[index].name, TVLINE, status, 
                                TVLINE, projectArray[index].assignID, TVLINE);
			
		printLine(TVLLINE, THLINE, THULINE, 17);
		for(i = 0; i < 48; i++)
			printf("%c", THLINE);
		printLine(THULINE, THLINE, THULINE, 21);
		for(i = 0; i < 29; i++)
			printf("%c", THLINE);		
	    printf("%c", TVRLINE);
				
		printf("\n%c Desciption: %-104s %c\n", TVLINE, projectArray[index].description, TVLINE);
        printf("%c Project Completion [%%]: %-10.2f %83c\n", TVLINE, projectArray[index].completion, TVLINE);
		printLine(TBLCORNER, THLINE, TBRCORNER, 118);
}

void
displayAssignProjectHeader()
{
	printf("%-50c Assinging Project ... %47c\n", TVLINE, TVLINE);
	printLine(TVLLINE, THLINE, TVRLINE, 118);
}

void
displayUserHeader()
{
	printf("\n");
	printLine(TTLCORNER, THLINE, TTRCORNER, 118);	
	printf("\n%-54c User Menu %55c\n", TVLINE, TVLINE);
	printLine(TVLLINE, THLINE, TVRLINE, 118);
	printf("\n");
}

void
displayCurrentTaskHeader()
{
	displayHeader();
	displayUserHeader();
	printf("%-52c Today's Tasks! %52c\n", TVLINE, TVLINE);
	printLine(TBLCORNER, THLINE, TBRCORNER, 118);
	printf("\n");
}

void
displayAllTaskHeader()
{
	displayHeader();
	displayUserHeader();
	printf("%-49c All Assigned Tasks! %50c\n", TVLINE, TVLINE);
	printLine(TBLCORNER, THLINE, TBRCORNER, 118);
	printf("\n");
}
