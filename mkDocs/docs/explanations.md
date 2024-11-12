# LampATTiny Explanations

Explanation is a discursive treatment of a subject, that permits reflection. Explanation is understanding-oriented.

## Electric project

source of current for all project part is 21700 cell this size is popular and has a relatively big capacity (compared to 18650 cells). For simplcity we use only one cell. Using more of them get more capacity but creates some problems:

- when connect in series:  
more complicated BMS and charger, higher voltage is not a problem, beacuse we regulate voltage later
- when connect in paralell:  
big carefull must be used to ensure balance cell before connection, best will be to spot weld cells with this same actual voltage

Cell is powered by TP4056 module. It check discharge current (up to 3A), and discharge voltage (above 2,5), so it doubles BMS, but for security BMS shall be used (now is not). 
When charging current is limited to 1A, and voltage is 4,2V
Some sources give information about problem with charge and discharge at the same time - Cell is not cut off in this situation and its cycles are used. Additionaly current limitation might not work and discharge limit (3A) might be used for charge cell. For this reason there is a plan to replace this module.

