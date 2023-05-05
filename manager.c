/**********************************************************************************
Description: This function initializes the project struct array from the project 
             text file.
    @param projectArray - destination struct array where the project information
            will be stored
    @param numProjects - address containing the number of existing projects
    @param fileName - file name of the source text file containing the project data
**********************************************************************************/
void
loadProjectRecord(struct project projectArray[], 
                  int * numProjects,
                  char* fileName)
{
    FILE *fProj; 
    
    fProj = fopen(fileName, "r");

    if (fProj == NULL)
    {
    	fProj = fopen(fileName, "w");
	    if(fProj != NULL)
	        fclose(fProj);
	}
    else 
	{
        while (fscanf(fProj,"%d ", &projectArray[*numProjects].projectID) != EOF)
        {
            fscanfLine(fProj, projectArray[*numProjects].name, 41);
            fscanf(fProj, "%d", &projectArray[*numProjects].assignID);
            fscanf(fProj, "%d", &projectArray[*numProjects].status);
            fscanf(fProj, "%f ", &projectArray[*numProjects].completion);
            fscanfLine(fProj, projectArray[*numProjects].description, 101); 

            (*numProjects)++;
        }
        fclose (fProj);
    }
}

/**********************************************************************************
Description: This function initializes the tasks struct array from the tasks
            text file.
    @param tasktArray - destination struct array where the task information
            will be stored
    @param numTasks - address containing the number of existing tasks
    @param fileName - file name of the source text file containing the task data
**********************************************************************************/
void
loadTaskRecord(struct task taskArray[],
               int * numTasks,
               char* fileName)
{
    FILE *fTasks; 

    fTasks = fopen(fileName, "r");
    
    if (fTasks == NULL)
    {
    	fTasks = fopen(fileName, "w");
	    if(fTasks != NULL)
	        fclose(fTasks);
	}
    else 
    {
        while (fscanf(fTasks, "%d ", &taskArray[*numTasks].taskID) != EOF)
        {
            fscanfLine(fTasks, taskArray[*numTasks].name, 41);
            fscanf(fTasks, "%d ", &taskArray[*numTasks].sequence);
            fscanfLine(fTasks, taskArray[*numTasks].description, 101);
            fscanf(fTasks, "%d", &taskArray[*numTasks].projectID);
            fscanf(fTasks, "%s\n%s", taskArray[*numTasks].startdate, taskArray[*numTasks].enddate);
            fscanf(fTasks, "%f", &taskArray[*numTasks].totalDuration);
            fscanf(fTasks, "%d", &taskArray[*numTasks].status);
            fscanf(fTasks, "%d", &taskArray[*numTasks].assignID);
            (*numTasks)++;
        }
        fclose(fTasks);
    }
}

/**********************************************************************************
Description: This function generates a randomized projectID to be assigned to
             newly added projects. If the newly generated ID already belongs to a 
             preexisting project, then it will generate another ID. 
    @param projectArray - struct array to be accessed 
    @param numProjects - number of existing projects
    @returns the generated project ID
**********************************************************************************/
int 
generateProjID(struct project projectArray[], 
               int numProjects)
{
    int projectID, 
        uniqueID,
		i;
		
    srand(time(NULL));
    
    do
	{
        uniqueID = 1;
        projectID = rand() % 9000 + 1000;
       	for(i = 0; i < numProjects; i++) // checks if the projectID already exists
           	if (projectArray[i].projectID == projectID)
               	uniqueID = 0;   
    } while(!uniqueID);

    return projectID;
}

/**********************************************************************************
Description: Using a linear search algorithm, this function returns the index of a 
    given personnelID in the personnelArray.
    @param key - the target personnelID that needs to be searched 
    @param personnelArray - struct array containing all the personnel information
    @param numPersonnel - number of existing personnel
    @returns the index of the personnelID in the array, if unfound, returns -1
**********************************************************************************/
int findPersonnel(int key, 
                  struct personnel personnelArray[], 
                  int numPersonnel)
{
    int index = 0, 
		found = 0; 

    while (!found && index < numPersonnel)
    {
        (key == personnelArray[index].personnelID) ?
            found = 1: 
            index++;
    }
    
    if (found)
        return index; 
        
    return -1; 
}

/**********************************************************************************
Description: Given a projectName, this function searches for a project with 
            the same name
    @param projectArray - struct array containing all projects 
    @param numProjects -  number of existing projects in projectArray
    @param projectName - the projectName to be searched for 

    @return -the index of the project with the same name;
            -1 if unfound
**********************************************************************************/
int 
checkProjectName(struct project projectArray[], 
		               int numProjects, 
		               str40 projectName)
{
	int i;

    for(i = 0; i < numProjects; i++)
    	if(strcmp(projectArray[i].name, projectName) == 0)
        	return i;
        
    return -1; 
}

/**********************************************************************************
Description: Given the maximum number of projects has not been reached yet, 
            this function allows the user to add a new project and input all 
            the necessary details. 
    @param projectArray - struct array where the new project will be stored 
    @param numProjects - number of existing projects
    @param personnelArray - struct array containing all personnel records; 
            needed for validating the input assignID
    @param numPersonnel - number of existing personnel in personnelArray[]
**********************************************************************************/
void 
addProject(struct project projectArray[],
           int *numProjects, 
           struct personnel personnelArray[], 
           int numPersonnel)
{
    int    projectExists,
		   found, 
           count = 0,
           index,
		   i; 
    struct project newProject;

    if (*numProjects == MAX_PROJECTS)
        printf("Maximum project count reached. You cannot add a new project.\n");
    else 
    {
    	displayAddProjectHeader();
    	printf("\n%c %-116s %c", TVLINE, "To whom would you like to assign this new project to?",TVLINE);
    	printf("\n");
    	printLine(TVLINE, 32, TVLINE, 118);	
    	for (i = 0; i < numPersonnel; i++)
        {
            if (personnelArray[i].access ==2) 
            {
                count++;
                printf("\n%c \t%d. %d %-102s %c", TVLINE, count, personnelArray[i].personnelID, personnelArray[i].username, TVLINE);
                if(count == 0)
                    printf("\n%c" "\e[1;31m" " %-116s " "\e[1;97m" "%c", TVLINE, "There are no Active Personnels.", TVLINE);	
       
            }
        }
    	displayAddTaskDivider();
    	
    	do 
		{
            printf("\nID of Assigned Personnel: ");
            scanf("%d", &newProject.assignID);
            fflush(stdin);

            index = findPersonnel(newProject.assignID, personnelArray, numPersonnel);
            found = index != -1;

            if(found)
                if (personnelArray[index].access != 2)
                    found = 0;
            
            if (!found)
                printf("\e[1;31m" "Invalid Personnel. Please input an existing Manager Personnel ID.\n" "\e[1;97m");
                        
        } while (!found);
    	
        newProject.projectID = generateProjID(projectArray, *numProjects); 
        
        do 
		{
		    printf("Project Name: ");
        	scanfLine(newProject.name, 41);
        	fflush(stdin);
		    
		    if(strlen(newProject.name) > 40)
		        printf("\e[1;31m" "Invalid input. Project name must not be greater than 40 characters.\n" "\e[1;97m");
		        
		    projectExists = checkProjectName(projectArray, *numProjects, newProject.name);

			if(projectExists >= 0)
				printf("\e[1;31m" "This Project already exists. Try again.\n" "\e[1;97m");
		    
		} while(strlen(newProject.name) > 40 || projectExists >= 0);

        
        do 
		{
            printf("Project Status: ");
            scanf("%d", &newProject.status);
            fflush(stdin);
            
            if (newProject.status < 1 || newProject.status > 3)
                printf("\e[1;31m" "Invalid Input. Please choose between [1] Not Started [2] In Progress [3] Done.\n" "\e[1;97m");
                
        } while (newProject.status < 1 || newProject.status > 3);
        
        newProject.completion = 0;
        
        do 
		{
		    printf("Description: ");
			scanfLine(newProject.description, 101);
        	fflush(stdin);
		    
		    if(strlen(newProject.description) > 100)
		        printf("\e[1;31m" "Invalid input. Project Description must not be greater than 100 characters.\n" "\e[1;97m");
		    
		} while(strlen(newProject.description) > 100);
        
        printDivider();
        printf("\e[1;32m" "\nNew Project added successfully.\n" "\e[1;97m");

        projectArray[*numProjects] = newProject;
        (*numProjects)++;
    }
}

/**********************************************************************************
Description: This function computes the number of tasks a project has, given its
             projectID.
    @param taskArray - struct array containing all existing tasks
    @param numTasks - number of tasks in taskArray
    @return the total number of tasks under the project
**********************************************************************************/
int 
countProjectTasks(struct task taskArray[], 
                  int numTasks, 
                  int projectID)
{
    int count = 0;

    for (int i = 0; i < numTasks; i++)
        if (taskArray[i].projectID == projectID)
            count++;

    return count; 
}

/**********************************************************************************
Description: This function generates a taskID for a newly added task based on its 
            assigned projectID. It firsts counts how many tasks belong to the same 
            project and appends it to the projectID. It verifies that the newly 
            generated taskID is unique, otherwise the function calls itself. 
    @param taskArray - struct array containing all the tasks & their details
    @param numTasks - number of existing tasks
    @param projectID - projectID of the newly added task
    @returns the generated task ID
**********************************************************************************/
int 
generateTaskID(struct task taskArray[], 
               int numTasks,
               int projectID)
{
    int unique = 1; 
    int count = countProjectTasks(taskArray, numTasks, projectID);
    int taskID = (projectID * 100) + count;

    for (int i = 0; i < numTasks; i++) // checks if unique taskID
        if (taskArray[i].taskID == taskID)
            unique = 0; 

    if (!unique)
        return generateTaskID(taskArray, numTasks + 1, projectID); 
    return taskID;
}
/**********************************************************************************
Description: In case the user edits a task sequence of a project, this function 
            adjusts all the other the sequence of tasks under the same project.
        @param taskArray - contains all the existing tasks to be accessed
        @param numTasks - number of existing tasks in taskArray
        @param projectID - project ID of the tasks to be modified & adjusted
        @param taskID - task ID of project that was updated 
        @param newSequence - the new task sequence of the edited task
        @param oldSequence - the old task sequence of the edited task
**********************************************************************************/
void 
adjustTasksSequence(struct task taskArray[], 
                    int numTasks, 
                    int projectID,
                    int taskID, 
                    int newSequence, int oldSequence)
{
   int forward = newSequence > oldSequence; 
   int backward = newSequence < oldSequence; 

   if (forward || backward)
      for (int i = 0; i < numTasks; i++)
        if (taskArray[i].projectID == projectID && taskArray[i].taskID != taskID) // doesnt touch the updated task 
        {
            if (forward)
            {   
                if ((taskArray[i].sequence <= newSequence) && (taskArray[i].sequence > oldSequence))
                    taskArray[i].sequence--; 
            }
            if (backward)
            {
                if ((taskArray[i].sequence >= newSequence) && (taskArray[i].sequence < oldSequence))
                    taskArray[i].sequence++;
            }
        }
}

/**********************************************************************************
Description: Given a taskName, this function searches for a task, under the same
            project, that has the same name
    @param taskArray - struct array containing all tasks
    @param numTasks - number of existing tasks in taskArray
    @param taskName - the taskName to be checked and compared with
    @param projectID - ID of project the task is under
    @param projectArray - struct array containing all projects
    @param numProjects - number of existing projects in projectArray

    @return the index of the task with the same name 
            -1 if not found
**********************************************************************************/
int 
checkTaskName(struct task taskArray[], 
              int numTasks, 
              str40 taskName,
              int projectID,
              struct project projectArray[],
              int numProjects)
{
    int i, 
		j;
    for (i = 0; i < numTasks; i++) {
        if (strcmp(taskArray[i].name, taskName) == 0 && taskArray[i].projectID == projectID)
            for (j = 0; j < numProjects; j++)
                if (projectArray[j].projectID == projectID)
                    return i;
    }
    return -1; 
}

/**********************************************************************************
Description: Using a linear search algorithm, this function returns the index of a 
    given projectID in the projectArray.
    @param key - the target projectID that needs to be searched 
    @param projectArray - struct array containing all the project information
    @param numProjects - number of existing projects
    @returns the index of the projectID in the array, if unfound, returns -1
**********************************************************************************/
int 
findProject(int key, 
            struct project projectArray[], 
            int numProjects)
{
    int index = 0, found = 0;

    while (!found && index < numProjects)
    {
       (key == projectArray[index].projectID) ?
            found = 1:
            index++;
    }
    
    if (found)
        return index; 
    return -1; 
}

/**********************************************************************************
Description: This function lets the user input the start and enddates of a task. 
    If the dates input are incorrectly formatted or invalid (startdate is later than
    enddate) then the function will prompt the user to input another date. 
    @param task - struct containing the task details where task dates will be 
            updated.
**********************************************************************************/
void 
inputDates(struct task *task)
{
    str12 startDate, endDate, // placeholder variables
          revStart,   revEnd;
    int formatted, valid = 0;
    
    do {
        do {
            fflush(stdin);
            printf("Start Date [MM/DD/YYYY]: ");
            scanf("%11s", startDate);

            formatted = isFormatted(startDate);
            if (!formatted)
                printf("\e[1;31m" "Incorrect date format.\n" "\e[1;97m");
        } while (!formatted);

        do {
            fflush(stdin);
            printf("End Date [MM/DD/YYYY]: ");
            scanf("%11s", endDate);

            formatted = isFormatted(endDate); 
            if (!formatted)
                printf("\e[1;31m" "Incorrect date format.\n" "\e[1;97m");
        } while (!formatted);
      
        reverseDate(startDate, revStart);
        reverseDate(endDate, revEnd);

        valid = strcmp(revStart, revEnd) != 1;
        if (!valid)
            printf("\e[1;31m" "Invalid dates! The start date should not be later than the end date.\n\n" "\e[1;97m");
    
    } while (!valid);
   
    strcpy(task->startdate, startDate);
    strcpy(task->enddate, endDate);
}
/**********************************************************************************
Description: This function computes a task's total duration by comparing its 
    start and end dates. 
Precondition: Assumes the start and end dates have been correctly input & formatted
    @param task - struct where the start & end dates will be accessed
    @return the total number of days from the startdate to the enddate
**********************************************************************************/
float 
computeDuration(struct task task) 
{
    float diffYears  = 0, 
          diffMonths = 0, 
          diffDays   = 0,
          avgDaysperYear = 365.25,
          totalDays;
    int   startMonth, startDay, startYear, 
          endMonth, endDay, endYear,
          prevMonth, prevMonthDays;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    startMonth = atoi(task.startdate + 0);
      startDay = atoi(task.startdate + 3);
     startYear = atoi(task.startdate + 6);

      endMonth = atoi(task.enddate + 0);
        endDay = atoi(task.enddate + 3);
       endYear = atoi(task.enddate + 6);

    diffYears = endYear - startYear;
    diffMonths = endMonth - startMonth;

    if (diffMonths < 0) 
    {
        diffYears--;
        diffMonths += 12;
    }

    diffDays = endDay - startDay;
    if (diffDays < 0) 
    {
        prevMonth = (startMonth == 1) ? 12 : startMonth - 1;
        prevMonthDays = daysInMonth[prevMonth - 1];
        if (prevMonth == 2 && startYear % 4 == 0 && (startYear % 100 != 0 || startYear % 400 == 0)) {
            prevMonthDays++;
        }
        diffDays += prevMonthDays;
        diffMonths--;
    }

    totalDays = diffDays + (diffMonths * daysInMonth[startMonth - 1]) + (diffYears * avgDaysperYear);

    return totalDays;
}
/**********************************************************************************
Description: Given the maximum number of tasks has not been reached yet, 
            this function allows the user to add a new task and input all 
            its necessary details. 
    @param taskArray - struct array where the new task will be stored 
    @param numTasks - number of existing tasks
    @param projectArray - struct array where all the projects' information are 
            stored; needed for validating the input projectID 
    @param numProjects - number of existing projects
    @param personnelArray - struct array containing all personnel records; 
            needed for validating the input assignID
    @param numPersonnel - number of existing personnel in personnelArray
**********************************************************************************/
void 
addTask(struct task taskArray[], 
        int *numTasks,
        struct project projectArray[],
        int numProjects,
        struct personnel personnelArray[],
        int numPersonnel)
{
        int valid = -1,
		    taskExists,
            count = 0,
            index,
		    i;
        struct task newTask;
		  
    if (*numTasks >= MAX_TASKS)
        printf("\e[1;31m" "Maximum task count reached.\n" "\e[1;97m");
    else if (numProjects == 0)
        printf("\e[1;31m" "There are no registered projects yet. Please make a project first.\n" "\e[1;97m");
    else 
    {
        displayAddTaskHeader();
        printf("\n%c %-116s %c", TVLINE, "To what project would you like to put this new task under?",TVLINE);
    	printf("\n");
    	printLine(TVLINE, 32, TVLINE, 118);	
    	for (i = 0; i < numProjects; i++)
    		printf("\n%c \t%d %-105s %c", TVLINE, projectArray[i].projectID, projectArray[i].name, TVLINE);
    	displayAddTaskDivider();
    	
    	do
		{
            printf("\nProject ID: ");
            scanf("%d", &newTask.projectID);
            fflush(stdin);
            
            valid = findProject(newTask.projectID, projectArray, numProjects) != -1;

            if (!valid)
                printf("\e[1;31m" "This ID does not belong to any existing project. Please input a valid Project ID\n" "\e[1;97m");
                
        } while (!valid);
        
    	system("cls");  
		  
		displayAddTaskHeader();
    	printf("\n%c %-116s %c", TVLINE, "To whom would you like to assign this new task to?",TVLINE);
    	printf("\n");
    	printLine(TVLINE, 32, TVLINE, 118);	
    	for (i = 0; i < numPersonnel; i++)
        {
            if (personnelArray[i].access != 0 && personnelArray[i].access != 1) 
            {
                count++;
                printf("\n%c \t%d. %d %-102s %c", TVLINE, count, personnelArray[i].personnelID, personnelArray[i].username, TVLINE);
                if(count == 0)
                    printf("\n%c" "\e[1;31m" " %-116s " "\e[1;97m" "%c", TVLINE, "There are no Active Personnels.", TVLINE);	
            }
        }
    	displayAddTaskDivider();
        
        do 
		{
            printf("\nID of Assigned Personnel: ");
            scanf("%d", &newTask.assignID);
            fflush(stdin);

            index = findPersonnel(newTask.assignID, personnelArray, numPersonnel);
            valid = index != -1;

            if(valid)
                if (personnelArray[index].access == 1)
                    valid = 0;
                
            if (!valid)
                printf("\e[1;31m" "Invalid Personnel. Please input an existing Manager/User Personnel ID.\n" "\e[1;97m");
                        
        } while (!valid);

        newTask.taskID = generateTaskID(taskArray, *numTasks, newTask.projectID);
        
        do 
		{
		    printf("\nTask Name: ");
        	scanfLine(newTask.name, 41);
        	fflush(stdin);
		    
		    if(strlen(newTask.name) > 40)
		        printf("\e[1;31m" "Invalid input. Task name must not be greater than 40 characters.\n" "\e[1;97m");
		        
		    taskExists = checkTaskName(taskArray, *numTasks, newTask.name, newTask.projectID, projectArray, numProjects);

			if(taskExists >= 0)
				printf("\e[1;31m" "This Task already exists. Try again.\n" "\e[1;97m");
		    
		} while(strlen(newTask.name) > 40 || taskExists >= 0);
        
        newTask.sequence = 1 + countProjectTasks(taskArray, *numTasks, newTask.projectID);
        
        do 
		{
		    printf("Description: ");
			scanfLine(newTask.description, 101);
        	fflush(stdin);
		    
		    if(strlen(newTask.description) > 100)
		        printf("\e[1;31m" "Invalid input. Task Description must not be greater than 100 characters.\n" "\e[1;97m");
		    
		} while(strlen(newTask.description) > 100);
        
        inputDates(&newTask);

        newTask.totalDuration = computeDuration(newTask);

        do 
		{
            printf("Task Status: ");
            scanf("%d", &newTask.status);
            fflush(stdin);
            
            if (newTask.status < 1 || newTask.status > 3)
                printf("\e[1;31m" "Invalid Input. Please choose between [1] Not Started [2] In Progress [3] Done.\n" "\e[1;97m");
                
        } while (newTask.status < 1 || newTask.status > 3);

        printDivider();
        printf("\e[1;32m" "\nNew Task Added successfully.\n" "\e[1;97m");
        taskArray[*numTasks] = newTask;
        (*numTasks)++;
        
    }
}


/**********************************************************************************
Description: Using a linear search algorithm, this function returns the index of a 
    given taskiD in the taskArray.
    @param key - the target taskID that needs to be searched 
    @param taskArray - struct array containing all the task information
    @param numTasks - number of existing tasks
    @returns the index of the taskID in the array, if unfound, returns -1
**********************************************************************************/
int 
findTask(int key,
         struct task taskArray[],
         int numTasks)
{
    int index = 0, 
		found = 0;

    while (!found && index < numTasks)
    {
        (key == taskArray[index].taskID) ?
            found = 1: 
            index++;
    }
    
    if (found)
        return index;
        
    return -1;
}

/**********************************************************************************
Description: This function simply displays all the details of a given task.
    @param taskArray the struct containing the task for displaying
**********************************************************************************/
void
displayTask(struct task taskArray)
{	
	int  i;
	char status[20];
	
	printLine(TVLLINE, THLINE, THDLINE, 17);
	for(i = 0; i < 16; i++)
		printf("%c", THLINE);
	printLine(THDLINE, THLINE, THDLINE, 49);
	for(i = 0; i < 16; i++)
		printf("%c", THLINE);		
	printLine(THDLINE, THLINE, TVRLINE, 16);
	
	printf("\n%c ProjectID: %-4d %c TaskID: %-6d %c Name: %-41s %c S: %-11s %c E: %-11s %c\n", 
						TVLINE, taskArray.projectID, TVLINE, taskArray.taskID, TVLINE, 
						taskArray.name, TVLINE, taskArray.startdate, TVLINE, taskArray.enddate, TVLINE);
						
		printLine(TVLLINE, THLINE, THULINE, 17);
		for(i = 0; i < 16; i++)
			printf("%c", THLINE);
		printLine(THULINE, THLINE, THULINE, 49);
		for(i = 0; i < 16; i++)
			printf("%c", THLINE);		
		printLine(THULINE, THLINE, TVRLINE, 16);
		
		switch (taskArray.status)
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
		
		printf("\n%c Desciption: %-104s %c\n", TVLINE, taskArray.description, TVLINE);
		printf("%c Assigned Personnel: %-96d %c\n", TVLINE, taskArray.assignID, TVLINE);
		printf("%c Status: %-108s %c\n", TVLINE, status, TVLINE);
		printf("%c Sequence: %-106d %c\n", TVLINE, taskArray.sequence, TVLINE);
		printf("%c Total Duration [Days]: %-10.2f %84c\n", TVLINE, taskArray.totalDuration, TVLINE);
		
		printLine(TBLCORNER, THLINE, TBRCORNER, 118);
		printf("\n");
}

/**********************************************************************************
Description: This function asks the user an existing projectID before allowing them
    to update/modify project details
	@param taskArray: An array of structs where all task information are stored
	@param numTasks: The number of tasks.
	@param projectArray: An array of structs where projects are stored
	@param numProjects: The number of projects.
**********************************************************************************/
void 
updateProject(struct project projectArray[],
	          int numProjects,
              struct personnel personnelArray[],
              int numPersonnel)
{
	int    k, 
           found = 0,
           option,
           projectID,
           projectExists,
           newStatus,
           newAssignID;
    str40  newProjectName;
    str100 newProjectDescription;

    displayHeader();
    displayManagerHeader();
    displayProjects(projectArray, numProjects);
    
	printf("\nEnter Project ID to update: ");
	scanf("%d", &projectID);
	
	for(k = 0; k < numProjects; k++)
	{
	     if (projectArray[k].projectID == projectID)
	 	{
	        found = 1;
	 		system("cls");
	        
            displayHeader();
            displayManagerHeader(); 
            displayProjectDetail(projectArray, k);
		    printf("\n");
            printLine(TTLCORNER, THLINE, TTRCORNER, 118);
            printf("\n%-48c Select Field to Update: %47c\n", TVLINE, TVLINE);
            printf("%-49c [1] Project Name %53c", TVLINE, TVLINE);
            printf("\n%-49c [2] Status %59c", TVLINE, TVLINE);
            printf("\n%-49c [3] Description %54c", TVLINE, TVLINE);
            printf("\n%-49c [4] Assigned Personnel %47c\n", TVLINE, TVLINE);
            printLine(TBLCORNER, THLINE, TBRCORNER, 118);
	        printf("\n");
	            
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
                        printf("New Project Name: ");
                        scanfLine(newProjectName, 41);
                        fflush(stdin);

                        if (strlen(newProjectName) > 40) 
                            printf("\e[1;31mInvalid input. Project name must not be greater than 40 characters.\n\e[1;97m");
                        
                        projectExists = checkProjectName(projectArray, numProjects, newProjectName);

                        if (projectExists >= 0) 
                                printf("\e[1;31mThis Project already exists. Try again.\n\e[1;97m");
            
                    } while (strlen(newProjectName) > 40 || projectExists >= 0);

                    strcpy(projectArray[k].name, newProjectName);

                    break;
                case 2: 
                    do 
                    {
                        printf("New Project Status: ");
                        scanf("%d", &newStatus);
                        fflush(stdin);
                        
                        if (newStatus < 1 || newStatus > 3)
                            printf("\e[1;31m" "Invalid Input. Please choose between [1] Not Started [2] In Progress [3] Done.\n" "\e[1;97m");
                            
                    } while (newStatus < 1 || newStatus > 3);

                    if (newStatus == 3)
                        projectArray[k].completion = 100;

                    projectArray[k].status = newStatus;

                    break;
                case 3:
                    do 
                    {
                        printf("New Project Description: ");
                        scanfLine(newProjectDescription, 101);
                        fflush(stdin);

                        if (strlen(newProjectDescription) > 101) 
                            printf("\e[1;31mInvalid input. Project name must not be greater than 40 characters.\n\e[1;97m");
                        
                    } while (strlen(newProjectDescription) > 101);

                    strcpy(projectArray[k].description, newProjectDescription);

                    break;
                case 4:
                    do 
                    {
                        printf("\nID of New Assigned Personnel: ");
                        scanf("%d", &newAssignID);
                        fflush(stdin);

                        found = findPersonnel(newAssignID, personnelArray, numPersonnel) != -1;

                        if (!found)
                            printf("\e[1;31m" "Personnel ID does not exist. Please input an existing Personnel ID.\n" "\e[1;97m");

                    } while (!found);

                    projectArray[k].assignID = newAssignID;

                    break;
	        }
	     }
    }

    if(!found)
         {
             printf("\e[1;31m" "Project ID does not exist. Please input an existing Project ID.\n\n" "\e[1;97m");
             clearScreen();
             updateProject(projectArray, numProjects, personnelArray, numPersonnel);
         }
}

/**********************************************************************************
Description: This function firsts asks the user for an existing taskID, then
            allows them to update the details of a given task
    @param taskArray - struct array where the new task will be stored 
    @param numTasks - number of existing tasks
    @param projectArray - struct array where all the projects' information are 
            stored; needed for validating the input projectID 
    @param numProjects - number of existing projects
    @param personnelArray - struct array containing all personnel records; 
            needed for validating the input assignID
    @param numPersonnel - number of existing personnel in personnelArray
**********************************************************************************/
void 
updateTask(struct task taskArray[], 
           int numTasks,
           struct project projectArray[],
           int numProjects,
           struct personnel personnelArray[],
           int numPersonnel)
{ 
       int targetID, 
		   taskIndex,
		   taskExists, 
		   option, 
		   valid,
		   nProjTasks,
           oldSequence,
           taskID,
           oldProjID,
           count = 0,
           i; 
	struct task updateTask;
    
    displayTasks(taskArray, numTasks);
    
    do 
	{
        printf("\nEnter Task ID to Update: ");
        scanf("%d", &targetID);
        fflush(stdin);

        taskIndex = findTask(targetID, taskArray, numTasks);
        
        if (taskIndex == -1)
            printf("\e[1;31m" "Invalid Input. Task ID does not match to any existing task.\n" "\e[1;97m");
            
    } while (taskIndex == -1);
    
    system("cls");

	displayHeader();
    displayManagerHeader();
	printf("%-48c Task %d Details ... %47c\n", TVLINE, targetID, TVLINE);
	
    displayTask(taskArray[taskIndex]);

    printLine(TTLCORNER, THLINE, TTRCORNER, 118);
	printf("\n%-48c Select Field to Update: %47c\n", TVLINE, TVLINE);
    printf("%-49c [1] Task Name %56c", TVLINE, TVLINE);
    printf("\n%-49c [2] Sequence %57c", TVLINE, TVLINE);
    printf("\n%-49c [3] Description %54c", TVLINE, TVLINE);
    printf("\n%-49c [4] Project ID %55c", TVLINE, TVLINE);
    printf("\n%-49c [5] Start & End Dates %48c", TVLINE, TVLINE);
    printf("\n%-49c [6] Status %59c", TVLINE, TVLINE);
    printf("\n%-49c [7] Assigned Personnel %47c\n", TVLINE, TVLINE);
    
	printLine(TBLCORNER, THLINE, TBRCORNER, 118);

    do 
	{
        printf("\n\nInput option: ");
        scanf("%d", &option);
        fflush(stdin);

        if (option < 1 || option > 7)
		    printf("\e[1;31m" "Invalid Input. Try again.\n" "\e[1;97m");
		    
    } while (option < 1 || option > 7);

    switch(option)
	{
        case 1: 
        	do 
			{
			    printf("\nNew Task Name: ");
	        	scanfLine(updateTask.name, 41);
	        	fflush(stdin);
			    
			    if(strlen(updateTask.name) > 40)
			        printf("\e[1;31m" "Invalid input. Task name must not be greater than 40 characters.\n" "\e[1;97m");
			        
		    	taskExists =checkTaskName(taskArray, numTasks, updateTask.name, taskArray[taskIndex].projectID, projectArray, numProjects);
	
				if(taskExists >= 0)
					printf("\e[1;31m" "This Task already exists. Try again.\n" "\e[1;97m");
			    
			} while(strlen(updateTask.name) > 40 || taskExists >= 0);
		
			strcpy(taskArray[taskIndex].name, updateTask.name);
		
            break; 
        case 2: 

            nProjTasks = countProjectTasks(taskArray, numTasks, taskArray[taskIndex].projectID);
            oldSequence = taskArray[taskIndex].sequence; 
            taskID = taskArray[taskIndex].taskID;
            do {
                printf("New Task sequence: ");
                scanf("%d", &updateTask.sequence);
                fflush(stdin);
            } while (updateTask.sequence < 1 || updateTask.sequence > nProjTasks);

            taskArray[taskIndex].sequence = updateTask.sequence; // new sequence 
            adjustTasksSequence(taskArray, numTasks, taskArray[taskIndex].projectID, 
                                taskID, updateTask.sequence, oldSequence);
            break; 
        case 3: 
        	do 
			{
			    printf("New Task Description: ");
				scanfLine(taskArray[taskIndex].description, 101);
	        	fflush(stdin);
			    
			    if(strlen(taskArray[taskIndex].description) > 100)
			        printf("\e[1;31m" "Invalid input. Task Description must not be greater than 100 characters.\n" "\e[1;97m");
			    
			} while(strlen(taskArray[taskIndex].description) > 100);
		
            break; 
        case 4: 

            oldProjID = taskArray[taskIndex].projectID;
            nProjTasks = countProjectTasks(taskArray, numTasks, oldProjID); // count tasks under old projectID 

	        system("cls");
	        displayHeader();
    		displayManagerHeader();
    		displayUpdateTaskHeader();
    		
	        printf("\n%c %-116s %c\n", TVLINE, "To what project would you like to put this task under?",TVLINE);
	    	printLine(TVLINE, 32, TVLINE, 118);
	        printf("\n%c Current Project: %-99d %c\n", TVLINE, taskArray[taskIndex].projectID ,TVLINE);
	    	printLine(TVLINE, 32, TVLINE, 118);	
	    	for (i = 0; i < numProjects; i++)
	    		printf("\n%c \t%d %-105s %c", TVLINE, projectArray[i].projectID, projectArray[i].name, TVLINE);
	    	displayAddTaskDivider();
	    	
	    	do {
	            printf("\n\nNew Project ID: ");
	            scanf("%d", &updateTask.projectID);
	            fflush(stdin);
	            
	            valid = findProject(updateTask.projectID, projectArray, numProjects) != -1;
	
	            if (!valid)
	                printf("\e[1;31m" "This ID does not belong to any existing project. Please input a valid Project ID\n" "\e[1;97m");
	                
	        } while (!valid);

            // adjust old project sequences & update new projectID , sequence, taskID
	        adjustTasksSequence(taskArray, numTasks, oldProjID, taskArray[taskIndex].taskID, 
                                nProjTasks, taskArray[taskIndex].sequence);
	        taskArray[taskIndex].projectID = updateTask.projectID;
            taskArray[taskIndex].sequence = countProjectTasks(taskArray, numTasks, taskArray[taskIndex].projectID); 
            taskArray[taskIndex].taskID = generateTaskID(taskArray, numTasks, taskArray[taskIndex].projectID);

            break; 
        
        case 5: 
            inputDates(&taskArray[taskIndex]); 
            taskArray[taskIndex].totalDuration = computeDuration(taskArray[taskIndex]); 
            break;
        
		case 6:
			do 
			{
	            printf("\n\nTask Status: ");
	            scanf("%d", &updateTask.status);
	            fflush(stdin);
	            
	            if (updateTask.status < 1 || updateTask.status > 3)
	                printf("\e[1;31m" "Invalid Input. Please choose between [1] Not Started [2] In Progress [3] Done.\n" "\e[1;97m");
	                
	        } while (updateTask.status < 1 || updateTask.status > 3);
	        	
	        taskArray[taskIndex].status = updateTask.status;
	        
			break; 

        case 7: 
        	system("cls");
	        displayHeader();
    		displayManagerHeader();
    		displayUpdateTaskHeader();
    		
	    	printf("\n%c %-116s %c\n", TVLINE, "To whom would you like to Reassign this task to?",TVLINE);
	    	printLine(TVLINE, 32, TVLINE, 118);	
	    	printf("\n%c Current Personnel: %-97d %c\n", TVLINE, taskArray[taskIndex].assignID ,TVLINE);
	    	printLine(TVLINE, 32, TVLINE, 118);
	    	for (i = 0; i < numPersonnel; i++)
            {
                if (personnelArray[i].access != 0 && personnelArray[i].access != 1) 
                {
                    count++;
                    printf("\n%c \t%d. %d %-102s %c", TVLINE, count, personnelArray[i].personnelID, personnelArray[i].username, TVLINE);
                    if(count == 0)
                        printf("\n%c" "\e[1;31m" " %-116s " "\e[1;97m" "%c", TVLINE, "There are no Active Personnels.", TVLINE);	
                }
            }
	    	displayAddTaskDivider();
    		
            do 
			{
	            printf("\nEnter Personnel ID: ");
	            scanf("%d", &updateTask.assignID);
	            fflush(stdin);
	            
	            valid = findPersonnel(updateTask.assignID, personnelArray, numPersonnel) != -1;
	            
	            if (!valid)
	                printf("\e[1;31m" "Personnel ID does not exist. Please input an existing Personnel ID.\n" "\e[1;97m");
	                
            } while (!valid);
            
            taskArray[taskIndex].assignID = updateTask.assignID;
            
            break;
    }

    printDivider();
    printf("\e[1;32m" "\nTask Updated successfully.\n" "\e[1;97m");
    
}

/**********************************************************************************
Description: This function displays all the active personnel, each displaying their 
    personnelID and username, and also displays the total number of active personnel
    @param personnelArray - struct array containing all personnel records; 
    @param numPersonnel - number of existing personnel in personnelArray
**********************************************************************************/
void 
activePersonnel(struct personnel personnelArray[],
                int numPersonnel)
{
    int count = 0, 
        i;
    
    displayPersonnelListHeader();
    
    for (i = 0; i < numPersonnel; i++)
    {
        if (personnelArray[i].active == 1) 
        {
            count++;
            printf("\n%c \t%d. %d %-102s %c", TVLINE, count, personnelArray[i].personnelID, personnelArray[i].username, TVLINE);
        }
        else if(count == 0)
        	printf("\n%c" "\e[1;31m" " %-116s " "\e[1;97m" "%c", TVLINE, "There are no Active Personnels.", TVLINE);	
    }
    printf("\n");
    printLine(TBLCORNER, THLINE, TBRCORNER, 118);
}

/**********************************************************************************
Description: This function firsts asks the user for an existing taskID, then
            allows them to assign the task to an existing user with an input 
            assignID.
    @param taskArray - struct array where the task details are accesed 
    @param numTasks - number of existing tasks
    @param personnelArray - struct array containing all personnel records; 
            needed for validating the input assignID
    @param numPersonnel - number of existing personnel in personnelArray
**********************************************************************************/
void
assignTask(struct task taskArray[], 
           int numTasks, 
           struct personnel personnelArray[],
           int numPersonnel)
{
    int targetID,
		newAssignID, 
		taskIndex, 
		i, 
        count = 0,
		valid; 

    displayTasks(taskArray, numTasks);
    
    do 
	{
        printf("\nEnter Task ID to Assign: ");
        scanf("%d", &targetID);
        fflush(stdin);

        taskIndex = findTask(targetID, taskArray, numTasks);
        
        if (taskIndex == -1)
            printf("\e[1;31m" "Invalid Input. Task ID does not match to any existing task.\n" "\e[1;97m");
            
    } while (taskIndex == -1);
    
    system("cls");
    displayHeader();
    displayManagerHeader();
	printf("%-49c Task %d Details ... %48c\n", TVLINE, targetID, TVLINE);
    displayTask(taskArray[taskIndex]);
    displayAssignTaskHeader();
    
    printf("\n%c %-116s %c\n", TVLINE, "To whom would you like to re-assign this task to?",TVLINE);
	printLine(TVLINE, 32, TVLINE, 118);	
	printf("\n%c Current Personnel: %-97d %c\n", TVLINE, taskArray[taskIndex].assignID ,TVLINE);
	printLine(TVLINE, 32, TVLINE, 118);
	for (i = 0; i < numPersonnel; i++)
            {
                if (personnelArray[i].access != 0 && personnelArray[i].access != 1) 
                {
                    count++;
                    printf("\n%c \t%d. %d %-102s %c", TVLINE, count, personnelArray[i].personnelID, personnelArray[i].username, TVLINE);
                    if(count == 0)
                        printf("\n%c" "\e[1;31m" " %-116s " "\e[1;97m" "%c", TVLINE, "There are no Active Personnels.", TVLINE);	
                }
            }
    printf("\n");
	printLine(TBLCORNER, THLINE, TBRCORNER, 118);
	printf("\n");
	
	do 
	{
	    printf("\nEnter Personnel ID: ");
	    scanf("%d", &newAssignID);
	    fflush(stdin);
	           
	    valid = findPersonnel(newAssignID, personnelArray, numPersonnel) != -1;
	        
	    if (!valid)
	        printf("\e[1;31m" "Personnel ID does not exist. Please input an existing Personnel ID.\n" "\e[1;97m");
	                
    } while (!valid);
    
    taskArray[taskIndex].assignID = newAssignID;
    
    printDivider();
    printf("\e[1;32m" "\nTask Assigned successfully.\n" "\e[1;97m");
}

/**********************************************************************************
Description: This function checks if the projectID is in the projectArray and taskArray.
    @param projectArray: An array of structs that stores project information.
	@param numProjects: The number of projects.
    @param targetProjectID: The Project that is being compared.
    @param taskArray: An array of structs that stores task information.
	@param numTasks: The number of tasks.
    @returns 1 if ID is found in taskArray and projectArray.
    @return 0 if ID is not found in taskArray.
**********************************************************************************/
int hasMatchingProjectID(struct project projectArray[], 
                         int numProjects, 
                         int targetProjectID, 
                         struct task taskArray[], 
                         int numTasks)
{
    int i;
    for (i = 0; i < numProjects; i++)
        if (projectArray[i].projectID == targetProjectID) {
            int j;
            for (j = 0; j < numTasks; j++) 
                if (taskArray[j].projectID == targetProjectID)
                    return 1; // Found a matching project ID in both arrays
            return 0; // Found a matching project ID in projectArray, but not in taskArray
        }
    return 0;
}

/**********************************************************************************
Description: This function displays all the active projects in the system before 
        asking the user to input the ID of a project whose details will be
        displayed next
    @param taskArray: An array of structs that stores task information.
	@param numTasks: The number of tasks.
    @param targetProjectID: The Project that is being compared.
    @param projectArray: An array of structs that stores project information.
	@param numProjects: The number of projects.
**********************************************************************************/
void displayTaskInProject(struct task taskArray[], 
                          int numTasks, 
                          int targetProjectID, 
                          struct project projectArray[], 
                          int numProjects)
{
    int i;

    if (hasMatchingProjectID(projectArray, numProjects, targetProjectID, taskArray, numTasks))
        for (i = 0; i < numTasks; i++)
            if (taskArray[i].projectID == targetProjectID)
                displayTask(taskArray[i]);
}



/**********************************************************************************
Description: This function displays all the active projects in the system before 
        asking the user to input the ID of a project whose details will be
        displayed next
    @param projectArray - struct array containing all the projects
    @param numProjects - number of existing projects in projectArray
**********************************************************************************/
void 
showProjectDetails(struct project projectArray[], 
                   int numProjects,
                   struct task taskArray[],
                   int numTasks)
{ 
	int count = 0;
    int targetID, index, i;
    
    displayProjectDetailsHeader();
    printLine(TVLLINE, THLINE, TVRLINE, 118);
    
    for(i = 0; i < numProjects; i++)
    {
    	if (projectArray[i].status == 2)
        {
            count++;
            printf("\n%c \t%d. %d %-102s %c", TVLINE, count, projectArray[i].projectID, projectArray[i].name, TVLINE);
        }
    }
    
    if(count == 0)
        	printf("\n%c" "\e[1;31m" " %-116s " "\e[1;97m" "%c", TVLINE, "There are no Active Projects.", TVLINE);

    printf("\n");
	printLine(TBLCORNER, THLINE, TBRCORNER, 118);
	
	if(count > 0)
	{
		do 
		{
	        printf("\n\nEnter Project ID: ");
	        scanf("%d", &targetID);
	        fflush(stdin);
	
	        index = findProject(targetID, projectArray, numProjects);
	        
	        if  (index == -1 || projectArray[index].status != 2) 
	            printf("\e[1;31m" "This ID does not belong to any existing active project. Please input a valid Active Project ID\n" "\e[1;97m");
	            
	    } while (index == -1 || projectArray[index].status != 2); 
	    
	    system("cls");
		displayHeader();
        displayManagerHeader();
        printf("%-47c Viewing Project %d ... %47c\n", TVLINE, targetID, TVLINE);
        displayProjectDetail(projectArray, index);

        if (hasMatchingProjectID(projectArray, numProjects, targetID, taskArray, numTasks))
        {
            printf("\n");
            printLine(TTLCORNER, THLINE, TTRCORNER, 118);	
            printf("\n%-47c Tasks under this project %47c\n", TVLINE, TVLINE);

            displayTaskInProject(taskArray, numTasks, targetID, projectArray, numProjects);
            printf("\n");
        }
	}
	else
		clearScreen();
}

/**********************************************************************************
Description: This function displayed all delayed tasks: all tasks whose endDate 
            is earlier than the currentDate && are not done yet
    @param taskArray - struct array containing all tasks to be checked
    @param numTasks - number of tasks in taskArray
**********************************************************************************/
void 
delayedTasks(struct task taskArray[], 
			 int numTasks)
{
    int   count = 0, 
		  done, 
		  late,
		  i;
    str12 currentDate, 
		  endDate;
    
    getDate(currentDate, 3); // get current date in YYYY/MM/DD format
    
    displayDelayedTaskHeader();
	printf("\n%c \t%c  %-6s %-40s %s %-48s %c", TVLINE, 32,  "ID", "Name", "Start Date", "End Date", TVLINE);
    
    for (i = 0; i < numTasks; i++)
    {
        done = taskArray[i].status == 3;
        reverseDate(taskArray[i].enddate, endDate);

        late = strcmp(currentDate, endDate) == 1;
        
        if (!done && late)
        {
            count++;
            printf("\n%c \t%d. %-6d %-40s %s %-48s %c", TVLINE, count,  taskArray[i].taskID, taskArray[i].name, taskArray[i].startdate, taskArray[i].enddate, TVLINE);
        }
    }
     if(count == 0)
        	printf("\n%c" "\e[1;31m" " %-116s " "\e[1;97m" "%c", TVLINE, "There are no delayed tasks.", TVLINE);
    printf("\n");
    printLine(TBLCORNER, THLINE, TBRCORNER, 118);
}

/**********************************************************************************
Description: This function computes the project completion rate given a projectID.
        It does this by checking the status of each task under the project. 
        @param taskArray - struct array containing all tasks & their details
        @param numTasks - current number of tasks in taskArray
        @param projectID - ID of project whose completion rate is to be computed
        @return the completion rate of the user
**********************************************************************************/
float 
computeCompletion(struct task taskArray[], 
                  int numTasks, 
                  int projectID)
{
    int totalTasks = 0,
         doneTasks = 0;

    for(int i = 0; i < numTasks; i++)
    {
        if (projectID == taskArray[i].projectID)
        {
            totalTasks++;
            if (taskArray[i].status == 3)
                doneTasks++;
        }
    }
    if (totalTasks == 0)
        return 0;
    return ((float) doneTasks / totalTasks) * 100;
}

/**********************************************************************************
Description: This function asks a user to input a projectID before computing & 
            displaying its project completion rate.
    @param projectArray - struct array containing all projects & their details
    @param numProjects - current number of projects in projectArray
    @param taskArray - struct array containing all tasks & their details
    @param numTasks - current number of tasks in taskArray
**********************************************************************************/
void 
projectCompletion(struct project projectArray[], 
                  int numProjects, 
                  struct task taskArray[],
                  int numTasks)
{
    int   targetID, 
          projIndex,
          doneTasks,
          nTasks = 0,
		  count = 0,
		  i;
    float completionRate;
    
    displayProjectCompletionHeader();
    
    for(i = 0; i < numProjects; i++)
	{
        count++;
        printf("\n%c \t%d. %d %-102s %c", TVLINE, count, projectArray[i].projectID, projectArray[i].name, TVLINE);
    }
    
	printf("\n");
	printLine(TBLCORNER, THLINE, TBRCORNER, 118);
    
    do 
	{
        printf("\nInput ID of project you wish to display details of: ");
        scanf("%d", &targetID);
        fflush(stdin);

        projIndex = findProject(targetID, projectArray, numProjects);
        
        if (projIndex == -1)
	        printf("\e[1;31m" "Project ID does not exist. Please input an existing Project ID.\n" "\e[1;97m");
            
    } while (projIndex == -1); 

	system("cls");
	displayProjectCompletionHeader();
    
    nTasks = countProjectTasks(taskArray, numTasks, targetID);
    completionRate = computeCompletion(taskArray, numTasks, targetID);
    doneTasks = (int) ((completionRate / 100) * nTasks); 
    if (projectArray[projIndex].status == 3)
        completionRate = 100;
    printf("\n%c Project Completion [%%]: %-10.2f %83c\n", TVLINE, completionRate, TVLINE); // FIXME: not printing properly if = 0
	printf("%c Number of Tasks: %-99d %c\n", TVLINE, nTasks, TVLINE);
	printf("%c Number of Done Tasks: %-94d %c\n", TVLINE, doneTasks, TVLINE);
	printLine(TBLCORNER, THLINE, TBRCORNER, 118);
	printf("\n");
}

/**********************************************************************************
Description: This function displays the manager menu and serves as the main hub for 
	         all of the possible actions that a can perform. It also updates the 
             completion rate of every project when tasks are modified.
    @param projectArray: An array of structs that stores project information.
    @param taskArray: An array of structs that stores task information.
    @param personnelArray: An array of structs that stores personnel information.
    @param numProject: The number of projects.
    @param numTasks: The number of tasks.
    @param numPersonnel: The number of current personnels.
    @return 0 if user wishes to go back to the main menu 
            1 if they wish to exit the program
**********************************************************************************/
int
managerMenu(struct project projectArray[], 
            struct task taskArray[],
            struct personnel personnelArray[],
            int *numProjects, 
            int *numTasks,
            int numPersonnel)
{
	int option = 0,
        i;
    
    // update projectCompletion first incase tasks were modified in other menus 
        for(i = 0; i < *numProjects; i++)
            projectArray[i].completion = (projectArray[i].status != 3) ?
                computeCompletion(taskArray, *numTasks, projectArray[i].projectID) : 100; 

    
    do
	{
        displayHeader();
    	displayManagerHeader();
    	
    	printf("%-50c [1] Add New Project %49c", TVLINE, TVLINE);
       	printf("\n%-50c [2] Add New Task %52c", TVLINE, TVLINE);
        printf("\n%-50c [3] Update Project %50c", TVLINE, TVLINE); 
       	printf("\n%-50c [4] Update Task %53c", TVLINE, TVLINE);
        printf("\n%-50c [5] Assign Task %53c", TVLINE, TVLINE);
       	printf("\n%-50c [6] Show Personnel List %45c", TVLINE, TVLINE);
       	printf("\n%-50c [7] Show Project Details %44c", TVLINE, TVLINE);
       	printf("\n%-50c [8] Show Delayed Task %47c", TVLINE, TVLINE);
       	printf("\n%-50c [9] Run Project Completion %42c", TVLINE, TVLINE);
        printf("\n%-50c [10] Show Login History    %42c", TVLINE, TVLINE);
       	printf("\n%-50c [11] Back to Main Menu %46c", TVLINE, TVLINE);
       	printf("\n%-50c [12] Exit %59c\n", TVLINE, TVLINE);
       	
       	printLine(TBLCORNER, THLINE, TBRCORNER, 118);
        
        do
		{
			printf("\n\nOption: ");
			scanf("%d", &option);
			fflush(stdin);

			if(option < 1 || option > 12)
		    	printf("\e[1;31m" "Invalid Input. Try again.\n" "\e[1;97m");
		    		
		} while(option < 1 || option > 12);
		
		fflush(stdin);
		system("cls");

        switch(option)
		{
			case 1: 
                addProject(projectArray, numProjects, personnelArray, numPersonnel);
                clearScreen();
                break; 
            case 2:
                if (*numProjects > 0)
                    addTask(taskArray, numTasks, projectArray, *numProjects, personnelArray, numPersonnel);
                else
                    printf("\e[1;31m" "There are no registered projects yet. Please make a project first.\n" "\e[1;97m");
                clearScreen();
                break;
            case 3:
                if (*numProjects > 0)
                    updateProject(projectArray, *numProjects, personnelArray, numPersonnel);
                else 
                    printf("\e[1;31m" "There are no registered projects yet. Please make a project first.\n" "\e[1;97m");
                clearScreen();
                break;
            case 4:
            	if(*numTasks > 0)
                	updateTask(taskArray, *numTasks, projectArray, *numProjects, personnelArray, numPersonnel);
                else
                	printf("\e[1;31m" "There are no registered tasks yet. Please make a task first.\n" "\e[1;97m");
                clearScreen();
                break; 
            case 5: 
                if(*numTasks > 0)
                	assignTask(taskArray, *numTasks, personnelArray, numPersonnel);
                else
                	printf("\e[1;31m" "There are no registered tasks yet. Please make a task first.\n" "\e[1;97m");
                clearScreen();
                break;
            case 6: 
                activePersonnel(personnelArray, numPersonnel);
                clearScreen();
                break; 
            case 7: 
                if (*numProjects > 0)
                    showProjectDetails(projectArray, *numProjects, taskArray, *numTasks);
                else 
                    printf("\e[1;31m" "There are no registered projects yet. Please make a project first.\n" "\e[1;97m");
                clearScreen();
                break; 
            case 8: 
                if(*numTasks > 0)
                    delayedTasks(taskArray, *numTasks);
                else 
                    printf("\e[1;31m" "There are no registered tasks yet. Please make a task first.\n" "\e[1;97m");
                clearScreen();
                break; 
            case 9: 
            	if(*numProjects > 0)
                	projectCompletion(projectArray, *numProjects, taskArray, *numTasks);
                else
                	printf("\e[1;31m" "There are no registered projects yet. Please make a project first.\n" "\e[1;97m");
				clearScreen();
                break; 
            case 10: 
                displayLoginHistory(2);
                clearScreen();
                break;
            case 11:
			case 12:
				printf("Logging out.\n");
                clearScreen();
				break;
        }
        
        if(option >= 1 && option <= 4)
	        for(i = 0; i < *numProjects; i++)
            	projectArray[i].completion = (projectArray[i].status != 3) ?
                	computeCompletion(taskArray, *numTasks, projectArray[i].projectID) : 100; 
                
    } while(option <= 10);

    
    if (option == 11)
        return 0;
    return 1;
}
