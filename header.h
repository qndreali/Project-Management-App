#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#define MAX_PROJECTS 50
#define MAX_TASKS 100
#define MAX_PERSONNEL 100

/**********************************************************************************
Description: typedef declarations for string with the size of 12, 40 and 100 that 
             considers the buffer overflow null terminator '\0' character.
**********************************************************************************/
typedef char str12[13];
typedef char str24[25];
typedef char str40[41];
typedef char str100[101];

/**********************************************************************************
Description: struct declaration for necessary records.
**********************************************************************************/
struct project{
    int projectID; 
    str40 name; 
    int status;
    float completion;
    str100 description; 
    int assignID; 
};

struct task{
    int taskID;
    str40 name;
    int sequence;
    str100 description;
    int projectID;
    str12 startdate;
    str12 enddate;
    float totalDuration;
    int status;
    int assignID;
};

struct personnel{
    int personnelID;
    str40 username;
    str40 password;
    int active;
    int access;
};

/**********************************************************************************
Description: A function that clears the terminal for a more readable user interface.
             It uses flush(stdin) to clear input buffer.
             It also uses getchar() to get user input as a prompt to system("cls").
**********************************************************************************/
void clearScreen(){
	printf("\nPress Enter to continue.\n");
    fflush(stdin);
	getchar();
	system("cls");
}

/**********************************************************************************
Description: This function takes in a string input, including those with spaces. 
    It will accept the string input until it scans a newline character or when the
    length of the string exceeds the allowed length
    @param string - destination string where the input will be stored
    @param length - allowed length of string
**********************************************************************************/
void scanfLine(char string[], 
               int length)
{
	char ch; 
	int  i = 0;
	
	fflush(stdin);
	do 
	{
		scanf("%c", &ch);
		if (ch != '\n')
		{
				string[i] = ch;
				i++;
				string[i] ='\0';
		}
	} while (i < length && ch != '\n');
}

/**********************************************************************************
Description: Similar to scanfLine, this function accepts string inputs directly 
    from a file.
    @param fp - file pointer to the input stream of the file
    @param string - destination string where the input will be stored
    @param length - allowed length of string
**********************************************************************************/
void 
fscanfLine(FILE *fp, 
		   char string[], 
		   int length)
{
	char ch;
	int  i = 0, 
		 check;
	do 
	{
		check = fscanf(fp, "%c", &ch);
		if (check == 1 && ch != '\n')
		{
				string[i] = ch;
				i++;
				string[i] = '\0';
		}
  	} while (i < length - 1 && ch != '\n' &&  check != EOF);
}


/**********************************************************************************
Description: Function Prototype for the three menu types
**********************************************************************************/
void
displayUserTypeMenu(struct personnel personnelArray[],
					int * numPersonnel,
					struct project projectArray[],
					int numProjects,
					struct task taskArray[],
					int numTasks);


/********************************************************************/
                    // helper funcs
void changePW(str40 password);

int findPersonnel(int key, 
                  struct personnel personnelArray[], 
                  int numPersonnel);

int 
checkProjectName(struct project projectArray[], 
		               int numProjects, 
		               str40 projectName);

int 
findProject(int key, 
            struct project projectArray[], 
            int numProjects);


/**********************************************************************************
                                  ADMIN FEATURE
**********************************************************************************/
                        
void 
loadFile(struct personnel personnelArray[], 
         int *numPersonnel, 
         str24 fileName);
int 
checkPersonnelUsername(struct personnel personnelArray[], 
		               int numPersonnel, 
		               char *username);
int 
login(struct personnel personnelArray[], 
      int numPersonnel, int *personnelID);

int 
randomPersonnelID(struct personnel personnelArray[], 
		          int numPersonnel);
        
void 
addUser(struct personnel personnelArray[], 
	    int *numPersonnel);

void 
updateUser(struct personnel personnelArray[], 
	       int numPersonnel);

void 
deleteUser(struct personnel personnelArray[], 
	       int *numPersonnel,
	       struct task taskArray[], 
	       int  numTasks,
	       struct project projectArray[],
	       int numProjects);

void 
archiveUser(struct personnel personnelArray[], 
	        int numPersonnel);

void
assignProject(struct project projectArray[], 
           int numProjects, 
           struct personnel personnelArray[],
           int numPersonnel);

int
adminMenu(struct personnel personnelArray[], 
	      int *numPersonnel,
	  	  struct task taskArray[],
	  	  int numTasks,
	  	  struct project projectArray[],
	  	  int numProjects);

/**********************************************************************************
 *                              MANAGER FUNCTIONS                                *    
**********************************************************************************/
void loadProjectRecord(struct project projectArray[], 
                  int * numProjects,
                  char* fileName);

void loadTaskRecord(struct task taskArray[],
               int * numTasks,
               char* fileName);

int generateProjID(struct project projectArray[], 
               int numProjects);

int findPersonnel(int key, 
                  struct personnel personnelArray[], 
                  int numPersonnel);

int checkProjectName(struct project projectArray[], 
		               int numProjects, 
		               str40 projectName);

void addProject(struct project projectArray[],
           int *numProjects, 
           struct personnel personnelArray[], 
           int numPersonnel);

int countProjectTasks(struct task taskArray[], 
                  int numTasks, 
                  int projectID);

int generateTaskID(struct task taskArray[], 
               int numTasks,
               int projectID);

void adjustTasksSequence(struct task taskArray[], 
                    int numTasks, 
                    int projectID,
                    int taskID, 
                    int newSequence, int oldSequence);

int checkTaskName(struct task taskArray[], 
              int numTasks, 
              str40 taskName,
              int projectID,
              struct project projectArray[],
              int numProjects);

int findProject(int key, 
            struct project projectArray[], 
            int numProjects);

void inputDates(struct task *task);

float computeDuration(struct task task);

void addTask(struct task taskArray[], int *numTasks, struct project projectArray[],
        int numProjects, struct personnel personnelArray[], int numPersonnel);

int findTask(int key, struct task taskArray[], int numTasks);

void displayTask(struct task taskArray);

void updateTask(struct task taskArray[],  int numTasks, struct project projectArray[], 
                int numProjects, struct personnel personnelArray[],int numPersonnel);

void activePersonnel(struct personnel personnelArray[],
                int numPersonnel);

void assignTask(struct task taskArray[], 
           int numTasks, 
           struct personnel personnelArray[],
           int numPersonnel);

int hasMatchingProjectID(struct project projectArray[], int numProjects,  int targetProjectID, 
                                                        struct task taskArray[], int numTasks);

void displayTaskInProject(struct task taskArray[], int numTasks, int targetProjectID, 
                          struct project projectArray[], int numProjects);

void showProjectDetails(struct project projectArray[], int numProjects, 
                                 struct task taskArray[], int numTasks);

void delayedTasks(struct task taskArray[], int numTasks);

float computeCompletion(struct task taskArray[], int numTasks, int projectID);

void projectCompletion(struct project projectArray[], int numProjects, 
                        struct task taskArray[], int numTasks);

int managerMenu(struct project projectArray[], struct task taskArray[], struct personnel personnelArray[],
                                                       int *numProjects, int *numTasks, int numPersonnel);

/**********************************************************************************
 *                              USER FUNCTIONS                                    *    
**********************************************************************************/

void changePW(str40 password);

void showCurrentTasks(struct task taskArray[], int numTasks, int personnelID);

void showAllTasks(struct task taskArray[], int numTasks, int personnelID);

void updateTaskStatus(struct task taskArray[], int numTasks, int personnelID);

int userMenu(struct personnel user, struct task taskArray[], int numTasks, 
                    struct personnel personnelArray[], int numPersonnel);

/**********************************************************************************
 *                              EXPORT FUNCTIONS                                  *    
**********************************************************************************/

int getLatestExport(str24 fnProjects, str24 fnTasks, str24 fnPersonnel);

void exportProjects(struct project projectArray[], int numProjects, str24 fileName);

void exportTasks(struct task taskArray[], int numTasks,str24 fileName);

void exportPersonnel(struct personnel personnelArray[], int numPersonnel, str24 fileName);

void exportData(struct project projectArray[], struct task taskArray[], 
                struct personnel personnelArray[],int numProjects, int numTasks, int numPersonnel);

/**********************************************************************************
 *                          OTHER IMPORTANT HELPER FUNCS                          *    
**********************************************************************************/

void reverseDate(str12 date, str12 reversedDate);

void getDate(str12 date, int format);

void getTime(str12 currentTime);

int isFormatted(str12 date);

/**********************************************************************************
 *                          BONUS FEATURES                                        *    
**********************************************************************************/

void updateProject(struct project projectArray[],int numProjects,
                    struct personnel personnelArray[], int numPersonnel);

void updateLoginHistory(struct personnel user);

void displayLoginHistory(int access);
