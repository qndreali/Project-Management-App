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
<img src = "https://github.com/qndreali/Project-Management-System/assets/132218960/ee9d9caf-f45c-49ec-aba3-1f45edd32a56" width = "700">

### Manager Menu
<img src = "https://github.com/qndreali/Project-Management-System/assets/132218960/15e62e2e-e26a-4aaa-8852-3bd194833f57" width = "700">
<img src = "https://github.com/qndreali/Project-Management-System/assets/132218960/21d8d5d9-6c66-4b03-ad44-1bb03417246b" width = "700">



### User Menu
<img src = "https://github.com/qndreali/Project-Management-System/assets/132218960/582cd45c-524e-470c-9abc-4c67f7d095b2" width = "700">
<img src = "https://github.com/qndreali/Project-Management-System/assets/132218960/e6ec38b4-911d-41bd-8be9-48951b962b21" width = "700">
<img src = "https://github.com/qndreali/Project-Management-System/assets/132218960/dba90966-45de-4bf6-a7bb-1a411b5f1207" width = "700">


### Bonus Features
- **Login History**
<img src = "https://github.com/qndreali/Project-Management-System/assets/132218960/2f7dd5a4-d063-4081-b1e0-de8dca7d5087" width = "700">

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
