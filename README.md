<a name="readme-top"></a>
<h1 align="center">Project Management System</h3>
<h4 align="center"> [CCPROG2] Programming with Structured Data Types — Machine Project</h4>
<div align="center"> <img src = "https://github.com/qndreali/Project-Management-System/assets/132218960/de71b3aa-3d32-48db-8737-0c63ae7e3ce0"  width = "1000"></div>

## About The Project

A Simple C Project Management Program designed to efficiently manage project resources, including Projects, Tasks, and Personnels. Within this system are three distinct personnel types — Admins, Managers, and Users. Each type playing distinct roles within the project management application. 

A **Personnel** profile is composed of five attributes, including a unique personnel ID, name, password, active status, and access level. Its respective menus are defined by their access level. *Admins* wield administrative privileges, being able to modify personnel data and project assignments. While *Managers* oversee project creation and progression and *Users* execute tasks allocated to them within projects.

A **Project** contains details that encompasses essential information such as its project ID, name, current status, completion status, description, and the personnel assigned to oversee its execution. Do note that only managers have the capability to create projects, and projects are exclusively assigned to Managers. 

A **Task** carries a range of attributes, including a task ID, name, sequence, comprehensive description, start and end dates, duration, current status, assigned personnel, and a link to the project under which it falls. Managers possess the authority to create tasks, which are then assigned to Users for execution.

</div>

## Features
- **Admin Menu** 
	- Add User
	- Update User
	- Delete User
	- Archive User
	- Assign Project
- **Manager Menu** 
	- Add Project
	- Show Project Details
	- Add Task
	- Update Task
	- Show Delayed Tasks
	- Run Project Completion
	- Show Personnel List
	
- **User Menu** 
	- Show Today's Task
	- Show All Assigned Task
	- Update Task Status
	
- **Export**
    - saves all Personnel, Project and Task information into specific text files upon termination of the program.

## Screenshots
### Admin Menu
<img src = "https://github.com/qndreali/Project-Management-System/assets/132218960/2267b7e1-37d4-4ed9-bc2d-5c9d1e8c6a4f" width = "700">
<img src = "https://github.com/qndreali/Project-Management-System/assets/132218960/e785426c-add2-4a4f-ba8f-b06da8d22f95" width = "700">

### Manager Menu
<img src = "https://github.com/qndreali/Project-Management-System/assets/132218960/1f2ccca6-7e7c-4036-9bc1-7594a9c0f3f5" width = "700">
<img src = "https://github.com/qndreali/Project-Management-System/assets/132218960/ee23ee11-d72c-4ffc-89d0-baa4946932c4" width = "700">



### User Menu
<img src = "https://github.com/qndreali/Project-Management-System/assets/132218960/bcbd0ae4-b8bd-4d4f-9434-a71aaddb1f30" width = "700">
<img src = "https://github.com/qndreali/Project-Management-System/assets/132218960/83e10a00-eee9-47ad-b616-2a73b1d431d8" width = "700">
<img src = "https://github.com/qndreali/Project-Management-System/assets/132218960/9fc96766-6442-4240-9df3-b6396ce10965" width = "700">


### Bonus Features
- **Login History**
<img src = "https://github.com/qndreali/Project-Management-System/assets/132218960/5ad47074-f92e-4d39-ab3d-54ee0c09e3e1" width = "700">

- **Admin Menu** 
	- View all users

- **Manager Menu** 
	- Update Project

## Issues
- [ ] Extended ASCII GUI is not compatible with all systems and terminal emulators.
- [ ] No error handling for Floating-point Inputs. 
- [ ] Function used for clearing screen is not compatible with all operating systems.

## Authors
[@qndreali](https://github.com/qndreali)

[@ryaexn](https://github.com/ryaexn)
 
<p align="right">(<a href="#readme-top">back to top</a>)</p>
