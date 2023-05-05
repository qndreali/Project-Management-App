/*************************************************************************************************
	This is to certify that this project is our own work, based on our personal efforts in
	studying and applying the concepts learned. We have constructed the functions and their
	respective algorithms and corresponding code by ourselves. The program was run, tested,
	and debugged by our own efforts. We further certify that we have not copied in part or
	whole or otherwise plagiarized the work of other students and/or persons.
					Andrea Li S. Santos, DLSU ID# 12209376
					Ryan Clemence R. Vasquez, DLSU ID# 12288397
*************************************************************************************************/

#include "header.h"  
#include "display.c" 
#include "admin.c"   //  Admin & User Feature
#include "manager.c" //  Manager Feature    
#include "export.c"	 //  Export Features 

/**********************************************************************************
Description: This function displays the three different User Types Menu depending on
			 the logged in user's access level.
	@param personnelArray: An array of structs that stores personnel information.
	@param numPersonnel: The number of current personnels.
	@param projectArray: An array of structs that stores project information.
	@param numProjects: The number of projects.
	@param taskArray: An array of structs that stores task information.
	@param numTasks: The number of tasks.
**********************************************************************************/
void
displayUserTypeMenu(struct personnel personnelArray[],
					int * numPersonnel,
					struct project projectArray[],
					int numProjects,
					struct task taskArray[],
					int numTasks)
{
	int personnelAccess,
		personnelID,
		personnelIndex;
	int exit = 0;

	while (!exit)
	{
		personnelAccess = login(personnelArray, *numPersonnel, &personnelID); 
		personnelIndex = findPersonnel(personnelID, personnelArray, *numPersonnel);
		updateLoginHistory(personnelArray[personnelIndex]);

		switch(personnelAccess)
		{
		case 1:
			exit = adminMenu(personnelArray, numPersonnel, taskArray, numTasks, projectArray, numProjects);
			break;
		case 2:
			exit = managerMenu(projectArray, taskArray, personnelArray, &numProjects, &numTasks, *numPersonnel);
			break;
		case 3:
			exit = userMenu(personnelArray[personnelIndex], taskArray, numTasks, personnelArray, *numPersonnel);
			break;
		}	
	}
}

int
main(){
	
	struct personnel personnelArray[MAX_PERSONNEL];
	struct project projectArray[MAX_PROJECTS];
	struct task taskArray[MAX_TASKS];
    int numPersonnel = 0;
	int numProjects = 0;
	int numTasks = 0;
	int exportExists; 
	
	str24 fnProjects, fnTasks, fnPersonnel; // stored should be the respective file names of each latest export file
	exportExists = getLatestExport(fnProjects, fnTasks, fnPersonnel);

	loadFile(personnelArray, &numPersonnel, "preloaded.txt");	// import said files & initialize to their respective struct array
	if (exportExists) {
		loadProjectRecord(projectArray, &numProjects, fnProjects);
		loadTaskRecord(taskArray, &numTasks, fnTasks);
	}
	
	displayUserTypeMenu(personnelArray, &numPersonnel, projectArray, numProjects, taskArray, numTasks);
	exportData(projectArray, taskArray, personnelArray, numProjects, numTasks, numPersonnel);
	
	return 0;
}
