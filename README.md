This program is used to create shift lists for work
The requirements are that the workplace must only have 1 shift per day (example 9:00 to 17:00) and that there are a fixed number of employees working Monday,Tuesday,Wednesday,etc

The program uses a custom algorithm to calculate which employees should work on a specific day of the shift list, it is roughly implemented as follows:
  - Create a list of all employees
  - Get the current day you are calculating for the shift list (Monday,Tuesday,Wednesday,etc)
  - Remove employees from the list of all employees if they cannot work on the current day
  - Further refine the list giving preference to employees that have the smallest number of days that they can work on (for example Employee x can work 3 days a week and Employee y can work 5 days a week, preference for the shift will be given to employee x)
  - Further refine the list giving preference to employees with the smallest number of total shifts (for example Employee x has a total of 5 shifts and Employee z has a total of 3 shifts, preference for the shift will be given to employee z)
  - Finally add this employee who is "the most deserving of the shift" to the shift list for the day
  - Remove that employee, who was added to the shift list, from the list of possible candidates (to avoid duplicates)
  - continue loop until the shift list is full for the day

There are improvements that can be done to the program such as adding a button to print out the shift list to a PDF document which can then be physically printed or sent to employees via social media
Another improvement would be to integrate a database system so that the user does not need to repeatedly add employees to the employee list each time the program is run

Below is an example of the program running:



This is the main UI screen

![pics1](https://github.com/HannesW101/Work_Schedule_creator/assets/86373722/fedf357a-978f-4d62-9c14-3ad0e44c319f)

Top left is a button to add an employee to the employee list

![pics2](https://github.com/HannesW101/Work_Schedule_creator/assets/86373722/30807c65-db30-47dc-ab8c-ec47802e4065)

When this button is clicked a custom dialogbox shows up where you can input the employees name as well as check the boxes which represent which days an employee is able to work

![pics8](https://github.com/HannesW101/Work_Schedule_creator/assets/86373722/0692627d-c0c9-4446-af59-2a71e7b75104)

As employees are added they appear in the employee list on the right hand side with a counter of the total employees top right, note the max number of employees is 100

![pics6](https://github.com/HannesW101/Work_Schedule_creator/assets/86373722/4d8a4547-d365-4106-8ace-463fd7a8b510)

There is a spin box which correlates to the number of days for which you would like to calculate the shift list for (7 is for 1 week, 14 is for 2 weeks...the max value which is 365 = 1 year)

![pics3](https://github.com/HannesW101/Work_Schedule_creator/assets/86373722/9f3fb3fb-d389-41f9-aa59-0dec2c4c8c83)

Above the table widget there are labels indicating the various days of the week, the spinboxes placed on the days indicate the number of employees that should work on a specific day

![pics5](https://github.com/HannesW101/Work_Schedule_creator/assets/86373722/82f5bd78-70e0-4f34-82aa-e53e99808437)

Lastly there is button which calculates the shift list taking into account the parameters the user has specified, it then outputs this shift list into the table widget

![pics4](https://github.com/HannesW101/Work_Schedule_creator/assets/86373722/2a58fd12-d2d3-4095-aeb7-952fd9789c47)

The output is in this table widget where the headers are the dates indicating the shiftlist for that date below in a column form where the employees names appear. Note that the last column of the table widget will give a list of all employees and in parenthesis indicate the total number of shifts that employee has accumulated in this specific shift list period

![pics7](https://github.com/HannesW101/Work_Schedule_creator/assets/86373722/f2de61bd-83d8-4c71-8947-35aabd931910)
