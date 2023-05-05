
/**********************************************************************************
 *                              DATE HELPER FUNCS                                  *
Description: This function changes the format of a date from MM/DD/YYYY to 
        YYYY/MM/DD
    Precondition: source date should be in MM/DD/YYYY 
    @param date - source string containing the date to be reversed
    @param reversedDate destination string containing the newly formatted date
**********************************************************************************/
void 
reverseDate(str12 date, 
            str12 reversedDate)
{
    for (int i = 0; i < 4; i++) // year 
        reversedDate[i] = date[6 + i];
    reversedDate[4] = '/';
    reversedDate[5] = date[0]; // month
    reversedDate[6] = date[1];
    reversedDate[7] = '/';
    reversedDate[8] = date[3];
    reversedDate[9] = date[4];
    reversedDate[10] = '\0';
} 

/**********************************************************************************
Description: This function gets the current date and formats it into a string.
    Formatting types : 
        1 - MM/DD/YYYY
        2 - YYYYMMDD
        3 - YYYY/MM/DD
    @param date - destination string where the formatted string is stored
    @param format - determines which format type will be used
**********************************************************************************/
// gets current date, stored in mm/mm/yyyy or yyyymmmm format 
void 
getDate(str12 date, 
        int format)
{
    time_t t; 
    time(&t);

    int  y = strlen(ctime(&t));
    char mm[3], 
         z[y];

    strcpy(z, ctime(&t)); // stores actual ctime output
    
    switch(z[4])
    {
        case 'J': (z[5] == 'a') ?  // january
                  strcpy(mm, "01") : (z[6] == 'n') ? // june or july
                                       strcpy(mm, "06") : strcpy(mm, "07");
                  break;
        case 'F': strcpy(mm, "02"); // feb
                  break;
        case 'M': (z[6] == 'r') ? // march or may
                  strcpy(mm, "03") : strcpy(mm, "05");
                  break;
        case 'A': (z[5] == 'p') ?  // april or aug
                  strcpy(mm, "04") : strcpy(mm, "08");
                  break;
        case 'S': strcpy(mm, "09"); // sept
                  break;
        case 'O': strcpy(mm, "10"); // oct
                  break;
        case 'N': strcpy(mm, "11"); // nov
                  break;
        case 'D': strcpy(mm, "12"); // dec
                  break;
    }

    if (format == 1) //   format: MM/DD/YYYY
    {
        char mmYY[11] = {'/', z[8], z[9], '/', z[20], z[21], z[22], z[23], '\0'};
        strcpy(date, mm);
        strcat(date, mmYY);
    }
          
    if (format == 2) // YYYYMMDD
    {
        char yyMD[9] = {z[20], z[21], z[22], z[23], mm[0], mm[1], z[8], z[9], '\0'};
        strcpy(date, yyMD);
    }
    if (format == 3) //YYYY/MM/DD
    {
        char yySlash[11] = {z[20], z[21], z[22], z[23], '/', mm[0], mm[1], '/', z[8], z[9], '\0'};
        strcpy(date, yySlash);
    }
}


/**********************************************************************************
Description: This function checks if the input date is in the correct format of
            MM/DD/YYYY.
    @param date - date to be checked 
    @return 1 if the date is correctly formatted, 0 otherwise
**********************************************************************************/
int isFormatted(str12 date)
{
    return (date[2] == '/') && (date[5] == '/') && (strlen(date) == 10) ;
}

/**********************************************************************************
Description: This function gets the latest export file names of each struct array 
		text file generated from exportData(), these file names will be stored in 
		the following parameters below. If exportDate.txt does not exist then the 
		function simply exist at once.
    @param projectArray - struct array that serves as a source of all projects 
            to be exported
    @param numProjects - number of existing projects to be exported
    @param fileName - name of text file to where the projects will be exported
	@return 1 if exportDate.txt exists, 0 otherwise 
**********************************************************************************/
int
getLatestExport(str24 fnProjects, str24 fnTasks, str24 fnPersonnel)
{
	FILE *fExport;
	fExport = fopen("exportDate.txt", "r");
	if (fExport != NULL)
	{
		fscanf(fExport, "%s\n%s\n%s", fnProjects, fnTasks, fnPersonnel);
		fclose(fExport);
		return 1;	
	}
	return 0;
}
/**********************************************************************************
Description: This function exports all the saved projects and their details 
            into a new text file. 
    @param projectArray - struct array that serves as a source of all projects 
            to be exported
    @param numProjects - number of existing projects to be exported
    @param fileName - name of text file to where the projects will be exported
**********************************************************************************/
void
exportProjects(struct project projectArray[], 
               int numProjects, 
               str24 fileName)
{
    FILE *fProjects;
    fProjects = fopen(fileName, "w");

    for (int i = 0; i < numProjects; i++)
    {
        fprintf(fProjects, "%d %s\n", projectArray[i].projectID, projectArray[i].name);
        fprintf(fProjects, "%d\n", projectArray[i].assignID);
        fprintf(fProjects, "%d\n%.3f\n", projectArray[i].status, projectArray[i].completion);
        fprintf(fProjects, "%s\n\n", projectArray[i].description);
    }
    fclose(fProjects);
}
/**********************************************************************************
Description: This function exports all the saved tasks details into a new text 
        file.
    @param taskArray - struct array that serves as a source of all tasks 
            to be exported
    @param numTasks - number of existing tasks to be exported
    @param fileName - name of text file where the tasks will be exported
**********************************************************************************/
void
exportTasks(struct task taskArray[], 
            int numTasks,
            str24 fileName)
{
    FILE *fTasks;

    fTasks = fopen(fileName, "w");
     
    for (int i = 0; i < numTasks; i++)
    {
        fprintf(fTasks, "%d %s\n", taskArray[i].taskID, taskArray[i].name);
        fprintf(fTasks, "%d\n%s\n", taskArray[i].sequence, taskArray[i].description);
        fprintf(fTasks, "%d\n%s\n%s\n", taskArray[i].projectID, taskArray[i].startdate, taskArray[i].enddate);
        fprintf(fTasks, "%.3f\n%d\n%d\n\n", taskArray[i].totalDuration, taskArray[i].status, taskArray[i].assignID);
    }
    fclose(fTasks);
}
/**********************************************************************************
Description: This function exports all the saved personnel details into a new text 
            file.
    @param personnelArray - struct array that serves as a source of all personnel 
            details to be exported
    @param numPersonnel- number of existing personnel records to be exported
    @param fileName - name of text file where the details shall be exported to
**********************************************************************************/
void 
exportPersonnel(struct personnel personnelArray[], 
                int numPersonnel, 
                str24 fileName)
{
    FILE *fPersonnel;  

    fPersonnel = fopen(fileName, "w");
    for (int i = 0; i < numPersonnel; i++)
    {
        fprintf(fPersonnel, "%d\n%s\n", personnelArray[i].personnelID, personnelArray[i].username);
        fprintf(fPersonnel, "%s\n%d\n%d\n\n", personnelArray[i].password, personnelArray[i].active, personnelArray[i].access);
    }
    fclose(fPersonnel);
}

/**********************************************************************************
Description: This function exports all the saved project, task, and personnel 
            details into new text files. Their filenames contain the date this 
            function was triggered. This function also writes a new text file
            (exportDate.txt) containing the filenames of the aforementioned 
            text files. 
    @param projectArray - struct array that serves as a source of all projects 
            to be exported
    @param numProjects - number of existing projects to be exported
    @param taskArray - struct array that serves as a source of all tasks 
            to be exported
    @param numTasks - number of existing tasks to be exported
    @param personnelArray - struct array that serves as a source of all personnel 
            details to be exported
    @param numPersonnel- number of existing personnel records to be exported 
**********************************************************************************/
void 
exportData(struct project projectArray[], 
           struct task taskArray[], 
           struct personnel personnelArray[],
           int numProjects, 
           int numTasks,
           int numPersonnel)
{
    FILE *fp;
    str12 currentDate;
    str24 fnProjects = "project_",
          fnTasks = "task_",
          fnPersonnel = "personnel_" ;
   
    getDate(currentDate, 2);
    strcat(fnProjects, currentDate);
    strcat(fnProjects, ".txt");

    strcat(fnTasks, currentDate);
    strcat(fnTasks, ".txt");

    strcat(fnPersonnel, currentDate);
    strcat(fnPersonnel, ".txt");

    exportProjects(projectArray, numProjects, fnProjects);
    exportTasks(taskArray, numTasks, fnTasks);
    exportPersonnel(personnelArray, numPersonnel, fnPersonnel);

    fp = fopen("exportDate.txt", "w");
    fprintf(fp, "%s\n%s\n%s", fnProjects, fnTasks, fnPersonnel);
    fclose(fp);
}
