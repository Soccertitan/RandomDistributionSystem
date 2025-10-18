# RandomDistributionSystem

This project is inspired by article written by Mike: https://www.codeproject.com/Articles/420046/Loot-Tables-Random-Maps-and-Monsters-Part-I
A lot of the design choices that were made stem from reading his article and I suggest giving it a read yourself if you want to learn more about Random Distribution Tables.

## Getting Started
1. Create a Data Table of type RandomDistributionRow. Then populate the rows as you like. You can hover over the different properties for a description of what each one means.
<p><img width="1039" height="632" alt="image" src="https://github.com/user-attachments/assets/56f41032-65d4-4bc2-bad0-e6c2a48967f4" /></p>
2. In a blueprint add a variable of type RandomDistributionExectution. From the drop down select the only option. This object is instanced editable.
<p><img width="533" height="518" alt="image" src="https://github.com/user-attachments/assets/f46bc742-62d3-48ea-9048-9d146f84e116" /></p>
3. Then create another variable of type RandomDistributionExecutionParams. For the Data Table, select the one you created earlier. And set a count to greater than or equal to 1.
<p><img width="534" height="523" alt="image" src="https://github.com/user-attachments/assets/d4b3eb83-89e9-41c0-802b-5c97fe67bfb0" /></p>
4. Then call GenerateResults from the new object.
<p><img width="501" height="209" alt="image" src="https://github.com/user-attachments/assets/c93f354d-d0aa-4f1c-9fe2-f229466eefbd" /></p>

That's it to all you need to start generating random results from a DataTable. Read the source code for more information. As I have time, I will update this Readme with more details.
