# CS-300-10456-M01-DSA-Analysis-and-Design-2026-C-1-Jan---Mar-

What was the problem you were solving in the projects for this course?
In these projects I built an advising tool for the ABCU Computer Science department that can load course data from a CSV file, print all CS courses in alphanumeric order, and display the title and prerequisites for a specific course on demand. My portfolio includes the pseudocode and runtime analysis for vector, hash table, and binary search tree designs, as well as a working C++ implementation that uses a map-based structure to store and query courses.

How did you approach the problem? Consider why data structures are important to understand.
I started by defining a clear Course model that captures the course number, title, and a list of prerequisites, then designed pseudocode for how to load this data into different data structures (vector, hash table, and BST) and support the required menu operations. After I had the pseudocode, I analyzed the Big O runtime and memory tradeoffs for each structure, focusing on file loading, searching for a course, and printing the course list in sorted order. This helped me see how the choice of data structure directly affects performance and user experience, especially as the number of courses grows.
​

How did you overcome any roadblocks you encountered while going through the activities or project?
One major roadblock was correctly parsing the input file and handling edge cases like malformed lines and flexible prerequisite formats. I resolved this by incrementally refining my parsing logic (using trimming, tokenization, and validation functions) and adding clear error messages so I could quickly see where the input failed. Another challenge was keeping the menu loop robust against invalid user input; I handled that with input validation and by resetting the input stream when users entered unexpected values.

How has your work on this project expanded your approach to designing software and developing programs?
This project pushed me to separate concerns more deliberately: I now think in terms of distinct phases like loading data, storing it in an appropriate structure, and then building simple interfaces (menus) on top of that core logic. It also reinforced the value of starting with pseudocode and analysis before coding, which made the final C++ implementation much smoother and easier to debug.

How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
I focused on writing small, single-purpose functions such as loadDataStructure, printCourseList, and printCourseInformation, each with clear responsibilities and names. Using a Course struct and a standard container (map<string, Course>) keeps the data model organized and makes it easy to swap in a different backing structure later if needed. Overall, I now pay more attention to input validation, error handling, and code organization so the program can be extended—for example, to support more query types or different data sources—without a major rewrite.

